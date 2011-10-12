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
#include "NGLlayer.h"
#include "NGLmain.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLLayer(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLLayer::CNGLLayer(void)
{
	Speed.fx	= Speed.fy = 1.0f;
	pr_Scene	= NULL;
	p_Bricks	= NULL;
	bVisible	= true;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLLayer(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLLayer::~CNGLLayer(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o layer
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLLayer::Release(void)
{
	//limpa os sprites da layer
	int i;
	for(i = (int)Sprites.size()-1; i >= 0; i--)
	{
		Sprites[i]->Release();
		delete Sprites[i];
	}
	Sprites.clear();

	//limpa os bricks da layer
	ClearBricks();
	
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: DeleteSprite(CNGLSprite **p_Sprite)
// Desc: Deleta um sprite e o remove da layer.
// Pams: referência ao ponteiro da layer
//---------------------------------------------------------------------------- 
bool CNGLLayer::DeleteSprite(CNGLSprite **p_Sprite)
{
	if(p_Sprite && *p_Sprite)
	{
		for(int i = (int)Sprites.size()-1; i >=0; i--)
		{
			if(Sprites[i] == *p_Sprite)
			{
				Sprites[i]->Release();
				delete Sprites[i];
				*p_Sprite = NULL;
				Sprites.erase(Sprites.begin()+i);
				return true;
			}
		}
	}

	//sprite não encontrado ou ponteiros inválidos
	return false;
}


//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza a layer
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLLayer::Update(void)
{
	CNGLVector LayerSize = GetLayerSize();
	if(LayerSize.fx >= pr_Scene->pr_Main->VideoManager.VideoSize.fx && LayerSize.fy >= pr_Scene->pr_Main->VideoManager.VideoSize.fy)
	{

		for(int i = (int)Sprites.size()-1; i >=0; i-- )
		{
			Sprites[i]->Update();

			Sprites[i]->Position.fx = (Sprites[i]->Position.fx < 0)? 
																	Sprites[i]->Position.fx + LayerSize.fx : 
																	Sprites[i]->Position.fx;
			Sprites[i]->Position.fy = (Sprites[i]->Position.fy < 0)? 
																	Sprites[i]->Position.fy + LayerSize.fy : 
																	Sprites[i]->Position.fy;

			Sprites[i]->Position.fx = (Sprites[i]->Position.fx > LayerSize.fx)? 
																	Sprites[i]->Position.fx - LayerSize.fx : 
																	Sprites[i]->Position.fx;
			Sprites[i]->Position.fy = (Sprites[i]->Position.fy > LayerSize.fy)? 
																	Sprites[i]->Position.fy - LayerSize.fy : 
																	Sprites[i]->Position.fy;
		}
	}
	else
	{
		for(int i = (int)Sprites.size()-1; i >=0; i-- )
		{
			Sprites[i]->Update();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Draw(void)
// Desc: Desenha a layer.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLLayer::Draw(void)
{
	if(p_Bricks)
	{
		int i = 0,j = 0;

		CNGLVector Pos = Offset;

		Pos.Floor();
		while(Pos.fx > 0)
		{
			Pos.fx -= BrickSize.fx;
			i--;
			i = (i < 0)? ((int)NumBricks.fx) - 1 : i;
		}

		while(Pos.fy > 0)
		{
			Pos.fy -= BrickSize.fy;
			j--;
			j = (j < 0)? ((int)NumBricks.fy) - 1 : j;
		}

		float fXPos = Pos.fx;
		int iStarti = i;
		int iSize = (int)NumBricks.fx;
		int jSize = (int)NumBricks.fy;
		for(; Pos.fy < (int)pr_Scene->pr_Main->VideoManager.VideoSize.fy; j = (j+1)%jSize)
		{
			for(; Pos.fx < (int)pr_Scene->pr_Main->VideoManager.VideoSize.fx; i = (i+1)%iSize)
			{
				if( p_Bricks[i + (j*iSize)] )
				{
					pr_Scene->pr_Main->VideoManager.BackBuffer.DrawImage(Pos,
															pr_Scene->TileImages[p_Bricks[i + (j*iSize)]->iImage],
															p_Bricks[i + (j*iSize)]->iFrame,
															NGLMIRROR_NONE);
				}
				Pos.fx += BrickSize.fx;
			}
			Pos.fy += BrickSize.fy;
			i = iStarti;
			Pos.fx = fXPos;
		}
	}

	//Pinta os sprites da layer
	int iSprites = (int)Sprites.size();
	for(int i = 0; i < iSprites; i++)
	{
		//somente desenha se o sprite estiver visível.
		if(Sprites[i]->bVisible)
		{
			Sprites[i]->Draw();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateSprite(void)
// Desc: Cria um sprite e adiciona ele à layer.
// Pams: caminho do arquivo, tamanho do quadro
//---------------------------------------------------------------------------- 
CNGLSprite* CNGLLayer::CreateSprite(const char*cp_chFileName,const CNGLVector &cFrameSize)
{
	CNGLSprite *p_Sprite = new CNGLSprite();
	if(p_Sprite)
	{
		//ajusta o ponteiro de layer do sprite e do objeto CNGLMain
		p_Sprite->pr_Layer = this;
		p_Sprite->pr_Main  = pr_Scene->pr_Main;
		//cria o sprite
		p_Sprite->Create(cp_chFileName,cFrameSize);
		//adiciona na lista de sprites da layer
		Sprites.push_back(p_Sprite);
		return p_Sprite;
	}
	return NULL;
}

//---------------------------------------------------------------------------- 
// Nome: Scroll(const CNGLVector & cScroll)
// Desc: Faz o Scroll(movimentação) da layer
// Pams: Tamanho do deslocamento
//---------------------------------------------------------------------------- 
void CNGLLayer::Scroll(const CNGLVector & cScroll)
{
	Offset.fx += cScroll.fx*Speed.fx;
	Offset.fy += cScroll.fy*Speed.fy;

	CNGLVector LayerSize = GetLayerSize();

	if(LayerSize.fx > 0.0f)
	{
		//O offset não pode ser menor que 0
		while(Offset.fx < 0.0f)
		{
			Offset.fx += LayerSize.fx;
		}
		//O offset não pode ser maior que o tamanho da layer
		while(Offset.fx > LayerSize.fx)
		{
			Offset.fx -= LayerSize.fx;
		}
	}

	if(LayerSize.fy > 0.0f)
	{
		//O offset não pode ser menor que 0
		while(Offset.fy < 0.0f)
		{
			Offset.fy += LayerSize.fy;
		}
		//O offset não pode ser maior que o tamanho da layer
		while(Offset.fy > LayerSize.fy)
		{
			Offset.fy -= LayerSize.fy;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateBricks(const CNGLVector &cNumBricks)
// Desc: Cria os bricks da layer.
// Pams: tamanho da matriz
//---------------------------------------------------------------------------- 
void CNGLLayer::CreateBricks(const CNGLVector &cNumBricks)
{
	//limpa o vetor de bricks
	ClearBricks();
	NumBricks = cNumBricks;
	NumBricks.Floor();
	int iSize = (int)NumBricks.fx*(int)NumBricks.fy;
	p_Bricks = new CNGLBrick*[iSize];

	memset(p_Bricks,0,iSize*sizeof(CNGLBrick*));
}

//---------------------------------------------------------------------------- 
// Nome: ClearBricks(void)
// Desc: Apaga todos os bricks da layer.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLLayer::ClearBricks(void)
{
	if(p_Bricks)
	{
		int iSize = (int)NumBricks.fx*(int)NumBricks.fy;
		for(int i = 0; i < iSize; i++)
		{
			if(p_Bricks[i])
			{
				delete p_Bricks[i];
				p_Bricks[i] = NULL;
			}
		}
		delete []p_Bricks;
		p_Bricks = NULL;
	}

}

//---------------------------------------------------------------------------- 
// Nome: SetBrick(const CNGLVector& cBrickPos, int iImage, int iFrame)
// Desc: Configura um brick.
// Pams: posição do brick, indices da imagem, numero do quadro
//---------------------------------------------------------------------------- 
void CNGLLayer::SetBrick(const CNGLVector& cBrickPos, int iImage, int iFrame)
{
	if(p_Bricks && cBrickPos.fy >= 0 && cBrickPos.fy < NumBricks.fy 
		&& cBrickPos.fx >= 0 && cBrickPos.fx < NumBricks.fx )
	{
		int iPos = ((int)cBrickPos.fx) + ((int)cBrickPos.fy*(int)NumBricks.fx);
		if(!p_Bricks[iPos])
		{
			p_Bricks[iPos] = new CNGLBrick();
		}
		p_Bricks[iPos]->iFrame = iFrame;
		p_Bricks[iPos]->iImage = iImage;
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateBricksFromBitmap(const char * cp_chFileName, stNGLBrickConfig* pr_BrickConfigs, int iConfigCount)
// Desc: Cria uma layer com bricks a partir de uma image (bitmap).
// Pams: nome do arquivo do bitmap, Vetor de BrickConfigs, tamanho do vetor
//---------------------------------------------------------------------------- 
void CNGLLayer::CreateBricksFromBitmap(const char * cp_chFileName, stNGLBrickConfig* pr_BrickConfigs, int iConfigCount)
{
	FILE *p_File = fopen(cp_chFileName,"rb");
	if(p_File)
	{
		short						sIdentifier				= 0;
		unsigned int		uiFileSize				= 0;
		unsigned int		uiReserved				= 0;
		unsigned int		uiBmpDataOffset		= 0;
		unsigned int		uiBmpHeaderSize		= 0;
		int							iWidth						= 0;
		int							iHeight						= 0;
		short						sPlanes						= 0;
		short						sBitsPerPixel			= 0;
		unsigned int		uiCompression			= 0;
		unsigned int		uiBmpDataSize			= 0;
		unsigned int		uiHResolution			= 0;
		unsigned int		uiVResolution			= 0;
		unsigned int		uiColors					= 0;
		unsigned int		uiImportantColors = 0;

		// Lê o cabeçalho
		fread(&sIdentifier,sizeof(short),1,p_File);
		fread(&uiFileSize,sizeof(int),1,p_File);
		fread(&uiReserved,sizeof(int),1,p_File);
		fread(&uiBmpDataOffset, sizeof(int),1,p_File);
		fread(&uiBmpHeaderSize,sizeof(int),1,p_File);
		fread(&iWidth,sizeof(int),1,p_File);
		fread(&iHeight,sizeof(int),1,p_File);
		fread(&sPlanes,sizeof(short),1,p_File);
		fread(&sBitsPerPixel,sizeof(short),1,p_File);
		fread(&uiCompression,sizeof(int),1,p_File);
		fread(&uiBmpDataSize,sizeof(int),1,p_File);
		fread(&uiHResolution,sizeof(int),1,p_File);
		fread(&uiVResolution,sizeof(int),1,p_File);
		fread(&uiColors,sizeof(int),1,p_File);
		fread(&uiImportantColors,sizeof(int),1,p_File);

		//Pega o tamanho da palheta
		unsigned int uiPaletteSize;
		int nColors = (uiColors) ? uiColors :	1 << sBitsPerPixel;
		if(nColors <= 256)
		{
			//cada entrada na palheta tem 4 bytes
			uiPaletteSize = nColors * 4;
		}
		else
		{
			if((sBitsPerPixel == 16 || sBitsPerPixel == 32) && uiCompression == 3L)
			{
				//A palheta contém 3 entrada (tipo dword) descrevendo a mascara de bits
				// como sizeof(DWORD) == 4 entao é 3*4
				//muito pouco usado
				uiPaletteSize =  12;
			}
			else
			{
				//nao tem palheta
				uiPaletteSize = 0;
			}
		}

		unsigned int uiSize = uiFileSize - uiBmpDataOffset + uiPaletteSize;
		unsigned char *p_DataAux = new unsigned char[uiSize];
		fread(p_DataAux, uiSize,1,p_File);

		fclose(p_File);

		CreateBricks(CNGLVector((float)iWidth,(float)iHeight));

		int i,j,k;
		unsigned char ucR, ucG, ucB;
		unsigned int  uiRGB;
		int iY;
		if(uiPaletteSize)
		{
			unsigned char *p_Palette = (unsigned char*)p_DataAux;
			unsigned char *p_Bits		= p_Palette + uiPaletteSize;
			//para cada linha
			for(j = 0; j < iHeight; j++)
			{
        iY = iHeight-1-j;
				//para cada coluna
				for(i = 0; i < iWidth; i++)
				{
					ucB		= p_Palette[4 * p_Bits[i +(iY * iWidth)]];
					ucG		= p_Palette[(4 * p_Bits[i +(iY * iWidth)]) + 1];
					ucR		= p_Palette[(4 * p_Bits[i +(iY * iWidth)]) + 2];
					uiRGB = RGB(ucR,ucG,ucB);
					//se o pixel está no brick config
					for(k = 0; k < iConfigCount; k++)
					{
						if(uiRGB == pr_BrickConfigs[k].uiColor)
						{
							//seta o brick
							SetBrick(CNGLVector((float)i,(float)j),pr_BrickConfigs[k].iImage,pr_BrickConfigs[k].iFrame);
							break;
						}
					}
				}
			}
		}
		else
		{
			int iLine;
			int iLineOffset = ((uiFileSize - uiBmpDataOffset)/iHeight) - (iWidth * 3);
			//para cada linha
			for(j = 0; j < iHeight; j++)
			{
        iY = iHeight-1-j;
				iLine = (iY * iWidth * 3) + (iLineOffset *iY);
				//para cada coluna
				for(i = 0; i < iWidth; i++)
				{
					ucB		= p_DataAux[(3 * i) + iLine];
					ucG		= p_DataAux[(3 * i) + iLine + 1];
					ucR		= p_DataAux[(3 * i) + iLine + 2];
					uiRGB = RGB(ucR,ucG,ucB);
					//se o pixel está no brick config
					for(k = 0; k < iConfigCount; k++)
					{
						if(uiRGB == pr_BrickConfigs[k].uiColor)
						{
							//seta o brick
							SetBrick(CNGLVector((float)i,(float)j),pr_BrickConfigs[k].iImage,pr_BrickConfigs[k].iFrame);
							break;
						}
					}
				}
			}
		}

		delete []p_DataAux;
	}

}


//---------------------------------------------------------------------------- 
// Nome: GetLayerSize(void)
// Desc: retorna o tamanho da layer em pixels
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLVector CNGLLayer::GetLayerSize(void)
{
	return CNGLVector(NumBricks.fx*BrickSize.fx, NumBricks.fy*BrickSize.fy);
}

//---------------------------------------------------------------------------- 
// Nome: GetLayerPos(const CNGLVector & BkBuffPos)
// Desc: retorna a posiçao na layer dada a posição no back buffer
// Pams: posição no back buffer
//---------------------------------------------------------------------------- 
CNGLVector CNGLLayer::GetLayerPos(const CNGLVector & BkBuffPos)
{
	CNGLVector LayerSize = GetLayerSize();

	CNGLVector PosRet = ((LayerSize - Offset) + BkBuffPos);
	//O PosRet não pode ser menor que 0
	while(PosRet.fx < 0.0f)
	{
		PosRet.fx += LayerSize.fx;
	}

	//O PosRet não pode ser menor que 0
	while(PosRet.fy < 0.0f)
	{
		PosRet.fy += LayerSize.fy;
	}

	//O PosRet não pode ser maior que o tamanho da layer
	while(PosRet.fx > LayerSize.fx)
	{
		PosRet.fx -= LayerSize.fx;
	}

	//O PosRet não pode ser maior que o tamanho da layer
	while(PosRet.fy > LayerSize.fy)
	{
		PosRet.fy -= LayerSize.fy;
	}

	return PosRet;
}

//---------------------------------------------------------------------------- 
// Nome: GetBackBufferPos(const CNGLVector & LayerPos)
// Desc: retorna a posição no back buffer dada a posição na layer
// Pams: posição na layer
//---------------------------------------------------------------------------- 
CNGLVector CNGLLayer::GetBackBufferPos(const CNGLVector & LayerPos, const CNGLVector &FrameSize)
{
	CNGLVector LayerSize = GetLayerSize();
	CNGLVector PosRet = LayerPos;
	if(LayerSize.fx >= pr_Scene->pr_Main->VideoManager.VideoSize.fx && LayerSize.fy >= pr_Scene->pr_Main->VideoManager.VideoSize.fy)
	{
		CNGLVector Aux = (LayerSize - Offset);
		Aux.fx = -Aux.fx;
		Aux.fy = -Aux.fy;
		PosRet += Aux;//(LayerSize - Offset);
		//O PosRet não pode ser menor que 0
		while(PosRet.fx < -FrameSize.fx)
		{
			PosRet.fx += LayerSize.fx;
		}

		//O PosRet não pode ser menor que 0
		while(PosRet.fy < -FrameSize.fy)
		{
			PosRet.fy += LayerSize.fy;
		}

		//O PosRet não pode ser maior que o tamanho da layer
		while(PosRet.fx > LayerSize.fx)
		{
			PosRet.fx -= LayerSize.fx;
		}

		//O PosRet não pode ser maior que o tamanho da layer
		while(PosRet.fy > LayerSize.fy)
		{
			PosRet.fy -= LayerSize.fy;
		}
	}
	return PosRet;
}
