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
#include "FlyerBomber.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CFlyerBomber(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CFlyerBomber::CFlyerBomber(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CFlyerBomber(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CFlyerBomber::~CFlyerBomber(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a cena
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CFlyerBomber::Release(void)
{
	CDummy::Release();
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(CNGLVector InitPos)
// Desc: Inicializa o inimigo.
// Pams: posi��o inicial
//---------------------------------------------------------------------------- 
bool CFlyerBomber::Initialize(CNGLVector InitPos)
{
	//22.2.1. 
	//1. cria sprite Flyer Bomber

	//1. Adiciona anima��o de movimenta��o do p�ssaro

	//1. atribui posi��o inicial ao p�ssaro

	//1. j� manda ele se movimentar

	//2. agente n�o vai usar gravidade


	return true;
}

//---------------------------------------------------------------------------- 
// Nome: OnAttacking(void)
// Desc: Trata o estado de ataque do inimigo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CFlyerBomber::OnAttacking(void)
{
	//22.2.2. 
	//1. se n�o v� o jogador, muda para estado de patrulha
	if(!SeePlayer())
	{

	}
	//2. programar ataque do agente
	else
	{
		// 20% do tempo em que est� atacando, o inimigo vai atirar.

		//inimigo continuar� andando

	}
}