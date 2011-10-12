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
#include "NGLtimehandler.h"
#include <windows.h>

//---------------------------------------------------------------------------- 
// Nome: CNGLTimeHandler(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLTimeHandler::CNGLTimeHandler(void)
{
	bPreventLowdown = true;
	Initialize();
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLTimeHandler(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLTimeHandler::~CNGLTimeHandler(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o time handler
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLTimeHandler::Release(void)
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize()
// Desc: inicializa o time handler
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLTimeHandler::Initialize()
{
	uiLastTime  = GetTickCount();
	fFrameTime  = 0.0f;
	iFrameTime  = 0;
	iFPS        = 0;
	iFrameCount = 0;
	iTimeAcum   = 0;
}

//---------------------------------------------------------------------------- 
// Nome: Update()
// Desc: Atualiza o tempo. Este m�todo deve ser chamado a cada quadro da aplica��o.
// Pams: nenhum 
//---------------------------------------------------------------------------- 
#define NGLMINFRAMEINTERVAL 5
#define NGLMAXFRAMEINTERVAL 50
void CNGLTimeHandler::Update()
{
	iFrameTime = 0;
	unsigned int uiCurrentTime;
	
	do
	{
		uiCurrentTime	= GetTickCount();
		iFrameTime		= (uiCurrentTime >  uiLastTime)? uiCurrentTime - uiLastTime : 0;
		uiLastTime		= (uiCurrentTime >= uiLastTime)? uiLastTime : uiCurrentTime;
	}while(!(iFrameTime >= NGLMINFRAMEINTERVAL));

	if(bPreventLowdown && (iFrameTime > NGLMAXFRAMEINTERVAL))
	{
		iFrameTime = NGLMAXFRAMEINTERVAL;
	}

	iTimeAcum  += iFrameTime;
	iFrameCount++;
	fFrameTime = (float)iFrameTime * 0.001f;

	if(iTimeAcum >= 1000)
	{
		iFPS				= iFrameCount;
		iFrameCount = 0;
		iTimeAcum   = 0;
	}

	uiLastTime = uiCurrentTime;
}

//---------------------------------------------------------------------------- 
// Nome: GetFPS()
// Desc: retorna o n�mero de quadros por segundo
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLTimeHandler::GetFPS()
{
	return iFPS;
}

//---------------------------------------------------------------------------- 
// Nome: Reset()
// Desc: Recome�a a contagem de tempo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLTimeHandler::Reset()
{
	uiLastTime = GetTickCount();
}