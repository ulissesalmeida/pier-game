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

#include "Presentation.h"
#include "NGLLayer.h"
#include "NGLMain.h"

//---------------------------------------------------------------------------- 
// Nome: CPresentation(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CPresentation::CPresentation(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CPresentation(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CPresentation::~CPresentation(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza a classe, liberando todos os objetos alocados.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CPresentation::Release(void)
{
	//libera a cena da classe pai
	CNGLScene::Release();

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
//		   criar todos os objetos e fazer inicializações necessárias.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CPresentation::Initialize(void)
{
	//imagem 0 para o fundo da tela de apresentação
	AddTileImage("Surfaces/bkg_Presentation.bmp",CNGLVector(640,480));
	//cria a layer de fundo (background). 1 único brick de 640x480
	CNGLLayer *p_LayBkg    = CreateLayer(CNGLVector(640,480),CNGLVector(1,1));
	//a imagem que queremos mostrar corresponde ao brick (0,0), da imagem 0, quadro 0
	p_LayBkg->SetBrick(CNGLVector(0,0),0,0);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Aguarda a tecla ENTER ser pressionada para trocar para a cena do jogo (CNGLLevel).
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CPresentation::Execute(void)
{
	if(pr_Main->InputManager.KeyPressed(DIK_RETURN)){
		pr_Main->SetCurrentScene(1);
	}
}