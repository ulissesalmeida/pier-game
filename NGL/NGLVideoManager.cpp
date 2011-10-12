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

#include "NGLvideomanager.h"
#include "ddraw.h"
#include "NGLMain.h"
//---------------------------------------------------------------------------- 
// Nome: CNGLVideoManager(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLVideoManager::CNGLVideoManager(void)
{
	//resolu��o padr�o de 640x480
	//voc� pode alterar esses valores (ex.: 800x600, 1024x768, etc.)
	VideoSize.fx								= 640.0f;
	VideoSize.fy								= 480.0f;

	//como padr�o, o jogo come�ar� em janela
	bFullScreen									= false;
	//ponteiro de refer�ncia para a principal classe da NGL
	pr_Main											= NULL;
	//objeto do DirectDraw a ser criado
	p_DDraw											= NULL;

	//Os ponteiros de refer�ncia do v�deo do FrontBuffer e BackBuffer
	//recebem o endere�o deste objeto (this)
	FrontBuffer.pr_VideoManager = this;
	BackBuffer.pr_VideoManager	= this;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLVideoManager(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLVideoManager::~CNGLVideoManager(void)
{
	//libera os recursos da classe
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o video manager
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLVideoManager::Release(void)
{
	string str;
	//deleta imagens lidas
	for(int i = (int)Images.size()-1; i >= 0; i--)
	{
		if(Images[i])
		{
			str = "Undeleted Image: ";
			str += Images[i]->FileName;
			str += "\n";
			OutputDebugString(str.c_str());
			delete Images[i];
			Images.erase(Images.begin()+i);
			break;
		}
	}
	Images.clear();

	//libera back e frontbuffer
	//libera objeto do DirectDraw
	if(p_DDraw)
	{
		BackBuffer.Release();
		FrontBuffer.Release();
		p_DDraw->Release();
		p_DDraw = NULL;
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize()
// Desc: inicializa o video manager
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLVideoManager::Initialize()
{
	//inicializa o direct draw
	if(FAILED(DirectDrawCreate(NULL,&p_DDraw,NULL)))
	{
		return false;
	}

	if(!bFullScreen)
	{
		//Ajusta estilo da janela
		SetWindowLong((HWND)pr_Main->pr_Wnd,GWL_STYLE,WS_CAPTION|WS_SYSMENU|WS_POPUP|WS_VISIBLE);

		//Ajusta cooperative level
		if(FAILED(p_DDraw->SetCooperativeLevel((HWND)pr_Main->pr_Wnd,DDSCL_NORMAL)))
		{
			p_DDraw->Release();
			p_DDraw = NULL;
			return false;
		}
		//Cria o Front Buffer
		if(!FrontBuffer.CreateFrontBuffer())
		{
			return false;
		}

		//Cria o Back Buffer
		if(!BackBuffer.CreateBackBuffer())
		{
			return false;
		}

		//Cria o directdraw clipper no front buffer
		//(somente quando o jogo est� em janela!)
		if(!FrontBuffer.CreateClipper())
		{
			return false;
		}
	}
	else
	{
		//Ajusta estilo da janela
		SetWindowLong((HWND)pr_Main->pr_Wnd,GWL_STYLE,WS_POPUP|WS_VISIBLE);
		
		//Ajusta o cooperative level
		if(FAILED(p_DDraw->SetCooperativeLevel((HWND)pr_Main->pr_Wnd,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)))
		{
			p_DDraw->Release();
			p_DDraw = NULL;
			return false;
		}
		//Ajusta o modo de v�deo
		if(FAILED(p_DDraw->SetDisplayMode((int)VideoSize.fx,(int)VideoSize.fy,16)))
		{
			p_DDraw->Release();
			p_DDraw = NULL;
			return false;
		}
		//Cria o Front Buffer
		if(!FrontBuffer.CreateFrontBuffer())
		{
			return false;
		}

		//Cria o Back Buffer
		if(!BackBuffer.CreateBackBuffer())
		{
			return false;
		}
	}
	
	//Atualiza o Frame da janela
	UpdateFrame();
	
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: LoadImage(const char * cp_chFileName)
// Desc: roda uma imagem e retorna seu ponteiro
// Pams: nome do arquivo
//---------------------------------------------------------------------------- 
CNGLImage* CNGLVideoManager::LoadImage(const char * cp_chFileName)
{
	//tenta encontrar uma imagem j� lida
	for(int i = (int)Images.size()-1; i>=0; i--)
	{
		//Se j� existe
		if(!Images[i]->FileName.compare(cp_chFileName))
		{
			//Adiciona uma refer�ncia
			Images[i]->sReferences++;
			//Retorna a imagem
			return Images[i];
		}
	}

	//Se n�o existe
	//Aloca a imagem
	CNGLImage *p_Image = new CNGLImage();
	if(p_Image)
	{
		//Roda do arquivo
		p_Image->pr_VideoManager = this;
		if(!p_Image->LoadFromFile(cp_chFileName))
		{
			delete p_Image;
			return NULL;
		}

		//Adiciona a lista
		Images.push_back(p_Image);

		//retorna a imagem
		return p_Image;
	}

	return NULL;
}

//---------------------------------------------------------------------------- 
// Nome: DeleteImage(CNGLImage** p_Image)
// Desc: deleta a imagem
// Pams: Endere�o do ponteiro da imagem a ser deletada
//---------------------------------------------------------------------------- 
bool CNGLVideoManager::DeleteImage(CNGLImage** p_Image)
{
	if(p_Image && *p_Image)
	{
		//procura pela imagem na lista
		for(int i = (int)Images.size()-1; i >= 0; i--)
		{
			if(Images[i] == *p_Image)
			{
				if(Images[i]->sReferences > 0)
				{
					Images[i]->sReferences--;
				}
				else
				{
					(*p_Image)->Release();
					delete *p_Image;
					Images.erase(Images.begin()+i);
				}
				*p_Image = NULL;
				return true;
			}
		}
	}

	return false;
}

//---------------------------------------------------------------------------- 
// Nome: Present(void)
// Desc: Desenha o backbuffer no front buffer/ ou faz flip se fullsecreen
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLVideoManager::Present(void)
{
  HRESULT hr = 0;

	while(1)
	{
		if(bFullScreen)
		{
			//faz o filp
			hr = FrontBuffer.p_Surface->Flip(NULL,0);
		}
		else
		{
			//pinta o backbuffer no front buffer
			hr = FrontBuffer.p_Surface->Blt((RECT*)&WindowFrame,BackBuffer.p_Surface,NULL,0,NULL);
		}
		
		if( hr == DDERR_SURFACELOST )
		{
			FrontBuffer.p_Surface->Restore();
			BackBuffer.p_Surface->Restore();
			ReloadImages();
			return false;
			break;
		}
		
		if( hr != DDERR_WASSTILLDRAWING )
		{
			return false;
			break;
		}
	}
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: ReloadImages(void)
// Desc: roda novamente as imagens
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLVideoManager::ReloadImages(void)
{
	int iSize = (int)Images.size();
	for(int i =0; i < iSize; i++)
	{
		if(Images[i])
		{
			Images[i]->Reload();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: UpdateFrame(void)
// Desc: Atualiza o frame da janela
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLVideoManager::UpdateFrame(void)
{
	RECT rct;
	if(!bFullScreen)
  {
		if(IsZoomed((HWND)pr_Main->pr_Wnd))
		{
			GetWindowRect((HWND)pr_Main->pr_Wnd, (RECT*)&rct);
		}
		else
		{
			GetClientRect((HWND)pr_Main->pr_Wnd, (RECT*)&rct);
			ClientToScreen((HWND)pr_Main->pr_Wnd, (POINT*)&rct);
			ClientToScreen((HWND)pr_Main->pr_Wnd, (POINT*)&rct + 1);
		}
	}
  else
  {
    SetRect((RECT*)&rct, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
  }
	WindowFrame = *((CNGLFrame*)&rct);
}


//---------------------------------------------------------------------------- 
// Nome: SetVideoMode(bool bFullscreen, const CNGLVector & NewSize)
// Desc: configura o modo de v�deo
// Pams: flag the fullscreen/window tamanho da tela
//---------------------------------------------------------------------------- 
void CNGLVideoManager::SetVideoMode(bool bFullscreenPam, const CNGLVector & NewSize)
{
	if(bFullscreenPam != bFullScreen || VideoSize != NewSize)
	{
		int iSize = (int)Images.size();
		for(iSize--; iSize >=0; iSize--)
		{
			Images[iSize]->Release();
		}
		BackBuffer.Release();
		FrontBuffer.Release();
		p_DDraw->Release();
		bFullScreen = bFullscreenPam;
		VideoSize		= NewSize;
    Initialize();
		ReloadImages();
		//centers the window if changing to windo wmode

		UpdateFrame();
		if(!bFullScreen)
		{
			SetWindowPos((HWND)pr_Main->pr_Wnd,HWND_NOTOPMOST,WindowFrame.iLeft,WindowFrame.iTop,WindowFrame.GetWidth(),WindowFrame.GetHeight(),SWP_FRAMECHANGED);
		}
		UpdateFrame();
	}
}
