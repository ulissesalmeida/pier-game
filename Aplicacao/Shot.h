
#ifndef _CSHOT_
#define _CSHOT_

#include "NGLObject.h"
#include "NGLVector.h"
#include "NGLTimeAccumulator.h"

class CLevel;
class CNGLSprite;
class CCharacter;
class CNGLSound;

//! Classe CShot
/*!
	Classe que trata cada tiro do jogo, tanto do jogador quanto dos inimigos.
*/
class CShot :	public CNGLObject
{
	private:
		//! Indica que este tiro é do jogador se verdadeiro.
		bool bPlayerShot;
		//! Referência para o personagem "dono" do tiro disparado.
		CCharacter *pr_Owner;
		//! Som de explosão do tiro.
		CNGLSound  *p_SndExplosion;

	public:
		typedef enum eShotState
		{
			SS_SHOT,
			SS_EXPLODE,
			SS_END
		}ShotState;

		//! Acumulador de tempo do tiro (tempo de vida).
		CNGLTimeAccumulator TimeAlive;

		//!Vetor de velocidade do tiro.
		CNGLVector vSpeed;

		//! Estado corrente do tiro.
		ShotState State;

		//!Referência para a classe CLevel.
    CLevel *pr_Level;

		//!Sprite do tiro.
		CNGLSprite *p_SprShot;

		//!Sprite da explosão.
		CNGLSprite *p_SprExplosion;

	public:
		/*!
			Construtor padrão.
		*/
		CShot(void);
		/*!
			Construtor que cria o tiro com os parâmetros necessários.
			\param p_OwnerParam: ponteiro para o personagem "dono" do tiro.
			\param p_ShotParam: ponteiro para o sprite de tiro.
			\param p_ExplodeParam: ponteiro para sprite de explosão.
			\param SpeedParam: velocidade do tiro.
			\param PositionParam: posição inicial do tiro.
		*/
		CShot(CCharacter *p_OwnerParam, CNGLSprite *p_ShotParam, CNGLSprite *p_ExplodeParam, CNGLVector SpeedParam, CNGLVector PositionParam);
		/*!
		*/
		~CShot(void);
		/*!
			Executa a maquina de estados do tiro.
		*/
		void Execute(void);
		/*!
			Libera recursos alocados para o tiro (som e sprites).
		*/
		bool Release(void);
		/*!
			Cria o tiro, atribuindo parâmetros necessários para uma instância do tiro.
			\param p_OwnerParam: ponteiro para o personagem que gerou o tiro
			\param p_ShotParam: ponteiro para Sprite de tiro
			\param p_ExplodeParam: ponteiro para Sprite de explosão
			\param SpeedParam: vetor que descreve velocidade do tiro
			\param PositionParam: vetor que descreve a posição inicial do tiro

		*/
		void Create(CCharacter *p_OwnerParam, CNGLSprite *p_ShotParam, CNGLSprite *p_ExplodeParam, CNGLVector SpeedParam, CNGLVector PositionParam);
		/*!
			Desenha o tiro ou explosão. Ela deve ser utilizada porque os clones destes sprites não são inseridos
			na lista de sprites do jogo.
		*/
		void Draw(void);
private:
		/*!
			Muda o estado atual do tiro
			/param NewState é o novo estado do tiro
		*/
		void ChangeState(CShot::ShotState NewState);
		/*!
			Trata a colisão do tiro com os personagens na tela.
		*/
		void HandleCharacterCollision(void);
		/*!
			Trata a colisão do tiro com os bricks do cenário.
		*/
		void HandleBrickCollsion(void);
};
#endif