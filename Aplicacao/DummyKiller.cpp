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
#include "DummyKiller.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CDummyKiller(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummyKiller::CDummyKiller(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CDummyKiller(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummyKiller::~CDummyKiller(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Libera recursos do inimigo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CDummyKiller::Release(void)
{
	CDummy::Release();
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(CNGLVector InitPos)
// Desc: Inicializa o inimigo.
// Pams: posi��o inicial
//---------------------------------------------------------------------------- 
bool CDummyKiller::Initialize(CNGLVector InitPos)
{
	//22.1.4.
	//1. criar o sprite

	//2. criar a anima��o de movimenta��o

	//3. inicializar posi��o

	//4. mandar ele se movimentar


	return true;
}

//---------------------------------------------------------------------------- 
// Nome: OnAttacking(void)
// Desc: Trata o estado ES_ATTACKING do inimigo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CDummyKiller::OnAttacking(void)
{
	//1. se o jogador n�o foi mais visto, faz o inimigo mudar para o estado patrolando
	if(!SeePlayer())
	{

	}
	//caso o inimigo esteja sendo visto, fazer o ataque
	else
	{
		//2. 20% do tempo o inimigo vai atirar (caso ele possa)

		//3. 10% do tempo o inimigo deve pular.

		//4. fazer o inimigo se movimentar

	}
}