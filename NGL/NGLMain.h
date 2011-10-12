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
  Esta classe é responsável por iniciar o jogo a partir de uma janela Windows
*/
class CNGLMain :	public CNGLObject
{
	private:

		//!Indica a finalização da NGL.
		bool bEnded;

		//!Lista de cenas do jogo.
		vector <CNGLScene *> Scenes;

		//!Referência para a cena corrente do jogo.
		CNGLScene *pr_CurrentScene;

		//!Indica se o jogo está pausado.
		bool bPaused;

	public:

		//!Referência para a janela Windows.
		void *pr_Wnd;

		//!Referência para a instância da aplicação Windows.
		void *pr_Inst;
		
		//!Gerenciador de vídeo.
		CNGLVideoManager VideoManager;

		//!Gerenciador de dispositivos de entrada.
		CNGLInputManager InputManager;

		//!Gerenciador de som.
		CNGLSoundManager SoundManager;

		//!Gerenciador de tempo da NGL.
		CNGLTimeHandler	 TimeHandler;

	public:
		
		/*!
			Informa se a NGL já finalizou sua execução.
			\return verdadeiro se já finalizou, caso contrário retorna falso.
		*/
		bool Ended();

		/*!
			Encerra o uso da NGL.
		*/
		void ExitNGL();

		/*!
			Inicializa os dispositivos da NGL: gráficos, teclado, mouse e som. Ajusta a primeira cena como corrente.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool Initialize();

		/*!
			Construtor padrão.
		*/
		CNGLMain(void);

		/*!
			Destrutor padrão.
		*/
		virtual ~CNGLMain(void);

		/*!
			Finaliza a classe.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool Release(void);

		/*!
			Loop principal do jogo. Essa rotina deve ser chamada a cada laço da aplicação.
		*/
		void Loop(void);

		/*!
			Adiciona uma cena à NGL.
			\param pr_Scene: Ponteiro da nova cena corrente.
		*/
		void AddScene(CNGLScene* pr_Scene);
		
		/*!
			Atribui uma nova cena corrente da NGL, de acordo com o índice. Caso já exista uma cena corrente configurada, ela é liberada e a nova é inicializada.
			\param iIndex: Índice da nova cena.
		*/
		void SetCurrentScene(int iIndex);
		
		/*!
			Retorna a cena corrente do jogo.
			\return Ponteiro para a cena corrente.
		*/
		inline CNGLScene* GetCurrentScene() { return pr_CurrentScene; };
		
		/*!
			Pausa o jogo. A pausa tranca a execução do jogo, mas não a renderização.
		*/
		void Pause(void);

		/*!
			Continua o jogo após uma pausa.
		*/
		void Resume(void);

		/*!
			Retorna se o jogo está pausado.
			\return verdadeiro se o jogo estiver pausado, senão retorna falso.
		*/
		inline bool IsPaused(void) { return bPaused; };
};
#endif