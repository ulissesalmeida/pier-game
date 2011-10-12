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
#include "NGLsound.h"

#include "NGLSoundManager.h"

#include <windows.h> // constantes do windows (WORD, DWORD, etc...)
#include <mmreg.h>  // constantes multimidia do windows

//---------------------------------------------------------------------------- 
// Nome: CNGLSound(CNGLSoundManager *pr_SoundManagerPam,char pc_chFileNamePam,bool bIsFXPam)
// Desc: construtor da classe de som
//       ela j� inicializa referencia pra SoundManager, Nome do Arquivo, e tipo de som
// Pams: Referencia para SoundManager, Nome do Arquivo, Flag se som � musica ou FX
//---------------------------------------------------------------------------- 
CNGLSound::CNGLSound(CNGLSoundManager *pr_SoundManagerPam,const char *cp_chFileNamePam,bool bIsFXPam)
{
	pr_SoundManager = pr_SoundManagerPam;
	FileName = cp_chFileNamePam;
	bIsFX = bIsFXPam;
	p_File = NULL;

	uiDataSize       = 0;    // tamanho dos dados (em bytes)
	uiWavCurPos		 = 0;    // Posicao do cursor de dados lidos na wav de som
	uiLastPlayPos    = 0;    // ultima posicao do play cursor no update sound
	uiMidBuffer      = 0;    // Cont�m o tamanho do buffer / 2 (streamming)
	p_Buffer         = NULL; // ponteiro para o buffer de som
	usChannels       = 0;    // numero de canais 
	uiFrequency      = 0;    // frequencia do som
	usBitsPerSamples = 0;    // bits (8 ou 16)
	uiAvgBytesPerSec = 0;    // media de bytes por segundo
	bMusicLoop       = false; // musica vai tocar em loop?
	uiEndMark        = 0; // flag para finaliza��o streamming
	bSameSeg         = false;  // outro flag para finaliza��o do streamming
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLSound(void)
// Desc: destrutor padr�o (automaticamente executa a funcao release
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLSound::~CNGLSound(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza um som
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLSound::Release(void)
{
	// se arquivo estiver aberto (streamming) ent�o fecha
	if (p_File)
	{
		fclose(p_File);
	}
	// se existir um buffer alocado, ent�o desaloca
	if (p_Buffer)
	{
		// para o som caso ele esteja tocando
		Stop();
		// libera o ponteiro do Buffer
		// DirectX cuida o Reference count
		p_Buffer->Release();
		p_Buffer = NULL;
	}
	return true;
}

//---------------------------------------------------------------------------- 
// Nome: LoadFromFile(char *cp_chFileName)
// Desc: le um arquivo wav de sons.
//       Abre o .wav
//       Verifica-se o tipo de som (musica ou FX)
//		 Cria o buffer DirectSoud conforme o tipo de som.
// Pams: ponteiro para vetor contante de caracteres
//---------------------------------------------------------------------------- 
bool CNGLSound::LoadFromFile(const char *cp_chFileName)
{
	if(!pr_SoundManager->p_DSound)
	{
		return false;
	}
	// estruturas necess�rias para criar buffer de som
	WAVEFORMATEX wfm;             // windows audio format
	DSBUFFERDESC stBufferDesc;    // directx buffer descritor
	HRESULT hr;

	// header de uma Wave
	char	        chRId[4] = {0,0,0,0};
	unsigned int    uiRLen;
	char	        chWId[4] = {0,0,0,0};
	char	        chFId[4] = {0,0,0,0};
	unsigned int	uiFLen;
	unsigned short  usFormatTag;
	unsigned short  usBlockAlign;
	char	        chDId[4] = {0,0,0,0};
	
	
	// reseta WAVEFORMATEX e DSBUFFERDESC
	memset(&stBufferDesc,0,sizeof(DSBUFFERDESC));
	memset(&wfm,0,sizeof(WAVEFORMATEX));


	// abre o arquivo de som .wav
	p_File = fopen(cp_chFileName,"rb");

	if (p_File)
	{
		// come�a a ler dados da wave
		//l� ID
		fread(&chRId,4,sizeof(char),p_File);
		// l� o tamanho do arquivo
		fread(&uiRLen,4,sizeof(char),p_File);
		// l� mais ID
		fread(&chWId,4,sizeof(char),p_File);
		// l� mais ID
		fread(&chFId,4,sizeof(char),p_File);
		// le o FLEn
		fread(&uiFLen,1,sizeof(unsigned int),p_File);
		// Le o FormatTag
		fread(&usFormatTag,1,sizeof(unsigned short),p_File);
		// le o numero de canais (1 - mono, 2 - stereo)
		fread(&usChannels,1,sizeof(unsigned short),p_File);
		// L� a frequencia do som
		fread(&uiFrequency,1,sizeof(unsigned int),p_File);
		// L� a m�dia de bytes por segundo (Freq * Bits * nChannels)
		fread(&uiAvgBytesPerSec,1,sizeof(unsigned int),p_File);
		// l� o block Align ( canais * BitsPerSample / 8)
		fread(&usBlockAlign,1,sizeof(unsigned short),p_File);
		// l� o numero de bits por Sample ( 8 ou 16 bits)
		fread(&usBitsPerSamples,1,sizeof(unsigned short),p_File);
		// le mais um identificador
		fread(&chDId,4,sizeof(char),p_File);
		// l� o tamanho dos dados (somente dados, sem header)
		fread(&uiDataSize,1,sizeof(unsigned int),p_File);

		// preenche a estrutura WAVEFORMATEX necess�ria para criar
		// o buffer de som
		wfm.wBitsPerSample = usBitsPerSamples;
		wfm.nAvgBytesPerSec = uiAvgBytesPerSec;
		wfm.nBlockAlign = usBlockAlign;
		wfm.wFormatTag  = usFormatTag;
		wfm.nChannels   = usChannels;
		wfm.nSamplesPerSec = uiFrequency;
		wfm.cbSize = 0;

		// agora preenche a estrutura DSBUFFERDESC (descritor do Buffer de som)
		stBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		stBufferDesc.dwBufferBytes = (bIsFX)? uiDataSize: wfm.nAvgBytesPerSec * 2;      // tamanho da wave (dados)
		stBufferDesc.lpwfxFormat = &wfm;              // seta referencia para WAVEFORMATEX
		stBufferDesc.dwFlags = (bIsFX)? DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME : DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;

		// Cria finalmente o sound Buffer (vazio)
		pr_SoundManager->p_DSound->CreateSoundBuffer(&stBufferDesc,&p_Buffer,NULL);

		// variaveis utilizadas para preencher buffer com som
		void *p_StartMemory = NULL;
		DWORD uiBytesLocked = 0;
		DWORD uiTotalLocked = 0;


		// se som for FX, cria de um jeito
		if (bIsFX)
		{
			// agora vamos travar o bufffer (lock) para preench�-lo com dados (o som)
			while (uiTotalLocked < uiDataSize)
			{
				hr = p_Buffer->Lock(
									uiTotalLocked,  // inicio do lock no buffer
									uiDataSize - uiTotalLocked, // o quanto deve trancar
									&p_StartMemory, // memoria trancada
									&uiBytesLocked, // quanto trancou
										NULL,
									0,
									DSBLOCK_FROMWRITECURSOR);
				// le bytes (dados da wav para o sound buffer
				fread(p_StartMemory,uiBytesLocked,sizeof(unsigned char),p_File);
				// soma os bytes trancados ao total j� trancado
				uiTotalLocked += uiBytesLocked;

				// libera a por��o do buffer j� preenchida com dados
				p_Buffer->Unlock(p_StartMemory,uiBytesLocked,NULL,0);
			} // repete a opera��o enquanto a quantidade de bytes trancadas � menor que o tamanho do buffer

			// fecha o arquivo, n�o precisamos mais.
			fclose(p_File);
			return true;
		}
		else   // m�sica
		{
			// Clear Sound Buffer
			ClearSoundBuffer();
			// set Mid of Buffer
			uiMidBuffer = stBufferDesc.dwBufferBytes / 2;		
			return true;
		}
	}
	return false;
}



//---------------------------------------------------------------------------- 
// Nome: Stop()
// Desc: P�ra de tocar um som, n�o faz o retorno do cursor de play
// caso outro play for dado, vai continuar de onde parou
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLSound::Stop(void)
{
	if(p_Buffer)
	{
		p_Buffer->Stop();
		if (!bIsFX)
		{
			// reseta variaveis utilizadas para finalizar o play streamming
			bSameSeg = false;
			uiEndMark = 0;

			// retira o som da lista de sons que est�o tocando
			int iSize = (int)pr_SoundManager->PlayMusic.size();
			for (int i = 0; i < iSize; i++)
			{
				if (pr_SoundManager->PlayMusic[i] == this)
				{
					pr_SoundManager->PlayMusic.erase(pr_SoundManager->PlayMusic.begin()+i);
					break;
				}
			}
			// limpa o buffer
			ClearSoundBuffer();
			// reseta o File Pointer para o inicio da �rea de dados
			SeekToWaveData();
			return true;
		}
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------- 
// Nome: Play(bool bLoopPam)
// Desc: Come�a a reproduzir o som.
// Pams: verdadeiro se som vai tocar em loop, falso caso contr�rio
//---------------------------------------------------------------------------- 
bool CNGLSound::Play(bool bLoopPam)
{
	HRESULT hr;

	// existe buffer de som?
	if (p_Buffer)
	{
		// som � do tipo efeito sonoro?
		if (bIsFX)
		{
			if (bLoopPam)
			{
				hr = p_Buffer->Play(0,0,DSBPLAY_LOOPING);
			}
			else
			{
				hr = p_Buffer->Play(0,0,0);
			}
			
		}
		else // som � do tipo m�sica
		{
			if (IsPlaying()) // se som j� estiver tocando, retorna
			{
				return false;
			}
			// insere no vetor de m�sicas tocando esta classe
			pr_SoundManager->PlayMusic.push_back(this);
			
			// j� preenche o buffer com dados
			DWORD dwBytesLocked = 0;
			DWORD dwTotalLocked = 0;
			void  *p_Data       = NULL;

			while (dwTotalLocked < (uiMidBuffer * 2))				
			{
				// tranca todo o buffer e insere som
				p_Buffer->Lock(dwTotalLocked,
				  						 (uiMidBuffer * 2) - dwTotalLocked,
											 &p_Data,
											 &dwBytesLocked,
											 NULL,
											 NULL,
											 0);
				fread((unsigned char *)p_Data,dwBytesLocked,sizeof(unsigned char),p_File);
				uiWavCurPos += dwBytesLocked;
				// destrava o peda�o de buffer trancado
				p_Buffer->Unlock(p_Data,dwBytesLocked,NULL,0);
				// soma ao total travado
				dwTotalLocked += dwBytesLocked;
			}
			// come�a a tocar o buffer
			hr = p_Buffer->Play(0,0,DSBPLAY_LOOPING);
			//seta loop
			bMusicLoop = bLoopPam;
		}
	}

	if (hr == DS_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//---------------------------------------------------------------------------- 
// Nome: SeekStartWaveData()
// Desc: Posiciona o File Pointer no inicio da �rea de dados da wave
//       necess�rio para streamming (som em loop)
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSound::SeekToWaveData(void)
{
	if (p_File)
	{
		// reseta o file pointer
		fseek(p_File,0,SEEK_SET);
		// pula o reader e vai direto pra parte de dados
		// apenas variavel tempor�ria (n�o vai ser usado)
		char temp[42];
		// l� todo o header da wave para poder pular.
		fread(temp,42,sizeof(unsigned char),p_File);
		// reseta a variavel que controla a posicao do cursor na wav (area de dados)
		uiWavCurPos = 0;
	}
}

//---------------------------------------------------------------------------- 
// Nome: ClearSoundBuffer(void)
// Desc: seta o buffer alocado com 0's (silencio)
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSound::ClearSoundBuffer(void)
{
	if (p_Buffer)
	{
		// estrutura directx que pega informa��es sobre buffer de som
		DSBCAPS dsbCaps;
		HRESULT hr;
		// vari�veis necess�rias para lock no buffer
		void *p_StartMemory = NULL;
		DWORD dwBytesLocked = 0;
		DWORD dwTotalLocked = 0;
		
		// seta o buffer
		dsbCaps.dwSize = sizeof(DSBCAPS);
		p_Buffer->GetCaps(&dsbCaps);

		// coloca o cursor do play buffer na posi��o 0;
		p_Buffer->SetCurrentPosition(0);

		// enquanto o total trancado for menor que o tamanho do buffer, continua
		while (dwTotalLocked < dsbCaps.dwBufferBytes)
		{
			p_Buffer->Lock(
						dwTotalLocked,  // inicio do lock no buffer
						dsbCaps.dwBufferBytes - dwTotalLocked, // o quanto deve trancar
						&p_StartMemory, // memoria trancada
						&dwBytesLocked, // quanto trancou
			    		NULL,
						0,
						DSBLOCK_FROMWRITECURSOR);

			// limpa o buffer
			memset(p_StartMemory,0,sizeof(Byte)*dwBytesLocked);
			// soma ao que j� foi trancado
			dwTotalLocked += dwBytesLocked;
			// destrava o buffer
			hr = p_Buffer->Unlock(p_StartMemory,dwBytesLocked,NULL,0);
		}	
	}
}


//---------------------------------------------------------------------------- 
// Nome: DuplicateSound(CNGLSound SoundSrc,CNGLSound SoundDest)
// Desc: Duplica um som, atrav�s de um outro j� existente. o Ponteiro para
//       o buffer de som apenas sera uma refer�ncia para um buffer j� criado
// Pams: Ponteiro para buffer Fonte, e ponteiro para buffer Destino
//---------------------------------------------------------------------------- 
bool CNGLSound::DuplicateSound(CNGLSound *p_SoundSrc)
{
	// copia todas as vari�veis de uma classe para outra
	uiDataSize		  = p_SoundSrc->GetDataSize();
	usChannels		  = p_SoundSrc->GetNumberOfChannels();
	uiFrequency	  = p_SoundSrc->GetFrequency();
	usBitsPerSamples = p_SoundSrc->GetBitsPerSample();
	uiAvgBytesPerSec = p_SoundSrc->GetAvgBytesPerSec();
	uiMidBuffer      = p_SoundSrc->GetMidOfBuffer();


	// DirectSound faz a duplica��o do buffer (reference count)
	if (pr_SoundManager->p_DSound->DuplicateSoundBuffer(p_SoundSrc->p_Buffer,&p_Buffer) == DS_OK)
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: IsPlaying()
// Desc: Retorna se o som est� sendo reproduzido.
// Pams: nenhum
//----------------------------------------------------------------------------
bool CNGLSound::IsPlaying()
{
	if (p_Buffer)
	{
		DWORD dwStatus;

		p_Buffer->GetStatus(&dwStatus);

		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{
			return true;
		}
		if ((dwStatus & DSBSTATUS_LOOPING) == DSBSTATUS_LOOPING)
		{
			return true;
		}
	}
	return false;
}