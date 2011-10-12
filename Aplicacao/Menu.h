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
#ifndef _CMENU_
#define _CMENU_

//Includes
#include "NGLSprite.h"

class CLevel;

//!Define n�mero de bot�es do menu principal como 3.
#define NUM_MAINITEMS			3
//!Define n�mero de bot�es do menu de op��es como 2.
#define NUM_OPTIONSITEMS	2
//!Nome do arquivo onde as op��es devem ser salvas e lidas.
#define OPTIONS_FILE			"options.dat"

//Ordem dos itens no menu principal
#define IDX_NEW_GAME	0
#define IDX_OPTIONS		1
#define IDX_QUIT		2

//Ordem dos itens no menu op��es
#define IDX_FULLSCREEN	0
#define IDX_BACK		1

//String com as localiza��es dos arquivos
#define PRESENTATION_BKG	"Surfaces/bkg_Presentation.bmp"
#define NEW_GAME_SPR		"Surfaces/btn_NewGame.bmp"
#define CONTINUE_SPR		"Surfaces/btn_Continue.bmp"
#define OPTIONS_SPR			"Surfaces/btn_Options.bmp"
#define QUIT_SPR			"Surfaces/btn_Quit.bmp"
#define FULLSCREEN_SPR		"Surfaces/btn_FullScreen.bmp"
#define BACK_SPR			"Surfaces/btn_Back.bmp"
#define CURSOR_SPR			"Surfaces/spr_Cursor.bmp"
#define MOUSE_OVER_WAV		"Sounds/sfx_MouseOver.wav"
#define MOUSE_CLICKED_WAV	"Sounds/sfx_MouseClicked.wav"

//! margins dos bot�es do menu
#define MARGIN_TOP_FIRST_MENU_ITEM 130.0f
#define MARGIN_TOP_MENU_TIEM 30.0f

//! Classe CMenu
/*!
	Respons�vel pelo tratamento do Menu Principal e de Op��es.
*/
class CMenu :	public CNGLObject
{
public:
	typedef enum eMenuState
	{
		MS_MAIN,
		MS_OPTIONS
	} MenuState;

private:
	//!Layer onde est�o os bot�es do menu principal.
	CNGLLayer *p_LayMain;
	//!Layer onde est�o os bot�es do menu de op��es.
	CNGLLayer *p_LayOptions;
	//!Estado atual da m�quina de estados.
	MenuState State;
	//!Vetor dos sprites do menu principal (bot�es).
	CNGLSprite *p_SprMain[NUM_MAINITEMS];
	//!Vetor dos sprites do menu de op��es (bot�es).
	CNGLSprite *p_SprOptions[NUM_OPTIONSITEMS];
	//!Sprite que representa o cursor do mouse.
	CNGLSprite *p_SprMouse;
	//!Som para quando o mouse passa em cima de um bot�o (MouseOver).
	CNGLSound *p_SndMouseOver;
	//!Som de clique do mouse em um bot�o.
	CNGLSound *p_SndMouseClick;

private:
	/*!
		Trata o estado MS_MAIN. � o estado do menu principal.
	*/
	void OnMain(void);
	/*!
		Trata o estado MS_OPTIONS. � o estado do menu de op��es.
	*/
	void OnOptions(void);
	/*!
		Testa se o mouse est� em cima do sprite (colis�o mouse X sprite).
		\param pr_Sprite: sprite a ser testado.
		\return verdadeiro se houver colis�o entre mouse e sprite, falso caso contr�rio.
	*/
	bool MouseOver(CNGLSprite* pr_Sprite);
	/*!
		Grava o arquivo de op��es do jogo.
	*/
	void SaveOptions(void);

	/*!
		Centraliza o Sprite em x
		by Ulisses
		\param sprite: Sprite que se deseja centralizar
		\param y: Altura em y desejada ao sprite
	*/
	void CentralizeSpriteInX(CNGLSprite* sprite, float y);

	/*!
		Centraliza o Sprites em x
		by Ulisses
		\param sprites: Array de Sprites que se deseja centralizar
		\param size: Tamanho do sprite 
	*/
	void CentralizeSpritesInX(CNGLSprite* sprite[], short size);

	/*!
		Configura a anima��o padr�o de bot�es dos sprites
		by Ulisses
		\param sprites: Array de Sprites que se deseja animar
		\param size: Tamanho do sprite 
	*/
	void ConfigureSpritesAnimation(CNGLSprite* sprite[], short size);

	/*!
		Configura a anima��o do sprite quando o mouse estiver por cima dele
		by Ulisses
		\param sprite: sprite
		\param mouseOver: true se o mouse estiver sobre o sprite
	*/
	void MouseOverSpriteAnimation(CNGLSprite* sprite, bool mouseOver);

public:
	//!Refer�ncia para a classe CLevel.
	CLevel *pr_Level;
	//!Indica se o jogo est� rodando
	bool bInGame;

	/*!
		Construtor padr�o
	*/
	CMenu(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CMenu(void);

	/*!
		Finaliza a classe liberando layers e sprites criados no Initialize().
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	
	/*!
		Cria as layers, sprites e sons necess�rios para o menu.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize(void);

	/*!
		Executa o menu de acordo com o seu estado.
	*/
	void Execute(void);
	/*!
		Muda o estado da m�quina de estados da CMenu.
		\param NewState: novo estado da m�quina.
	*/
	void ChangeState(CMenu::MenuState NewState);
	/*!
		Desenha o cursor do mouse na tela. Ela deve ser chamada na CLevel::Draw()
		para que se garanta que o cursor seja a �ltima imagem a ser desenhada.
	*/
	void DrawMouse(void);
	/*!
		L� as op��es do jogo de um arquivo.
		\param: pr_Main: refer�ncia para CNGLMain, pois as op��es devem ser lidas antes da NGL inicializar.
	*/
	void LoadOptions(CNGLMain *pr_Main);
	/*!
		Mostra ou esconde o menu.
	*/
	void Show(bool bShow);
	/*!
		Retorna o estado corrente do menu.
		\return CMenu::MenuState com o estado atual da m�quina.
	*/
	CMenu::MenuState GetState(void);
};

#endif