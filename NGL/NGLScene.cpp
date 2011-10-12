/*NGL v1.0 - Nology Game Library 
Copyright (C) 2003, 2004 Nology Softwares SC Ltda. Todos os direitos reservados

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
#include "NGLscene.h"
#include "NGLmain.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLScene(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLScene::CNGLScene(void)
{
	pr_Main = NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLScene(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLScene::~CNGLScene(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a cena
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLScene::Release(void)
{
	int i;
	//deleta as layers da cena
	for(i = (int)Layers.size()-1; i >= 0; i--)
	{
		Layers[i]->Release();
		delete Layers[i];
	}
	Layers.clear();

	//deleta os tiles da cena
	for(i = (int)TileImages.size()-1; i >= 0; i--)
	{
		pr_Main->VideoManager.DeleteImage(&TileImages[i]);
	}
	TileImages.clear();
	
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Faz a atualiza��o da cena
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLScene::Update(void)
{
	int iSize = (int)Layers.size();
	for(int i = 0; i < iSize; i++)
	{
		Layers[i]->Update();
	}
}

//---------------------------------------------------------------------------- 
// Nome: Draw(void)
// Desc: Desenha a cena. Esta rotina � virtual porque ela pode ser reescrita na cena.
//		   Isso � usado em ocasi�es onde a cena do usu�rio desenha objetos que a cena da NGL n�o
//		   tem controle. Caso essa rotina seja reescrita na classe filha, deve-se chamar a Draw()
//		   da classe pai, para que continue se desenhando os objetos j� adicionados na cena.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLScene::Draw(void)
{
	//faz um la�o para desenhar todas as layers
	int iSize = (int)Layers.size();
	for(int i = 0; i < iSize; i++)
	{
		if(Layers[i]->bVisible)
		{
			Layers[i]->Draw();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: DeleteLayer(CNGLLayer **p_Layer)
// Desc: Deleta uma layer
// Pams: refer�ncia ao ponteiro da layer
//---------------------------------------------------------------------------- 
bool CNGLScene::DeleteLayer(CNGLLayer **p_Layer)
{
	if(p_Layer && *p_Layer)
	{
		for(int i = (int)Layers.size()-1; i >=0; i--)
		{
			if(Layers[i] == *p_Layer)
			{
				Layers[i]->Release();
				delete Layers[i];
				*p_Layer = NULL;
				Layers.erase(Layers.begin()+i);
				return true;
			}
		}
	}

	//layer n�o encontrada ou ponteiros inv�lidos
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: Scroll(const CNGLVector &cScroll)
// Desc: faz o scroll de todas as layers da cena
// Pams: vetor de scroll
//---------------------------------------------------------------------------- 
void CNGLScene::Scroll(const CNGLVector &cScroll)
{
	for(int i = (int)Layers.size()-1; i >=0; i--)
	{
		Layers[i]->Scroll(cScroll);
	}
}

//---------------------------------------------------------------------------- 
// Nome: AddTileImage(const char * cp_chFileName, const CNGLVector & cFrameSize)
// Desc: adiciona uma imagem para ser utilizada como tile nas layers
//			 e retorna seu �ndice no vetor de imagens da cena
// Pams: nome do arquivo de imagem, Tamanho do quadro da imagem
//---------------------------------------------------------------------------- 
int CNGLScene::AddTileImage(const char * cp_chFileName, const CNGLVector & cFrameSize)
{
	CNGLImage *p_Image = pr_Main->VideoManager.LoadImage(cp_chFileName);
	if(p_Image)
	{
		p_Image->SetFrameSize(cFrameSize);
		TileImages.push_back(p_Image);
		return (int)TileImages.size()-1;
	}
	else
	{
		return -1;
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateLayer(const CNGLVector &cBrickSize,const CNGLVector &cNumBricks)
// Desc: cria uma layer na cena
// Pams: tamanho o brick, matriz contendo o n�mero de bricks
//---------------------------------------------------------------------------- 
CNGLLayer *CNGLScene::CreateLayer(const CNGLVector &cBrickSize,const CNGLVector &cNumBricks)
{
	CNGLLayer *p_Layer = CreateLayer(cBrickSize);
	if(p_Layer)
	{
		p_Layer->CreateBricks(cNumBricks);
		return p_Layer;
	}
  return NULL;  
}

//---------------------------------------------------------------------------- 
// Nome: CreateLayer()
// Desc: cria uma layer na cena com o tamanho de brick passado por par�metro
// Pams: tamanho do brick
//---------------------------------------------------------------------------- 
CNGLLayer *CNGLScene::CreateLayer(const CNGLVector &cBrickSize)
{
	CNGLLayer *p_Layer = new CNGLLayer();
	if(p_Layer)
	{
		p_Layer->BrickSize				= cBrickSize;
		p_Layer->pr_Scene					= this;
		Layers.push_back(p_Layer);
		return p_Layer;
	}
  return NULL;  
}