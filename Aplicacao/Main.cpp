/*NGL - Game Development Library 
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

#include <windows.h>
#include "NGLMain.h"
#include "Level.h"
#include "Presentation.h"

//global que indica se a janela do jogo est� ativa
bool			g_bActive		= true;
//ponteiro global para a classe principal da NGL (usado pela rotina WindowProc)
CNGLMain	*g_pr_Main	= NULL;

//-------------------------------------------------
// Nome: WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
// Desc: Essa fun��o trata as mensagens do Windows recebidas pela aplica��o
//-------------------------------------------------
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_ERASEBKGND:
		case WM_NCPAINT:
		case WM_SYNCPAINT:
		{
			if(g_pr_Main->VideoManager.bFullScreen)
			{
				//se tiver em tela cheia, retorna 0 para essas tr�s mensagens
				//(evita "flick" ou "tremedeira" no jogo em tela cheia)
				return 0;
			}
			break;
		}
		case WM_MOUSEMOVE:
		{
			//atualiza posi��o do mouse na NGL
			g_pr_Main->InputManager.SetWindowsMousePos(CNGLVector((float)LOWORD(lParam),(float)HIWORD(lParam)));
			break;
		}
		case WM_MOVE:
		{
			//se a janela foi movida, atualizar o frame do v�deo
			(g_pr_Main)? g_pr_Main->VideoManager.UpdateFrame() : 0;
			break;
		}
		case WM_PAINT:
		{
			//se a janela n�o est� ativa
			if(g_pr_Main && !g_bActive)
			{
				//pega o estado de pausa do jogo
				bool bIsPaused = g_pr_Main->IsPaused();
				//o c�digo a seguir pinta o jogo com ele pausado, pois n�o deve
				//haver atualiza��es de tempo e dos objetos
				if(!bIsPaused)
				{
					//pausa o jogo (caso ele n�o estivesse pausado)
					g_pr_Main->Pause();
				}
				//desenha o jogo
				g_pr_Main->Loop();
				if(!bIsPaused)
				{
					//continua o jogo (caso ele n�o estivesse pausado)
					g_pr_Main->Resume();
				}
			}
			return DefWindowProc(hwnd,msg,wParam,lParam);
			break;
		}
		case WM_GETDLGCODE:
		{
			//diz para o Windows que essa aplica��o requer teclado
			return DLGC_WANTALLKEYS;
			break;
		}
		case WM_SETCURSOR:
		{
			//o trecho abaixo faz o cursor do mouse do Windows desaparecer
			//quando o mouse estiver em "cima" da janela (estamos usando cursor via NGL)
			SetCursor(NULL);
			return TRUE;
			break;
		}
		case WM_SIZE:
		{
			//se a janela foi redimensionada, atualizar o frame do v�deo
			(g_pr_Main)? g_pr_Main->VideoManager.UpdateFrame() : 0;
			return 0;
			break;
		}
		case WM_ACTIVATE:
		{
			//essa mensagem informa que a aplica��o ganhou ou perdeu foco
			if(LOWORD(wParam) == WA_INACTIVE)
			{
				//aplica��o perdeu foco
				g_bActive = false;
			}
			else
			{
				if(HIWORD(wParam) == 0)
				{
					//aplica��o ganhou foco.
					//deve-se Resetar o tempo da NGL para os objetos do jogo
					//mantenham-se na mesma posi��o de quando a janela foi desativada.
					(g_pr_Main) ? g_pr_Main->TimeHandler.Reset() : 0;
					g_bActive = true;
				}
			}
			break;
		}
		case WM_EXITMENULOOP:
		{
			//quando sai do menu da janela
			(g_pr_Main) ? g_pr_Main->TimeHandler.Reset() : 0;
			break;
		}
		case WM_EXITSIZEMOVE:
		{
			//quando p�ra de mover ou redimensionar a janela
			(g_pr_Main) ? g_pr_Main->TimeHandler.Reset() : 0;
			break;
		}
		case WM_SYSCOMMAND:
		{
			//Previne contra movimenta��o/redimensionamento/maximiza��o
			//e desligamento do monitor (protetor de tela) da janela
			switch( wParam )
			{
				case SC_MOVE:
				case SC_SIZE:
				case SC_MAXIMIZE:
				case SC_MONITORPOWER:
				return TRUE;
			}
			break;
		}
		case WM_CLOSE:
		{
			//caso seja clicado o "X" da janela ou ALT+F4 deve-se fechar 
			//a aplica��o.
			PostQuitMessage(0);
			return 0;
			break;
		}
	}

	//chama o tratamento padr�o de mensagens
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

//---------------------------------------------------------------------------- 
// Nome: WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
// Desc: Fun��o de entrada da aplica��o
//---------------------------------------------------------------------------- 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CNGLMain	Main;												//objeto principal da NGL
	WNDCLASS	winclass;										//descritora da classe de janela
	MSG				msg;												//estrutura de mensagem do windows
	HWND			hWnd;												//handle da janela da aplica��o
	char			chName[11] = "NGL_Window";	//nome da janela/aplica��o

	//ajusta o ponteiro global da CNGLMain
	g_pr_Main = &Main;

	//colocar os par�metros da janela a ser criada
	winclass.style					= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc		= WindowProc;
	winclass.cbClsExtra			= 0;
	winclass.cbWndExtra			= 0;
	winclass.hInstance			= hInstance;
	winclass.hIcon					= NULL;
	winclass.hCursor				= NULL;
	winclass.hbrBackground	= CreateSolidBrush(RGB(0,0,0));
	winclass.lpszMenuName		= NULL; 
	winclass.lpszClassName	= chName;

	//registrando a classe
	if(!RegisterClass(&winclass))
	{
		return -1;
	}

	//ajustando dimnens�o do v�deo (640x480)
	Main.VideoManager.VideoSize = CNGLVector(640,480);
	//cria a janela principal do jogo, com a dimens�o ajustada acima
	if(!(hWnd = CreateWindowEx(0,chName,"NGL Game",WS_CAPTION|WS_SYSMENU|WS_POPUP|WS_VISIBLE,0,0,(int)Main.VideoManager.VideoSize.fx,(int)Main.VideoManager.VideoSize.fy,NULL,NULL,hInstance,NULL)))
	{
		//retorna se deu erro
		return -1;
	}

	//atribui inst�ncia e window handle da aplica��o (esses valores s�o usados pelo DirecX)
	Main.pr_Inst	= (void*)hInstance;
	Main.pr_Wnd		= (void*)hWnd;

	//cenas do jogo
	CLevel Level;
	CPresentation Presentation;

	//16.3.10.
	//ler arquivo de op��es do jogo para a NGL saber se 
	//deve iniciar em Janela ou Tela Cheia
	Level.Menu.LoadOptions(&Main);

	//adicionando duas cenas � NGL
	Main.AddScene(&Presentation);
	Main.AddScene(&Level);

	//inicializa o main
	if(!Main.Initialize())
	{
		//retorna se deu erro
		Main.Release();
		return -1;
	}

	//la�o de recebimento e encaminhamento de mensagens
	while(!Main.Ended())//enquanto NGL n�o terminou
	{		
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			//caso a mensagem seja de sa�da, terminar a aplica��o
			if(WM_QUIT == msg.message)
			{
				//chamada de sa�da da NGL
				Main.ExitNGL();
			}
			//encaminha mensagem para o WindowProc para ser tratada
			DispatchMessage(&msg);
		}
		
		//se a janela estiver ativa
		if(g_bActive)
		{
			//faz a atualiza��o da NGL
			Main.Loop();
		}
		else
		{
			//se a janela n�o est� ativa, deve-se sempre reinicializar o tempo do jogo
			Main.TimeHandler.Reset();
		}
	}
	
	DeleteObject(winclass.hbrBackground);
	ClipCursor(NULL);

	return 0;
}