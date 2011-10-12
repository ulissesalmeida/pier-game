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
#include "Enemy.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"
#include <time.h>

//---------------------------------------------------------------------------- 
// Nome: CEnemy(void)
// Desc: construtor padr�o
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
// Desc: destrutor padr�o
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
	//atualizando f�sica do inimigo
	CCharacter::Execute();
	
	if(State == ES_DIEING)
	{
		//21.1.2. 
		//se o inimigo estiver morrendo e acabou a anima��o de estouro
		//deve-se mudar o estado para ES_END

	}
	else
	{
		//acumulando tempo desde o �ltimo tiro
		AccumShot.Update();
	}
}

//---------------------------------------------------------------------------- 
// Nome: IsPlayer(void)
// Desc: Retorna falso pois este n�o � um objeto de CPlayer.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::IsPlayer(void)
{
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: MoveTo(CNGLVector Dest)
// Desc: Move o inimigo para um determinado ponto.
// Pams: posi��o destino
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
// Desc: Retorna verdadeiro se este inimigo est� vendo o jogador. Se o inimigo est� de costas para o jogador, ou a dist�ncia
//       entre o jogador e o inimigo � maior que o raio de vis�o do inimigo, ent�o retorna verdadeiro.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CEnemy::SeePlayer(void)
{
	//20.2.5. 
	// se o inimigo est� de costas para o jogador ent�o retorna falso (n�o est� vendo)

	// se a dist�ncia entre o jogador e o inimigo for maior que
	// o raio de vis�o, ent�o retorna falso.


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

	//2. criar a anima��o do estouro no sprite p_SprPain

	//3. ajustar como anima��o corrente a 0

	//4. esconder com o inimigo

	//5. sprite do estouro deve receber a posi��o do inimigo

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
	// ve se j� n�o est� pulando
	if(!bJump)
	{
		bJump			= true;
		CurrentSpeed.fy = -450.0f;
	}
}

//---------------------------------------------------------------------------- 
// Nome: Move(void)
// Desc: Faz o inimigo se movimentar de acordo com a dire��o, velocidade e alcance de patrulha
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CEnemy::Move(void)
{
	//20.2.4. 
	//verificar qual dire��o o inimigo est� se movimentando
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

	//2. criar vetor de velocidade e dire��o que representa a dist�ncia entre
	//o centro do inimigo e o centro do jogador


	//3. Normaliza o vetor para pegar seu valor unit�rio.

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
	//22.1.3. retornar se o acumulador de tempo de tiros terminou ou n�o!
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