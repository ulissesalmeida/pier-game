#include "Shot.h"
#include "NGLSprite.h"
#include "NGLFrame.h"
#include "Character.h"
#include "Level.h"
#include "NGLMain.h"

//---------------------------------------------------------------------------- 
// Nome: CShot(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CShot::CShot(void)
{
	State						= SS_SHOT;
	bPlayerShot			= false;
	p_SndExplosion	= NULL;
	pr_Owner				= NULL;
}

//---------------------------------------------------------------------------- 
// Nome: CShot(void)
// Desc: construtor que cria o tiro com os par�metros necess�rios.
// Pams: nenhum
//---------------------------------------------------------------------------- 
CShot::CShot(CCharacter *p_OwnerParam, CNGLSprite *p_ShotParam, CNGLSprite *p_ExplodeParam, CNGLVector SpeedParan, CNGLVector PositionParam)
{
	pr_Level = p_OwnerParam->pr_Level;
	Create(p_OwnerParam,p_ShotParam,p_ExplodeParam,SpeedParan,PositionParam);
}

//---------------------------------------------------------------------------- 
// Nome: ~CShot(void)
// Desc: destrutor padr�o 
// Pams: nenhum
//---------------------------------------------------------------------------- 
CShot::~CShot(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Executa a maquina de estados do tiro
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CShot::Execute(void)
{
	switch(State)
	{
		case SS_SHOT:
		{
			if(p_SprShot)
			{
				//19.2.1. 
				//1. atualiza o tempo do tiro

				//2. Se o tiro estiver dentro de seu tempo de vida
				if(!TimeAlive.Ended()) //se o tiro n�o terminou...
				{
					//atualiza a posi��o do tiro


					CNGLVector LayerSize = p_SprShot->pr_Layer->GetLayerSize();
					//termina o tiro caso tenha passado dos limites da layer
					if(p_SprShot->Position.fy < 0 || p_SprShot->Position.fy > LayerSize.fy ||
						p_SprShot->Position.fx < 0 || p_SprShot->Position.fx > LayerSize.fx)
					{
						State = SS_END;
					}
					
					//trata colis�o do tiro com o cen�rio

					//trata as colis�es do tiro com personagens

				}
				else
				{
					//3. explode se o tempo do tiro acabou

				}
			}
			break;
		}
		case SS_EXPLODE:
		{
			//19.2.1. 
			//4. atualiza o sprite da explos�o

			//5. caso a anima��o tenha terminado trocar estado para SS_END


			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: HandleCharacterCollision(void)
// Desc: trata a colis�o do tiro com os personagens
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CShot::HandleCharacterCollision(void)
{
	//21.1.4.

}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Libera recursos alocados para o tiro (som e sprites)
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CShot::Release(void)
{
	//deletando sprite do tiro
	if(p_SprShot)
	{
		delete p_SprShot;
		p_SprShot = NULL;
	}
	//deletando sprite da explos�o
	if(p_SprExplosion)
	{
		delete p_SprExplosion;
		p_SprExplosion = NULL;
	}
	
	//deletando sons
	pr_Level->pr_Main->SoundManager.DeleteSound(&p_SndExplosion);
	
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: HandleBrickCollsion(void)
// Desc: Trata colis�o do tiro com os bricks do cen�rio
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CShot::HandleBrickCollsion(void)
{
  CNGLLayer *p_LayLevel = p_SprShot->pr_Layer;
	//pega o tamanho do brick 
	int iBrickWidth = (int)p_LayLevel->BrickSize.fx;
	int iBrickHeight = (int)p_LayLevel->BrickSize.fy;

	//pega o quadro do tiro
	CNGLFrame SpriteFrame((int)p_SprShot->Position.fx,
												(int)p_SprShot->Position.fy,
                        (int)(p_SprShot->Position.fx + p_SprShot->pr_Image->FrameSize.fx),
												(int)(p_SprShot->Position.fy + p_SprShot->pr_Image->FrameSize.fy));

	//pega os indices dos bricks sobre os quais a extremidades do sprite est�o
	int iX    = SpriteFrame.iLeft/iBrickWidth;
	int iY	  = SpriteFrame.iTop/iBrickHeight;
	int iMaxX = (SpriteFrame.iRight/iBrickWidth)+1;
	int iMaxY = (SpriteFrame.iBottom/iBrickHeight)+1;

	//testa a validade dos indices
  if(iX >= 0 && iY  >= 0)
	{
		int index = 0;
		//varre os bricks sobre os quais os sprite est�
		for(iX = SpriteFrame.iLeft/iBrickWidth; iX <= iMaxX; iX++)
		{
			for(iY	= SpriteFrame.iTop/iBrickHeight; iY <= iMaxY; iY++)
			{
				//pega o indice no vetor da layer do brick
				index  = (iX < (int)p_LayLevel->NumBricks.fx)? iX : iX - (int)p_LayLevel->NumBricks.fx;
				index += (iY < (int)p_LayLevel->NumBricks.fy)? iY*(int)p_LayLevel->NumBricks.fx : (iY - (int)p_LayLevel->NumBricks.fy)*(int)p_LayLevel->NumBricks.fx;

				//se o brick existe
				if(p_LayLevel->p_Bricks[index])
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
						ChangeState(SS_EXPLODE);
					}//if
				}//if
			}//for
		}//for
	}
}

//---------------------------------------------------------------------------- 
// Nome: Create(void)
// Desc: Cria o tiro, atribuindo par�metros necess�rios para uma inst�ncia do tiro.
// Pams: dono do tiro, sprite do tiro, explos�o do tiro, velocidade, posi��o inicial
//---------------------------------------------------------------------------- 
void CShot::Create(CCharacter *p_OwnerParam, CNGLSprite *p_ShotParam, CNGLSprite *p_ExplodeParam, CNGLVector SpeedParam, CNGLVector PositionParam)
{
	//inicializando tempo de vida do tiro
	TimeAlive.Init(&pr_Level->pr_Main->TimeHandler,1000);
	//estado inicial do tiro
	State								= SS_SHOT;
	//"dono" do tiro
	pr_Owner						= p_OwnerParam;
	//verdadeiro se for um tiro do jogador
	bPlayerShot					= p_OwnerParam->IsPlayer();
	//clonar o sprite do tiro
	p_SprShot						= p_ShotParam->GetClone(false);
	//clonar o sprite da explos�o
	p_SprExplosion			= p_ExplodeParam->GetClone(false);
	//velocidade do tiro
	vSpeed							= SpeedParam;
	//posi��o inicial do tiro
	p_SprShot->Position	= PositionParam;
	//som da explos�o
	p_SndExplosion			= pr_Level->pr_Main->SoundManager.LoadSound("Sounds/sfx_Explosion.wav",true);
}

//---------------------------------------------------------------------------- 
// Nome: Draw(void)
// Desc: Desenha o tiro ou explos�o. Ela deve ser utilizada porque os clones destes sprites
//			 n�o s�o inseridos na lista de sprites do jogo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CShot::Draw(void)
{
	switch(State)
	{
		//19.2.4. 	
		case SS_SHOT: 
		{
			//1. desenha sprite do tiro

			break;
		}
		case SS_EXPLODE: 
		{
			//2. desenha sprite da explos�o

			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(ShotState NewState)
// Desc: Muda o estado da m�quina
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CShot::ChangeState(CShot::ShotState NewState)
{
	//somente muda o estado se o novo for diferente do atual
	if(State != NewState)
	{
		switch(NewState)
		{
			case SS_EXPLODE:
			{
				if(State == SS_SHOT)
				{
					//19.2.2. 
					//1. Posiciona o sprite de explos�o

					//2. Inicia a anima��o de explos�o

					//3. Tocar o som de explos�o


					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
			case SS_END:
			{
				if(State == SS_EXPLODE)
				{
					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
		}
	}
}
