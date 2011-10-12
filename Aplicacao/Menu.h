/*NGL - Game Development Library 
Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

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
#ifndef _CMENU_
#define _CMENU_

//Includes
#include "NGLSprite.h"

class CLevel;

//!Define número de botões do menu principal como 3.
#define NUM_MAINITEMS			3
//!Define número de botões do menu de opções como 2.
#define NUM_OPTIONSITEMS	2
//!Nome do arquivo onde as opções devem ser salvas e lidas.
#define OPTIONS_FILE			"options.dat"

//Ordem dos itens no menu principal
#define IDX_NEW_GAME	0
#define IDX_OPTIONS		1
#define IDX_QUIT		2

//Ordem dos itens no menu opções
#define IDX_FULLSCREEN	0
#define IDX_BACK		1

//String com as localizações dos arquivos
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

//! margins dos botões do menu
#define MARGIN_TOP_FIRST_MENU_ITEM 130.0f
#define MARGIN_TOP_MENU_TIEM 30.0f

//! Classe CMenu
/*!
	Responsável pelo tratamento do Menu Principal e de Opções.
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
	//!Layer onde estão os botões do menu principal.
	CNGLLayer *p_LayMain;
	//!Layer onde estão os botões do menu de opções.
	CNGLLayer *p_LayOptions;
	//!Estado atual da máquina de estados.
	MenuState State;
	//!Vetor dos sprites do menu principal (botões).
	CNGLSprite *p_SprMain[NUM_MAINITEMS];
	//!Vetor dos sprites do menu de opções (botões).
	CNGLSprite *p_SprOptions[NUM_OPTIONSITEMS];
	//!Sprite que representa o cursor do mouse.
	CNGLSprite *p_SprMouse;
	//!Som para quando o mouse passa em cima de um botão (MouseOver).
	CNGLSound *p_SndMouseOver;
	//!Som de clique do mouse em um botão.
	CNGLSound *p_SndMouseClick;

private:
	/*!
		Trata o estado MS_MAIN. É o estado do menu principal.
	*/
	void OnMain(void);
	/*!
		Trata o estado MS_OPTIONS. É o estado do menu de opções.
	*/
	void OnOptions(void);
	/*!
		Testa se o mouse está em cima do sprite (colisão mouse X sprite).
		\param pr_Sprite: sprite a ser testado.
		\return verdadeiro se houver colisão entre mouse e sprite, falso caso contrário.
	*/
	bool MouseOver(CNGLSprite* pr_Sprite);
	/*!
		Grava o arquivo de opções do jogo.
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
		Configura a animação padrão de botões dos sprites
		by Ulisses
		\param sprites: Array de Sprites que se deseja animar
		\param size: Tamanho do sprite 
	*/
	void ConfigureSpritesAnimation(CNGLSprite* sprite[], short size);

	/*!
		Configura a animação do sprite quando o mouse estiver por cima dele
		by Ulisses
		\param sprite: sprite
		\param mouseOver: true se o mouse estiver sobre o sprite
	*/
	void MouseOverSpriteAnimation(CNGLSprite* sprite, bool mouseOver);

public:
	//!Referência para a classe CLevel.
	CLevel *pr_Level;
	//!Indica se o jogo está rodando
	bool bInGame;

	/*!
		Construtor padrão
	*/
	CMenu(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CMenu(void);

	/*!
		Finaliza a classe liberando layers e sprites criados no Initialize().
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	
	/*!
		Cria as layers, sprites e sons necessários para o menu.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Initialize(void);

	/*!
		Executa o menu de acordo com o seu estado.
	*/
	void Execute(void);
	/*!
		Muda o estado da máquina de estados da CMenu.
		\param NewState: novo estado da máquina.
	*/
	void ChangeState(CMenu::MenuState NewState);
	/*!
		Desenha o cursor do mouse na tela. Ela deve ser chamada na CLevel::Draw()
		para que se garanta que o cursor seja a última imagem a ser desenhada.
	*/
	void DrawMouse(void);
	/*!
		Lê as opções do jogo de um arquivo.
		\param: pr_Main: referência para CNGLMain, pois as opções devem ser lidas antes da NGL inicializar.
	*/
	void LoadOptions(CNGLMain *pr_Main);
	/*!
		Mostra ou esconde o menu.
	*/
	void Show(bool bShow);
	/*!
		Retorna o estado corrente do menu.
		\return CMenu::MenuState com o estado atual da máquina.
	*/
	CMenu::MenuState GetState(void);
};

#endif