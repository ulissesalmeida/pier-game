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
#include "NGLbrick.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLBrick(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLBrick::CNGLBrick(void)
{
	iImage = 0;
	iFrame = 0;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLBrick(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLBrick::~CNGLBrick(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o brick 
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLBrick::Release(void)
{
	return true;
}
