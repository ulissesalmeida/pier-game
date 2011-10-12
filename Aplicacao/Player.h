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
#ifndef _CPLAYER_
#define _CPLAYER_

//Includes
#include "Character.h"
#include "NGLTimeAccumulator.h"

#define NUM_LIVES			3

//! Classe CPlayer
/*!
	Classe derivada de CCharacter, respons�vel por tratar o jogador.
*/
class CPlayer :	public CCharacter
{
private:

private:
	//! Som de tiro do jogador.
	CNGLSound  *p_SndShot;
	//! Acumulador que assegura o tempo que o jogador ficar� imune ao renascer.
	CNGLTimeAccumulator AccumImmunity;

public:
	//! N�mero de pontos do jogador.
	unsigned int uiPoints;
	//! N�mero de vidas do jogador.
	unsigned int uiLives;
	//! Indica que o jogador est� invenc�vel.
	bool bInvincible;
	//! Indica que o jogador est� imune (usado quando jogador renasce).
	bool bImmune;

	/*!
		Construtor padr�o
	*/
	CPlayer(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CPlayer(void);

	/*!
		Finaliza o inimigo, desalocando recursos (sprite e som de tiro).
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa o jogador, com as devidas anima��es, posi��o, vidas, etc.
		\param InitPos: posi��o inicial
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize(CNGLVector InitPos);

	/*!
		Trata a entrada de dados do teclado para movimentar jogador, pular e piscar.
	*/
	void Execute(void);
	/*!
		Faz o jogador atirar para todas as dire��es.
	*/
	void Shot(void);
	/*!
		Retorna sempre verdadeiro pois trata-se do jogador.
		\return verdadeiro sempre.
	*/
	bool IsPlayer(void);
protected:
	/*!
		Faz as tratativas para a morte do jogador.
	*/
	void Die(void);
private:
	/*!
		Faz o jogador renascer (ap�s sua morte) e deixa-o piscando por alguns segundos.
	*/
	void Reborn(void);
};

#endif