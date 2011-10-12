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
#ifndef _CNGLFRAME_
#define _CNGLFRAME_

//!Classe CNGLFrame
/*!
  Esta classe armazena as informações de um quadro de animação.
*/
class CNGLFrame
{
public:
	//!Posição X à esquerda
	int iLeft;
	//!Posição Y acima
	int iTop;
	//!Posição X à direita
	int iRight;
	//!Posição Y abaixo
	int iBottom;

  /*!
		Construtor padrão.
  */
	CNGLFrame(void);

	/*!
		Contrutor com parâmetros
		\param iLeftPam: Posição esquerda do quadro
		\param iTopPam: Posição do alto do quadro
		\param iRightPam: Posição direita do quadro
		\param iBottomPam: Posição de baixo do quadro
	*/
	CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);

  /*!
		Obtém a largura do quadro.
		\return Largura do quadro em pixels.
  */
	int GetWidth(void);
  /*!
		Obtém a altura de um quadro.
    \return Altura do quadro em pixels.
  */
	int GetHeight(void);

	/*!
		Verifica se o quadro é válido.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
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