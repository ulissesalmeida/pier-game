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

#include "Presentation.h"
#include "NGLLayer.h"
#include "NGLMain.h"

//---------------------------------------------------------------------------- 
// Nome: CPresentation(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CPresentation::CPresentation(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: ~CPresentation(void)
// Desc: destrutor padr�o
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
//		   criar todos os objetos e fazer inicializa��es necess�rias.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CPresentation::Initialize(void)
{
	//imagem 0 para o fundo da tela de apresenta��o
	AddTileImage("Surfaces/bkg_Presentation.bmp",CNGLVector(640,480));
	//cria a layer de fundo (background). 1 �nico brick de 640x480
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