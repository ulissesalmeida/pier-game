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
#ifndef _CDUMMYKILLER_
#define _CDUMMYKILLER_

//Includes
#include "Dummy.h"

//! Classe CDummy
/*!
	Representa o inimigo DummyKiller, que � derivado de CDummy. Possui a IA para andar, pular e atirar.
*/
class CDummyKiller :	public CDummy
{
private:

public:
	/*!
		Construtor padr�o
	*/
	CDummyKiller(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CDummyKiller(void);

	/*!
		Libera recursos do inimigo.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);
	/*!
		Inicia (cria sprite e atribui anima��es do sprite). Tamb�m j� atribui a primeira movimenta��o do inimigo.
		\param InitPos: Posi��o inicial do sprite na layer.
	*/
	bool Initialize(CNGLVector InitPos);
protected:
	/*!
		Trata o estado ES_ATTACKING do inimigo.
	*/
	void OnAttacking(void);
};

#endif