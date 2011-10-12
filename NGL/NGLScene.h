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
#ifndef _CNGLSCENE_
#define _CNGLSCENE_

//Includes
#include "NGLobject.h"
#include "stlfiles.h"
#include "NGLlayer.h"
#include "NGLimage.h"
#include "NGLsound.h"

//prot�tipos
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

	//!Lista de imagens que cont�m os tiles.
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
		\param p_Layer: refer�ncia ao ponteiro para uma layer que ser� desalocada.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool DeleteLayer(CNGLLayer **p_Layer);
	
	/*!
		Atualiza as informa�oes da cena.
	*/
	void Update();

	/*!
		Desenha a cena. Esta rotina � virtual porque ela pode ser reescrita na cena.
		Isso � usado em ocasi�es onde a cena do usu�rio desenha objetos que a cena da NGL n�o
		tem controle. Caso essa rotina seja reescrita na classe filha, deve-se chamar a Draw()
		da classe pai, para que continue se desenhando os objetos j� adicionados na cena.
		*/
	virtual void Draw();

	/*!
		Construtor padr�o.
	*/
	CNGLScene(void);

	/*!
		Destrutor padr�o.
	*/
	virtual ~CNGLScene(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);
	
	/*!
		Adiciona uma imagem para ser utilizada como tile nas layers e retorna seu indice no vetor de imagens da cena.
		\param cp_chFileName: Nome do arquivo da imagem.
		\param cFrameSize: Tamanho do quadro na imagem.
		\return �ndice da imagem no vetor da cena.
	*/
	int AddTileImage(const char * cp_chFileName, const CNGLVector &cFrameSize);

	/*!
		Inicializa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		criar todos os objetos e fazer inicializa��es necess�rias.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	virtual bool Initialize(void) = 0;

	/*!
		Executa a cena. Essa rotina deve ser reescrita na cena, para que se possa
		fazer a execu��o da cena.
	*/
	virtual void Execute(void) = 0;
};

#endif