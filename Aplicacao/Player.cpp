/*NGL v1.0 - Game Development Library 
Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

O uso desta biblioteca de software em forma de c�digo fonte ou arquivo bin�rio, 
com ou sem modifica��es, � permitido contanto que sejam atendidas as seguintes condi��es:

1. A redistribui��o deste software em qualquer forma, seu uso comercial 
e em treinamentos de qualquer natureza est�o sujeitos a aprova��o 
pr�via por escrito da Nology Softwares, estando estas a��es 
proibidas em quaisquer outras condi��es.

2. A altera��o do conte�do deste software est� autorizada contanto que 
sejam mantidas as informa��es de copyright dos arquivos originais.

3. O uso deste software � permitido para uso educacional livre 
de quaisquer obriga��es desde que seja atendida a condi��o n�mero 1.

4. A Nology Softwares, detentora dos direitos autorais sobre este software, 
n�o oferece nenhuma garantia de funcionamento e n�o pode ser responsabilizada 
por quaisquer danos diretos, indiretos, acidentais, especiais ou 
espec�ficos causados pelo uso deste software. 
*/

#include "NGLMain.h"
#include "Player.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"

#define BLINK_TIME 3000

//---------------------------------------------------------------------------- 
// Nome: CPlayer(void)
// Desc: construtor padr�o
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
// Desc: destrutor padr�o
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
// Desc: Inicializa o jogador, com as devidas anima��es, posi��o, vidas, etc.
// Pams: posi��o inicial
//---------------------------------------------------------------------------- 
bool CPlayer::Initialize(CNGLVector InitPos)
{
	//15.3.3
	//cria sprite do jogador
	p_Sprite	= pr_Level->p_LayLevel->CreateSprite("Surfaces/spr_Kangoo.bmp",CNGLVector(75,90));
	//configura as anima��es para o sprite
	//anima��o de corrida (movimenta��o)
	p_Sprite->AddAnimation(12,true,8,0,1,2,3,4,5,6,7);
	//anima��o de pulo
	p_Sprite->AddAnimation(10,false,4,8,9,10,11);
	//anima��o parado
	p_Sprite->AddAnimation(7,true,4,13,14,15,16);
	//anima��o de morte
	p_Sprite->AddAnimation(12,false,6,18,19,20,21,22,23);
	//ajusta anima��o 0 como corrente
	p_Sprite->SetCurrentAnimation(0);
	//ajusta posi��o inicial
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


	//atualiza movimenta��o e f�sica do personagem
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

	// se o jogador apertou a tecla A e o personagem n�o estiver pulando, ent�o pula.
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
	// se o jogador apertou a tecla S ent�o atira.
	if(pr_Level->pr_Main->InputManager.KeyPressed(DIK_S))
	{
    Shot();
	}

}

//---------------------------------------------------------------------------- 
// Nome: Shot(void)
// Desc: Faz o jogador atirar para todas as dire��es.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPlayer::Shot(void)
{
	//pega o centro do personagem
	CNGLVector Pos = p_Sprite->Position;
	Pos += p_Sprite->pr_Image->FrameSize*0.5f;
	CNGLVector vShot;
	
	//direciona o tiro conforme a tecla que o jogador esta pressionando
	//no momento e atribui a velocidade padr�o do tiro (600). O jogador est�
	//com a seta para cima pressionada, ent�o tiro em y � negativo (para cima)
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_UP))
	{
		vShot.fy += -600.0f;
	}
	// jogador esta com a tecla baixo pressionada, ent�o
	// tiro em y � positivo (para baixo)
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_DOWN))
	{
		vShot.fy += 600.0f;
	}
	// jogador esta com a tecla esquerda pressionada, ent�o
	// tiro em x � negativo.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_LEFT))
	{
		vShot.fx += -600.0f;
	}
	// jogador esta com a tecla esquerda pressionada, ent�o
	// tiro em x � positivo.
	if(pr_Level->pr_Main->InputManager.KeyDown(DIK_RIGHT))
	{
		vShot.fx += 600.0f;
	}
	// se o jogador estiver parado. a velocidade do tiro n�o foi configurada.
	if(vShot.fx == 0.0f && vShot.fy == 0.0f)
	{
		// se o jogador esta parado sem espelhamento, atira para a direita
		if(p_Sprite->byMirror == NGLMIRROR_NONE)
		{
			vShot.fx = 600.0f;
		}
		else // sen�o atira para a esquerda.
		{
			vShot.fx = -600.0f;
		}
	}
	// adiciona a velocidade em x do personagem � velocidade em x do tiro
	vShot.fx += CurrentSpeed.fx;
	// Normaliza o vetor para saber a dire��o do tiro.
	vShot.Normalize();
	// M�ltiplica os componentes do vetor pela velocidade do tiro.
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
// Desc: Retorna verdadeiro, pois este � um jogador.
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
	// se estiver invencivel ou transparente, n�o morre
	if(bInvincible || bImmune)
	{
		bIsDieing = false;
	}
	else
	{
		//21.2.1. 
		//jogador n�o est� invenc�vel e nem piscando
		//coloca anima��o de morte do jogador

	}
}

//---------------------------------------------------------------------------- 
// Nome: Reborn(void)
// Desc: Faz o jogador renascer (ap�s sua morte) e deixa-o piscando por alguns segundos.
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
		//2. informar que o jogador n�o est� mais morrendo

		//3. ajusta a anima��o corrente para a zero

		//4. diminuir o n�mero de vidas em uma unidade, pois o jogador acabou de morrer

		//5. ajusta o atributo bImmune para verdadeiro, indicando que ele vai piscar

		//6. Iniciar o acumulador de tempo que o jogador deve piscar

	}
}
