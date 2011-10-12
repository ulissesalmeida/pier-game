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
#ifndef _CCHARACTER_
#define _CCHARACTER_

//Includes
#include "NGLObject.h"

class CLevel;

//! Classe CCharacter
/*!
	Representa um personagem (jogador ou inimigo). Respons�vel por tratar movimenta��o, gravidade, colis�o e morte.
*/
class CCharacter :	public CNGLObject
{
private:
	/*!
		Trata da colis�o com o cen�rio na esquerda e na direita do personagem (eixo X).
	*/
	void HandleCollisionLeftRight(void);
	/*!
		Trata da colis�o com o cen�rio acima e abaixo do personagem (eixo Y).
	*/
	void HandleCollisionUpDown(void);

protected:
	//! Indica se o personagem est� pulando ou caindo no momento.
	bool bJump;
	//! Indica se a gravidade vai agir sobre o personagem.
	bool bUseGravity;
	/*!
		M�todo que deve ser reescrito pelo inimigo ou jogador para tratar morte do personagem.
	*/
	virtual void Die(void) = 0;
	//! Indica se o personagem est� morrendo.
	bool bIsDieing;
	//! Velocidade atual do personagem.
	CNGLVector CurrentSpeed;
	//! Velocidade padr�o de deslocamento e queda do personagem.
	CNGLVector DefaultSpeed;
	//! Cont�m o valor de gravidade do personagem.
	float fGravity;

public:
	//! Posi��o do personagem no la�o anterior do jogo.
	CNGLVector LastPos;
	//! Sprite que cont�m as anima��es do personagem.
	CNGLSprite *p_Sprite;
	//! Refer�ncia para a classe CLevel.
	CLevel *pr_Level;

	/*!
		Construtor padr�o
	*/
	CCharacter(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CCharacter(void);

	/*!
		Finaliza a classe, liberando sprite do personagem.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	/*!
		M�todo que deve ser reescrito pelo inimigo ou jogador para inici�-lo (sprites, anima��es e posi��o).
		\param InitPos: Posi��o inicial do personagem ao iniciar a fase.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	virtual bool Initialize(CNGLVector InitPos) = 0;
	/*!
		Atualiza gravidade, trata colis�o com bricks, atualiza posi��o do personagem e ajusta as anima��es do personagem.
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
		M�todo que deve ser reescrito pelas classes que herdam desta para dizer se � jogador ou inimigo.
	*/
	virtual bool IsPlayer(void) = 0;
	/*!
		Mata o personagem.
	*/
	void Kill(void);
	/*!
		Retorna verdadeiro caso personagem esteja morrendo.
		\return verdadeiro se o personagem estiver morrendo, falso caso contr�rio
	*/
	bool IsDieing(void);
};

#endif