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
#ifndef _CNGLVIDEOMANAGER_
#define _CNGLVIDEOMANAGER_

//includes
#include "NGLobject.h"
#include "NGLImage.h"
#include "NGLFrame.h"

//prot�tipos de classe
class CNGLMain;

//!Classe CNGLVideoManager
/*!
	Gerencia os recursos de v�deo da NGL.
*/
class CNGLVideoManager :	public CNGLObject
{
	public:

		//!Define o tamanho da janela Windows.
		CNGLFrame						WindowFrame;

		//!Define a exibi��o em tela cheia ou janela. Deve ser atribu�do antes de ser chamado o Initialize().
		bool								bFullScreen;
		
		//!Define o tamanho do BackBuffer do DirectDraw.
		CNGLVector					VideoSize;

		//!Lista de imagens carregadas.
		vector<CNGLImage*>	Images;

		//!Ponteiro de refer�ncia para a CNGLMain.
		CNGLMain						*pr_Main;

		//!Interface do DirectDraw.
		IDirectDraw					*p_DDraw;
		
		//!FrontBuffer
		CNGLImage						FrontBuffer;
		
		//! BackBuffer
		CNGLImage						BackBuffer;

	public:
		
	/*!
		Inicializa o v�deo usando o DirectDraw. Cria tamb�m o FrontBuffer e BackBuffer.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize();
	CNGLVideoManager(void);
	virtual ~CNGLVideoManager(void);
	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
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
		\param p_Image: Endere�o do ponteiro da imagem a ser deletada.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool DeleteImage(CNGLImage** p_Image);

	/*!
		Faz a troca do BackBuffer para o FrontBuffer, mostrando na tela.		
	*/
	bool Present(void);

	/*!
		Recarrega as imagens previamente carregadas. � usada para recuperar superf�cies perdidas,
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
		\param NewSize: Dimens�es do jogo (ex.: 640x480,800x600,1024x768).
	*/
	void SetVideoMode(bool bFullscreenPam, const CNGLVector & NewSize);
};

#endif