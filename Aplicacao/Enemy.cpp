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
#include "Enemy.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"
#include <time.h>

//---------------------------------------------------------------------------- 
// Nome: CEnemy(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CEnemy::CEnemy(void)
{
	//incializa atributos do agente
	State						= ES_PATROLING;
	Direction				= ED_NONE;
	fXPatrolRange		= 600.0f;
	fVisionRay			= 200.0f;
	p_SprPain				= NULL;
	DefaultSpeed.fx = 100.0f;
	DefaultSpeed.fy = 400.0f;
	//inicializa randomizador
	srand((unsigned int)time(NULL));
}

//---------------------------------------------------------------------------- 
// Nome: ~CEnemy(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CEnemy::~CEnemy(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o inimigo, desalocando recursos (sprite).
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::Release(void)
{
	CCharacter::Release();
	pr_Level->p_LayLevel->DeleteSprite(&p_SprPain);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Atualiza o inimgo de acordo com o seu estado.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Execute(void)
{
	//atualizando física do inimigo
	CCharacter::Execute();
	
	if(State == ES_DIEING)
	{
		//21.1.2. 
		//se o inimigo estiver morrendo e acabou a animação de estouro
		//deve-se mudar o estado para ES_END

	}
	else
	{
		//acumulando tempo desde o último tiro
		AccumShot.Update();
	}
}

//---------------------------------------------------------------------------- 
// Nome: IsPlayer(void)
// Desc: Retorna falso pois este não é um objeto de CPlayer.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::IsPlayer(void)
{
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: MoveTo(CNGLVector Dest)
// Desc: Move o inimigo para um determinado ponto.
// Pams: posição destino
//---------------------------------------------------------------------------- 
void CEnemy::MoveTo(CNGLVector Dest)
{
	//20.2.1. 
	
}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(CEnemy::EnemyState NewState)
// Desc: Muda o estado do inimigo
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CEnemy::ChangeState(CEnemy::EnemyState NewState)
{
	switch(NewState)
	{
		case ES_DIEING:
		{
			State = ES_DIEING;
			break;
		}
		case ES_END:
		{
			if(State == ES_DIEING)
			{
				State = ES_END;
				break;
			}
			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetState(void)
// Desc: Retorna o estado corrente do inimigo
// Pams: nenhum
//---------------------------------------------------------------------------- 
CEnemy::EnemyState CEnemy::GetState(void)
{
	return State;
}

//---------------------------------------------------------------------------- 
// Nome: SeePlayer(void)
// Desc: Retorna verdadeiro se este inimigo está vendo o jogador. Se o inimigo está de costas para o jogador, ou a distância
//       entre o jogador e o inimigo é maior que o raio de visão do inimigo, então retorna verdadeiro.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::SeePlayer(void)
{
	//20.2.5. 
	// se o inimigo está de costas para o jogador então retorna falso (não está vendo)

	// se a distância entre o jogador e o inimigo for maior que
	// o raio de visão, então retorna falso.


	return false;
}

//---------------------------------------------------------------------------- 
// Nome: Die(void)
// Desc: Faz o inimigo morrer
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Die(void)
{
	//21.1.1.
	//1. criar o sprite de estouro

	//2. criar a animação do estouro no sprite p_SprPain

	//3. ajustar como animação corrente a 0

	//4. esconder com o inimigo

	//5. sprite do estouro deve receber a posição do inimigo

	//6. adiciona pontos ao jogador

	//7. mudar estado do inimigo para ES_DIEING

}

//---------------------------------------------------------------------------- 
// Nome: Jump(void)
// Desc: Faz o inimigo pular.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Jump(void)
{
	// ve se já não está pulando
	if(!bJump)
	{
		bJump			= true;
		CurrentSpeed.fy = -450.0f;
	}
}

//---------------------------------------------------------------------------- 
// Nome: Move(void)
// Desc: Faz o inimigo se movimentar de acordo com a direção, velocidade e alcance de patrulha
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Move(void)
{
	//20.2.4. 
	//verificar qual direção o inimigo está se movimentando
	switch(Direction)
	{
		//1. agente indo para direita (ponto B)
		case CEnemy::ED_RIGHT:
		{
			//ajusta velocidade corrente do inimigo

			
			// se em x chegou ao destino (ponto B), manda se movimentar para o ponto A


			break;
		}
		//2. agente indo para esquerda (ponto A)
		case CEnemy::ED_LEFT:
		{
			//ajusta velocidade corrente do inimigo (inverso para ir para ponto A)


			// se em x chegou ao destino (ponto A), manda se movimentar para o ponto B


			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Shot(void)
// Desc: Faz o inimigo atirar.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Shot(void)
{
	//22.1.1. 
	//1. Criar um vetor que representa o centro do inimigo (ponto de origem do tiro)

	//2. criar vetor de velocidade e direção que representa a distância entre
	//o centro do inimigo e o centro do jogador


	//3. Normaliza o vetor para pegar seu valor unitário.

	//4. velocidade do tiro do inimigo

	//5. cria o tiro do inimigo

	//6. inicializa acumulador de tiro

}

//---------------------------------------------------------------------------- 
// Nome: CanShot(void)
// Desc: Retorna verdadeiro caso o inimigo possa atirar
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::CanShot(void)
{
	//22.1.3. retornar se o acumulador de tempo de tiros terminou ou não!
	//(substitua a linha abaixo)
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: AddPointsToPlayer(void)
// Desc: Adiciona pontos ao jogador de acordo com o tipo de inimigo morto
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::AddPointsToPlayer(void)
{
	if(Type == CEnemy::ET_DUMMY)
	{
		pr_Level->GetPlayer()->uiPoints += 10;
		return;
	}
	if(Type == CEnemy::ET_DUMMY_KILLER)
	{
		pr_Level->GetPlayer()->uiPoints += 15;
		return;
	}
	if(Type == CEnemy::ET_FLYER_BOMBER)
	{
		pr_Level->GetPlayer()->uiPoints += 25;
		return;
	}
}