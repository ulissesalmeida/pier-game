/*NGL v1.0 - Nology Game Library 
Copyright (C) 2003, 2004 Nology Softwares SC Ltda. Todos os direitos reservados

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
#include "NGLscene.h"
#include "NGLmain.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLScene(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLScene::CNGLScene(void)
{
	pr_Main = NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLScene(void)
// Desc: destrutor padrão
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
// Desc: Faz a atualização da cena
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
// Desc: Desenha a cena. Esta rotina é virtual porque ela pode ser reescrita na cena.
//		   Isso é usado em ocasiões onde a cena do usuário desenha objetos que a cena da NGL não
//		   tem controle. Caso essa rotina seja reescrita na classe filha, deve-se chamar a Draw()
//		   da classe pai, para que continue se desenhando os objetos já adicionados na cena.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLScene::Draw(void)
{
	//faz um laço para desenhar todas as layers
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
// Pams: referência ao ponteiro da layer
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

	//layer não encontrada ou ponteiros inválidos
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
//			 e retorna seu índice no vetor de imagens da cena
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
// Pams: tamanho o brick, matriz contendo o número de bricks
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
// Desc: cria uma layer na cena com o tamanho de brick passado por parâmetro
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