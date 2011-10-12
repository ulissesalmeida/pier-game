/*NGL v1.0 - Game Development Library 
Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

O uso desta biblioteca de software em forma de código fonte ou arquivo binário, 
com ou sem modificações, é permitido contanto que sejam atendidas as seguintes condições:

1. A redistribuição deste software em qualquer forma, seu uso comercial 
e em treinamentos de qualquer natureza estão sujeitos a aprovação 
prévia por escrito da Nology Softwares, estando estas ações 
proibidas em quaisquer outras condições.

2. A alteração do conteúdo deste software está autorizada contanto que 
sejam mantidas as informações de copyright dos arquivos originais.

3. O uso deste software é permitido para uso educacional livre 
de quaisquer obrigações desde que seja atendida a condição número 1.

4. A Nology Softwares, detentora dos direitos autorais sobre este software, 
não oferece nenhuma garantia de funcionamento e não pode ser responsabilizada 
por quaisquer danos diretos, indiretos, acidentais, especiais ou 
específicos causados pelo uso deste software. 
*/

#include "NGLMain.h"
#include "Player.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"

#define BLINK_TIME 3000

//---------------------------------------------------------------------------- 
// Nome: CPlayer(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CPlayer::CPlayer(void)
{
	uiPoints				= 0;
	uiLives					= NUM_LIVES;
	bInvincible			= false;
	bImmune				= false;
	DefaultSpeed.fx	= 300.0f;
	DefaultSpeed.fy	= 470.0f;
	p_SndShot				= NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CPlayer(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CPlayer::~CPlayer(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza o inimigo, desalocando recursos (sprite e som de tiro).
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CPlayer::Release(void)
{
	CCharacter::Release();
	pr_Level->pr_Main->SoundManager.DeleteSound(&p_SndShot);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(CNGLVector InitPos)
// Desc: Inicializa o jogador, com as devidas animações, posição, vidas, etc.
// Pams: posição inicial
//---------------------------------------------------------------------------- 
bool CPlayer::Initialize(CNGLVector InitPos)
{
	//15.3.3
	//cria sprite do jogador
	p_Sprite	= pr_Level->p_LayLevel->CreateSprite("Surfaces/spr_Kangoo.bmp",CNGLVector(75,90));
	//configura as animações para o sprite
	//animação de corrida (movimentação)
	p_Sprite->AddAnimation(12,true,8,0,1,2,3,4,5,6,7);
	//animação de pulo
	p_Sprite->AddAnimation(10,false,4,8,9,10,11);
	//animação parado
	p_Sprite->AddAnimation(7,true,4,13,14,15,16);
	//animação de morte
	p_Sprite->AddAnimation(12,false,6,18,19,20,21,22,23);
	//ajusta animação 0 como corrente
	p_Sprite->SetCurrentAnimation(0);
	//ajusta posição inicial
	p_Sprite->Position = InitPos;

	//som de tiro do jogador
	p_SndShot	= pr_Level->pr_Main->SoundManager.LoadSound("Sounds/sfx_Shot.wav",true);

	//inicializa os vidas e os pontos
	uiLives = NUM_LIVES;
	uiPoints = 0;

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Trata a entrada de dados do teclado para movimentar jogador, pular e piscar.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPlayer::Execute(void)
{
	//21.2.3
	//1. Tratamento do renascimento do jogador


	//atualiza movimentação e física do personagem
	CCharacter::Execute();

	//21.2.3
	//Tratamento do imunidade do jogador
	if(bImmune)
	{
		//2. atualizando tempo de imunidade (tempo que pisca)

		//3. troca visibilidade de verdadeiro pra falso e vice-versa

		//4. se terminou tempo de piscagem...
		if(AccumImmunity.Ended())
		{
			bImmune = false;
			p_Sprite->bVisible = true;
		}
	}

	// se o jogador apertou a tecla A e o personagem não estiver pulando, então pula.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_A) && !bJump)
	{
		bJump			= true;
		CurrentSpeed.fy = (CurrentSpeed.fy == 0.0f)? -DefaultSpeed.fy : CurrentSpeed.fy;
		p_Sprite->ResetAnimation();
	}
	// se o jogador apertou a tecla esquerda, move o personagem para a esquerda.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_LEFT))
	{
		p_Sprite->byMirror = NGLMIRROR_LEFTRIGHT;
		CurrentSpeed.fx = -DefaultSpeed.fx;
	}
	// se o jogador apertou a tecla para a direita, move o personagem para a direita.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_RIGHT))
	{
		p_Sprite->byMirror = NGLMIRROR_NONE;
		CurrentSpeed.fx = DefaultSpeed.fx;
	}
	// se o jogador apertou a tecla S então atira.
	if(pr_Level->pr_Main->InputManager.KeyPressed(DIK_S))
	{
    Shot();
	}

}

//---------------------------------------------------------------------------- 
// Nome: Shot(void)
// Desc: Faz o jogador atirar para todas as direções.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPlayer::Shot(void)
{
	//pega o centro do personagem
	CNGLVector Pos = p_Sprite->Position;
	Pos += p_Sprite->pr_Image->FrameSize*0.5f;
	CNGLVector vShot;
	
	//direciona o tiro conforme a tecla que o jogador esta pressionando
	//no momento e atribui a velocidade padrão do tiro (600). O jogador está
	//com a seta para cima pressionada, então tiro em y é negativo (para cima)
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_UP))
	{
		vShot.fy += -600.0f;
	}
	// jogador esta com a tecla baixo pressionada, então
	// tiro em y é positivo (para baixo)
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_DOWN))
	{
		vShot.fy += 600.0f;
	}
	// jogador esta com a tecla esquerda pressionada, então
	// tiro em x é negativo.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_LEFT))
	{
		vShot.fx += -600.0f;
	}
	// jogador esta com a tecla esquerda pressionada, então
	// tiro em x é positivo.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_RIGHT))
	{
		vShot.fx += 600.0f;
	}
	// se o jogador estiver parado. a velocidade do tiro não foi configurada.
	if(vShot.fx == 0.0f && vShot.fy == 0.0f)
	{
		// se o jogador esta parado sem espelhamento, atira para a direita
		if(p_Sprite->byMirror == NGLMIRROR_NONE)
		{
			vShot.fx = 600.0f;
		}
		else // senão atira para a esquerda.
		{
			vShot.fx = -600.0f;
		}
	}
	// adiciona a velocidade em x do personagem à velocidade em x do tiro
	vShot.fx += CurrentSpeed.fx;
	// Normaliza o vetor para saber a direção do tiro.
	vShot.Normalize();
	// Múltiplica os componentes do vetor pela velocidade do tiro.
	vShot *= 600.0f;
	pr_Level->CreatePlayerShot(Pos,vShot);

	// reproduz o som do tiro
	if(p_SndShot)
	{
		p_SndShot->Play();
	}
}

//---------------------------------------------------------------------------- 
// Nome: IsPlayer(void)
// Desc: Retorna verdadeiro, pois este é um jogador.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CPlayer::IsPlayer(void)
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Die(void)
// Desc: Faz as tratativas para a morte do jogador.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPlayer::Die(void)
{
	// se estiver invencivel ou transparente, não morre
	if(bInvincible || bImmune)
	{
		bIsDieing = false;
	}
	else
	{
		//21.2.1. 
		//jogador não está invencível e nem piscando
		//coloca animação de morte do jogador

	}
}

//---------------------------------------------------------------------------- 
// Nome: Reborn(void)
// Desc: Faz o jogador renascer (após sua morte) e deixa-o piscando por alguns segundos.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPlayer::Reborn(void)
{
	//21.2.2.
	if(uiLives == 0)
	{
		//1. muda para para o estado GS_GAMEOVER

	}
	else
	{
		//2. informar que o jogador não está mais morrendo

		//3. ajusta a animação corrente para a zero

		//4. diminuir o número de vidas em uma unidade, pois o jogador acabou de morrer

		//5. ajusta o atributo bImmune para verdadeiro, indicando que ele vai piscar

		//6. Iniciar o acumulador de tempo que o jogador deve piscar

	}
}
