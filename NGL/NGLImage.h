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
#ifndef _CNGLIMAGE_
#define _CNGLIMAGE_
//inlcudes
#include "NGLobject.h"
#include "NGLVector.h"
#include "NGLFrame.h"
#include <ddraw.h>
#include "StlFiles.h"

//prot�tipos
class CNGLVideoManager;

//!Constantes de Espelhamento (Mirror)
#define NGLMIRROR_NONE			0
#define NGLMIRROR_LEFTRIGHT 1
#define NGLMIRROR_UPDOWN		2

//!Classe CNGLImage
/*!
  Esta classe manipula arquivos de imagem.
*/
class CNGLImage :	public CNGLObject
{
	public:

		//!N�mero de refer�ncias existentes para esta imagem.
		short sReferences;

		//!Nome do arquivo de imagem (bitmap).
		string FileName;

		//!Dimens�es da imagem em pixels.
		CNGLVector Size;

		//!Tamanho do quadro que ser� pintado na tela, em pixels.
		CNGLVector FrameSize;

		//!Refer�ncia para o gerenciador de v�deo.
		CNGLVideoManager *pr_VideoManager;

		//!Ponteiro para uma superf�cie de DirectDraw.
		IDirectDrawSurface	*p_Surface;

		//!Lista de quadros de anima��o da imagem.
		vector <CNGLFrame*>	Frames;
	
	public:
		
		/*!
			Carrega o arquivo de imagem.
			\param cp_chFileName: nome do arquivo de imagem.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool LoadFromFile(const char *cp_chFileName);
		
		/*!
			Cria o clipper para o front buffer do DirectDraw
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool CreateClipper();
		
		/*!
			Cria o BackBuffer do DirectDraw.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool CreateBackBuffer();
		
		/*!
			Cria o FrontBuffer do DirectDraw.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool CreateFrontBuffer();
		
		/*!
			Construtor Padr�o.
		*/
		CNGLImage(void);
		
		/*!
			Destrutor padr�o.
		*/
		virtual ~CNGLImage(void);

		/*!
			Finaliza a classe.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool Release(void);

		/*!
			Cria uma imagem com dimens�es espec�ficas.
			\param cSize: cont�m a dimens�o da imagem.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool Create(const CNGLVector cSize);
		
		/*!
			Ajusta a cor de transpar�ncia.
			\param uiColorKey: cor RGB para transpar�ncia utilizando NGI.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		void SetColorKey(unsigned int uiColorKey);
		
		/*!
			Recarrega o arquivo atual de imagem. � usado para recuperar superf�cies perdidas,
			como por exemplo, quando a janela do jogo perde o foco (usando Alt-TAB, ou outro evento
			do Windows).
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		void Reload(void);
		
		/*!
			Pinta a superf�cie com uma cor espec�fica.
			\param uiColor: cor em RGB para pintar a superf�cie.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		void Clear(unsigned int uiColor);
		
		/*!
			Converte o formato de cor
			\param uiColor: formato de cor no padr�o NGI
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		unsigned int ConvertGDIColor(unsigned int uiColor);
		/*!
			Ajusta o tamanho do quadro de anima��o.
			\param cSizePam: define as dimens�es do quadro.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		void SetFrameSize(const CNGLVector & cSizePam);

		/*!
			Limpa os quadros de anima��o da imagem.
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		void ClearFrames(void);

		/*!
			Pinta a imagem origem nesta imagem.
			\param p_DestFrame: Quadro destino (posi��o e dimens�o) nesta imagem a ser pintado o quadro origem.
			\param p_SrcImage: Imagem de origem a ser copiada para esta imagem.
			\param p_SrcFrame: Quadro da imagem origem a ser copiado para esta imagem.
			\param byMirror: Forma como os quadros ser�o pintados (use NGLMIRROR_NONE, NGLMIRROR_LEFTRIGHT, NGLMIRROR_UPDOWN). O padr�o � NGLMIRROR_NONE. Pode-se se usar combina��es destes flags usando operador OU (ex: NGLMIRROR_LEFTRIGHT | NGLMIRROR_UPDOWN).
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool DrawImage(CNGLFrame *p_DestFrame, CNGLImage *p_SrcImage,CNGLFrame *p_SrcFrame,Byte byMirror = NGLMIRROR_NONE);

		/*!
			Pinta a imagem de um frame espec�fico nesta imagem.
			\param cPosition: posi��o nesta imagem a partir da qual o quadro ser� pintado.
			\param p_SrcImage: imagem de origem a ser copiado o frame.
			\param iFrame: n�mero do quadro a ser pintado.
			\param byMirror: Forma como os quadros ser�o pintados (use NGLMIRROR_NONE, NGLMIRROR_LEFTRIGHT, NGLMIRROR_UPDOWN). O padr�o � NGLMIRROR_NONE. Pode-se se usar combina��es destes flags usando operador OU (ex: NGLMIRROR_LEFTRIGHT | NGLMIRROR_UPDOWN).
			\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
		*/
		bool DrawImage(const CNGLVector &cPosition, CNGLImage *p_SrcImage, int iFrame,Byte byMirror = NGLMIRROR_NONE);
};

#endif