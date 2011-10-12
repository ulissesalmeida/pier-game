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
#ifndef _CDUMMYKILLER_
#define _CDUMMYKILLER_

//Includes
#include "Dummy.h"

//! Classe CDummy
/*!
	Representa o inimigo DummyKiller, que é derivado de CDummy. Possui a IA para andar, pular e atirar.
*/
class CDummyKiller :	public CDummy
{
private:

public:
	/*!
		Construtor padrão
	*/
	CDummyKiller(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CDummyKiller(void);

	/*!
		Libera recursos do inimigo.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release(void);
	/*!
		Inicia (cria sprite e atribui animações do sprite). Também já atribui a primeira movimentação do inimigo.
		\param InitPos: Posição inicial do sprite na layer.
	*/
	bool Initialize(CNGLVector InitPos);
protected:
	/*!
		Trata o estado ES_ATTACKING do inimigo.
	*/
	void OnAttacking(void);
};

#endif