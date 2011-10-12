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
#ifndef _CLEVEL_
#define _CLEVEL_

//Includes
#include "NGLScene.h"
#include "Player.h"
#include "Item.h"
#include "Menu.h"
#include "Shot.h"
#include "Enemy.h"


//!Número de algarismos do placar.
#define NUM_ALGARISMS 5
#define NUMBERS_SPR "Surfaces/spr_Numbers.bmp"
#define LIVES_SPR "Surfaces/spr_Lives.bmp"
#define PAUSED_MSG "Surfaces/msg_Paused.bmp"
#define GAME_OVER_MSG "Surfaces/msg_GameOver.bmp"
#define CONGRATS_MSG "Surfaces/msg_Congrats.bmp"

//! Classe CLevel
/*!
	Classe principal do jogo, responsável pela máquina de estados global do jogo, por criar e atualizar jogador, itens, inimigos e menus.
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
	} GameState; //tipo de dado definido pelo usuário que representa o estado da classe

private:
	//!Estado atual da FSM
	GameState State;
	//!Referência para o jogador
	CPlayer *pr_Player;
	//!Lista de itens
	vector <CItem*> ListItems;
	//!Lista de tiros
	vector <CShot*> ListShots;
	//!Sprites dos números do placar (NUM_ALGARISMS = 5)
	CNGLSprite *p_SprNumbers[NUM_ALGARISMS];
	//!Vetor de sprites das vidas (NUM_LIVES = 3).
	CNGLSprite *p_SprLives[NUM_LIVES];
	//!Sprite com a mensagem "Jogo Pausado"
	CNGLSprite *p_MsgPaused;
	//!Sprite com a mensagem "Game Over"
	CNGLSprite *p_MsgGameOver;
	//!Sprite com a mensagem "Parabéns! Você concluiu o jogo!"
	CNGLSprite *p_MsgCongrats;
	//!Sprite modelo para o tiro
	CNGLSprite *p_SprShot;
	//!Sprite modelo para a explosão do tiro
	CNGLSprite *p_SprShotExplode;
	//!Sprite da moeda final
	CNGLSprite *p_SprCoin;
	//!Sprite da alavanca
	CNGLSprite *p_SprSwitch;
	//!Layer da interface
	CNGLLayer *p_LayInterface;
	//!Som da alavanca
	CNGLSound *p_SndSwitch;
	//!Som de congratulações (final do jogo)
	CNGLSound *p_SndCongrats;
	//!Música do jogo
	CNGLSound *p_SndTrack;

public:

	//!Menu do jogo
	CMenu Menu;
	//!Layer principal da fase (cenário)
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
		\param Position: posição do item.
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
		Construtor padrão
	*/
	CLevel(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CLevel(void);

	/*!
		Finaliza a classe, liberando todos os objetos alocados.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa a cena. Inicializa cenários,interfaces, jogador, inimigos e itens.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Initialize(void);
	/*!
		Executa o jogo. Verifica cada estado da máquina e chama o método adequado.
	*/
	void Execute(void);
	/*!
		Desenha a cena.
	*/
	void Draw(void);
	/*!
		Retorna a referência para o jogador.
		\return referência para um objeto CPlayer que representa o jogador.
	*/
	inline CPlayer* GetPlayer(void) {	return pr_Player; };
	/*!
		Muda o estado da máquina de estados da CLevel.
		\param NewState: novo estado da máquina.
	*/
	void ChangeState(CLevel::GameState NewState);
	/*!
		Cria um tiro proveniente do jogador.
		\param Position: posição inicial do tiro.
		\param vSpeed: velocidade do tiro.
	*/
	void CreatePlayerShot(CNGLVector Position, CNGLVector vSpeed);
	/*!
		Cria um tiro proveniente do inimigo.
		\param pr_Enemy: referência para o inimigo que atirou.
		\param Position: posição inicial do tiro.
		\param vSpeed: velocidade do tiro.
	*/
	void CreateEnemyShot(CEnemy *pr_Enemy,CNGLVector Position, CNGLVector vSpeed);

private:
	/*!
		Cria um inimigo.
		\param Type: tipo de inimigo.
		\param Position: posição inicial do inimigo.
		\param fXPatrolRange: raio de patrulha do inimigo.
	*/
	void CreateEnemy(CEnemy::EnemyType Type, CNGLVector Position, float fXPatrolRange);
	/*!
		Cria os inimigos do jogo.
	*/
	void CreateEnemies(void);
	/*!
		Desabilita conjunto de bricks.
		\param Rect: retângulo ou região que os bricks devem ser desabilitados.
	*/
	void DisableBricks(CNGLFrame Rect);
	/*!
		Cria os itens do jogo.
	*/
	void CreateItems(void);
};

#endif