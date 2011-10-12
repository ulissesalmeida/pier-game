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
#include "NGLMain.h"
#include "NGLimage.h"
#include "NGLVideoManager.h"
#include <stdio.h>
#include <string.h>
#include <string>

//---------------------------------------------------------------------------- 
// Nome: CNGLImage(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLImage::CNGLImage(void)
{
	//número de referências para essa imagem começa em zero
	sReferences			= 0;
	//inicia a superfície do DirectDraw em nulo
	p_Surface				= NULL;
	//inicia o ponteiro para o CNGLVideoManager em nulo
	pr_VideoManager = NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLImage(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLImage::~CNGLImage(void)
{
	//libera os recursos da classe
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a imagem
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLImage::Release(void)
{
	if(p_Surface)
	{
		p_Surface->Release();
		p_Surface = NULL;
	}
	ClearFrames();
	
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: CreateFrontBuffer()
// Desc: Cria a imagem como um front buffer
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLImage::CreateFrontBuffer()
{
	if(pr_VideoManager)
	{
		Release();
		DDSURFACEDESC	SurfaceDesc;
		ZeroMemory(&SurfaceDesc, sizeof(SurfaceDesc));
		SurfaceDesc.dwSize = sizeof(SurfaceDesc);
		Size =	pr_VideoManager->VideoSize;

		if(!pr_VideoManager->bFullScreen)
		{
			//configura a superfície primária do modo janela
			SurfaceDesc.dwFlags        = DDSD_CAPS;
			SurfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		}
		else
		{
			//configura a superfície primária com 1 back buffer (modo tela cheia)
			SurfaceDesc.dwFlags           = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			SurfaceDesc.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
																			DDSCAPS_COMPLEX;
			SurfaceDesc.dwBackBufferCount = 1;
		}

		//cria a superfície
		if(FAILED(pr_VideoManager->p_DDraw->CreateSurface(&SurfaceDesc, &p_Surface, NULL)))
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateBackBuffer()
// Desc: Cria a imagem como back buffer
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLImage::CreateBackBuffer()
{
	if(pr_VideoManager)
	{
		Release();
		DDSURFACEDESC	SurfaceDesc;
		ZeroMemory(&SurfaceDesc, sizeof(SurfaceDesc));
		SurfaceDesc.dwSize = sizeof(SurfaceDesc);
		Size = pr_VideoManager->VideoSize;

		if(!pr_VideoManager->bFullScreen)
		{
			//se não é tela cheia, cria uma surface normal
			SurfaceDesc.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;    
			SurfaceDesc.dwWidth        = (DWORD)Size.fx;
			SurfaceDesc.dwHeight       = (DWORD)Size.fy;
			if(FAILED(pr_VideoManager->p_DDraw->CreateSurface(&SurfaceDesc, &p_Surface, NULL)))
			{
				return false;
			}
		}
		else
		{
			//Se é tela cheia, ajusta a capacidade da superfície para ser
			//um back buffer
			DDSCAPS ddscaps;
			ZeroMemory(&ddscaps, sizeof(ddscaps));
			ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

			if(FAILED(pr_VideoManager->FrontBuffer.p_Surface->GetAttachedSurface(&ddscaps, &p_Surface)))
			{
				return false;
			}
			else
			{
				p_Surface->AddRef();
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}


//---------------------------------------------------------------------------- 
// Nome: CreateClipper()
// Desc: Cria directdraw clipper
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLImage::CreateClipper()
{
	if(pr_VideoManager)	
	{
		LPDIRECTDRAWCLIPPER p_Clipper = NULL;
		
		if(FAILED(pr_VideoManager->p_DDraw->CreateClipper(0, &p_Clipper, NULL)))
		{
			return false;
		}

		if(FAILED(p_Clipper->SetHWnd(0, (HWND)pr_VideoManager->pr_Main->pr_Wnd)))
		{
			p_Clipper->Release();
			return false;
		}

		if(FAILED(p_Surface->SetClipper(p_Clipper)))
		{
			p_Clipper->Release();
			return false;
		}
		//finaliza o clipper
		p_Clipper->Release();
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------- 
// Nome: Load(const char *cp_chFileName)
// Desc: Carrega a imagem do arquivo
// Pams: nome do arquivo
//---------------------------------------------------------------------------- 
bool CNGLImage::LoadFromFile(const char *cp_chFileNamePam)
{
	Release();
	if(cp_chFileNamePam)
	{
		FileName = cp_chFileNamePam;

		HGLOBAL						hDIB = NULL;
		BITMAPFILEHEADER	bmfHeader;
		HBITMAP						hBitmap = NULL;
		HPALETTE					hPalette = NULL;
		unsigned int			uiFilePos;
		unsigned int			uiFileSize;
		unsigned int			uiPackedDIBLen;

		FILE *p_File =	fopen(FileName.c_str(),"rb");
		if(p_File)
		{

			//Pega o tamanho do arquivo
			uiFilePos = ftell(p_File);
			fseek(p_File,0,SEEK_END);
			uiFileSize = ftell(p_File);
			fseek(p_File,uiFilePos,SEEK_SET);


			// Lê o header
			fread((void*)&bmfHeader, sizeof(bmfHeader),1,p_File);

				
			// Pega o tamanho do restante do arquivo e aloca a memória
			uiPackedDIBLen = uiFileSize - sizeof(BITMAPFILEHEADER);

			hDIB = GlobalAlloc(GMEM_FIXED, uiPackedDIBLen);
			if (hDIB == 0)
			{
				return false;
			}

			// Lê o restante do arquivo de bitmap
			if(fread((void*)hDIB, uiPackedDIBLen,1,p_File) != 1)
			{
				GlobalFree(hDIB);
				return false;
			}


			BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
			BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

			// Se bmiHeader.biClrUsed é zero pega o numero de cores através do
			// numero de bits
			int iColors = (bmiHeader.biClrUsed) ? bmiHeader.biClrUsed :	1 << bmiHeader.biBitCount;

			LPVOID lpDIBBits;
			if( bmInfo.bmiHeader.biBitCount > 8 )
			{
				lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
					((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
			}
			else
			{
				lpDIBBits = (LPVOID)(bmInfo.bmiColors + iColors);
			}

			// Cria a palheta
			if( iColors <= 256 )
			{
				UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * iColors);
				LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

				pLP->palVersion = 0x300;
				pLP->palNumEntries = iColors;

				for( int i=0; i < iColors; i++)
				{
					pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
					pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
					pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
					pLP->palPalEntry[i].peFlags = 0;
				}

				hPalette = CreatePalette(pLP );

				delete[] pLP;
			}
			if(!Create(CNGLVector((float)bmInfo.bmiHeader.biWidth, (float)bmInfo.bmiHeader.biHeight)))
			{
				return false;
			}

			//ajusta a cor de transparência como rosa
			SetColorKey(RGB(255,0,255));


			HDC hSurfaceDC = NULL;
			p_Surface->GetDC(&hSurfaceDC);

			if(GetDeviceCaps(hSurfaceDC, RASTERCAPS) & RC_PALETTE )
			{
				SelectPalette(hSurfaceDC, hPalette, FALSE );
				RealizePalette(hSurfaceDC);
			}

			hBitmap = CreateDIBitmap( hSurfaceDC,		// handle to device context 
																&bmiHeader,	// pointer to bitmap size and format data 
																CBM_INIT,	// initialization flag 
																lpDIBBits,	// pointer to initialization data 
																&bmInfo,	// pointer to bitmap color-format data 
																DIB_RGB_COLORS);		// color-data usage 


			//Pinta o bitmap na surface DirectDraw
			HDC hMemDC = CreateCompatibleDC( hSurfaceDC );
			
			SelectObject(hMemDC, hBitmap);

			BitBlt(hSurfaceDC, 0, 0, (int)Size.fx, (int)Size.fy, hMemDC, 0, 0,SRCCOPY);

			DeleteDC(hMemDC);
			DeleteObject(hBitmap);
			p_Surface->ReleaseDC(hSurfaceDC);
			DeleteObject(hPalette);
			GlobalFree(hDIB);

			SetFrameSize(Size);
			fclose(p_File);
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: Create(const CNGLVector cSize)
// Desc: Cria a imagem dado seu tamanho
// Pams: Tamanho da imagem
//---------------------------------------------------------------------------- 
bool CNGLImage::Create(const CNGLVector cSize)
{
	//configuração da superfície
	DDSURFACEDESC				SurfaceDesc;
	ZeroMemory( &SurfaceDesc, sizeof(SurfaceDesc) );
	SurfaceDesc.dwSize         = sizeof(SurfaceDesc);
	SurfaceDesc.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	SurfaceDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	SurfaceDesc.dwWidth        = (DWORD)cSize.fx;
	SurfaceDesc.dwHeight       = (DWORD)cSize.fy;
	Size = cSize;

	//Cria a superfície directdraw
	HRESULT hr = pr_VideoManager->p_DDraw->CreateSurface(&SurfaceDesc, &p_Surface, NULL);

	if(FAILED(hr))
	{
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: SetColorKey(unsigned int uiColorKey)
// Desc: Ajusta a Cor de transparência
// Pams: Cor
//---------------------------------------------------------------------------- 
void CNGLImage::SetColorKey(unsigned int uiColorKey)
{

	unsigned int uiSurfaceColor;

	uiSurfaceColor = ConvertGDIColor(uiColorKey);

  DDCOLORKEY DDCK;
  DDCK.dwColorSpaceLowValue  = uiSurfaceColor;
  DDCK.dwColorSpaceHighValue = uiSurfaceColor;
  
  //Ajusta a trasparência para a surface
	p_Surface->SetColorKey(DDCKEY_SRCBLT, &DDCK);

}

//---------------------------------------------------------------------------- 
// Nome: Reload(void)
// Desc: Roda a imagem novamente
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLImage::Reload(void)
{
	string Name = FileName;
  CNGLVector v = FrameSize;
	FrameSize.fx++;
	LoadFromFile(Name.c_str());
	SetFrameSize(v);
}

//---------------------------------------------------------------------------- 
// Nome: DrawImage(CNGLFrame *p_DestFrame, CNGLImage *p_SrcImage,CNGLFrame *p_SrcFrame)
// Desc: Pinta uma imagem sobre esta 
// Pams: Frame Destino, Imagem Fonte, Frame Fonte
//---------------------------------------------------------------------------- 
bool CNGLImage::DrawImage(CNGLFrame *p_DestFrame, CNGLImage *p_SrcImage,CNGLFrame *p_SrcFrame,Byte byMirror)
{
	CNGLFrame Dest;
	CNGLFrame Source;
  if(p_DestFrame)
	{
		Dest = *p_DestFrame;
	}
	else
	{
		p_DestFrame  = &Dest;
		Dest.iLeft   = Dest.iTop = 0;
		Dest.iBottom = (int)p_SrcImage->Size.fy;
		Dest.iRight  = (int)p_SrcImage->Size.fx;
	}

	if(p_SrcFrame)
	{

		Source = *p_SrcFrame;
	}
	else
	{
		p_SrcFrame		 = &Source;
		Source.iLeft   = Source.iTop = 0;
		Source.iBottom = (int)p_SrcImage->Size.fy;
		Source.iRight  = (int)p_SrcImage->Size.fx;
	}

	float fDiv, fDifX, fDifY;
	fDiv  = (float)p_DestFrame->GetWidth();
	fDifX = (fDiv != 0.0f)? (float)p_SrcFrame->GetWidth()/fDiv : 1.0f;

	fDiv = (float)p_DestFrame->GetHeight();
	fDifY = (fDiv != 0.0f)? (float)p_SrcFrame->GetHeight()/fDiv : 1.0f;

  DDBLTFX ddbltfx;
  ZeroMemory(&ddbltfx, sizeof(ddbltfx));
  ddbltfx.dwSize      = sizeof(ddbltfx);


	switch(byMirror)
	{
		//Sem Espelho
		case NGLMIRROR_NONE:
		{
			if(Dest.iTop < 0)
			{
				float fDif = (float)(Source.iBottom - Source.iTop)/(float)(Dest.iBottom - Dest.iTop);
				Source.iTop += (int)((float)(-Dest.iTop) * fDif);
				Dest.iTop = 0;
			}
			if(Dest.iLeft < 0)
			{
				float fDif = (float)(Source.iRight - Source.iLeft)/(float)(Dest.iRight - Dest.iLeft);
				Source.iLeft += (int)((float)(-Dest.iLeft) * fDif);
				Dest.iLeft = 0;
			}
			if(Dest.iBottom >= (int)Size.fy)
			{
				float fDif = (float)(Source.iBottom - Source.iTop)/(float)(Dest.iBottom - Dest.iTop);
				Source.iBottom -= (int)((float)(Dest.iBottom - (int)Size.fy) * fDif);
				Dest.iBottom = (int)Size.fy;
			}
			if(Dest.iRight >= (int)Size.fx )
			{
				float fDif = (float)(Source.iRight - Source.iLeft)/(float)(Dest.iRight - Dest.iLeft);
				Source.iRight -= (int)((float)(Dest.iRight - (int)Size.fx) * fDif);
				Dest.iRight = (int)Size.fx;
			}

			if(Dest.iRight < 0 || Dest.iLeft > (int)Size.fx || 
				Dest.iBottom < 0 || Dest.iTop  > (int)Size.fy || 
				!Dest.IsValid() || !Source.IsValid())
			{
				return false;
			}
			while(DDERR_WASSTILLDRAWING == p_Surface->Blt((RECT*)&Dest, p_SrcImage->p_Surface, (RECT*)&Source, DDBLT_KEYSRC, NULL));
			break;
		}

		//Espelho esquerda-direita
		case NGLMIRROR_LEFTRIGHT:
		{
			ddbltfx.dwDDFX			= DDBLTFX_MIRRORLEFTRIGHT;


			int iSrcWidth     = p_SrcFrame->GetWidth();
			int iSrcHeight		= p_SrcFrame->GetHeight();


			if(p_DestFrame->iLeft + iSrcWidth > (int)Size.fx )
			{
				Source.iLeft	  += p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
				Dest.iRight -= p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
			}

			if(p_DestFrame->iTop + iSrcHeight > (int)Size.fy  )
			{
				Source.iBottom	  -= p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
				Dest.iBottom	-= p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
			}

			if(p_DestFrame->iTop < 0)
			{
				Source.iTop		-= (int)(((float)p_DestFrame->iTop)*fDifY);
				Dest.iTop	-= p_DestFrame->iTop;
			}

			if(p_DestFrame->iLeft < 0)
			{
				Source.iRight		+= (int)(((float)p_DestFrame->iLeft)*fDifX);
				Dest.iLeft		-= p_DestFrame->iLeft;
			}

			if(Dest.IsValid() && Source.IsValid())
			{
				while(DDERR_WASSTILLDRAWING == p_Surface->Blt( (RECT*)&Dest, p_SrcImage->p_Surface, (RECT*)&Source, DDBLT_DDFX|DDBLT_KEYSRC , &ddbltfx )); 
			}
			break;
		}
		//Espelho cima-baixo
		case NGLMIRROR_UPDOWN:
		{
			ddbltfx.dwDDFX			= DDBLTFX_MIRRORUPDOWN;

			int iSrcWidth     = p_SrcFrame->iRight  - p_SrcFrame->iLeft;
			int iSrcHeight		= p_SrcFrame->iBottom - p_SrcFrame->iTop;

			if(p_DestFrame->iLeft + iSrcWidth > (int)Size.fx )
			{
				Source.iRight  -= p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
				Dest.iRight -= p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
			}

			if(p_DestFrame->iTop + iSrcHeight > (int)Size.fy )
			{
				Source.iTop	    += p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
				Dest.iBottom	-= p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
			}

			if(p_DestFrame->iTop < 0)
			{
				Source.iBottom	+= p_DestFrame->iTop;
				Dest.iTop		-= p_DestFrame->iTop;
			}

			if(p_DestFrame->iLeft < 0)
			{
				Source.iLeft			-= p_DestFrame->iLeft;
				Dest.iLeft		-= p_DestFrame->iLeft;
			}



			if(Dest.IsValid() && Source.IsValid())
			{
				while(DDERR_WASSTILLDRAWING == p_Surface->Blt( (RECT*)&Dest, p_SrcImage->p_Surface, (RECT*)&Source, DDBLT_DDFX  | DDBLT_KEYSRC , &ddbltfx )); 
			}

			break;
		}
		//Esquerda-direita
		//Cima-baixo
		case NGLMIRROR_UPDOWN | NGLMIRROR_LEFTRIGHT:
		{
			ddbltfx.dwDDFX			= DDBLTFX_MIRRORUPDOWN | DDBLTFX_MIRRORLEFTRIGHT;

			int iSrcWidth     = p_SrcFrame->iRight  - p_SrcFrame->iLeft;
			int iSrcHeight		= p_SrcFrame->iBottom - p_SrcFrame->iTop;


			if(p_DestFrame->iLeft + iSrcWidth > (int)Size.fx )
			{
				Source.iLeft	  += p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
				Dest.iRight -= p_DestFrame->iLeft + iSrcWidth - (int)Size.fx;
			}

			if(p_DestFrame->iTop + iSrcHeight > (int)Size.fy )
			{
				Source.iTop	    += p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
				Dest.iBottom	-= p_DestFrame->iTop + iSrcHeight - (int)Size.fy;
			}

			if(p_DestFrame->iTop < 0)
			{
				Source.iBottom	+= p_DestFrame->iTop;
				Dest.iTop		-= p_DestFrame->iTop;
			}

			if(p_DestFrame->iLeft < 0)
			{
				Source.iRight		+= p_DestFrame->iLeft;
				Dest.iLeft		-= p_DestFrame->iLeft;
			}


			if(Dest.IsValid() && Source.IsValid())
			{
				while(DDERR_WASSTILLDRAWING == p_Surface->Blt( (RECT*)&Dest, p_SrcImage->p_Surface, (RECT*)&Source, DDBLT_DDFX |DDBLT_KEYSRC , &ddbltfx )); 
			}
			break;
		}
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Clear(unsigned int uiColor)
// Desc: Pinta a surface com a cor fornecida
// Pams: cor
//---------------------------------------------------------------------------- 
void CNGLImage::Clear(unsigned int uiColor)
{
	DDBLTFX ddbltfx;
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize      = sizeof(ddbltfx);
	ddbltfx.dwFillColor = ConvertGDIColor(uiColor);

	//espera caso o DirectDraw ainda esteja desenhando
	while(DDERR_WASSTILLDRAWING == p_Surface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL , &ddbltfx));
}

//---------------------------------------------------------------------------- 
// Nome: ConvertGDIColor(unsigned int uiColor)
// Desc: Converte um cor GDI para uma cor compativel com a surface
// Pams: cor GDI
//---------------------------------------------------------------------------- 
unsigned int CNGLImage::ConvertGDIColor(unsigned int uiColor)
{
	unsigned int uiSurfaceColor;
	DDSURFACEDESC	SurfaceDesc;
	memset(&SurfaceDesc,0,sizeof(SurfaceDesc));
	SurfaceDesc.dwSize = sizeof(SurfaceDesc);
	SurfaceDesc.dwFlags = DDSD_PIXELFORMAT;

	p_Surface->GetSurfaceDesc(&SurfaceDesc);
	switch(SurfaceDesc.ddpfPixelFormat.dwRGBBitCount)
	{
		case 24:
		case 32:
		{
      uiSurfaceColor = GetRValue(uiColor)<<16 | GetGValue(uiColor) << 8 | GetBValue(uiColor);
			break;
		}
		case 16:
		{
			//teste para surfaces 555
			if(SurfaceDesc.ddpfPixelFormat.dwRBitMask == 0x00007c00 && 
				 SurfaceDesc.ddpfPixelFormat.dwGBitMask == 0x000003e0 &&
				 SurfaceDesc.ddpfPixelFormat.dwBBitMask == 0x0000001f)
			{
	      uiSurfaceColor = ((GetRValue(uiColor)>>3) & 0x1f)<<11 | ((GetGValue(uiColor)>>3) & 0x1f) << 5 | ((GetBValue(uiColor)>>3) & 0x1f);
			}
			else
			{
				//é 565
				unsigned int uiR = GetRValue(uiColor); 
				unsigned int uiG = GetGValue(uiColor);
				unsigned int uiB = GetBValue(uiColor);
	      uiSurfaceColor = ((GetRValue(uiColor)>>3) & 0x1f)<<11 | ((GetGValue(uiColor)>>2) & 0x3f) << 5 | ((GetBValue(uiColor)>>3) & 0x1f);
			}
			break;
		}
	}
	return uiSurfaceColor;
}

//---------------------------------------------------------------------------- 
// Nome: SetFrameSize(const CNGLVector & cSizePam)
// Desc: Ajusta o tamannho do Frame para esta imagem
// Pams: Tamanho do frame
//---------------------------------------------------------------------------- 
void CNGLImage::SetFrameSize(const CNGLVector & cSizePam)
{
	if(FrameSize != cSizePam)
	{
		FrameSize = cSizePam;
		FrameSize.fx = (FrameSize.fx > Size.fx)? Size.fx : FrameSize.fx;
		FrameSize.fy = (FrameSize.fy > Size.fy)? Size.fy : FrameSize.fy;
		ClearFrames();
		if(FrameSize.fx >= 1.0f && FrameSize.fy >= 1.0f)
		{
			int iSizeX = ((int)Size.fx)/((int)FrameSize.fx);
			int iSizeY = ((int)Size.fy)/((int)FrameSize.fy);

			for(int j = 0; j < iSizeY; j++)
			{
				for(int i = 0; i < iSizeX; i++)
				{
					CNGLFrame *p_Frame = new CNGLFrame();
					p_Frame->iTop			= j*(int)FrameSize.fy;
					p_Frame->iBottom	= (j+1)*(int)FrameSize.fy;
					p_Frame->iLeft		= i*(int)FrameSize.fx;
					p_Frame->iRight		= (i+1)*(int)FrameSize.fx;
					Frames.push_back(p_Frame);
				}
			}
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: ClearFrames(void)
// Desc: limpa os frames da imagem
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLImage::ClearFrames(void)
{
	for(int i = (int)Frames.size()-1; i >=0; i--)
	{
		delete Frames[i];
	}
	Frames.clear();
}

//---------------------------------------------------------------------------- 
// Nome: DrawImage(void)
// Desc: Pinta uma imagem sobre a outra
// Pams: posição no destino, imagem fonte, numero do frame na imagem fonte
//---------------------------------------------------------------------------- 
bool CNGLImage::DrawImage(const CNGLVector &cPosition, CNGLImage *p_SrcImage, int iFrame,Byte byMirror)
{
	if((iFrame < 0) || (iFrame >= (int)p_SrcImage->Frames.size()))
	{
		return false;
	}
	CNGLFrame Source = *p_SrcImage->Frames[iFrame];
	CNGLFrame Dest;
	Dest.iLeft		= (int)cPosition.fx;
	Dest.iTop			= (int)cPosition.fy;
	Dest.iBottom	= Dest.iTop  + (int)p_SrcImage->FrameSize.fy;
	Dest.iRight	  = Dest.iLeft + (int)p_SrcImage->FrameSize.fx;

	return DrawImage(&Dest,p_SrcImage,&Source,byMirror);
}
