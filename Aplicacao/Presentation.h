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
#ifndef _CPRESENTATION_
#define _CPRESENTATION_

//Includes
#include "NGLScene.h"

//! Classe CPresentation
/*!
	Classe que mostra uma tela de apresenta��o do jogo e deve chamar a CLevel quando a tecla ENTER for pressionada.
*/
class CPresentation :	public CNGLScene
{
	public:
	/*!
		Construtor padr�o
	*/
	CPresentation(void);

	/*!
		Destrutor padr�o
	*/
	virtual ~CPresentation(void);

	/*!
		Finaliza a classe, liberando todos os objetos alocados.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	
	/*!
		Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		criar todos os objetos e fazer inicializa��es necess�rias.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize(void);
	/*!
		Aguarda a tecla ENTER ser pressionada para trocar para a cena do jogo (CNGLLevel).
	*/
	void Execute(void);
};

#endif