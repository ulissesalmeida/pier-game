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
#ifndef _CNGLSCENE_
#define _CNGLSCENE_

//Includes
#include "NGLobject.h"
#include "stlfiles.h"
#include "NGLlayer.h"
#include "NGLimage.h"
#include "NGLsound.h"

//protótipos
class CNGLMain;

//!Classe CNGLScene
/*!
	Representa a cena de um jogo e gerencia layers e tiles.
*/
class CNGLScene :	public CNGLObject
{
public:
	
	//!Lista de zero ou mais layers.
	vector<CNGLLayer*> Layers;

	//!Lista de imagens que contém os tiles.
	vector<CNGLImage*> TileImages;

	//!Ponteiro	para o CNGLMain.
	CNGLMain		   *pr_Main;

public:

	/*!
		Faz o Scroll de todas as layers da cena.
		\param cScroll: tamanho do deslocamento das layers na cena.
	*/
	void Scroll(const CNGLVector &cScroll);
	  	
	/*!
		Cria uma layer e adiciona na cena.
		\param cBrickSize: tamanho dos bricks da layer.
		\param cNumBricks: tamanho da matriz de bricks.
		\return Ponteiro para a Layer criada.
	*/
	CNGLLayer	*CreateLayer(const CNGLVector &cBrickSize,const CNGLVector &cNumBricks);

	/*!
		Cria uma layer e adiciona na cena.
		\param cBrickSize: tamanho dos bricks da layer.
		\return Ponteiro para a Layer criada.
	*/
	CNGLLayer	*CreateLayer(const CNGLVector &cBrickSize);

	/*!
		Desaloca a layer e a remove da cena.
		\param p_Layer: referência ao ponteiro para uma layer que será desalocada.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool DeleteLayer(CNGLLayer **p_Layer);
	
	/*!
		Atualiza as informaçoes da cena.
	*/
	void Update();

	/*!
		Desenha a cena. Esta rotina é virtual porque ela pode ser reescrita na cena.
		Isso é usado em ocasiões onde a cena do usuário desenha objetos que a cena da NGL não
		tem controle. Caso essa rotina seja reescrita na classe filha, deve-se chamar a Draw()
		da classe pai, para que continue se desenhando os objetos já adicionados na cena.
		*/
	virtual void Draw();

	/*!
		Construtor padrão.
	*/
	CNGLScene(void);

	/*!
		Destrutor padrão.
	*/
	virtual ~CNGLScene(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release(void);
	
	/*!
		Adiciona uma imagem para ser utilizada como tile nas layers e retorna seu indice no vetor de imagens da cena.
		\param cp_chFileName: Nome do arquivo da imagem.
		\param cFrameSize: Tamanho do quadro na imagem.
		\return Índice da imagem no vetor da cena.
	*/
	int AddTileImage(const char * cp_chFileName, const CNGLVector &cFrameSize);

	/*!
		Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		criar todos os objetos e fazer inicializações necessárias.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	virtual bool Initialize(void) = 0;

	/*!
		Executa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		fazer a execução da cena.
	*/
	virtual void Execute(void) = 0;
};

#endif