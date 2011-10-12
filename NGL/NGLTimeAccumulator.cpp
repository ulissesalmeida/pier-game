#include ".\ngltimeaccumulator.h"
#include "NGLTimeHandler.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLTimeAccumulator(void)
// Desc: Construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLTimeAccumulator::CNGLTimeAccumulator(void)
{
	pr_TimeHandler	= NULL;
	uiTimeAccum			= 0;
	uiTimeLimit			= 0;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLTimeAccumulator(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLTimeAccumulator::~CNGLTimeAccumulator(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release()
// Desc: Finaliza o acumulador de tempo
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLTimeAccumulator::Release(void)
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Init(void)
// Desc: Inicializa o acumulador de tempo
// Pams: ponteiro de referência para gerenciador de tempo, limite de tempo do acumulador
//---------------------------------------------------------------------------- 
void CNGLTimeAccumulator::Init(CNGLTimeHandler *pr_TimeHandlerPam, unsigned int uiTimeLimitPam)
{
	uiTimeAccum			= 0;
	uiTimeLimit			= uiTimeLimitPam;
	pr_TimeHandler	= pr_TimeHandlerPam;
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza o acumulador de tempo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLTimeAccumulator::Update(void)
{
	if(pr_TimeHandler)
	{
		//soma o tempo corrente ao acumulador
		uiTimeAccum += pr_TimeHandler->iFrameTime;
	}
}

//---------------------------------------------------------------------------- 
// Nome: Restart(void)
// Desc: Reinicia o acumulador de tempo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLTimeAccumulator::Restart(void)
{
	uiTimeAccum %= uiTimeLimit;
}

//---------------------------------------------------------------------------- 
// Nome: Ended(void)
// Desc: Retorna verdadeiro se o acumulador de tempo já excedeu o limite.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLTimeAccumulator::Ended(void)
{
	return uiTimeAccum >= uiTimeLimit;
}