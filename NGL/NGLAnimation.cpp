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
#include "NGLanimation.h"
#include "NGLmain.h"
#include ".\nglanimation.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLAnimation(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLAnimation::CNGLAnimation(void)
{
	bRepeat						= false;
	iCurrentFrame			= 0;
	iFramesPerSecond	= 1;
	pr_Main						= NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLAnimation(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLAnimation::~CNGLAnimation(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a anima��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLAnimation::Release(void)
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Ended(void)
// Desc: retorna verdadeiro se a anima��o acabou
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLAnimation::Ended(void)
{
	return (bRepeat)? false : iCurrentFrame >= (char)Frames.size();
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza a anima��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLAnimation::Update(void)
{
	if(pr_Main)
	{
		//Atualiza o acumulador de tempo
		TimeAccum.Update();

		//Se o acumulador eh maior que o intervalo entre quadros
		if(TimeAccum.Ended())
		{
			//pega o intervalo entre os quadros
			unsigned int uiFrameInterval = (iFramesPerSecond)? 1000/iFramesPerSecond : 1;
			
			//Calcula quantos quadros se passaram
			int iSum = (int)(TimeAccum.uiTimeAccum / uiFrameInterval);

			//Soma os quadros ao quadro corrente
			if(bRepeat)
			{
        //troca para o pr�ximo quadro
				iCurrentFrame += iSum;
				//Neste caso o pr�ximo quadro � calculado como uma fila circular.
				//Caso iCurrentFrame seja igual ao n�mero total de quadros, ent�o
				//o pr�ximo quadro ser� ZERO.
				iCurrentFrame %= Frames.size();
			}
			else
			{
				//troca para o pr�ximo quadro
				iCurrentFrame += (iCurrentFrame < (char)Frames.size())? iSum : 0;
			}
			//recome�a o acumulador
			TimeAccum.Restart();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetCurrentFrame(void)
// Desc: Retorna o quadro corrente da anima��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLAnimation::GetCurrentFrame(void)
{
	return (iCurrentFrame >= 0 && iCurrentFrame < (int)Frames.size())? Frames[iCurrentFrame] : Frames[Frames.size()-1];
}

//---------------------------------------------------------------------------- 
// Nome: Reset(void)
// Desc: Reinicia a anima��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLAnimation::Reset(void)
{
	TimeAccum.Init(&pr_Main->TimeHandler,(iFramesPerSecond) ? 1000/iFramesPerSecond : 1);
	iCurrentFrame = 0;
}

//---------------------------------------------------------------------------- 
// Nome: GetClone(void)
// Desc: retorna um clone da anima��o
// Pams: 
//---------------------------------------------------------------------------- 
CNGLAnimation* CNGLAnimation::GetClone(void)
{
	CNGLAnimation *p_Clone		= new CNGLAnimation();
	if(p_Clone)
	{
		p_Clone->bRepeat					= bRepeat;
		p_Clone->iCurrentFrame		= iCurrentFrame;
		p_Clone->pr_Main					= pr_Main;
		p_Clone->SetFrameInterval(iFramesPerSecond,TimeAccum.uiTimeAccum);

		int iSize = (int)Frames.size();
		for(int i = 0; i < iSize; i++)
		{
			p_Clone->Frames.push_back(Frames[i]);
		}
		return p_Clone;
	}
	return NULL;
}

//---------------------------------------------------------------------------- 
// Nome: SetFrameInterval(int iFrameInterval)
// Desc: Configura o intervalo de tempo entre os quadros (em FPS).
// Pams: Intervalo de tempo, tempo inicial do acumulador de tempo
//---------------------------------------------------------------------------- 
void CNGLAnimation::SetFrameInterval(int iFrameInterval, unsigned int uiTimeAccum)
{
	iFramesPerSecond = iFrameInterval;
	TimeAccum.Init(&pr_Main->TimeHandler,(iFramesPerSecond) ? 1000/iFramesPerSecond : 1);
	TimeAccum.uiTimeAccum = uiTimeAccum;
}
