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
#include "NGLframe.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLFrame::CNGLFrame(void)
{
	iLeft = iTop = iBottom = iRight = 0;
}

//---------------------------------------------------------------------------- 
// Nome: CNGLFrame(int iLeftPam, int iTopPam, int iRightPam, int iBottomPam);
// Desc: contrutor com parâmetros
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
// Desc: retorna verdadeiro se o quadro for válido
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLFrame::IsValid(void)
{
	return (iBottom >= iTop && iRight >= iLeft);
}

//---------------------------------------------------------------------------- 
// Nome: Collide(const CNGLFrame & Frame)
// Desc: retorna verdadeiro se os dois quadros colidem
// Pams: outro quadro para testar colisão
//---------------------------------------------------------------------------- 
bool CNGLFrame::Collide(const CNGLFrame & Frame)
{
	return((iLeft < Frame.iRight)  && (iRight  > Frame.iLeft) && 
				 (iTop  < Frame.iBottom) && (iBottom > Frame.iTop));
}