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
#ifndef _CLEVEL_
#define _CLEVEL_

//Includes
#include "NGLScene.h"
#include "Player.h"
#include "Item.h"
#include "Menu.h"
#include "Shot.h"
#include "Enemy.h"


//!N�mero de algarismos do placar.
#define NUM_ALGARISMS 5
#define NUMBERS_SPR "Surfaces/spr_Numbers.bmp"
#define LIVES_SPR "Surfaces/spr_Lives.bmp"
#define PAUSED_MSG "Surfaces/msg_Paused.bmp"
#define GAME_OVER_MSG "Surfaces/msg_GameOver.bmp"
#define CONGRATS_MSG "Surfaces/msg_Congrats.bmp"

//! Classe CLevel
/*!
	Classe principal do jogo, respons�vel pela m�quina de estados global do jogo, por criar e atualizar jogador, itens, inimigos e menus.
*/
class CLevel :	public CNGLScene
{
public:
	//enumerando estados da classe CLevel
	typedef enum eGameState
	{
		GS_MENU,
		GS_GAME,
		GS_PAUSE,
		GS_GAMEOVER,
		GS_CONGRATULATIONS
	} GameState; //tipo de dado definido pelo usu�rio que representa o estado da classe

private:
	//!Estado atual da FSM
	GameState State;
	//!Refer�ncia para o jogador
	CPlayer *pr_Player;
	//!Lista de itens
	vector <CItem*> ListItems;
	//!Lista de tiros
	vector <CShot*> ListShots;
	//!Sprites dos n�meros do placar (NUM_ALGARISMS = 5)
	CNGLSprite *p_SprNumbers[NUM_ALGARISMS];
	//!Vetor de sprites das vidas (NUM_LIVES = 3).
	CNGLSprite *p_SprLives[NUM_LIVES];
	//!Sprite com a mensagem "Jogo Pausado"
	CNGLSprite *p_MsgPaused;
	//!Sprite com a mensagem "Game Over"
	CNGLSprite *p_MsgGameOver;
	//!Sprite com a mensagem "Parab�ns! Voc� concluiu o jogo!"
	CNGLSprite *p_MsgCongrats;
	//!Sprite modelo para o tiro
	CNGLSprite *p_SprShot;
	//!Sprite modelo para a explos�o do tiro
	CNGLSprite *p_SprShotExplode;
	//!Sprite da moeda final
	CNGLSprite *p_SprCoin;
	//!Sprite da alavanca
	CNGLSprite *p_SprSwitch;
	//!Layer da interface
	CNGLLayer *p_LayInterface;
	//!Som da alavanca
	CNGLSound *p_SndSwitch;
	//!Som de congratula��es (final do jogo)
	CNGLSound *p_SndCongrats;
	//!M�sica do jogo
	CNGLSound *p_SndTrack;

public:

	//!Menu do jogo
	CMenu Menu;
	//!Layer principal da fase (cen�rio)
	CNGLLayer *p_LayLevel;
	//!Lista de personagens
	vector <CCharacter*> ListCharacters;

private:

	/*!
		Faz a cena "olhar" para o jogador, mantendo ele sempre centralizado na tela.
	*/
	void LookToPlayer(void);
	/*!
		Cria o jogador.
	*/
	void CreatePlayer(void);
	/*!
		Cria um item.
		\param Type: tipo do item.
		\param Position: posi��o do item.
	*/
	void CreateItem(CItem::ItemType Type, CNGLVector Position);
	/*!
		Inicializa layer e sprites de interface.
	*/	
	void InitializeInterface(void);
	/*!
		Atualiza os sprites de vida na tela.
	*/
	void UpdateScore(void);
	/*!
		Atualiza o placar do jogo na tela.
	*/
	void UpdateLives(void);

	/*!
		Trata do estado GS_GAMEOVER.
	*/	
	void OnGameOver(void);
	/*!
		Trata o estado GS_CONGRATULATIONS.
	*/	
	void OnCongratulations(void);
	/*!
		Trata o estado GS_MENU.
	*/	
	void OnMenu(void);
	/*!
		Trata o estado GS_GAME.
	*/	
	void OnGame(void);
	/*!
		Trata o estado GS_PAUSE.
	*/	
	void OnPause(void);

	/*!
		Desaloca os personagens.
	*/	
	void ReleaseCharacters(void);
	/*!
		Desaloca os itens.
	*/	
	void ReleaseItems(void);

	void Centralize(CNGLSprite* sprite);

public:

	/*!
		Construtor padr�o
	*/
	CLevel(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CLevel(void);

	/*!
		Finaliza a classe, liberando todos os objetos alocados.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa a cena. Inicializa cen�rios,interfaces, jogador, inimigos e itens.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize(void);
	/*!
		Executa o jogo. Verifica cada estado da m�quina e chama o m�todo adequado.
	*/
	void Execute(void);
	/*!
		Desenha a cena.
	*/
	void Draw(void);
	/*!
		Retorna a refer�ncia para o jogador.
		\return refer�ncia para um objeto CPlayer que representa o jogador.
	*/
	inline CPlayer* GetPlayer(void) {	return pr_Player; };
	/*!
		Muda o estado da m�quina de estados da CLevel.
		\param NewState: novo estado da m�quina.
	*/
	void ChangeState(CLevel::GameState NewState);
	/*!
		Cria um tiro proveniente do jogador.
		\param Position: posi��o inicial do tiro.
		\param vSpeed: velocidade do tiro.
	*/
	void CreatePlayerShot(CNGLVector Position, CNGLVector vSpeed);
	/*!
		Cria um tiro proveniente do inimigo.
		\param pr_Enemy: refer�ncia para o inimigo que atirou.
		\param Position: posi��o inicial do tiro.
		\param vSpeed: velocidade do tiro.
	*/
	void CreateEnemyShot(CEnemy *pr_Enemy,CNGLVector Position, CNGLVector vSpeed);

private:
	/*!
		Cria um inimigo.
		\param Type: tipo de inimigo.
		\param Position: posi��o inicial do inimigo.
		\param fXPatrolRange: raio de patrulha do inimigo.
	*/
	void CreateEnemy(CEnemy::EnemyType Type, CNGLVector Position, float fXPatrolRange);
	/*!
		Cria os inimigos do jogo.
	*/
	void CreateEnemies(void);
	/*!
		Desabilita conjunto de bricks.
		\param Rect: ret�ngulo ou regi�o que os bricks devem ser desabilitados.
	*/
	void DisableBricks(CNGLFrame Rect);
	/*!
		Cria os itens do jogo.
	*/
	void CreateItems(void);
};

#endif