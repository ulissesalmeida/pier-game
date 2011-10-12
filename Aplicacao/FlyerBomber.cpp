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
#include "FlyerBomber.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CFlyerBomber(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CFlyerBomber::CFlyerBomber(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CFlyerBomber(void)
// Desc: destrutor padrão
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
// Pams: posição inicial
//---------------------------------------------------------------------------- 
bool CFlyerBomber::Initialize(CNGLVector InitPos)
{
	//22.2.1. 
	//1. cria sprite Flyer Bomber

	//1. Adiciona animação de movimentação do pássaro

	//1. atribui posição inicial ao pássaro

	//1. já manda ele se movimentar

	//2. agente não vai usar gravidade


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
	//1. se não vê o jogador, muda para estado de patrulha
	if(!SeePlayer())
	{

	}
	//2. programar ataque do agente
	else
	{
		// 20% do tempo em que está atacando, o inimigo vai atirar.

		//inimigo continuará andando

	}
}