/*NGL v1.0 - Nology Game Library 
Copyright (C) 2003, 2004 Nology Softwares SC Ltda. Todos os direitos reservados

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
#ifndef _CNGLFRAME_
#define _CNGLFRAME_

//!Classe CNGLFrame
/*!
  Esta classe armazena as informa��es de um quadro de anima��o.
*/
class CNGLFrame
{
public:
	//!Posi��o X � esquerda
	int iLeft;
	//!Posi��o Y acima
	int iTop;
	//!Posi��o X � direita
	int iRight;
	//!Posi��o Y abaixo
	int iBottom;

  /*!
		Construtor padr�o.
  */
	CNGLFrame(void);

	/*!
		Contrutor com par�metros
		\param iLeftPam: Posi��o esquerda do quadro
		\param iTopPam: Posi��o do alto do quadro
		\param iRightPam: Posi��o direita do quadro
		\param iBottomPam: Posi��o de baixo do quadro
	*/
	CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);

  /*!
		Obt�m a largura do quadro.
		\return Largura do quadro em pixels.
  */
	int GetWidth(void);
  /*!
		Obt�m a altura de um quadro.
    \return Altura do quadro em pixels.
  */
	int GetHeight(void);

	/*!
		Verifica se o quadro � v�lido.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
  */
	bool IsValid(void);

	/*!
		Retorna verdadeiro se os dois quadros colidem
		\param Frame: outro quadro
		\return verdadeiro se os quadros colidem
	*/
	bool Collide(const CNGLFrame & Frame);
};

#endif