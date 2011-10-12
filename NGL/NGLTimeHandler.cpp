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
#include "NGLtimehandler.h"
#include <windows.h>

//---------------------------------------------------------------------------- 
// Nome: CNGLTimeHandler(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLTimeHandler::CNGLTimeHandler(void)
{
	bPreventLowdown = true;
	Initialize();
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLTimeHandler(void)
// Desc: destrutor padrão
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
// Desc: Atualiza o tempo. Este método deve ser chamado a cada quadro da aplicação.
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
// Desc: retorna o número de quadros por segundo
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLTimeHandler::GetFPS()
{
	return iFPS;
}

//---------------------------------------------------------------------------- 
// Nome: Reset()
// Desc: Recomeça a contagem de tempo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLTimeHandler::Reset()
{
	uiLastTime = GetTickCount();
}