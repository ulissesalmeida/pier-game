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
#ifndef _CPRESENTATION_
#define _CPRESENTATION_

//Includes
#include "NGLScene.h"

//! Classe CPresentation
/*!
	Classe que mostra uma tela de apresentação do jogo e deve chamar a CLevel quando a tecla ENTER for pressionada.
*/
class CPresentation :	public CNGLScene
{
	public:
	/*!
		Construtor padrão
	*/
	CPresentation(void);

	/*!
		Destrutor padrão
	*/
	virtual ~CPresentation(void);

	/*!
		Finaliza a classe, liberando todos os objetos alocados.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		criar todos os objetos e fazer inicializações necessárias.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Initialize(void);
	/*!
		Aguarda a tecla ENTER ser pressionada para trocar para a cena do jogo (CNGLLevel).
	*/
	void Execute(void);
};

#endif