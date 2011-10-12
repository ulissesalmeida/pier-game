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
#include "NGLmain.h"
#include "NGLmain.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLMain(void)
// Desc: constructor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLMain::CNGLMain(void)
{
	pr_CurrentScene						= NULL;
	pr_Wnd								= NULL;
	pr_Inst								= NULL;
	bEnded								= false;
	bPaused								= false;
	VideoManager.pr_Main  = this;
	InputManager.pr_Main  = this;
	SoundManager.pr_Main  = this;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLMain(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLMain::~CNGLMain(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a NGL Main 
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLMain::Release(void)
{
	//setando cena corrente como nula
	if(pr_CurrentScene)
	{
		pr_CurrentScene->Release();
		pr_CurrentScene = NULL;
	}
	
	//liberando video
	VideoManager.Release();
	
	//liberando entradas
	InputManager.Release();

	//liberando som
	SoundManager.Release();

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize()
// Desc: Inicializa os dispositivos da NGL: gr�ficos, teclado, mouse e som. Ajusta a primeira cena como corrente.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLMain::Initialize()
{
	//inicializando video
	if(!VideoManager.Initialize())
	{
		return false;
	}

	//inicializando entradas
	if(!InputManager.Initialize())
	{
		return false;
	}

	//inicializa o som
	SoundManager.Initialize();

	//ajusta a primeira cena como corrente, caso nenhuma esteja ajustada
	if(!pr_CurrentScene)
	{
		SetCurrentScene(0);
	}
	
	return true;	
}

//---------------------------------------------------------------------------- 
// Nome: ExitNGL()
// Desc: finaliza a execu��o da NGL
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::ExitNGL()
{
	bEnded = true;
}

//---------------------------------------------------------------------------- 
// Nome: Ended()
// Desc: retorna verdadeiro se a NGL terminou sua execu��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLMain::Ended()
{
	if(bEnded)
	{
		Release();
	}

	return bEnded;
}

//---------------------------------------------------------------------------- 
// Nome: Loop(void)
// Desc: la�o principal do jogo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::Loop(void)
{
	//l� entradas
	InputManager.Read();

	//atualiza tempo
	TimeHandler.Update();

	//atualiza Som (Streamming)
	SoundManager.Update();

	//limpa o backbuffer
	VideoManager.BackBuffer.Clear(RGB(255,255,255));

	//desenha cena
	if(pr_CurrentScene)
	{
		pr_CurrentScene->Draw();
		
		//somente atualiza o jogo se ele n�o estiver pausado
		if(!bPaused)
		{
			pr_CurrentScene->Update();
			pr_CurrentScene->Execute();
		}
	}
	
	//mostra imagens
	VideoManager.Present();
}

//---------------------------------------------------------------------------- 
// Nome: AddScene(CNGLScene* pr_NewScene)
// Desc: Adiciona uma cena � NGL.
// Pams: ponteiro para a nova cena
//---------------------------------------------------------------------------- 
void CNGLMain::AddScene(CNGLScene* pr_NewScene)
{
	if(pr_NewScene)
	{
		//adiciona a cena � lista
		Scenes.push_back(pr_NewScene);
	}
}

//---------------------------------------------------------------------------- 
// Nome: SetCurrentScene(int iIndex)
// Desc: Atribui uma nova cena corrente da NGL, de acordo com o �ndice. Caso j� exista uma cena corrente configurada, ela � liberada e a nova � inicializada.
// Pams: �ndice da nova cena
//---------------------------------------------------------------------------- 
void CNGLMain::SetCurrentScene(int iIndex)
{
	if(iIndex < (int)Scenes.size())
	{
		//pega a nova cena a ser ajustada
		CNGLScene *pr_NewScene = Scenes[iIndex];
		if(pr_NewScene)
		{	
			//se j� existia uma cena ativa, ent�o libera ela.
			if(pr_CurrentScene)
			{
				pr_CurrentScene->Release();
				pr_CurrentScene = NULL;
			}

			//atribui a nova cena corrente
			pr_CurrentScene = pr_NewScene;
			
			//atribui o main � cena
			pr_CurrentScene->pr_Main = this;

			//inicializa a nova cena
			if(!pr_CurrentScene->Initialize())
			{
				pr_CurrentScene->Release();
				pr_CurrentScene = NULL;
			}
			TimeHandler.Reset();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Pause(void)
// Desc: Pausa o jogo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::Pause(void)
{
	bPaused = true;
}

//---------------------------------------------------------------------------- 
// Nome: Resume(void)
// Desc: Continua o jogo ap�s uma pausa.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLMain::Resume(void)
{
	if(bPaused)
	{
		TimeHandler.Reset();
		bPaused = false;
	}
}