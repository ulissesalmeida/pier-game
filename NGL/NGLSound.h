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
#ifndef _CNGLSOUND_
#define _CNGLSOUND_

#include "NGLobject.h"
#include "StlFiles.h"
#include <dsound.h>

class CNGLSoundManager;

//! Classe CNGLSound
/*!
	Manipula arquivos de efeitos sonoros e m�sica
*/
class CNGLSound :	public CNGLObject
{
	//! Refer�ncia para o gerenciador de Som
	CNGLSoundManager *pr_SoundManager;

	//! Flag que me diz se o som � efeito sonoro (verdadeiro) ou musica (falso)
	bool bIsFX;

	//! tamanho do som em bytes (s� os dados, header n�o)
	unsigned int uiDataSize;
	//! Cont�m 1 se o som for mono e 2 se o som for est�reo.
	unsigned short  usChannels;
	//! Frequencia do som (8Khz, 22Khz, 44Khz, etc...)
	unsigned int    uiFrequency;
	//! Bits por amostra (8 ou 16 bits)
	unsigned short	usBitsPerSamples;
	//! Media de bytes por segundos tocados
	unsigned int    uiAvgBytesPerSec;

	//! Cont�m a metade do tamanho do buffer, necess�rio para a opera��o de streamming.
	unsigned int uiMidBuffer;

	
	/*!
		Limpa o Buffer (preenche com 0�s) para deix�-lo pronto para streamming
	*/
	void ClearSoundBuffer(void);

public:

	//!Interface para o buffer de som do DirectSound.
	IDirectSoundBuffer *p_Buffer;
	//! Nome e caminho do arquivo de som (.wav).
	string FileName;
	//! Informa se a m�sica tocar� em continuamente (streamming) ou n�o.
	bool bMusicLoop;
	//! Indica a posi��o do Buffer para o som parar de tocar.
	unsigned int uiEndMark;
	//! Indica o fim do streamming (m�sica). Momento em que o cursor de Play est� no mesmo segmento do uiEndMark (som quase parando).
	bool bSameSeg;
	//! Posi��o do cursor na Wav de musica (usado para streamming)
	unsigned int uiWavCurPos;
	//! Guarda a �ltima posi��o em que se encontra o cursor do Play (usado para streamming).
	unsigned int uiLastPlayPos;
	//! Ponteiro para arquivo de som usado para streamming de m�sica
	FILE *p_File;
	
	/*!
		Faz a leitura de um .wav (cria buffer de som, e inicializa variaveis)
		\param cp_chFileName � vetor constante de caracteres que contem o nome do arquivo
		\return verdadeiro se som foi lido, falso caso contrario
	*/
	bool LoadFromFile(const char *cp_chFileName);

	/*!
		Posiciona o File Pointer no inicio da �rea de dados da wave
	*/
	void SeekToWaveData();


		/*!
		Faz com que um som utilize um recurso deo som j� criado (buffer de som)
		Ap�s a chamada desta rotina, o ponteiro para buffer de som do objeto
		estar� apontando para o Buffer de Som de SoundSrc.
		\param p_SoundSrc � o Som de Origem cujo o buffer ser� utilizado
		\return verdadeiro se duplicou, falso caso contr�rio
	*/
	bool DuplicateSound(CNGLSound *p_SoundSrc);


	/*!
		Contrutor padr�o
		\param pr_SoundManagerPam � ponteiro para sound manager
		\param cp_chFileNamePam � ponteiro para string nome do arquivo
		\param bIsFXPam verdadeiro para Som - falso para M�sica
	*/
	CNGLSound(CNGLSoundManager *pr_SoundManagerPam,const char *cp_chFileNamePam,bool bIsFXPam);
	/*!
		Destrutor padr�o
	*/
	~CNGLSound(void);
	/*!
		Finaliza a classe
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso
	*/
	bool Release(void);
	/*!
		P�ra de tocar o som.
		\return verdadeiro se parou, falso caso contr�rio
	*/
	bool Stop(void);
	/*!
		Come�a a reproduzir o som.
		\param bLoopPam � verdadeiro para som ficar tocando em loop, falso toca uma vez
		\return verdadeiro se o som estiver tocando, falso caso contr�rio
	*/
	bool Play(bool bLoopPam = false);

	/*!
		Retorna se o som est� sendo reproduzido.
		\return verdadeiro se estiver reproduzindo, falso caso contr�rio
	*/
	bool IsPlaying();

	/*!
		Retorna a frequ�ncia nativa do som (impresso no header do .wav)
		\return Frequ�ncia do som (ex: 44100 Khz, 22050 Khz...)
	*/
	unsigned int GetFrequency() { return uiFrequency;};
	/*!
		Retorna o n�mero de bits utilizado para amostra de som
		\return Bits por amostra (8 ou 16)
	*/
	unsigned short GetBitsPerSample() { return usBitsPerSamples;};
	/*!
		Retorna se o som est� em Mono ou St�reo
		\return Numero de canais do som (1 ou 2)
	*/
	unsigned short GetNumberOfChannels() { return usChannels;};
	/*!
		Retorna o tamanho da wave (somente os dados)
		\return tamanho da wave em bytes (somente dados)
	*/
	unsigned int GetDataSize() { return uiDataSize;};
	/*!
		Retorna a m�dia de bytes lidos por segundo pelo DirectSound.
		\return Bytes por segundo lidos.
	*/
	unsigned int GetAvgBytesPerSec() { return uiAvgBytesPerSec;};
	/*!
		Retorna o Tamanho do buffer / 2
		\return Tamanho do buffer / 2 (necess�rio para atualiza��o do streaming)
	*/
	unsigned int GetMidOfBuffer() { return uiMidBuffer; };

};

#endif