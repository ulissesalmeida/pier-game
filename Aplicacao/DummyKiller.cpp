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
#include "DummyKiller.h"
#include "NGLImage.h"
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CDummyKiller(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CDummyKiller::CDummyKiller(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CDummyKiller(void)
// Desc: destrutor padrão
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
// Pams: posição inicial
//---------------------------------------------------------------------------- 
bool CDummyKiller::Initialize(CNGLVector InitPos)
{
	//22.1.4.
	//1. criar o sprite

	//2. criar a animação de movimentação

	//3. inicializar posição

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
	//1. se o jogador não foi mais visto, faz o inimigo mudar para o estado patrolando
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