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
#ifndef _CDUMMY_
#define _CDUMMY_

//Includes
#include "Enemy.h"

//! Classe CDummy
/*!
	Representa o inimigo Dummy, que é derivado de CEnemy. Possui a IA para andar e pular.
*/
class CDummy :	public CEnemy
{
private:

public:
	/*!
		Construtor padrão
	*/
	CDummy(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CDummy(void);

	/*!
		Libera recursos do inimigo.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
		Inicializa o inimigo (sprite, animações e comando de movimentação).
		\param InitPos: Posição inicial do sprite na layer.
	*/
	bool Initialize(CNGLVector InitPos);
	/*!
		Atualiza o estado do inimigo.
	*/
	void Execute(void);
protected:
	/*!
		Trata o estado ES_PATROLING do inimigo.
	*/
	virtual void OnPatroling(void);
	/*!
		Muda o estado do inimigo. 
		\param NewState: novo estado.
	*/
	virtual void ChangeState(CEnemy::EnemyState NewState);
	/*!
		Trata o estado ES_ATTACKING do inimigo.
	*/
	virtual void OnAttacking(void);
};

#endif