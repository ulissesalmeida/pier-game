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
#ifndef _CNGLIMAGE_
#define _CNGLIMAGE_
//inlcudes
#include "NGLobject.h"
#include "NGLVector.h"
#include "NGLFrame.h"
#include <ddraw.h>
#include "StlFiles.h"

//protótipos
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

		//!Número de referências existentes para esta imagem.
		short sReferences;

		//!Nome do arquivo de imagem (bitmap).
		string FileName;

		//!Dimensões da imagem em pixels.
		CNGLVector Size;

		//!Tamanho do quadro que será pintado na tela, em pixels.
		CNGLVector FrameSize;

		//!Referência para o gerenciador de vídeo.
		CNGLVideoManager *pr_VideoManager;

		//!Ponteiro para uma superfície de DirectDraw.
		IDirectDrawSurface	*p_Surface;

		//!Lista de quadros de animação da imagem.
		vector <CNGLFrame*>	Frames;
	
	public:
		
		/*!
			Carrega o arquivo de imagem.
			\param cp_chFileName: nome do arquivo de imagem.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool LoadFromFile(const char *cp_chFileName);
		
		/*!
			Cria o clipper para o front buffer do DirectDraw
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool CreateClipper();
		
		/*!
			Cria o BackBuffer do DirectDraw.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool CreateBackBuffer();
		
		/*!
			Cria o FrontBuffer do DirectDraw.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool CreateFrontBuffer();
		
		/*!
			Construtor Padrão.
		*/
		CNGLImage(void);
		
		/*!
			Destrutor padrão.
		*/
		virtual ~CNGLImage(void);

		/*!
			Finaliza a classe.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool Release(void);

		/*!
			Cria uma imagem com dimensões específicas.
			\param cSize: contém a dimensão da imagem.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool Create(const CNGLVector cSize);
		
		/*!
			Ajusta a cor de transparência.
			\param uiColorKey: cor RGB para transparência utilizando NGI.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		void SetColorKey(unsigned int uiColorKey);
		
		/*!
			Recarrega o arquivo atual de imagem. É usado para recuperar superfícies perdidas,
			como por exemplo, quando a janela do jogo perde o foco (usando Alt-TAB, ou outro evento
			do Windows).
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		void Reload(void);
		
		/*!
			Pinta a superfície com uma cor específica.
			\param uiColor: cor em RGB para pintar a superfície.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		void Clear(unsigned int uiColor);
		
		/*!
			Converte o formato de cor
			\param uiColor: formato de cor no padrão NGI
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		unsigned int ConvertGDIColor(unsigned int uiColor);
		/*!
			Ajusta o tamanho do quadro de animação.
			\param cSizePam: define as dimensões do quadro.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		void SetFrameSize(const CNGLVector & cSizePam);

		/*!
			Limpa os quadros de animação da imagem.
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		void ClearFrames(void);

		/*!
			Pinta a imagem origem nesta imagem.
			\param p_DestFrame: Quadro destino (posição e dimensão) nesta imagem a ser pintado o quadro origem.
			\param p_SrcImage: Imagem de origem a ser copiada para esta imagem.
			\param p_SrcFrame: Quadro da imagem origem a ser copiado para esta imagem.
			\param byMirror: Forma como os quadros serão pintados (use NGLMIRROR_NONE, NGLMIRROR_LEFTRIGHT, NGLMIRROR_UPDOWN). O padrão é NGLMIRROR_NONE. Pode-se se usar combinações destes flags usando operador OU (ex: NGLMIRROR_LEFTRIGHT | NGLMIRROR_UPDOWN).
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool DrawImage(CNGLFrame *p_DestFrame, CNGLImage *p_SrcImage,CNGLFrame *p_SrcFrame,Byte byMirror = NGLMIRROR_NONE);

		/*!
			Pinta a imagem de um frame específico nesta imagem.
			\param cPosition: posição nesta imagem a partir da qual o quadro será pintado.
			\param p_SrcImage: imagem de origem a ser copiado o frame.
			\param iFrame: número do quadro a ser pintado.
			\param byMirror: Forma como os quadros serão pintados (use NGLMIRROR_NONE, NGLMIRROR_LEFTRIGHT, NGLMIRROR_UPDOWN). O padrão é NGLMIRROR_NONE. Pode-se se usar combinações destes flags usando operador OU (ex: NGLMIRROR_LEFTRIGHT | NGLMIRROR_UPDOWN).
			\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
		*/
		bool DrawImage(const CNGLVector &cPosition, CNGLImage *p_SrcImage, int iFrame,Byte byMirror = NGLMIRROR_NONE);
};

#endif