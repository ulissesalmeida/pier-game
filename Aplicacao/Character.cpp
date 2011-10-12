/*NGL v1.0 - Game Development Library 
Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

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

#include "NGLMain.h"
#include "Character.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"

//definição para simplificar o código
#define FTIME pr_Level->pr_Main->TimeHandler.fFrameTime

//---------------------------------------------------------------------------- 
// Nome: CCharacter(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CCharacter::CCharacter(void)
{
	pr_Level		= NULL;
	//inicialmente o personagem não está pulando e nem morrendo
	bJump				= false;
	bIsDieing		= false;
	//a aceleração da gravidade nesta cena é da 900 pixels/segundo^2
	fGravity		= 900.0f;
	//por padrão, os personagens são afetados pela gravidade
	bUseGravity = true;
}

//---------------------------------------------------------------------------- 
// Nome: ~CCharacter(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CCharacter::~CCharacter(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza a classe, liberando sprite do personagem.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CCharacter::Release(void)
{
	//libera o sprite do personagem
	pr_Level->p_LayLevel->DeleteSprite(&p_Sprite);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Atualiza gravidade, trata colisão com bricks, atualiza posição do personagem 
//		 e ajusta as animações do personagem.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CCharacter::Execute(void)
{
	//última posição recebe a posição atual
	LastPos = p_Sprite->Position;

	//se o personagem usa gravidade
	if(bUseGravity)
	{
		//atualiza gravidade usando MQL
		//ajusta posição Y
		p_Sprite->Position.fy += (CurrentSpeed.fy*FTIME) + ((fGravity*FTIME*FTIME)*0.5f);
		//ajusta velocidade em Y
		CurrentSpeed.fy += fGravity*FTIME;
		//ajusta velocidade máxima de queda (600 pixels por segundo)
		CurrentSpeed.fy = (CurrentSpeed.fy > 600.0f)? 600.0f : CurrentSpeed.fy;
	}

	//trata colisão do personagem com o cenário (acima e abaixo)
	HandleCollisionUpDown();

	//ajusta posição em X (deslocamento lateral), usando MRU
	p_Sprite->Position.fx += CurrentSpeed.fx * FTIME;

	//se personagem estiver caindo ou pulando
	if((floor(p_Sprite->Position.fy) != floor(LastPos.fy)) || bJump)
	{
		bJump = true;
		p_Sprite->SetCurrentAnimation(1);
	}
	else
	{
		//se personagem está em movimento lateral
		if(CurrentSpeed.fx != 0.0f)
		{
			//ajusta animação de caminhada
			p_Sprite->SetCurrentAnimation(0);
		}
		else
		{
			//ajusta animação do personagem parado
			p_Sprite->SetCurrentAnimation(2);
		}
	}

	//trata colisão do personagem com o cenário (esquerda e direita)
	HandleCollisionLeftRight();

	//ajusta posição do personagem: não pode ter X menor do que ZERO
	p_Sprite->Position.fx = (p_Sprite->Position.fx < 0.0f)? 0.0f : p_Sprite->Position.fx;
	//ajusta posição do personagem: não pode passar do final da layer
	p_Sprite->Position.fx = (p_Sprite->Position.fx > (pr_Level->p_LayLevel->GetLayerSize().fx - p_Sprite->pr_Image->FrameSize.fx)) ? pr_Level->p_LayLevel->GetLayerSize().fx - p_Sprite->pr_Image->FrameSize.fx : p_Sprite->Position.fx;

	//coloca velocidade em X em ZERO, pois a nova posição X já foi calculada
	//caso você comente a linha abaixo, o personagem ficará sempre se movimentando
	CurrentSpeed.fx = 0.0f;
}

//---------------------------------------------------------------------------- 
// Nome: HandleCollisionUpDown(void)
// Desc: Trata da colisão com o cenário acima e abaixo do personagem (eixo Y)
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CCharacter::HandleCollisionUpDown()
{
	//pega o tamanho do brick
	int iBrickWidth = (int)pr_Level->p_LayLevel->BrickSize.fx;
	int iBrickHeight = (int)pr_Level->p_LayLevel->BrickSize.fy;

	//pega o quadro do sprite
	CNGLFrame SpriteFrame((int)p_Sprite->Position.fx,
												(int)p_Sprite->Position.fy,
                        (int)(p_Sprite->Position.fx + p_Sprite->pr_Image->FrameSize.fx),
												(int)(p_Sprite->Position.fy + p_Sprite->pr_Image->FrameSize.fy));


	//pega o centro do sprite
	CNGLVector SpriteCenter((SpriteFrame.iLeft + SpriteFrame.iRight)>>1, (SpriteFrame.iTop + SpriteFrame.iBottom)>>1);

  //pega os indices dos bricks sobre os quais a extremidades do sprite estão
	int iX		= SpriteFrame.iLeft/iBrickWidth;
	int iY		= SpriteFrame.iTop/iBrickHeight;
	int iMaxX = SpriteFrame.iRight/iBrickWidth;
	int iMaxY = SpriteFrame.iBottom/iBrickHeight;


  //testa a validade dos índices
	if(iX >= 0 && iY  >= 0)
	{
		int index;
		//varre os bricks sobre os quais os sprite está
		for(iX = SpriteFrame.iLeft/iBrickWidth; iX <= iMaxX; iX++)
		{
			for(iY	= SpriteFrame.iTop/iBrickHeight; iY <= iMaxY; iY++)
			{
				//pega o indice no vetor da layer do brick
				index  = (iX < (int)pr_Level->p_LayLevel->NumBricks.fx)? iX : iX - (int)pr_Level->p_LayLevel->NumBricks.fx;
				index += (iY < (int)pr_Level->p_LayLevel->NumBricks.fy)? iY*(int)pr_Level->p_LayLevel->NumBricks.fx : (iY - (int)pr_Level->p_LayLevel->NumBricks.fy)*(int)pr_Level->p_LayLevel->NumBricks.fx;
				
				//se o brick existe
				if(pr_Level->p_LayLevel->p_Bricks[index])
				{
					//pega o frame do brick
					CNGLFrame BrickFrame;
					BrickFrame.iLeft	 = iX*iBrickWidth;
					BrickFrame.iRight  = (iX+1)*iBrickWidth;
					BrickFrame.iTop	   = iY*iBrickHeight;
					BrickFrame.iBottom = (iY+1)*iBrickHeight;

					//se os quadros do brick e o do sprite colidem
					if(BrickFrame.Collide(SpriteFrame))
					{
						//pega o centro do brick
						CNGLVector BrickCenter((iX*iBrickWidth) + (iBrickWidth>>1), (iY*iBrickHeight) + (iBrickHeight>>1));

						//calcula o valor da distância mínima entre o brick e o sprite
 						float fMinDist = ((pr_Level->p_LayLevel->BrickSize.fy + p_Sprite->pr_Image->FrameSize.fy)*0.5f);

						//se o centro do sprite está acima do brick
						if(SpriteCenter.fy <= BrickCenter.fy && SpriteCenter.fy > BrickCenter.fy - fMinDist)
						{
              //anula o flag de pulo
							bJump	= false;
							//zera a velocidade vertical
							CurrentSpeed.fy = 0.0f;
							//afasta o centro do sprite do centro do brick em y
							SpriteCenter.fy = BrickCenter.fy - fMinDist;
						}
						else
						{
							if(SpriteCenter.fy > BrickCenter.fy && SpriteCenter.fy < BrickCenter.fy + fMinDist)
							{
								//zera a velocidade vertical
								CurrentSpeed.fy = 0.0f;
								//afasta o centro do sprite do centro do brick em y
								SpriteCenter.fy = BrickCenter.fy + fMinDist;
							}
						}
					}
				}
			}
		}
	}
	//atualiza a posição do sprite em relação ao centro
	p_Sprite->Position.fy = SpriteCenter.fy - (float)floor((p_Sprite->pr_Image->FrameSize.fy*0.5f));
/*	float fNewPos = SpriteCenter.fy - (float)floor((p_Sprite->pr_Image->FrameSize.fy*0.5f));
	p_Sprite->Position.fy = (floor(fNewPos) != floor(p_Sprite->Position.fy))? fNewPos : p_Sprite->Position.fy;*/
}

