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
#include "Level.h"
#include "NGLImage.h"
#include <math.h>
#include <time.h>
#include "Dummy.h"
#include "DummyKiller.h"
#include "FlyerBomber.h"

//---------------------------------------------------------------------------- 
// Nome: CLevel(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CLevel::CLevel(void)
{
	p_LayLevel			= NULL;
	p_LayInterface	= NULL;
	p_MsgPaused			= NULL;
	p_MsgGameOver		= NULL;
	p_MsgCongrats		= NULL;
	p_SprCoin				= NULL;
	p_SprSwitch			= NULL;
	pr_Player				= NULL;
	p_SndCongrats		= p_SndTrack = p_SndSwitch = NULL;
	State						= GS_MENU;
	memset(p_SprNumbers,0,sizeof(p_SprNumbers));
	memset(p_SprLives,0,sizeof(p_SprLives));
}

//---------------------------------------------------------------------------- 
// Nome: ~CLevel(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CLevel::~CLevel(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza a classe, liberando todos os objetos alocados.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CLevel::Release(void)
{
	//desaloca os personagens
	ReleaseCharacters();
	//desaloca os itens
	ReleaseItems();
	//releasing menu
	Menu.Release();

	//deleta os sons
	pr_Main->SoundManager.DeleteSound(&p_SndSwitch);
	pr_Main->SoundManager.DeleteSound(&p_SndCongrats);
	pr_Main->SoundManager.DeleteSound(&p_SndTrack);

	//libera a cena da classe pai
	CNGLScene::Release();

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: Inicializa a cena. Inicializa cenários,interfaces, jogador, inimigos e itens.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CLevel::Initialize(void)
{
	//15.3.1
	//Adiciona as imagens a cena
	//imagem 0
	AddTileImage("Surfaces/tile_Level.bmp",CNGLVector(32,32)); //tiles para compor cenário
	//imagem 1
	AddTileImage("Surfaces/tile_Background.bmp",CNGLVector(128,350)); //tile do fundo

	//cria a layer de fundo (background). 1 único brick de 128x350
	CNGLLayer *p_LayBkg    = CreateLayer(CNGLVector(128,350),CNGLVector(1,1));
	//cria a layer do meio. Bricks de 32x32
	CNGLLayer *p_LayMiddle = CreateLayer(CNGLVector(32,32));
	//cria layer da fase (cenário). Bricks de 32x32
	p_LayLevel = CreateLayer(CNGLVector(32,32));

	//configura as velocidades para as layers
	//velocidade menor para dar impressão de profundidade
	p_LayBkg->Speed			= CNGLVector(0.5f,0.5f); 
	p_LayMiddle->Speed	= CNGLVector(0.7f,0.7f);

	//inicializa a layer de background
	//o Brick da posição (0,0) utiliza a imagem 1 e o quadro 0
	p_LayBkg->SetBrick(CNGLVector(0,0),1,0);
	p_LayBkg->Offset.fy = 200.0f; //pequeno deslocamento para ajustar brick

	//inicializa a layer intermediária
	//estrutura de configuração de bricks
	stNGLBrickConfig ConfigMiddle[3];
	//cor vermelha refere-se ao quadro 16 da imagem 0
	ConfigMiddle[0].uiColor		= RGB(255,0,0);
	ConfigMiddle[0].iImage		= 0;
	ConfigMiddle[0].iFrame		= 16;
	//cor verde refere-se ao quadro 17 da imagem 0
	ConfigMiddle[1].uiColor		= RGB(0,255,0);
	ConfigMiddle[1].iImage		= 0;
	ConfigMiddle[1].iFrame		= 17;
	//cor azul refere-se ao quadro 18 da imagem 0
	ConfigMiddle[2].uiColor		= RGB(0,0,255);
	ConfigMiddle[2].iImage		= 0;
	ConfigMiddle[2].iFrame		= 18;
	//faz a criação dos bricks configurados
	p_LayMiddle->CreateBricksFromBitmap("Surfaces/lay_Middle.bmp",ConfigMiddle,3);

	//inicializa a layer da frente (cenário da fase)
	//estrutura de configuração de bricks
	stNGLBrickConfig ConfigLevel[2];
	//cor preta refere-se ao quadro 0 da imagem 0
	ConfigLevel[0].uiColor	= RGB(0,0,0);
	ConfigLevel[0].iImage		= 0;
	ConfigLevel[0].iFrame		= 0;
	//cor vermelha refere-se ao quadro 4 da imagem 0
	ConfigLevel[1].uiColor	= RGB(255,0,0);
	ConfigLevel[1].iImage		= 0;
	ConfigLevel[1].iFrame		= 4;
	p_LayLevel->CreateBricksFromBitmap("Surfaces/lay_Level.bmp",ConfigLevel,2);

	//inicializa modelo de tiro (fica invisível)
	p_SprShot = p_LayLevel->CreateSprite("Surfaces/spr_Shot.bmp",CNGLVector(9,9));
	p_SprShot->bVisible = false;
	//inicializa o modelo da explosão
	p_SprShotExplode = p_LayLevel->CreateSprite("Surfaces/spr_Explosion.bmp",CNGLVector(64,64));
	p_SprShotExplode->AddAnimation(30,false,17,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1);
	p_SprShotExplode->SetCurrentAnimation(0);
	p_SprShotExplode->bVisible = false;

	//inicia o menu
	Menu.pr_Level = this; //referência para classe CLevel
	Menu.Initialize();

	//iniciando interface
	InitializeInterface();

	//23.1.1.
	//1. criar o sprite da moeda final

	//1. adicionar sua animação contínua

	//1. ajustar animação corrente como 0

	//1. colocar moeda na posição (7235,430)


	//2. carrega o som de congratulação


	//3. criar o sprite da alavanca

	//3. adicionar as animações da alavanca


	//3. ajustar animação corrente como 0

	//3. colocar a alavanca na posição (7314,224)


	//4. carregar o som da alavanca


	//5. carregar trilha sonora


	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Executa o jogo. Verifica cada estado da máquina e chama o método adequado.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::Execute(void)
{
	switch(State)
	{
		case GS_MENU:
		{
			OnMenu();
			break;
		}
		case GS_GAME:
		{
			OnGame();
			break;
		}
		case GS_PAUSE:
		{
			OnPause();
			break;
		}
		case GS_CONGRATULATIONS:
		{
			OnCongratulations();
			break;
		}
		case GS_GAMEOVER:
		{
			OnGameOver();
			break;
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: Draw(void)
// Desc: desenha a cena
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::Draw(void)
{
	//chama primeiro o Draw do pai
	CNGLScene::Draw();

	//16.3.2
	//2. desenha o cursor do mouse se estiver no estado menu

	if(State == GS_MENU){
		Menu.DrawMouse();	
	}

	//desenha os tiros somente se o estado for GS_GAME
	if(State == GS_GAME)
	{
		int iSize = (int)ListShots.size();
		for(int i = 0; i < iSize; i++)
		{
			ListShots[i]->Draw();
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: LookToPlayer(void)
// Desc: Faz a cena "olhar" para o jogador, mantendo ele sempre centralizado na tela.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::LookToPlayer(void)
{
	//15.3.5
	//Armazena o tamanho da layer
	CNGLVector LayerSize = p_LayLevel->GetLayerSize();

	//Vetor que representa o deslocamento minimo para fazer 
	//a movimentação da layer
	CNGLVector vOffset = pr_Main->VideoManager.VideoSize;

	//divide o tamanho da tela por dois para pegar o centro
	vOffset.fx *= 0.5f;
	vOffset.fy *= 0.5f;

	//o offset minimo em x é o centro da tela menos a metade do tamanho 
	//do quadro do sprite o que faz com que o deslocamento sempre coloque
	//o sprite no centro em x.
	vOffset.fx -= pr_Player->p_Sprite->pr_Image->FrameSize.fx * 0.5f;

	//Vetor de deslocamento da cena
	//o deslocamento da cena é o inverso do deslocamento do sprite
	//se o sprite avança 1 pixel, a cena retorna 1 pixel
	CNGLVector vScroll = pr_Player->LastPos - pr_Player->p_Sprite->Position;
	
	//Se o deslocamento do sprite em relação ao inicio ou fim da layer 
	//é menor ou igual ao deslocamento mínimo (vOffset.fx) então não move a layer em x
	if((pr_Player->p_Sprite->Position.fx <= vOffset.fx) || (pr_Player->p_Sprite->Position.fx >= LayerSize.fx - vOffset.fx))
	{
		vScroll.fx = 0.0f;
	}

	//Se o deslocamento do sprite em relação ao inicio ou fim da layer 
	//é menor ou igual ao deslocamento mínimo (vOffset.fy) então não move a layer em y
	if((pr_Player->p_Sprite->Position.fy <= vOffset.fy) || (pr_Player->p_Sprite->Position.fy >= LayerSize.fy - vOffset.fy))
	{
		vScroll.fy = 0.0f;
	}

	//faz o deslocamento da cena
	Scroll(vScroll);

	//A layer em que o sprite se encontra (em X), sempre possui como deslocamento o inverso
	//da posição do sprite menos o offset mínimo fazendo com que o personagem fique no centro da tela
	if(vScroll.fx != 0.0f)
	{
		p_LayLevel->Offset.fx = -(pr_Player->p_Sprite->Position.fx - vOffset.fx);
	}

	//A layer em que o sprite se encontra (em Y), sempre possui como deslocamento o inverso
	//da posição do sprite menos offset mínimo fazendo com que o personagem fique 
	//um pouco abaixo do centro da tela
	if(vScroll.fy != 0.0f)
	{
		p_LayLevel->Offset.fy = -(pr_Player->p_Sprite->Position.fy - vOffset.fy);
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreatePlayer(void)
// Desc: Cria o jogador
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::CreatePlayer(void)
{
	//15.3.3
	CPlayer *p_Player = NULL;
	p_Player = new CPlayer();
	if(p_Player)
	{
		//inicializando o jogador (player)
		p_Player->pr_Level = this;
		//inicializa o jogador na posição (0,0)
		p_Player->Initialize(CNGLVector(0,0));
		//adiciona player na lista de personagens
		ListCharacters.push_back(p_Player);
		//ajustando player corrente
		pr_Player = p_Player;
		//ajusta todas as layers da cena para irem à sua posição (0,0)
		int iLayers = (int)Layers.size();
		for(int i = 0 ; i < iLayers; i++)
		{
			Layers[i]->Offset = CNGLVector(0,0);
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateItem(CItem::ItemType Type, CNGLVector Position)
// Desc: Cria um item
// Pams: tipo do item, posição
//---------------------------------------------------------------------------- 
void CLevel::CreateItem(CItem::ItemType Type, CNGLVector Position)
{
	//15.3.4
	CItem *p_Item = NULL;
	p_Item = new CItem();
	if(p_Item)
	{
		//inicializando o item
		p_Item->pr_Level = this;
		p_Item->Initialize(Type);
		//ajusta a posição do sprite
		p_Item->p_Sprite->Position = Position;
		//adiciona item na lista
		ListItems.push_back(p_Item);
	}
}

//---------------------------------------------------------------------------- 
// Nome: OnMenu(void)
// Desc: Trata o estado GS_MENU
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::OnMenu(void)
{
	//executa o menu
	Menu.Execute();
}

//---------------------------------------------------------------------------- 
// Nome: OnGame(void)
// Desc: Trata o estado GS_GAME
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::OnGame(void)
{
	if(pr_Main->InputManager.KeyPressed(DIK_ESCAPE))
	{
		ChangeState(GS_MENU);
	}	

	//atualiza os personagens o laço é feito de trás para diante porque caso
	//um ou mais personagens tenham terminado sua execução, eles podem ser
	//excluídos sem dar problema de índices inválidos no vetor.
	int i = 0;
	for(i = (short)ListCharacters.size()-1; i >= 0; i--)
	{
		//executa o personagem
		ListCharacters[i]->Execute();

		//21.1.5.
		//se o personagem morreu e não for o jogador, remover da lista

	}
	
	//atualiza a câmera no jogador se ele não estiver morrendo
	if (!pr_Player->IsDieing())
	{
		LookToPlayer();
	}
	
	//17.5.1. 
	//colocar o jogo em pausa, caso tecla P seja pressionada
	if(pr_Main->InputManager.KeyPressed(DIK_P))
	{
		ChangeState(GS_PAUSE);
	}

	
	//18.2.6. Atualização ou execução dos itens
	//o laço é feito de trás para frente porque caso um ou mais
	//itens tenham terminado sua execução, eles podem ser removidos
	//sem dar problema de índices inválidos no vetor.

	int iSize = (int) ListItems.size();

	for(int i=iSize-1; i >= 0; i--){
		ListItems[i]->Execute();
		if(ListItems[i]->GetState() == CItem::IS_END){
			ListItems[i]->Release();
			delete ListItems[i];
			ListItems.erase(ListItems.begin()+i);
		}
	}

	//23.1.3. 
	//2. se os itens terminaram, preparar programação de fim de jogo.
	if(iSize == 0)
	{
		//a alavanca ainda não foi ativada...
		if(p_SprSwitch->sCurrentAnim == 0)
		{
			//se o jogador colide com a alavanca

		}
		//3. interação do jogador com a moeda	
		else
		{
			//caso o jogador encoste na moeda, mudar estado do jogo

		}
	}

	//se existe a layer de interface...
	if(p_LayInterface)
	{
		//17.2.3. Atualizar o placar
		UpdateScore();
		//17.3.3. Atualizar o número de vidas
		UpdateLives();

	}

	//19.2.3. atualiza os tiros
	//remove aqueles que estão no estado SS_END

}

//---------------------------------------------------------------------------- 
// Nome: OnPause(void)
// Desc: Trata o estado GS_PAUSE
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::OnPause(void)
{
	//17.5.2. colocar o jogo em GS_GAME se a tecla P for pressionada
	if(pr_Main->InputManager.KeyPressed(DIK_P))
	{
		ChangeState(GS_GAME);
	}
}

//---------------------------------------------------------------------------- 
// Nome: OnGameOver(void)
// Desc: Trata o estado GS_GAMEOVER
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::OnGameOver(void)
{
	if(pr_Main->InputManager.KeyPressed(DIK_ESCAPE)||pr_Main->InputManager.KeyPressed(DIK_RETURN))
	{
		ChangeState(GS_MENU);
	}
}

//---------------------------------------------------------------------------- 
// Nome: OnCongratulations(void)
// Desc: Trata o estado GS_CONGRATULATIONS
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::OnCongratulations(void)
{
	//21.1.5. trocar estado do jogo para GS_MENU caso as teclas ESC ou ENTER tenham sido pressionadas

}

//---------------------------------------------------------------------------- 
// Nome: InitializeInterface(void)
// Desc: Inicializa layer e sprites de interface.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::InitializeInterface(void)
{
	int i = 0;
	//17.1.
	//1. criar a layer da interface
	p_LayInterface = CreateLayer(CNGLVector(0,0));	

	//2. colocar a velocidade da layer como nula, para que ela não
	//sofra deslocamento
	p_LayInterface->Speed = CNGLVector(0,0);

	//3. esconder a layer de interface
	p_LayInterface->bVisible = false;

	//17.2.1
	//Abaixo a criação de um vetor com os números para as pontuações
	for(int i = 0; i < NUM_ALGARISMS; i++){
		p_SprNumbers[i] = p_LayInterface->CreateSprite(NUMBERS_SPR,CNGLVector(26,38));
		if(p_SprNumbers[i]){
			for(int j = 0; j < 10; j++){
				p_SprNumbers[i]->AddAnimation(1,false,1,j);
			}
			p_SprNumbers[i]->Position.fy = 0.0f;
			p_SprNumbers[i]->Position.fx = 300.0f + (float) (i*p_SprNumbers[i]->GetFrame().GetWidth());
		}

	}

	//17.3.1. 
	//1. Criar um sprite para cada uma das três posições do vetor de vidas
	for(i = 0; i < NUM_LIVES; i++)
	{
		//1. criar o sprite
		p_SprLives[i] = p_LayInterface->CreateSprite(LIVES_SPR, CNGLVector(34,49));

		//2. quadro 0 de animação é o vazio (vida vazia)
		//2. quadro 1, 2 ou 3 corresponde a vida cheia -- Foda-se Quero vidas da mesma cor
		p_SprLives[i]->AddAnimation(1,false,1,0);
		p_SprLives[i]->AddAnimation(1,false,1,1);

		//3 posiciona as vidas
		p_SprLives[i]->Position.fy = 0.0f;
		p_SprLives[i]->Position.fx = (float) (i*p_SprLives[i]->GetFrame().GetWidth());
	}

	//17.4.
	//1. cria mensagem de pausa
	p_MsgPaused = p_LayInterface->CreateSprite(PAUSED_MSG,CNGLVector(200,30));
	p_MsgPaused->AddAnimation(1,false,1,0);
	p_MsgPaused->bVisible = false;
	Centralize(p_MsgPaused);

	//2. cria mensagem de game over
	p_MsgGameOver = p_LayInterface->CreateSprite(GAME_OVER_MSG,CNGLVector(148,26));
	p_MsgGameOver->AddAnimation(1,false,1,0);
	p_MsgGameOver->bVisible = false;
	Centralize(p_MsgGameOver);

	//3. cria mensagem de cangratulações
	p_MsgCongrats = p_LayInterface->CreateSprite(CONGRATS_MSG,CNGLVector(246,66));
	p_MsgCongrats->AddAnimation(1,false,1,0);
	p_MsgCongrats->bVisible = false;
	Centralize(p_MsgCongrats);

}

void CLevel::Centralize(CNGLSprite *sprite){
	sprite->Position.fx = (pr_Main->VideoManager.VideoSize.fx * 0.5f) - (sprite->GetFrame().GetWidth()*0.5f);
	sprite->Position.fy = (pr_Main->VideoManager.VideoSize.fy * 0.5f) - (sprite->GetFrame().GetHeight()*0.5f);
}

//---------------------------------------------------------------------------- 
// Nome: UpdateScore(void)
// Desc: Atualiza o placar do jogo na tela.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::UpdateScore(void)
{
	//17.2.2.
	//lembre-se que são NUM_ALGARISMS algarismos que devem ser mostrados na tela.
	//Portanto, deve-se separar cada algarismo da variável pr_Player->uiPoints
	//e mostrá-lo corretamente na tela.
	int iDiv = (int) pow (10.0f,NUM_ALGARISMS-1);
	for(int i =0; i < NUM_ALGARISMS; i++){
		int iIndex = ((pr_Player->uiPoints / iDiv)%10);
		p_SprNumbers[i]->SetCurrentAnimation(iIndex);
		iDiv /= 10;
	}

}

//---------------------------------------------------------------------------- 
// Nome: UpdateLives(void)
// Desc: Atualiza os sprites de vida na tela
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::UpdateLives(void)
{
	//17.3.2. 
	//1. Ajustando os sprites de vidas com o quadro 0 (vazio)
	for(unsigned int i =0; i < NUM_LIVES; i++){
		p_SprLives[i]->SetCurrentAnimation(0);
	}

	//2. muda os quadros de vidas para representar número de vidas do jogador

	for(unsigned int i = 0; i < pr_Player->uiLives; i++){
		p_SprLives[i]->SetCurrentAnimation(1);
	}
}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(CLevel::GameState NewState)
// Desc: Muda o estado da máquina de estados da CLevel
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CLevel::ChangeState(CLevel::GameState NewState)
{
	//somente muda o estado se o novo for diferente do atual
	if(State != NewState)
	{
		switch(NewState)
		{
			case GS_GAME:
			{
				if(State == GS_MENU)
				{
					if(!Menu.bInGame)
					{
						Menu.bInGame = true; //indica para o menu que o jogo está rodando
						CreateItems();		//cria os itens
						CreateEnemies();	//cria os inimigos
						CreatePlayer();		//cria o jogador						
						if(p_SprSwitch)
						{
							//ajusta animação da alavanca da fase para 0 (levantada)
							p_SprSwitch->SetCurrentAnimation(0);
						}
						//faz aparecer layer de interface (com pontos e vidas)
						p_LayInterface->bVisible = true;
					}					
					//esconde menu
					Menu.Show(false);

					State = NewState; //estado atual recebe novo estado
					break;
				}
				if(State == GS_PAUSE)
				{
					//17.5.3. Esconder mensagem de pausa
					p_MsgPaused->bVisible = false;

					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
			case GS_PAUSE:
			{
				if(State == GS_GAME)
				{
					//17.5.3. Exibir mensagem de pausa
					if(p_MsgPaused)
					{
						p_MsgPaused->bVisible = true;
					}

					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
			case GS_MENU:
			{
				if(State == GS_GAME)
				{	
					Menu.bInGame = true; //mostrará botão "Continuar"
					Menu.Show(true); //mostra o menu principal
					State = NewState; //estado atual recebe novo estado
					break;
				}
				if((State == GS_CONGRATULATIONS)||(State == GS_GAMEOVER))
				{
					if(p_MsgCongrats)
					{
						//esconde mensagem de congratulação
						p_MsgCongrats->bVisible = false;
					}
					if(p_MsgGameOver)
					{
						//esconde mensagem de game over
						p_MsgGameOver->bVisible = false;
					}
					ReleaseCharacters();	//desalocando os inimigos
					ReleaseItems();				//desalocando os itens
					Menu.bInGame = false; //mostrará botão "Novo Jogo"
					Menu.Show(true);			//mostra o menu principal
					Scroll(CNGLVector(0,0)); //desloca a as layers para o início da fase
					
					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
			case GS_GAMEOVER:
			{
				if(State == GS_GAME)
				{
					if(p_MsgGameOver)
					{
						//mostra mensagem de game over
						p_MsgGameOver->bVisible = true;
					}
					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
			case GS_CONGRATULATIONS:
			{
				if(State == GS_GAME)
				{
					//21.1.4.
					//1. mostrar mensagem de congratulação

					//2. reproduz o som de congratulação

					//3. troca a animação do jogador para a 2


					State = NewState; //estado atual recebe novo estado
					break;
				}
				break;
			}
		}
	}
}

//---------------------------------------------------------------------------- 
// Nome: ReleaseCharacters(void)
// Desc: Desaloca os personagens
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::ReleaseCharacters(void)
{
	for(short s = (short)ListCharacters.size()-1; s >= 0; s--)
	{
		ListCharacters[s]->Release();
		delete ListCharacters[s];
	}
	ListCharacters.clear();
}

//---------------------------------------------------------------------------- 
// Nome: ReleaseItems(void)
// Desc: Desaloca os itens
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::ReleaseItems(void)
{
	for(short s = (short)ListItems.size()-1; s >= 0; s--)
	{
		ListItems[s]->Release();
		delete ListItems[s];
	}
	ListItems.clear();
}

//---------------------------------------------------------------------------- 
// Nome: CreatePlayerShot(CNGLVector Position, CNGLVector vSpeed)
// Desc: Cria um tiro proveniente do jogador.
// Pams: posição inicial do tiro, velocidade do tiro
//---------------------------------------------------------------------------- 
void CLevel::CreatePlayerShot(CNGLVector Position, CNGLVector vSpeed)
{
	CShot *p_Shot = new CShot(pr_Player, p_SprShot, p_SprShotExplode, vSpeed, Position);
	ListShots.push_back(p_Shot);
}

//---------------------------------------------------------------------------- 
// Nome: CreateEnemyShot(CNGLVector Position, CNGLVector vSpeed)
// Desc: Cria um tiro proveniente do inimigo
// Pams: referência para o inimigo que atirou,posição inicial do tiro, velocidade do tiro
//---------------------------------------------------------------------------- 
void CLevel::CreateEnemyShot(CEnemy *pr_Enemy,CNGLVector Position, CNGLVector vSpeed)
{
	//22.1.2. 

}

//---------------------------------------------------------------------------- 
// Nome: CreateEnemy(CEnemy::EnemyType Type, CNGLVector Position,fXPatrolRange)
// Desc: Cria um inimigo
// Pams: tipo do inimigo, posição inicial, raio de patrulha
//---------------------------------------------------------------------------- 
void CLevel::CreateEnemy(CEnemy::EnemyType Type, CNGLVector Position,float fXPatrolRange)
{
	//15.3.2
	CEnemy *pr_Enemy = NULL;
	switch(Type)
	{
		case CEnemy::ET_DUMMY:
		{
			CDummy *p_Dummy = new CDummy();
			pr_Enemy = p_Dummy;
			break;
		}
		case CEnemy::ET_FLYER_BOMBER:
		{
			CFlyerBomber *p_FlyerBomber = new CFlyerBomber();
			pr_Enemy = p_FlyerBomber;
			break;
		}
		case CEnemy::ET_DUMMY_KILLER:
		{
			CDummyKiller *p_DummyKiller = new CDummyKiller();
			pr_Enemy = p_DummyKiller;
			break;
		}
	}
	
	//se foi criado um inimigo...
	if(pr_Enemy)
	{
		pr_Enemy->pr_Level = this;
		pr_Enemy->Type = Type;
		pr_Enemy->fXPatrolRange = fXPatrolRange;
		pr_Enemy->Initialize(Position);
		//adiciona inimigo na lista de personagens
		ListCharacters.push_back(pr_Enemy);
	}
}

//---------------------------------------------------------------------------- 
// Nome: CreateEnemies(void)
// Desc: Cria os inimigos do jogo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::CreateEnemies(void)
{
	//20.2.8. criar inimigos do tipo Dummy

	
	//22.1.6. criar inimigos do tipo DummyKiller


	//22.2.3. criar inimigos do tipo FlyerBomber

}

//---------------------------------------------------------------------------- 
// Nome: DisableBricks(CNGLFrame Rect)
// Desc: Desabilita conjunto de bricks
// Pams: retângulo ou região que os bricks devem ser desabilitados
//---------------------------------------------------------------------------- 
void CLevel::DisableBricks(CNGLFrame Rect)
{
	//23.1.2. 
	//lembre-se para acessar o vetor p_LayLevel->p_Bricks como uma matriz
	//use: vetor[(linha*total_colunas) + coluna], onde linha = Y e coluna = X

}

//---------------------------------------------------------------------------- 
// Nome: CreateItems(void)
// Desc: Cria os itens do jogo
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CLevel::CreateItems(void)
{
	//18.2.7. criar alguns itens
	CreateItem(CItem::IT_YELLOW,CNGLVector(200,256));
	CreateItem(CItem::IT_BLUE,CNGLVector(250,200));
	CreateItem(CItem::IT_RED,CNGLVector(300,156));
	CreateItem(CItem::IT_INVENCIBLE,CNGLVector(350,100));
	CreateItem(CItem::IT_YELLOW,CNGLVector(500,100));
	CreateItem(CItem::IT_BLUE,CNGLVector(700,120));
	CreateItem(CItem::IT_RED,CNGLVector(4000,280));
	CreateItem(CItem::IT_INVENCIBLE,CNGLVector(7060,440));
	CreateItem(CItem::IT_YELLOW,CNGLVector(6880,420));
	CreateItem(CItem::IT_BLUE,CNGLVector(6930,420));
	CreateItem(CItem::IT_RED,CNGLVector(6980,420));
	CreateItem(CItem::IT_INVENCIBLE,CNGLVector(7030,420));

}