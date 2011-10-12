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
#ifndef _CNGLSOUNDMANAGER_
#define _CNGLSOUNDMANAGER_

// includes
#include "NGLobject.h"
#include "NGLsound.h"
#include "stlfiles.h"
#include "NGLSound.h"

class CNGLMain;

//! Classe CNGLSoundManager
/*!
	Gerencia todos os recursos sonoros utilizados pela NGL.
	Mant�m uma lista de sons alocados durante o jogo. E uma
	lista de sons que est�o sendo atualmente tocados (m�sica)
*/
class CNGLSoundManager : public CNGLObject
{
public:
	
	//! Ponteiro de refer�ncia para a NGL Main
	CNGLMain						*pr_Main;

	//! Principal ponteiro do DirectSound
	IDirectSound    *p_DSound;
	//! Buffer prim�rio. � criado uma vez e recebe os outros sons
	IDirectSoundBuffer *p_Primary;

	//! Vetor adicional de que contem a lista de sons que est�o tocando (streamming)
	vector<CNGLSound*> PlayMusic;
	//!List de recursos sonoros
	vector<CNGLSound*> Sounds;

	/*!
		Inicializa o DirectSound. Cria o buffer de som prim�rio
		\return verdadeiro se criou directsound, falso caso contr�rio
	*/
	bool Initialize(void);
	/*!
		Cria um Buffer de som e carrega o arquivo .wav para essa mem�ria
		\param cp_chFileName contem o nome do arquivo .wav
		\param bIsFX � verdadeiro para FX e falso para M�sica
		\return Ponteiro para CGLDSound se som foi alocado corretamente
	*/
	CNGLSound *LoadSound(char *cp_chFileName,bool bIsFX);

	/*!
		Desaloca o som e o remove da lista de sons.
		\param **p_Sound: refer�ncia ao ponteiro para um som que ser� desalocado.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool DeleteSound(CNGLSound **p_Sound);

	/*!
		Construtor padr�o
	*/
	CNGLSoundManager(void);
	/*!
		Destrutor padr�o
	*/
	virtual ~CNGLSoundManager(void);
	/*!
		Finaliza a classe
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	/*!
		Faz o update de sons que est�o no modo streamming (m�sica)
	*/
	void Update(void);
};

#endif