#include "NGLmain.h"
#include "NGLsprite.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLSprite(void)
// Desc: desfault constructor
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLSprite::CNGLSprite(void)
{
	bVisible			= true;
	byMirror			= NGLMIRROR_NONE;
	sCurrentAnim	= -1;
	pr_Main				= NULL;
	pr_Layer			= NULL;
	pr_Image			= NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLSprite(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLSprite::~CNGLSprite(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o Sprite
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLSprite::Release(void)
{
	if(pr_Main)
	{
		if(pr_Image)
		{
			pr_Main->VideoManager.DeleteImage(&pr_Image);
		}
	}
	ClearAnimations();
	
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Create(void)
// Desc: Cria o sprite
// Pams: nome do arquivo de imagem, tamanho do frame
//---------------------------------------------------------------------------- 
bool CNGLSprite::Create(const char*cp_chFileName,const CNGLVector &cFrameSize)
{
  if(pr_Main)
	{
		pr_Image = pr_Main->VideoManager.LoadImage(cp_chFileName);
		pr_Image->SetFrameSize(cFrameSize);
	}
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: Draw(void)
// Desc: Desenha o sprite no back buffer
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSprite::Draw(void)
{
	if(pr_Main)
	{
		CNGLVector Pos;
		if(pr_Layer)
		{
			Pos = pr_Layer->GetBackBufferPos(Position,pr_Image->FrameSize);
		}
		else
		{
			Pos = Position;
		}
		Pos.Floor();
		if(sCurrentAnim >= 0 && sCurrentAnim < (int)Animations.size())
		{
			pr_Main->VideoManager.BackBuffer.DrawImage(Pos,pr_Image,Animations[sCurrentAnim]->GetCurrentFrame(),byMirror);
		}
		else
		{
			pr_Main->VideoManager.BackBuffer.DrawImage(Pos,pr_Image,0,byMirror);
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: Atualiza o sprite
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSprite::Update(void)
{
	//se existe animação e o índice dela é válido então atualiza a animação corrente
	if((sCurrentAnim >= 0) && (sCurrentAnim < (int)Animations.size()))
	{
		Animations[sCurrentAnim]->Update();
	}
}

//---------------------------------------------------------------------------- 
// Nome: AddAnimation(void)
// Desc: Adiciona uma animação ao sprite
// Pams: Número de quadros por segundo, indica se a animação é contínua ou finita, Número de quadros da animação, quadros da animação
//---------------------------------------------------------------------------- 
void CNGLSprite::AddAnimation(int iFPS, bool bRepeat, int iFrameCount,...)
{
  //cria um novo objeto de animação
	CNGLAnimation *p_Animation = new CNGLAnimation();
	//passa os parâmetros para a animação
	p_Animation->pr_Main					= pr_Main;
	p_Animation->bRepeat					= bRepeat;
	p_Animation->SetFrameInterval(iFPS);

	va_list marker;
	//inicializa a lista para extrair os quadros da animação (parâmetro "...")
	va_start(marker, iFrameCount);

	//extrai cada quadro da lista e adiciona na animação
	for(int i = 0; i < iFrameCount; i++)
	{
		p_Animation->Frames.push_back(va_arg(marker, int));
	}
	
	//finaliza a lista
	va_end( marker );

	//adiciona a animação na lista do sprite
	Animations.push_back(p_Animation);
}

//---------------------------------------------------------------------------- 
// Nome: ResetAnimation(void)
// Desc: Reinicia a animação corrente
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSprite::ResetAnimation(void)
{
	if(sCurrentAnim >= 0 && sCurrentAnim < (int)Animations.size())
	{
		Animations[sCurrentAnim]->Reset();
	}
}

//---------------------------------------------------------------------------- 
// Nome: SetCurrentAnimation(short sAnim)
// Desc: seta a animação corrente
// Pams: animação
//---------------------------------------------------------------------------- 
void CNGLSprite::SetCurrentAnimation(short sAnim)
{
	if(sAnim != sCurrentAnim)
	{
		sCurrentAnim = sAnim;
		ResetAnimation();
	}
}

//---------------------------------------------------------------------------- 
// Nome: ClearAnimations(void)
// Desc: Exclui todas as animações do vetor
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSprite::ClearAnimations(void)
{
	for(int i = (int)Animations.size()-1; i >=0; i--)
	{
		delete Animations[i];
	}
	Animations.clear();
}

//---------------------------------------------------------------------------- 
// Nome: GetClone(bool bAddToLayer)
// Desc: Retorna um clone ou cópia deste sprite.
// Pams: indica se o sprite deve ser adicionado à mesma layer do sprite fonte.
//---------------------------------------------------------------------------- 
CNGLSprite *CNGLSprite::GetClone(bool bAddToLayer)
{
	CNGLSprite *p_Clone		= new CNGLSprite();
	if(p_Clone)
	{
		p_Clone->bVisible			= bVisible;
		p_Clone->byMirror			= byMirror;

		p_Clone->pr_Image			= pr_Image;
		pr_Image->sReferences++;

		p_Clone->pr_Layer			= pr_Layer;
		p_Clone->pr_Main			= pr_Main;
		p_Clone->Position			= Position;
		p_Clone->sCurrentAnim = sCurrentAnim;

		int iSize = (int)Animations.size();
		for(int i = 0; i < iSize; i++)
		{
			p_Clone->Animations.push_back(Animations[i]->GetClone());
		}
		if(bAddToLayer && pr_Layer)
		{
			pr_Layer->Sprites.push_back(p_Clone);
		}
		return p_Clone;
	}
	return NULL;
}

//---------------------------------------------------------------------------- 
// Nome: GetFrame(void)
// Desc: Retorna o frame do sprite
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLFrame CNGLSprite::GetFrame(void)
{
	CNGLFrame Frame;
	Frame.iLeft = (int)Position.fx;
	Frame.iTop = (int)Position.fy;
	Frame.iRight = (int)(Position.fx + pr_Image->FrameSize.fx);
	Frame.iBottom = (int)(Position.fy + pr_Image->FrameSize.fy);
	
	return Frame;
}
