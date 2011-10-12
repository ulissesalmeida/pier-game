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
#ifndef _CFLYERBOMBER_
#define _CFLYERBOMBER_

//Includes
#include "Dummy.h"

//! Classe CDummy
/*!
	Representa o inimigo FlyerBomber, que é derivado de CDummy. Possui a IA para voar e atirar.
*/
class CFlyerBomber :	public CDummy
{
private:

public:
	/*!
		Construtor padrão
	*/
	CFlyerBomber(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CFlyerBomber(void);

	/*!
		Finaliza a classe
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
	*/
	bool Initialize(CNGLVector InitPos);
protected:
	/*!
	*/
	void OnAttacking(void);
};

#endif