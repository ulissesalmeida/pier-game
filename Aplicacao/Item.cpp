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
#include "Item.h"
#include "NGLSprite.h"
#include <math.h>
#include "Level.h"
#include <time.h>

//tempo de invencibilidade de 8 segundos
#define INVINCIBILITY_TIME 8000

//---------------------------------------------------------------------------- 
// Nome: CItem(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CItem::CItem(void)
{
	// atribui estado inicial do item
	State						= IS_IDLE;
	// ponteiro para sprite do item
	p_Sprite				= NULL;
	p_SprShield			= NULL;
	p_SndPickup			= NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CItem(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CItem::~CItem(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Libera recursos alocados pelo item (sprites e som)
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CItem::Release(void)
{
	pr_Level->p_LayLevel->DeleteSprite(&p_Sprite);
	pr_Level->p_LayLevel->DeleteSprite(&p_SprShield);
	pr_Level->pr_Main->SoundManager.DeleteSound(&p_SndPickup);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: Inicializa os sprites e sons do item de acordo com o seu tipo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CItem::Initialize(CItem::ItemType TypePam)
{
	Type = TypePam;

	string FileName;
	CNGLVector FrameSize;
	switch(Type)
	{
		case IT_YELLOW:
		{
			FileName = ITEM_YELLOW_SPR;
			FrameSize = CNGLVector(30,30);
			break;
		}
		case IT_BLUE:
		{
			FileName = ITEM_BLUE_SPR;
			FrameSize = CNGLVector(45,45);
			break;
		}
		case IT_RED:
		{
			FileName = ITEM_RED_SPR;
			FrameSize = CNGLVector(60,60);
			break;
		}
		case IT_INVENCIBLE:
		{
			FileName = ITEM_INVENCIBLE_SPR;
			FrameSize = CNGLVector(50,70);
			
			//criando sprite do escudo, caso o item seja de invencibilidade
			p_SprShield = pr_Level->p_LayLevel->CreateSprite(ITEM_SHIELD_SPR,CNGLVector(100,110));
			//deixando o escudo invisível, pois ele somente aparecerá quando o jogador pegá-lo
			p_SprShield->bVisible = false;
			//adicionando animação do escudo
			p_SprShield->AddAnimation(10,true,4,0,1,2,3);
			p_SprShield->SetCurrentAnimation(0);
			
			break;
		}
	}
	
	
	//18.2.1. 
	//1. cria o sprite do item
	p_Sprite = pr_Level->p_LayLevel->CreateSprite(FileName.c_str(),FrameSize);
	//2. adiciona as animações do item parado e desaparecendo 
	p_Sprite->AddAnimation(4,true,4,0,1,2,1);
	p_Sprite->AddAnimation(10,false,4,3,4,5,6);
	//3. ajusta a primeira animação (0) como corrente
	p_Sprite->SetCurrentAnimation(0);

	//4. carregar o som correto de quando o item é pego, de acordo com o tipo
	if(Type != IT_INVENCIBLE)
	{
		// carregando som como efeito sonoro para quando se pega um item.
		p_SndPickup = pr_Level->pr_Main->SoundManager.LoadSound(ITEM_PICKUP_WAV,true);
	}
	else
	{
		// carregando som como efeito sonoro para quando se pega um item invencibilidade.
		p_SndPickup = pr_Level->pr_Main->SoundManager.LoadSound(ITEM_INVENCIBLE_WAV,true);
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Executa o item de acordo com cada estado dele
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CItem::Execute(void)
{
	switch(State)
	{
		case IS_IDLE:
		{
			OnIdle();
			break;
		}
		case IS_RUN:
		{
			OnRun();
			break;
		}
		case IS_END:
		{
			//Este estado que indica que o item não tem mais utilidade. 
			//Será eliminado do jogo pela CLevel.
			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(CItem::ItemState NewState)
// Desc: Muda a máquina de estados do item
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CItem::ChangeState(CItem::ItemState NewState)
{
	//somente muda o estado se o novo for diferente do atual
	if(State != NewState)
	{
		switch(NewState)
		{
			case IS_RUN:
			{
				if(State == IS_IDLE)
				{
					//18.2.3. 
					//1. muda animação para "explodir" o item
					if(p_Sprite) p_Sprite->SetCurrentAnimation(1);

					//1. soma pontos ao jogador
					AddPointsToPlayer();
					
					//2. tocando som de item pego
					if(p_SndPickup) p_SndPickup->Play(false);

					//3. tratamento especial para o item de invencibilidade
					if(Type == IT_INVENCIBLE)
					{
						UpdateShieldOnPlayer();

						//inicializa acumulador 
						AccumInv.Init(&pr_Level->pr_Main->TimeHandler, INVINCIBILITY_TIME);
					}

					//estado atual recebe novo estado
					State = NewState;
					break;
				}
				break;
			}
			case IS_END:
			{
				if(State == IS_RUN)
				{
					//18.2.3.
					//4. caso o item seja de invencibilidade, o jogador deve ter seu atributo bIvencible em false
					if(Type == IT_INVENCIBLE){
						pr_Level->GetPlayer()->bInvincible = false;
					}
					//estado atual recebe novo estado
					State = NewState;
					break;
				}
				break;
			}
		}
	}
}

void CItem::UpdateShieldOnPlayer(){
	//ajusta posição do escudo
	p_SprShield->Position = pr_Level->GetPlayer()->p_Sprite->Position;

	//ajuste da posição do escudo, para ficar em cima do jogador
	p_SprShield->Position.fx -= 15.0f;
	p_SprShield->Position.fy -=5.0f;
	//exibe o escudo
	p_SprShield->bVisible = true;
}

//---------------------------------------------------------------------------- 
// Nome: OnIdle(void)
// Desc: Trata o estado IS_IDLE. Este estado ocorre quando o item está em espera no jogo.
//			 Se colidir com o jogador, então muda para o estado IS_RUN.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CItem::OnIdle(void)
{
	//18.2.2. 
	//se o jogador encostar (colidir) neste item, então deve-se
	//mudar estado do item para IS_RUN
	if(p_Sprite->GetFrame().Collide(pr_Level->GetPlayer()->GetFrame())){
		ChangeState(IS_RUN);
	}

}

//---------------------------------------------------------------------------- 
// Nome: OnRun(void)
// Desc: Trata o estado IS_RUN. Este estado somente verifica se acabou a animação de item explodindo.
//			 Se terminou, então muda o estado para IS_END. A CLevel se encarregará  de remover este item
//			 de sua lista e desalocá-lo do jogo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CItem::OnRun(void)
{
	//18.2.5. 
	//1. caso o item não seja de invencibilidade, verificar se terminou a animação
	//de desaparecimento e terminar o item se positivo
	if(Type != IT_INVENCIBLE)
	{
		// se terminou animação de item desaparecendo, então mudar de estado.
		if(p_Sprite->Animations[1]->Ended()) ChangeState(IS_END);

	}
	//2. se o item for de invencibilidade, deve-se atualizar acumulador e
	//verificar se o tempo terminou. Caso positivo, muda de estado para IS_END.
	//Senão, ajusta posição do escudo em cima do jogador
	else
	{
		AccumInv.Update();
		if(AccumInv.Ended()) ChangeState(IS_END);
		else UpdateShieldOnPlayer();
	}
}

//---------------------------------------------------------------------------- 
// Nome: AddPointsToPlayer(void)
// Desc: Esta função deve somar pontos ao jogador de acordo com o item que foi pego.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CItem::AddPointsToPlayer(void)
{
	//18.2.4. acumular pontos ao jogador de acordo com o item pego
	switch(Type){
		case IT_BLUE:
			pr_Level->GetPlayer()->uiPoints += 100; 
		break;
		case IT_RED:
			pr_Level->GetPlayer()->uiPoints += 150; 
		break;
		case IT_YELLOW:
			pr_Level->GetPlayer()->uiPoints += 200; 
		break;
		case IT_INVENCIBLE:
			pr_Level->GetPlayer()->uiPoints += 250; 
		break;
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetState(void)
// Desc: Retorna o estado corrente do item
// Pams: nenhum
//---------------------------------------------------------------------------- 
CItem::ItemState CItem::GetState(void)
{
	return State;
}


