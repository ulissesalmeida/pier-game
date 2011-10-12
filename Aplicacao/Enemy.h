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
#ifndef _CENEMY_
#define _CENEMY_

//Includes
#include "Character.h"
#include "NGLTimeAccumulator.h"

//! Classe CEnemy
/*!
	Classe derivada de CCharacter que é base para os inimigos. Possui funções e atributos de movimentação, tiro e morte.
*/
class CEnemy :	public CCharacter
{
public:
	//enumerando os tipos de inimigos
	typedef enum eEnemyType
	{
		ET_DUMMY,
		ET_DUMMY_KILLER,
		ET_FLYER_BOMBER
	}EnemyType;

	//enumerando estados da classe CEnemy
	typedef enum eEnemyState
	{
		ES_PATROLING,
		ES_ATTACKING,
		ES_DIEING,
		ES_END
	}EnemyState;

	//enumerando direções
	typedef enum eEnemyDirection
	{
		ED_NONE,
		ED_LEFT,
		ED_RIGHT
	}EnemyDirection;

protected:
	//! Estado corrente do inimigo (ES_PATROLING, ES_ATTACKING, ES_DIEING ou ES_END).
	EnemyState State;
	//! Informa a direção que o inimigo está indo (ED_NONE,ED_LEFT ou ED_RIGHT).
	EnemyDirection Direction;
	//! Posição de destino que o inimigo está indo.
	CNGLVector MovingDest;
	//! Raio de visão do inimigo.
	float fVisionRay;
	//! Acumulador que controla tempo entre um tiro e outro.
	CNGLTimeAccumulator AccumShot;
	//! Sprite com animação do inimigo morrendo.
	CNGLSprite *p_SprPain;

public:
	//! Tipo de inimigo (ET_DUMMY, ET_DUMMY_KILLER ou ET_FLYER_BOMBER).
	EnemyType Type;
	//! Raio de patrulha do inimigo.
	float fXPatrolRange;
	/*!
		Construtor padrão
	*/
	CEnemy(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CEnemy(void);

	/*!
		Finaliza o inimigo, desalocando recursos (sprite).
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
		Atualiza o inimgo de acordo com o seu estado.
	*/
	void Execute(void);
	/*!
		Retorna falso pois este não é um objeto de CPlayer.
	*/
	bool IsPlayer(void);
protected:
	/*!
		Move o inimigo para uma posição definida na layer.
		\param Dest: posição destino x,y na layer.
	*/
	void MoveTo(CNGLVector Dest);
public:
	/*!
	*/
	virtual void ChangeState(CEnemy::EnemyState NewState);
	/*!
		Retorna o estado atual do inimigo.
		\return EnemyState: Estado atual do inimigo (ES_PATROLING, ES_ATTACKING, ES_DIEING, ES_END).
	*/
	CEnemy::EnemyState GetState(void);
protected:
	/*!
		Retorna verdadeiro se este inimigo está vendo o jogador. Se o inimigo está de costas para
		o jogador, ou a distância	entre o jogador e o inimigo é maior que o raio de visão
		do inimigo, então retorna verdadeiro.
		\return Verdadeiro se este inimigo está vendo o jogador, falso caso contrário.
	*/
	bool SeePlayer(void);
	/*!
		Faz o inimigo morrer.
	*/
	void Die(void);
	/*!
		Faz o inimigo pular.
	*/
	void Jump(void);
	/*!
		Faz o inimigo se movimentar de acordo com a direção, velocidade e alcance de patrulha.
	*/
	void Move(void);
	/*!
		Faz o inimigo atirar.
	*/
	void Shot(void);
	/*!
		Retorna verdadeiro caso o inimigo possa atirar.
		\return bool: verdadeiro se o inimigo pode atirar, falso caso contrário
	*/
	bool CanShot(void);
private:
	/*!
		Adiciona pontos ao jogador de acordo com o tipo de inimigo morto.
	*/
	void AddPointsToPlayer(void);
};

#endif