//---------------------------------------------------------------------------- 
// Nome: HandleCollisionLeftRight(void)
// Desc: Trata da colisão com o cenário na esquerda e na direita do personagem (eixo X)
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CCharacter::HandleCollisionLeftRight(void)
{
	//pega o tamanho do brick 
	int iBrickWidth = (int)pr_Level->p_LayLevel->BrickSize.fx;
	int iBrickHeight = (int)pr_Level->p_LayLevel->BrickSize.fy;

	//pega o quadro do sprite
	CNGLFrame SpriteFrame((int)p_Sprite->Position.fx,
												(int)p_Sprite->Position.fy,
                        (int)(p_Sprite->Position.fx + p_Sprite->pr_Image->FrameSize.fx),
												(int)(p_Sprite->Position.fy + p_Sprite->pr_Image->FrameSize.fy));

	//pega o centro do sprite
	CNGLVector SpriteCenter((SpriteFrame.iLeft + SpriteFrame.iRight)/2, 
		                      (SpriteFrame.iTop + SpriteFrame.iBottom)/2);

	//pega os indices dos bricks sobre os quais a extremidades do sprite estão
	int iX    = SpriteFrame.iLeft/iBrickWidth;
	int iY	  = SpriteFrame.iTop/iBrickHeight;
	int iMaxX = (SpriteFrame.iRight/iBrickWidth)+1;
	int iMaxY = (SpriteFrame.iBottom/iBrickHeight)+1;

	//testa a validade dos indices
  if(iX >= 0 && iY  >= 0)
	{
		int index;
		//varre os bricks sobre os quais os sprite está
		for(iX = SpriteFrame.iLeft/iBrickWidth; iX <= iMaxX; iX++)
		{
			for(iY	= SpriteFrame.iTop/iBrickHeight; iY <= iMaxY; iY++)
			{
				//pega o indice no vetor da layer do brick
				index  = (iX < (int)pr_Level->p_LayLevel->NumBricks.fx)? iX : iX - (int)pr_Level->p_LayLevel->NumBricks.fx;
				index += (iY < (int)pr_Level->p_LayLevel->NumBricks.fy)? iY*(int)pr_Level->p_LayLevel->NumBricks.fx : (iY - (int)pr_Level->p_LayLevel->NumBricks.fy)*(int)pr_Level->p_LayLevel->NumBricks.fx;

				//se o brick existe
				if(pr_Level->p_LayLevel->p_Bricks[index])
				{
					//pega o frame do brick
					CNGLFrame BrickFrame;
					BrickFrame.iLeft	 = iX*iBrickWidth;
					BrickFrame.iRight  = (iX+1)*iBrickWidth;
					BrickFrame.iTop	   = iY*iBrickHeight;
					BrickFrame.iBottom = (iY+1)*iBrickHeight;

					//se os quadros do brick e o do sprite colidem
          if(BrickFrame.Collide(SpriteFrame))
					{
						//pega o centro do brick
						CNGLVector BrickCenter((iX*iBrickWidth) + (iBrickWidth>>1), (iY*iBrickHeight) + (iBrickHeight>>1));

						//calcula o valor da distância mínima entre o brick e o sprite
						float fMinDist = ((pr_Level->p_LayLevel->BrickSize.fx + p_Sprite->pr_Image->FrameSize.fx)*0.5f);

						//se o centro do sprite está a esquerda do brick
						if(SpriteCenter.fx <= BrickCenter.fx && SpriteCenter.fx > BrickCenter.fx - fMinDist)
						{
							//zera a velocidade do sprite
							CurrentSpeed.fx = 0.0f;
							//afasta o centro do sprite do centro do brick em x
							SpriteCenter.fx = BrickCenter.fx - fMinDist;
						}
						else
						{
							//se o centro do sprite está a direita do brick
							if(SpriteCenter.fx > BrickCenter.fx && SpriteCenter.fx < BrickCenter.fx + fMinDist)
							{
								//zera a velocidade do sprite
								CurrentSpeed.fx = 0.0f;
								//afasta o centro do sprite do centro do brick
								SpriteCenter.fx = BrickCenter.fx + fMinDist;
							}
						}//else
					}//if
				}//if
			}//for
		}//for
		//atualiza a posição do sprite em relação ao centro
		float fNewPos = SpriteCenter.fx - (float)floor((p_Sprite->pr_Image->FrameSize.fx*0.5f));
		p_Sprite->Position.fx = (floor(fNewPos) != floor(p_Sprite->Position.fx))? fNewPos : p_Sprite->Position.fx;
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetFrame(void)
// Desc: Retorna um CNGLFrame contendo o quadro do sprite do personagem
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLFrame CCharacter::GetFrame(void)
{
	CNGLFrame Frame;
	Frame.iLeft = (int)p_Sprite->Position.fx;
	Frame.iTop = (int)p_Sprite->Position.fy;
	// Atribui a Frame.iRight a posição do personagem + o seu tamanho em x
	Frame.iRight = (int)(p_Sprite->Position.fx + p_Sprite->pr_Image->FrameSize.fx);
	// Atribui a Frame.iRight a posição do personagem + o seu tamanho em y
	Frame.iBottom = (int)(p_Sprite->Position.fy + p_Sprite->pr_Image->FrameSize.fy);

	return Frame;
}

//---------------------------------------------------------------------------- 
// Nome: Shot(void)
// Desc: Faz o personagem atirar, devendo ser reescrita nas classes filhas
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CCharacter::Shot(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Kill(void)
// Desc: Mata o personagem
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CCharacter::Kill(void)
{
	//21.1.3. 
	//personagem só pode morrer caso ele não esteja morrendo no momento
	if(!bIsDieing)
	{

	}
}

//---------------------------------------------------------------------------- 
// Nome: IsDieing(void)
// Desc: Retorna verdadeiro caso personagem esteja morrendo
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CCharacter::IsDieing(void)
{
	return bIsDieing;
}