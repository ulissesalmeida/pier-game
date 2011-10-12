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
#include "NGLanimation.h"
#include "NGLmain.h"
#include ".\nglanimation.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLAnimation(void)
// Desc: construtor padrão
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
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLAnimation::~CNGLAnimation(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza a animação
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLAnimation::Release(void)
{
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Ended(void)
// Desc: retorna verdadeiro se a animação acabou
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLAnimation::Ended(void)
{
	return (bRepeat)? false : iCurrentFrame >= (char)Frames.size();
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza a animação
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
        //troca para o próximo quadro
				iCurrentFrame += iSum;
				//Neste caso o próximo quadro é calculado como uma fila circular.
				//Caso iCurrentFrame seja igual ao número total de quadros, então
				//o próximo quadro será ZERO.
				iCurrentFrame %= Frames.size();
			}
			else
			{
				//troca para o próximo quadro
				iCurrentFrame += (iCurrentFrame < (char)Frames.size())? iSum : 0;
			}
			//recomeça o acumulador
			TimeAccum.Restart();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetCurrentFrame(void)
// Desc: Retorna o quadro corrente da animação
// Pams: nenhum
//---------------------------------------------------------------------------- 
int CNGLAnimation::GetCurrentFrame(void)
{
	return (iCurrentFrame >= 0 && iCurrentFrame < (int)Frames.size())? Frames[iCurrentFrame] : Frames[Frames.size()-1];
}

//---------------------------------------------------------------------------- 
// Nome: Reset(void)
// Desc: Reinicia a animação
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLAnimation::Reset(void)
{
	TimeAccum.Init(&pr_Main->TimeHandler,(iFramesPerSecond) ? 1000/iFramesPerSecond : 1);
	iCurrentFrame = 0;
}

//---------------------------------------------------------------------------- 
// Nome: GetClone(void)
// Desc: retorna um clone da animação
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
