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
#include "Dummy.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CDummy(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummy::CDummy(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CDummy(void)
// Desc: destrutor padrão
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
// Desc: Inicializa o inimigo (sprite, animações e comando de movimentação).
// Pams: posição inicial
//---------------------------------------------------------------------------- 
bool CDummy::Initialize(CNGLVector InitPos)
{
	//20.2.2. 
	//1. criar o sprite do Dummy

	//2. criar animação de movimentação

	//3. criar animação de pulo

	//4. colocar InitPos como posição inicial do sprite

	//5. manda o inimigo se movimentar para a posição dele mais o raio de patrulha


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
	//1. chamar execução da classe pai

	
	//2. chamar o método de tratamento adequado de acordo com o estado atual

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
	//caso não veja mais o jogador, volta para o estado de patrulha

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

