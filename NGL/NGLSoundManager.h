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
	Mantém uma lista de sons alocados durante o jogo. E uma
	lista de sons que estão sendo atualmente tocados (música)
*/
class CNGLSoundManager : public CNGLObject
{
public:
	
	//! Ponteiro de referência para a NGL Main
	CNGLMain						*pr_Main;

	//! Principal ponteiro do DirectSound
	IDirectSound    *p_DSound;
	//! Buffer primário. é criado uma vez e recebe os outros sons
	IDirectSoundBuffer *p_Primary;

	//! Vetor adicional de que contem a lista de sons que estão tocando (streamming)
	vector<CNGLSound*> PlayMusic;
	//!List de recursos sonoros
	vector<CNGLSound*> Sounds;

	/*!
		Inicializa o DirectSound. Cria o buffer de som primário
		\return verdadeiro se criou directsound, falso caso contrário
	*/
	bool Initialize(void);
	/*!
		Cria um Buffer de som e carrega o arquivo .wav para essa memória
		\param cp_chFileName contem o nome do arquivo .wav
		\param bIsFX é verdadeiro para FX e falso para Música
		\return Ponteiro para CGLDSound se som foi alocado corretamente
	*/
	CNGLSound *LoadSound(char *cp_chFileName,bool bIsFX);

	/*!
		Desaloca o som e o remove da lista de sons.
		\param **p_Sound: referência ao ponteiro para um som que será desalocado.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool DeleteSound(CNGLSound **p_Sound);

	/*!
		Construtor padrão
	*/
	CNGLSoundManager(void);
	/*!
		Destrutor padrão
	*/
	virtual ~CNGLSoundManager(void);
	/*!
		Finaliza a classe
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
		Faz o update de sons que estão no modo streamming (música)
	*/
	void Update(void);
};

#endif