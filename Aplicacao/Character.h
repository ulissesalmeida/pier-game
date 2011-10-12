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
#ifndef _CCHARACTER_
#define _CCHARACTER_

//Includes
#include "NGLObject.h"

class CLevel;

//! Classe CCharacter
/*!
	Representa um personagem (jogador ou inimigo). Responsável por tratar movimentação, gravidade, colisão e morte.
*/
class CCharacter :	public CNGLObject
{
private:
	/*!
		Trata da colisão com o cenário na esquerda e na direita do personagem (eixo X).
	*/
	void HandleCollisionLeftRight(void);
	/*!
		Trata da colisão com o cenário acima e abaixo do personagem (eixo Y).
	*/
	void HandleCollisionUpDown(void);

protected:
	//! Indica se o personagem está pulando ou caindo no momento.
	bool bJump;
	//! Indica se a gravidade vai agir sobre o personagem.
	bool bUseGravity;
	/*!
		Método que deve ser reescrito pelo inimigo ou jogador para tratar morte do personagem.
	*/
	virtual void Die(void) = 0;
	//! Indica se o personagem está morrendo.
	bool bIsDieing;
	//! Velocidade atual do personagem.
	CNGLVector CurrentSpeed;
	//! Velocidade padrão de deslocamento e queda do personagem.
	CNGLVector DefaultSpeed;
	//! Contém o valor de gravidade do personagem.
	float fGravity;

public:
	//! Posição do personagem no laço anterior do jogo.
	CNGLVector LastPos;
	//! Sprite que contém as animações do personagem.
	CNGLSprite *p_Sprite;
	//! Referência para a classe CLevel.
	CLevel *pr_Level;

	/*!
		Construtor padrão
	*/
	CCharacter(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CCharacter(void);

	/*!
		Finaliza a classe, liberando sprite do personagem.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
		Método que deve ser reescrito pelo inimigo ou jogador para iniciá-lo (sprites, animações e posição).
		\param InitPos: Posição inicial do personagem ao iniciar a fase.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	virtual bool Initialize(CNGLVector InitPos) = 0;
	/*!
		Atualiza gravidade, trata colisão com bricks, atualiza posição do personagem e ajusta as animações do personagem.
	*/
	virtual void Execute(void);
	/*!
		Retorna um CNGLFrame contendo o quadro do sprite do personagem.
		\return Retorna CNGLFrame com o quadro do personagem.
	*/
	CNGLFrame GetFrame(void);
	/*!
		Faz o personagem atirar, devendo ser reescrita nas classes filhas.
	*/
	virtual void Shot(void);
	/*!
		Método que deve ser reescrito pelas classes que herdam desta para dizer se é jogador ou inimigo.
	*/
	virtual bool IsPlayer(void) = 0;
	/*!
		Mata o personagem.
	*/
	void Kill(void);
	/*!
		Retorna verdadeiro caso personagem esteja morrendo.
		\return verdadeiro se o personagem estiver morrendo, falso caso contrário
	*/
	bool IsDieing(void);
};

#endif