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
#ifndef _CENEMY_
#define _CENEMY_

//Includes
#include "Character.h"
#include "NGLTimeAccumulator.h"

//! Classe CEnemy
/*!
	Classe derivada de CCharacter que � base para os inimigos. Possui fun��es e atributos de movimenta��o, tiro e morte.
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

	//enumerando dire��es
	typedef enum eEnemyDirection
	{
		ED_NONE,
		ED_LEFT,
		ED_RIGHT
	}EnemyDirection;

protected:
	//! Estado corrente do inimigo (ES_PATROLING, ES_ATTACKING, ES_DIEING ou ES_END).
	EnemyState State;
	//! Informa a dire��o que o inimigo est� indo (ED_NONE,ED_LEFT ou ED_RIGHT).
	EnemyDirection Direction;
	//! Posi��o de destino que o inimigo est� indo.
	CNGLVector MovingDest;
	//! Raio de vis�o do inimigo.
	float fVisionRay;
	//! Acumulador que controla tempo entre um tiro e outro.
	CNGLTimeAccumulator AccumShot;
	//! Sprite com anima��o do inimigo morrendo.
	CNGLSprite *p_SprPain;

public:
	//! Tipo de inimigo (ET_DUMMY, ET_DUMMY_KILLER ou ET_FLYER_BOMBER).
	EnemyType Type;
	//! Raio de patrulha do inimigo.
	float fXPatrolRange;
	/*!
		Construtor padr�o
	*/
	CEnemy(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CEnemy(void);

	/*!
		Finaliza o inimigo, desalocando recursos (sprite).
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	/*!
		Atualiza o inimgo de acordo com o seu estado.
	*/
	void Execute(void);
	/*!
		Retorna falso pois este n�o � um objeto de CPlayer.
	*/
	bool IsPlayer(void);
protected:
	/*!
		Move o inimigo para uma posi��o definida na layer.
		\param Dest: posi��o destino x,y na layer.
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
		Retorna verdadeiro se este inimigo est� vendo o jogador. Se o inimigo est� de costas para
		o jogador, ou a dist�ncia	entre o jogador e o inimigo � maior que o raio de vis�o
		do inimigo, ent�o retorna verdadeiro.
		\return Verdadeiro se este inimigo est� vendo o jogador, falso caso contr�rio.
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
		Faz o inimigo se movimentar de acordo com a dire��o, velocidade e alcance de patrulha.
	*/
	void Move(void);
	/*!
		Faz o inimigo atirar.
	*/
	void Shot(void);
	/*!
		Retorna verdadeiro caso o inimigo possa atirar.
		\return bool: verdadeiro se o inimigo pode atirar, falso caso contr�rio
	*/
	bool CanShot(void);
private:
	/*!
		Adiciona pontos ao jogador de acordo com o tipo de inimigo morto.
	*/
	void AddPointsToPlayer(void);
};

#endif