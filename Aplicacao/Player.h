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
#ifndef _CPLAYER_
#define _CPLAYER_

//Includes
#include "Character.h"
#include "NGLTimeAccumulator.h"

#define NUM_LIVES			3

//! Classe CPlayer
/*!
	Classe derivada de CCharacter, responsável por tratar o jogador.
*/
class CPlayer :	public CCharacter
{
private:

private:
	//! Som de tiro do jogador.
	CNGLSound  *p_SndShot;
	//! Acumulador que assegura o tempo que o jogador ficará imune ao renascer.
	CNGLTimeAccumulator AccumImmunity;

public:
	//! Número de pontos do jogador.
	unsigned int uiPoints;
	//! Número de vidas do jogador.
	unsigned int uiLives;
	//! Indica que o jogador está invencível.
	bool bInvincible;
	//! Indica que o jogador está imune (usado quando jogador renasce).
	bool bImmune;

	/*!
		Construtor padrão
	*/
	CPlayer(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CPlayer(void);

	/*!
		Finaliza o inimigo, desalocando recursos (sprite e som de tiro).
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa o jogador, com as devidas animações, posição, vidas, etc.
		\param InitPos: posição inicial
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Initialize(CNGLVector InitPos);

	/*!
		Trata a entrada de dados do teclado para movimentar jogador, pular e piscar.
	*/
	void Execute(void);
	/*!
		Faz o jogador atirar para todas as direções.
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
		Faz o jogador renascer (após sua morte) e deixa-o piscando por alguns segundos.
	*/
	void Reborn(void);
};

#endif