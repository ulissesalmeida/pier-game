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
#ifndef _CNGLSOUND_
#define _CNGLSOUND_

#include "NGLobject.h"
#include "StlFiles.h"
#include <dsound.h>

class CNGLSoundManager;

//! Classe CNGLSound
/*!
	Manipula arquivos de efeitos sonoros e música
*/
class CNGLSound :	public CNGLObject
{
	//! Referência para o gerenciador de Som
	CNGLSoundManager *pr_SoundManager;

	//! Flag que me diz se o som é efeito sonoro (verdadeiro) ou musica (falso)
	bool bIsFX;

	//! tamanho do som em bytes (só os dados, header não)
	unsigned int uiDataSize;
	//! Contém 1 se o som for mono e 2 se o som for estéreo.
	unsigned short  usChannels;
	//! Frequencia do som (8Khz, 22Khz, 44Khz, etc...)
	unsigned int    uiFrequency;
	//! Bits por amostra (8 ou 16 bits)
	unsigned short	usBitsPerSamples;
	//! Media de bytes por segundos tocados
	unsigned int    uiAvgBytesPerSec;

	//! Contém a metade do tamanho do buffer, necessário para a operação de streamming.
	unsigned int uiMidBuffer;

	
	/*!
		Limpa o Buffer (preenche com 0´s) para deixá-lo pronto para streamming
	*/
	void ClearSoundBuffer(void);

public:

	//!Interface para o buffer de som do DirectSound.
	IDirectSoundBuffer *p_Buffer;
	//! Nome e caminho do arquivo de som (.wav).
	string FileName;
	//! Informa se a música tocará em continuamente (streamming) ou não.
	bool bMusicLoop;
	//! Indica a posição do Buffer para o som parar de tocar.
	unsigned int uiEndMark;
	//! Indica o fim do streamming (música). Momento em que o cursor de Play está no mesmo segmento do uiEndMark (som quase parando).
	bool bSameSeg;
	//! Posição do cursor na Wav de musica (usado para streamming)
	unsigned int uiWavCurPos;
	//! Guarda a última posição em que se encontra o cursor do Play (usado para streamming).
	unsigned int uiLastPlayPos;
	//! Ponteiro para arquivo de som usado para streamming de música
	FILE *p_File;
	
	/*!
		Faz a leitura de um .wav (cria buffer de som, e inicializa variaveis)
		\param cp_chFileName é vetor constante de caracteres que contem o nome do arquivo
		\return verdadeiro se som foi lido, falso caso contrario
	*/
	bool LoadFromFile(const char *cp_chFileName);

	/*!
		Posiciona o File Pointer no inicio da área de dados da wave
	*/
	void SeekToWaveData();


		/*!
		Faz com que um som utilize um recurso deo som já criado (buffer de som)
		Após a chamada desta rotina, o ponteiro para buffer de som do objeto
		estará apontando para o Buffer de Som de SoundSrc.
		\param p_SoundSrc é o Som de Origem cujo o buffer será utilizado
		\return verdadeiro se duplicou, falso caso contrário
	*/
	bool DuplicateSound(CNGLSound *p_SoundSrc);


	/*!
		Contrutor padrão
		\param pr_SoundManagerPam é ponteiro para sound manager
		\param cp_chFileNamePam é ponteiro para string nome do arquivo
		\param bIsFXPam verdadeiro para Som - falso para Música
	*/
	CNGLSound(CNGLSoundManager *pr_SoundManagerPam,const char *cp_chFileNamePam,bool bIsFXPam);
	/*!
		Destrutor padrão
	*/
	~CNGLSound(void);
	/*!
		Finaliza a classe
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso
	*/
	bool Release(void);
	/*!
		Pára de tocar o som.
		\return verdadeiro se parou, falso caso contrário
	*/
	bool Stop(void);
	/*!
		Começa a reproduzir o som.
		\param bLoopPam é verdadeiro para som ficar tocando em loop, falso toca uma vez
		\return verdadeiro se o som estiver tocando, falso caso contrário
	*/
	bool Play(bool bLoopPam = false);

	/*!
		Retorna se o som está sendo reproduzido.
		\return verdadeiro se estiver reproduzindo, falso caso contrário
	*/
	bool IsPlaying();

	/*!
		Retorna a frequência nativa do som (impresso no header do .wav)
		\return Frequência do som (ex: 44100 Khz, 22050 Khz...)
	*/
	unsigned int GetFrequency() { return uiFrequency;};
	/*!
		Retorna o número de bits utilizado para amostra de som
		\return Bits por amostra (8 ou 16)
	*/
	unsigned short GetBitsPerSample() { return usBitsPerSamples;};
	/*!
		Retorna se o som está em Mono ou Stéreo
		\return Numero de canais do som (1 ou 2)
	*/
	unsigned short GetNumberOfChannels() { return usChannels;};
	/*!
		Retorna o tamanho da wave (somente os dados)
		\return tamanho da wave em bytes (somente dados)
	*/
	unsigned int GetDataSize() { return uiDataSize;};
	/*!
		Retorna a média de bytes lidos por segundo pelo DirectSound.
		\return Bytes por segundo lidos.
	*/
	unsigned int GetAvgBytesPerSec() { return uiAvgBytesPerSec;};
	/*!
		Retorna o Tamanho do buffer / 2
		\return Tamanho do buffer / 2 (necessário para atualização do streaming)
	*/
	unsigned int GetMidOfBuffer() { return uiMidBuffer; };

};

#endif