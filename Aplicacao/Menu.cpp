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
#include "Menu.h"
#include "NGLImage.h"
#include <math.h>
#include "Level.h"

//---------------------------------------------------------------------------- 
// Nome: CMenu(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CMenu::CMenu(void)
{
	State						= MS_MAIN;
	pr_Level				= NULL;
	p_LayMain				= NULL;
	p_LayOptions		= NULL;
	p_SprMouse			= NULL;
	p_SndMouseOver	= NULL;
	p_SndMouseClick	= NULL;
	bInGame					= false;
	memset(p_SprMain,0,sizeof(p_SprMain));
	memset(p_SprOptions,0,sizeof(p_SprOptions));
}

//---------------------------------------------------------------------------- 
// Nome: ~CMenu(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CMenu::~CMenu(void)
{
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: Finaliza a classe liberando layers e sprites criados no Initialize().
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CMenu::Release(void)
{
	//16.3.9. 
	if(pr_Level)
	{
		//1. Liberar layers
		p_LayMain->Release();
		p_LayOptions->Release();

		//2. Liberar sons
		pr_Level->pr_Main->SoundManager.DeleteSound(&p_SndMouseClick);
		pr_Level->pr_Main->SoundManager.DeleteSound(&p_SndMouseOver);
	}

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: Cria as layers, sprites e sons necessários para o menu.
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CMenu::Initialize(void)
{
	//prática 16.3.1.
	
	//1. estado inicial da máquina
	State = MS_MAIN;
  
	//2. Criação das Layers
	//criando layer do menu Principal
	p_LayMain = pr_Level->CreateLayer(CNGLVector(0,0));

	//cria a Layer do menu de Opções
	p_LayOptions	= pr_Level->CreateLayer(CNGLVector(0,0));

	//3. Criação dos botões (sprites) dos menus
	//criação dos botões do menu Principal

	p_SprMain[IDX_NEW_GAME] = p_LayMain->CreateSprite(NEW_GAME_SPR,CNGLVector(150,23));
	p_SprMain[IDX_OPTIONS] = p_LayMain->CreateSprite(OPTIONS_SPR,CNGLVector(100,31));
	p_SprMain[IDX_QUIT] = p_LayMain->CreateSprite(QUIT_SPR,CNGLVector(65,23));

	//criação dos botões (sprites) do menu de Opções

	p_SprOptions[IDX_FULLSCREEN] = p_LayOptions->CreateSprite(FULLSCREEN_SPR,CNGLVector(182,30));
	p_SprOptions[IDX_BACK] = p_LayOptions->CreateSprite(BACK_SPR,CNGLVector(100,22));

	//4. Posicionamento dos botões

	//posicionar botões do menu principal
	CentralizeSpritesInX(p_SprMain,NUM_MAINITEMS);

	//posicionar botões do menu de opções
	CentralizeSpritesInX(p_SprOptions,NUM_OPTIONSITEMS);	

	//5. Configuração dos sprites com as animações

	ConfigureSpritesAnimation(p_SprMain,NUM_MAINITEMS);

	ConfigureSpritesAnimation(p_SprOptions,NUM_OPTIONSITEMS);

	p_SprOptions[IDX_FULLSCREEN]->SetCurrentAnimation(pr_Level->pr_Main->VideoManager.bFullScreen ? 1 : 0);
	
	//6. Ajusta visibilidade das layers
	p_LayMain->bVisible = true;

	//deixa a layer de opções invisível
	p_LayOptions->bVisible = false;

	//7. Criar o sprite do Mouse, deixando-o invisível
	p_SprMouse = p_LayMain->CreateSprite(CURSOR_SPR,CNGLVector(30,30));
	p_SprMouse->bVisible = false;

	//8. criando sons de menu
	p_SndMouseOver = pr_Level->pr_Main->SoundManager.LoadSound(MOUSE_OVER_WAV,true);
	p_SndMouseClick = pr_Level->pr_Main->SoundManager.LoadSound(MOUSE_CLICKED_WAV,true);

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: CentralizeSpriteInX(void)
// Desc: Centraliza um sprite em x
// Pams: sprite - sprite que deseja centralizar e y - Y desejado que ele fique
//---------------------------------------------------------------------------- 
void CMenu::CentralizeSpriteInX(CNGLSprite* sprite, float y){

	sprite->Position.fx = ((pr_Level->pr_Main->VideoManager.VideoSize.fx * 0.5f) 
										- (sprite->GetFrame().GetWidth()*0.5f));
	sprite->Position.fy = y;
}

//---------------------------------------------------------------------------- 
// Nome: CentralizeSpritesInX(void)
// Desc: Centraliza sprites em x
// Pams: sprites desejados para centralizar e o tamanho do array
//---------------------------------------------------------------------------- 
void CMenu::CentralizeSpritesInX(CNGLSprite* sprites[], short size){
	float y = MARGIN_TOP_FIRST_MENU_ITEM;
	for(int i = 0; i < size; i++) {
		CentralizeSpriteInX(sprites[i], y);
		y += p_SprMain[i]->GetFrame().GetHeight() + MARGIN_TOP_MENU_TIEM;
	}
}
//---------------------------------------------------------------------------- 
// Nome: ConfigureSpritesAnimation(void)
// Desc: Configura animação padrão dos sprites
// Pams: sprites e tamanhos
//---------------------------------------------------------------------------- 
void CMenu::ConfigureSpritesAnimation(CNGLSprite* sprites[], short size){
	for(int i = 0; i < size; i++) {
		sprites[i]->AddAnimation(1,false,1,0);
		sprites[i]->AddAnimation(1,false,1,1);
		sprites[i]->SetCurrentAnimation(0);
	}
}

//---------------------------------------------------------------------------- 
// Nome: Execute(void)
// Desc: Executa o menu de acordo com o seu estado.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CMenu::Execute(void)
{
	//16.3.3
	//1. Atualizar posição do cursor do mouse
	p_SprMouse->Position = pr_Level->pr_Main->InputManager.GetMousePos();

	//2. Chamar método adequado de tratamento de estado	
	if(State == MS_MAIN)
		OnMain();

	else if(State == MS_OPTIONS)
		OnOptions();
}

//---------------------------------------------------------------------------- 
// Nome: ChangeState(CMenu::MenuState NewState)
// Desc: Muda o estado da máquina de estados da CMenu
// Pams: novo estado
//---------------------------------------------------------------------------- 
void CMenu::ChangeState(CMenu::MenuState NewState)
{
	//16.3.7. 
	//somente muda o estado se o novo for diferente do atual
	if(State != NewState)
	{
		switch(NewState)
		{
			case MS_MAIN:
			{
				//somente troca para estado MS_MAIN se o estado
				//atual for MS_OPTIONS. Aqui está se garantindo
				//a consistência da transição
				if(State == MS_OPTIONS)
				{
					p_LayMain->bVisible = true;
					p_LayOptions->bVisible = false;					
				}
				break;
			}
			case MS_OPTIONS:
			{
				//somente troca para estado MS_OPTIONS se o estado
				//atual for MS_MAIN. Aqui está se garantindo
				//a consistência da transição
				if(State == MS_MAIN)
				{
					//2. Esconder p_LayMain e mostrar p_LayOptions
					p_LayMain->bVisible = false;
					p_LayOptions->bVisible = true;
				}
				break;
			}
		}
		//estado atual recebe novo estado
		State = NewState;
	}
}

//---------------------------------------------------------------------------- 
// Nome: OnMain(void)
// Desc: Trata o estado MS_MAIN. É o estado do menu principal.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CMenu::OnMain(void)
{
	//16.3.5.
	//1. Programação do mouse over

	short sMouseOver = -1;

	for( int i = 0; i < NUM_MAINITEMS; i++) {		
		if(MouseOver(p_SprMain[i])){
			MouseOverSpriteAnimation(p_SprMain[i],true);
			sMouseOver = i;
		}
		else MouseOverSpriteAnimation(p_SprMain[i],false);
	}

	if(pr_Level->pr_Main->InputManager.MouBtnPressed(0)){

		if(p_SndMouseClick) p_SndMouseClick->Play(false);

		switch(sMouseOver){
			case IDX_NEW_GAME:
				pr_Level->ChangeState(CLevel::GS_GAME);
			break;
			case IDX_OPTIONS:
				ChangeState(MS_OPTIONS);
			break;
			case IDX_QUIT:
				pr_Level->pr_Main->ExitNGL();
			break;
		}
	}

	if(pr_Level->pr_Main->InputManager.KeyPressed(DIK_ESCAPE)) pr_Level->pr_Main->ExitNGL();

}

void CMenu::MouseOverSpriteAnimation(CNGLSprite* sprite, bool mouseOver){
	if(mouseOver){
		if(p_SndMouseOver && (sprite->sCurrentAnim == 0))
			p_SndMouseOver->Play(false);

		sprite->SetCurrentAnimation(1);
	}
	else
		sprite->SetCurrentAnimation(0);
}

//---------------------------------------------------------------------------- 
// Nome: OnOptions(void)
// Desc: Trata o estado MS_OPTIONS. É o estado do menu de opções.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CMenu::OnOptions(void)
{
	//16.3.6. 
	//1. Programação do mouse over (somente para índice 1)
	short sMouseOver = -1;

	if(MouseOver(p_SprOptions[0]))
		sMouseOver = 0;

	if(MouseOver(p_SprOptions[1])){
		MouseOverSpriteAnimation(p_SprOptions[1],true);
		sMouseOver = 1;
	}
	else MouseOverSpriteAnimation(p_SprOptions[1],false);

	//2. Tratamento do botão "Tela Cheia"

	if(pr_Level->pr_Main->InputManager.MouBtnPressed(0)){
		if(p_SndMouseClick) p_SndMouseClick->Play(false);
		switch(sMouseOver){
			//Tela cheia
			case 0:
				pr_Level->pr_Main->VideoManager.SetVideoMode(!pr_Level->pr_Main->VideoManager.bFullScreen,pr_Level->pr_Main->VideoManager.VideoSize);
				p_SprOptions[0]->SetCurrentAnimation(pr_Level->pr_Main->VideoManager.bFullScreen ? 1:0);
				SaveOptions();
			break;
			//Menu principal
			case 1:
				ChangeState(MS_MAIN);
			break;
		}
	}

	
	//3. Voltar ao menu principal caso a tecla ESC seja pressionada

	if(pr_Level->pr_Main->InputManager.KeyPressed(DIK_ESCAPE)) 	ChangeState(MS_MAIN);

}

//---------------------------------------------------------------------------- 
// Nome: MouseOver(CNGLSprite* pr_Sprite)
// Desc: Testa se o mouse está em cima do sprite (colisão mouse X sprite)
// Pams: sprite a ser testado
//---------------------------------------------------------------------------- 
bool CMenu::MouseOver(CNGLSprite* pr_Sprite)
{
	//16.3.4. Retorna verdadeiro caso o sprite colida com o mouse
	return p_SprMouse->GetFrame().Collide(pr_Sprite->GetFrame());
}

//---------------------------------------------------------------------------- 
// Nome: DrawMouse(void)
// Desc: Desenha o cursor do mouse na tela. Ela deve ser chamada na CLevel::Draw()
//			 para que se garanta que o cursor seja a última imagem a ser desenhada.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CMenu::DrawMouse(void)
{
	//16.3.2
	//1. Desenhar o sprite do mouse (verificar validade do ponteiro)
	if(p_SprMouse){
		p_SprMouse->Draw();
	}
}

//---------------------------------------------------------------------------- 
// Nome: LoadOptions(CNGLMain *pr_Main)
// Desc: Lê as opções do jogo de um arquivo.
// Pams: Referência para CNGLMain. É necessário passar este parâmetro pois as
//       opções devem ser lidas antes da NGL iniciar.
//---------------------------------------------------------------------------- 
void CMenu::LoadOptions(CNGLMain *pr_Main)
{
	FILE *p_File = NULL;
	p_File = fopen(OPTIONS_FILE,"rb");
	if(p_File)
	{
		fread(&pr_Main->VideoManager.bFullScreen,sizeof(bool),1,p_File);
		fclose(p_File);
	}
}

//---------------------------------------------------------------------------- 
// Nome: SaveOptions(void)
// Desc: Grava o arquivo de opções do jogo.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CMenu::SaveOptions(void)
{
	FILE *p_File = NULL;
	p_File = fopen(OPTIONS_FILE,"wb");
	if(p_File)
	{
		fwrite(&pr_Level->pr_Main->VideoManager.bFullScreen,sizeof(bool),1,p_File);
		fclose(p_File);
	}
}

//---------------------------------------------------------------------------- 
// Nome: Show(bool bShow)
// Desc: Mostra ou esconde o menu
// Pams: parêmetro de visibilidade
//---------------------------------------------------------------------------- 
void CMenu::Show(bool bShow)
{
	//16.3.8. 
	//1. Esconder ou mostrar o main menu dependendo de bShow

	p_LayMain->bVisible = bShow;

	
	//2. Colocar o botão certo do menu principal

	if(bShow){
		if(bInGame){
			p_LayMain->DeleteSprite(&p_SprMain[0]);
			p_SprMain[IDX_NEW_GAME] = p_LayMain->CreateSprite(CONTINUE_SPR, CNGLVector(153,25));
		}
		else{
			p_LayMain->DeleteSprite(&p_SprMain[0]);
			p_SprMain[IDX_NEW_GAME] = p_LayMain->CreateSprite(NEW_GAME_SPR, CNGLVector(150,23));
		}

		CentralizeSpriteInX(p_SprMain[IDX_NEW_GAME], MARGIN_TOP_FIRST_MENU_ITEM);
	}
}

//---------------------------------------------------------------------------- 
// Nome: GetState(void)
// Desc: Retorna o estado corrente do menu
// Pams: nenhum
//---------------------------------------------------------------------------- 
CMenu::MenuState CMenu::GetState(void)
{
	return State;
}
