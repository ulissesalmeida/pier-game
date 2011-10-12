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
#include "NGLframe.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLFrame::CNGLFrame(void)
{
	iLeft = iTop = iBottom = iRight = 0;
}

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);
// Desc: contrutor com par�metros
// Pams: left, top, right, bottom
//---------------------------------------------------------------------------- 
CNGLFrame::CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam)
{
	iLeft		= iLeftPam;
	iTop		= iTopPam;
	iRight	= iRightPam;
	iBottom = iBottomPam;
}

//---------------------------------------------------------------------------- 
// Nome: GetWidth(void)
// Desc: retorna a largura do quadro
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLFrame::GetWidth(void)
{
	return iRight - iLeft;
}

//---------------------------------------------------------------------------- 
// Nome: GetHeight(void)
// Desc: retorna a altura do quadro
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLFrame::GetHeight(void)
{
	return iBottom - iTop;
}

//---------------------------------------------------------------------------- 
// Nome: IsValid(void)
// Desc: retorna verdadeiro se o quadro for v�lido
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLFrame::IsValid(void)
{
	return (iBottom >= iTop && iRight >= iLeft);
}

//---------------------------------------------------------------------------- 
// Nome: Collide(const CNGLFrame & Frame)
// Desc: retorna verdadeiro se os dois quadros colidem
// Pams: outro quadro para testar colis�o
//---------------------------------------------------------------------------- 
bool CNGLFrame::Collide(const CNGLFrame & Frame)
{
	return((iLeft < Frame.iRight)  && (iRight  > Frame.iLeft) && 
				 (iTop  < Frame.iBottom) && (iBottom > Frame.iTop));
}