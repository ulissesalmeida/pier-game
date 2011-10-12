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
#include "Dummy.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CDummy(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummy::CDummy(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CDummy(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummy::~CDummy(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Libera recursos do inimigo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CDummy::Release(void)
{
	CEnemy::Release();
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(CNGLVector InitPos)
// Desc: Inicializa o inimigo (sprite, anima��es e comando de movimenta��o).
// Pams: posi��o inicial
//---------------------------------------------------------------------------- 
bool CDummy::Initialize(CNGLVector InitPos)
{
	//20.2.2. 
	//1. criar o sprite do Dummy

	//2. criar anima��o de movimenta��o

	//3. criar anima��o de pulo

	//4. colocar InitPos como posi��o inicial do sprite

	//5. manda o inimigo se movimentar para a posi��o dele mais o raio de patrulha


	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Atualiza o estado do inimigo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CDummy::Execute(void)
{
	//20.2.3. 
	//1. chamar execu��o da classe pai

	
	//2. chamar o m�todo de tratamento adequado de acordo com o estado atual

}

//---------------------------------------------------------------------------- 
// Nome: OnPatroling(void)
// Desc: Trata o estado ES_PATROLING do inimigo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CDummy::OnPatroling(void)
{
	//20.2.6. caso veja o jogador, muda estado para ataque

}

//---------------------------------------------------------------------------- 
// Nome: OnAttacking(void)
// Desc: Trata o estado ES_ATTACKING do inimigo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CDummy::OnAttacking(void)
{
	//20.2.7. 
	//caso n�o veja mais o jogador, volta para o estado de patrulha

}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(CEnemy::EnemyState NewState)
// Desc: Muda o estado do inimigo
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CDummy::ChangeState(CEnemy::EnemyState NewState)
{
	CEnemy::ChangeState(NewState);
	switch(NewState)
	{
		case CEnemy::ES_ATTACKING:
		{
			if(State == CEnemy::ES_PATROLING)
			{
				State = NewState;
				break;
			}
			break;
		}
		case CEnemy::ES_PATROLING:
		{
			if(State == CEnemy::ES_ATTACKING)
			{
				State = NewState;
				break;
			}
			break;
		}
	}
}

