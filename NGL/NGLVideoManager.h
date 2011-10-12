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
#ifndef _CNGLVIDEOMANAGER_
#define _CNGLVIDEOMANAGER_

//includes
#include "NGLobject.h"
#include "NGLImage.h"
#include "NGLFrame.h"

//protótipos de classe
class CNGLMain;

//!Classe CNGLVideoManager
/*!
	Gerencia os recursos de vídeo da NGL.
*/
class CNGLVideoManager :	public CNGLObject
{
	public:

		//!Define o tamanho da janela Windows.
		CNGLFrame						WindowFrame;

		//!Define a exibição em tela cheia ou janela. Deve ser atribuído antes de ser chamado o Initialize().
		bool								bFullScreen;
		
		//!Define o tamanho do BackBuffer do DirectDraw.
		CNGLVector					VideoSize;

		//!Lista de imagens carregadas.
		vector<CNGLImage*>	Images;

		//!Ponteiro de referência para a CNGLMain.
		CNGLMain						*pr_Main;

		//!Interface do DirectDraw.
		IDirectDraw					*p_DDraw;
		
		//!FrontBuffer
		CNGLImage						FrontBuffer;
		
		//! BackBuffer
		CNGLImage						BackBuffer;

	public:
		
	/*!
		Inicializa o vídeo usando o DirectDraw. Cria também o FrontBuffer e BackBuffer.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Initialize();
	CNGLVideoManager(void);
	virtual ~CNGLVideoManager(void);
	/*!
		Finaliza a classe.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release(void);

	/*!
		Carrega uma imagem.
		\param cp_chFileName: arquivo do bitmap da imagem a ser criada.
		\return Ponteiro para a imagem criada.
	*/
	CNGLImage* LoadImage(const char * cp_chFileName);

	/*!
		Deleta uma imagem.
		\param p_Image: Endereço do ponteiro da imagem a ser deletada.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool DeleteImage(CNGLImage** p_Image);

	/*!
		Faz a troca do BackBuffer para o FrontBuffer, mostrando na tela.		
	*/
	bool Present(void);

	/*!
		Recarrega as imagens previamente carregadas. É usada para recuperar superfícies perdidas,
		como por exemplo, quando a janela do jogo perde o foco (usando Alt-TAB, ou outro evento
		do Windows).
	*/
	void ReloadImages(void);

	/*!
		Atualiza o frame da janela.
	*/
	void UpdateFrame(void);
	
	/*!
		Muda o modo de video da NGL.
		\param bFullscreenPam: verdadeiro para Tela Cheia e falso para Janela.
		\param NewSize: Dimensões do jogo (ex.: 640x480,800x600,1024x768).
	*/
	void SetVideoMode(bool bFullscreenPam, const CNGLVector & NewSize);
};

#endif