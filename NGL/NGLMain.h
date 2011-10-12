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
#ifndef _CNGLMAIN_
#define _CNGLMAIN_

#include "NGLObject.h"
#include "NGLVideoManager.h"
#include "NGLInputManager.h"
#include "NGLTimeHandler.h"
#include "NGLScene.h"
#include "NGLSoundManager.h" 

//!  Classe CNGLMain
/*!
  Esta classe � respons�vel por iniciar o jogo a partir de uma janela Windows
*/
class CNGLMain :	public CNGLObject
{
	private:

		//!Indica a finaliza��o da NGL.
		bool bEnded;

		//!Lista de cenas do jogo.
		vector <CNGLScene *> Scenes;

		//!Refer�ncia para a cena corrente do jogo.
		CNGLScene *pr_CurrentScene;

		//!Indica se o jogo est� pausado.
		bool bPaused;

	public:

		//!Refer�ncia para a janela Windows.
		void *pr_Wnd;

		//!Refer�ncia para a inst�ncia da aplica��o Windows.
		void *pr_Inst;
		
		//!Gerenciador de v�deo.
		CNGLVideoManager VideoManager;

		//!Gerenciador de dispositivos de entrada.
		CNGLInputManager InputManager;

		//!Gerenciador de som.
		CNGLSoundManager SoundManager;

		//!Gerenciador de tempo da NGL.
		CNGLTimeHandler	 TimeHandler;

	public:
		
		/*!
			Informa se a NGL j� finalizou sua execu��o.
			\return verdadeiro se j� finalizou, caso contr�rio retorna falso.
		*/
		bool Ended();

		/*!
			Encerra o uso da NGL.
		*/
		void ExitNGL();

		/*!
			Inicializa os dispositivos da NGL: gr�ficos, teclado, mouse e som. Ajusta a primeira cena como corrente.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool Initialize();

		/*!
			Construtor padr�o.
		*/
		CNGLMain(void);

		/*!
			Destrutor padr�o.
		*/
		virtual ~CNGLMain(void);

		/*!
			Finaliza a classe.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool Release(void);

		/*!
			Loop principal do jogo. Essa rotina deve ser chamada a cada la�o da aplica��o.
		*/
		void Loop(void);

		/*!
			Adiciona uma cena � NGL.
			\param pr_Scene: Ponteiro da nova cena corrente.
		*/
		void AddScene(CNGLScene* pr_Scene);
		
		/*!
			Atribui uma nova cena corrente da NGL, de acordo com o �ndice. Caso j� exista uma cena corrente configurada, ela � liberada e a nova � inicializada.
			\param iIndex: �ndice da nova cena.
		*/
		void SetCurrentScene(int iIndex);
		
		/*!
			Retorna a cena corrente do jogo.
			\return Ponteiro para a cena corrente.
		*/
		inline CNGLScene* GetCurrentScene() { return pr_CurrentScene; };
		
		/*!
			Pausa o jogo. A pausa tranca a execu��o do jogo, mas n�o a renderiza��o.
		*/
		void Pause(void);

		/*!
			Continua o jogo ap�s uma pausa.
		*/
		void Resume(void);

		/*!
			Retorna se o jogo est� pausado.
			\return verdadeiro se o jogo estiver pausado, sen�o retorna falso.
		*/
		inline bool IsPaused(void) { return bPaused; };
};
#endif