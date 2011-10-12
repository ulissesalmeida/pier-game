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
#ifndef _CNGLLAYER_
#define _CNGLLAYER_

//includes
#include "NGLobject.h"
#include "NGLvector.h"
#include "NGLbrick.h"
#include "NGLsprite.h"
#include "stlfiles.h"

//prot�tipos
class CNGLScene;

//!NGLBrickConfig
/*!
Usada para criar uma layer a partir de um bitmap.
Indica que, quando a cor for encontrada deve-se utilizar a
imagem e o quadro no brick
*/
typedef struct stNGLBrickConfig
{
	//!Cor a ser utilizada para esta configura��o
	unsigned int	uiColor;
	//!indice da imagem na cena
	int						iImage;
	//!indice do quadro na imagem
	int						iFrame;
}NGLBrickConfig;

//!Classe CNGLLayer
/*!
	Controla a cria��o e exibi��o da layer no jogo.
*/
class CNGLLayer :	public CNGLObject
{
public:
	
	//!Ponteiro para a cena.
	CNGLScene	*pr_Scene;

	//!N�mero de bricks em x e y na layer.
	CNGLVector NumBricks;

	//!Tamanho dos bricks na layer.
	CNGLVector BrickSize;

	//!Layer offset - deslocamento da layer em rela��o ao v�deo.
	CNGLVector Offset;

	//!Velocidade da layer no Scroll.
	CNGLVector Speed;

	//!Vetor de Bricks (tijolos) que preenchem a layer.
	CNGLBrick	**p_Bricks;

	//!Lista de sprites da layer.
	vector<CNGLSprite*> Sprites;

	//!Flag que indica se a layer est� vis�vel ou n�o
	bool bVisible;

public:

	/*!
		Construtor padr�o.
	*/
	CNGLLayer(void);

	/*!
		Destrutor padr�o.
	*/
	virtual ~CNGLLayer(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);

	/*!
	Atualiza a layer.
	*/
	void Update(void);

	/*!
	Desenha a layer.
	*/
	void Draw(void);

	/*!
	Cria um sprite e adiciona ele � layer.
	\param cp_chFileName: Imagem de origem do sprite.
	\param cFrameSize: Tamanho do quadro do sprite.
	\return Ponteiro para o sprite criado.
	*/
	CNGLSprite* CreateSprite(const char* cp_chFileName,const CNGLVector &cFrameSize);

	/*!
		Deleta um sprite e o remove da layer.
		\param p_Sprite: refer�ncia ao ponteiro para um sprite que ser� desalocado.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool DeleteSprite(CNGLSprite **p_Sprite);

	/*!
		Faz o Scroll (deslocamento) da layer.
		\param cScroll: Tamanho do deslocamento.
	*/
	void Scroll(const CNGLVector & cScroll);

	/*!
		Cria os bricks da layer.
		\param cNumBricks: Tamanho da Matriz de Bricks (ex: 40x40).
	*/
	void CreateBricks(const CNGLVector &cNumBricks);

	/*!
		Apaga todos os bricks da layer.
	*/
	void ClearBricks(void);

	/*!
		Ajusta a configura��o de um brick.
		\param cBrickPos: posi��o do brick no vetor de Bricks.
		\param iImage: indice da imagem na cena.
		\param iFrame: indice do quadro na imagem.
	*/
	void SetBrick(const CNGLVector& cBrickPos, int iImage, int iFrame);
	
	/*!
		Cria uma layer com bricks a partir de um bitmap.
		\param cp_chFileName: imagem que cont�m a disposi��o dos bricks.
		\param pr_BrickConfigs: configura��o de cada brick (onde se associa a cor do pixel com o brick correspondente).
		\param iConfigCount: n�mero de configura��es de bricks.
	*/
	void CreateBricksFromBitmap(const char * cp_chFileName, stNGLBrickConfig* pr_BrickConfigs, int iConfigCount);

	/*!
		Retorna o tamanho da layer em pixels
		\return Vetor com o tamanho da layer em pixels(x,y)
	*/
	CNGLVector GetLayerSize(void);

	/*!
		Retorna a posi��o na layer dada a posi��o no back buffer
		\param BkBuffPos: Posi��o no back buffer
		\return Vetor com a posi�ao na layer
	*/
	CNGLVector GetLayerPos(const CNGLVector &BkBuffPos);
	/*!
		Retorna a posi��o no back buffer dada a posi��o na layer e o tamanho
		do quadro do objeto que utilizar� esta posi��o.
		\param LayerPos: Posi��o na layer
		\param FrameSize: Tamanho do quadro do objeto 
	*/
	CNGLVector GetBackBufferPos(const CNGLVector &LayerPos, const CNGLVector &FrameSize = CNGLVector(0.0f,0.0f));
};

#endif