/*NGL v1.0 - Nology Game Library 
Copyright (C) 2003, 2004 Nology Softwares SC Ltda. Todos os direitos reservados

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
#ifndef _CNGLOBJECT_
#define _CNGLOBJECT_

/*!
	Definição do tipo Byte.
*/
typedef unsigned char Byte;

//!Classe CNGLObject
/*!
	Classe base para todas as classes da NGL.
*/
class CNGLObject
{
public:

	/*!
		Finaliza a classe. Deve ser implementada nas classes filhas.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	virtual bool Release() = 0;
	/*!
		Construtor padrão.
	*/
	CNGLObject(void);
	/*!
		Destrutor padrão.
	*/
	virtual ~CNGLObject(void);
};

#endif