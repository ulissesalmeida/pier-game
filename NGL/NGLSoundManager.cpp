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
#include "NGLsoundmanager.h"
#include "NGLMain.h"


//---------------------------------------------------------------------------- 
// Nome: CNGLSoundManager(void)
// Desc: construtor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLSoundManager::CNGLSoundManager(void)
{
	p_DSound  = NULL;
	p_Primary = NULL;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLSoundManager(void)
// Desc: destrutor padr�o
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLSoundManager::~CNGLSoundManager(void)
{
	Release();
}

//---------------------------------------------------------------------------- 
// Nome: Release(void)
// Desc: finaliza o sound manager
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLSoundManager::Release(void)
{
	// limpa o vetor de musicas tocando
	PlayMusic.clear();

	// libera memoria de todos os sons alocados
	for (int i = (int)Sounds.size() - 1; i >=0; i--)
	{
		Sounds[i]->Release();
		delete Sounds[i];
		Sounds[i] = NULL;
	}
	// limpa o vetor de sons
	Sounds.clear();

	// deletando o buffer prim�rio (Mixer)
	if (p_Primary)
	{
		p_Primary->Stop();
		p_Primary->Release();
		p_Primary = NULL;
	}
	// deletando o DirectSound
	if (p_DSound)
	{
		p_DSound->Release();
		p_DSound = NULL;
	}	

	return true;
}

//---------------------------------------------------------------------------- 
// Nome: DeleteSound(CNGLLayer **p_Layer)
// Desc: Deleta um som e retira do sound manager
// Pams: refer�ncia ao ponteiro do som
//---------------------------------------------------------------------------- 
bool CNGLSoundManager::DeleteSound(CNGLSound **p_Sound)
{
	if(p_Sound && *p_Sound)
	{
		for(int i = (int)Sounds.size()-1; i >=0; i--)
		{
			if(Sounds[i] == *p_Sound)
			{
				Sounds[i]->Release();
				delete Sounds[i];
				*p_Sound = NULL;
				Sounds.erase(Sounds.begin()+i);
				return true;
			}
		}
	}

	//objeto de som n�o encontrado
	return false;
}

//---------------------------------------------------------------------------- 
// Nome: LoadSound(char *cp_chFileName,bool bol bIsFX)
// Desc: Insere um novo som no vetor de sons do Manager o inicializa
// Pams: cp_chFileName nome do arquivo de som (.wav)
//       BIsFX � variavel que diz se o som � musica ou efeito sonoro.
//---------------------------------------------------------------------------- 
CNGLSound *CNGLSoundManager::LoadSound(char *cp_chFileName,bool bIsFX)
{
	//tenta encontrar uma som j� lido
	// (varre o vetor de traz pra frente)
	for(int i = (int)Sounds.size()-1; i>=0; i--)
	{
		//Se j� existe som alocado
		if(!Sounds[i]->FileName.compare(cp_chFileName))
		{
			// cria o objeto CNGLSound
			CNGLSound *p_Sound = new CNGLSound(this,cp_chFileName,bIsFX);
			// faz o ponteiro para som apontar para o mesmo
			//buffer de Sounds[i]
			p_Sound->DuplicateSound(Sounds[i]);
			// inclui o som no vetor stl de sons
			Sounds.push_back(p_Sound);
			return p_Sound;
		}
	}

	//Se n�o existe ainda o som, ent�o aloca o objeto 
	// e carrega o arquivo de som
	CNGLSound *p_Sound = new CNGLSound(this,cp_chFileName,bIsFX);
	if(p_Sound)
	{
		if (p_Sound->LoadFromFile(cp_chFileName))
		{
			//Adiciona a lista
			Sounds.push_back(p_Sound);
		}
		else // n�o conseguiu carregar som. Deleta a classe e retorna null
		{
			delete p_Sound;
			p_Sound = NULL;
		}
	}
	//retorna o Som
	return p_Sound;
}

//---------------------------------------------------------------------------- 
// Nome: Initialize(void)
// Desc: Inicializa o DirectSound e cria o buffer prim�rio 
// Pams: nenhum
//---------------------------------------------------------------------------- 
bool CNGLSoundManager::Initialize(void)
{
	// Descritores para o Buffer Prim�rio
	DSBUFFERDESC   stBufferDesc;
	WAVEFORMATEX   wfm;

	// Cria o principal objeto directsound
	if (DirectSoundCreate(NULL, &p_DSound,NULL) != DS_OK)
	{
		return false;
	}

	//ajusta cooperative level usado para interagir com outras aplica��es windows
	if (p_DSound->SetCooperativeLevel((HWND)pr_Main->pr_Wnd,DSSCL_PRIORITY ) != DS_OK)
	{
		Release();
		return false;
	}
	
	//preenche descritor para buffer prim�rio
	memset(&stBufferDesc,0,sizeof(DSBUFFERDESC));
	stBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	stBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	stBufferDesc.dwBufferBytes = 0;
	stBufferDesc.lpwfxFormat = NULL;

	// preenche estrutura do Buffer prim�rio para o formato desejado
	memset(&wfm,0,sizeof(WAVEFORMATEX));
	wfm.wFormatTag			= WAVE_FORMAT_PCM;  // sem compress�o
	wfm.nChannels				= 2;                // stereo
	wfm.nSamplesPerSec	= 44100;						// 44.1 Khz
	wfm.wBitsPerSample	= 16;								// 16 bits de som
	wfm.nBlockAlign			= wfm.wBitsPerSample * wfm.nChannels / 8; // bytes lidos por vez
	wfm.nAvgBytesPerSec	= wfm.nSamplesPerSec * wfm.nBlockAlign; // m�dia de bytes por segundo

	// cria o buffer prim�rio
	if (p_DSound->CreateSoundBuffer(&stBufferDesc,&p_Primary,NULL) != DS_OK)
	{
		Release();
		return false;
	}	

	// Ajusta o formato para o mixer (buffer prim�rio)	
	if (p_Primary->SetFormat(&wfm) != 0)
	{
		Release();
		return false;
	}
	
	// faz o buffer prim�rio tocar continuamente
	if (p_Primary->Play(0,0,DSBPLAY_LOOPING) != DS_OK)
	{
		Release();
		return false;
	}

	return true; // tudo inicializado com sucesso!
}

//---------------------------------------------------------------------------- 
// Nome: Update(void)
// Desc: rotina que � chamada a cada la�o, faz o update do som de musica
//       quando o play cursor chegar na metade, atualiza a primeira por��o
//       quando o play cursor chegar no fim, atualiza a segunda por��o
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLSoundManager::Update(void)
{
	// se houver musica tocando, ent�o vamos dar um "refresh"
	for (int iIndex = (int)PlayMusic.size() - 1 ; iIndex >= 0 ; iIndex--)
	{
		CNGLSound *p_Music = PlayMusic[iIndex];
		DWORD dwPlay        = 0;
		DWORD dwMidBuffer   = 0;
		DWORD dwStartOfs    = 0;
		void         *lpData       = NULL;
		DWORD dwBytesLocked = 0;
		DWORD dwTotalLocked = 0;
			
		// pega a posic�o do play cursor no buffer de som
		p_Music->p_Buffer->GetCurrentPosition(&dwPlay,&dwStartOfs);
			
		// copia o valor da metade do buffer (s� pra facilitar)
		dwMidBuffer = p_Music->GetMidOfBuffer();

		// trata fim do som, n�o precisa mais preencher com dados.
		if (p_Music->bSameSeg)
		{
			if ((dwPlay >= p_Music->uiEndMark) ||
				 (dwPlay > dwMidBuffer && p_Music->uiEndMark < dwMidBuffer) ||
				 (dwPlay < dwMidBuffer && p_Music->uiEndMark > dwMidBuffer))
			{
				p_Music->Stop();
				continue;
			}
			continue;
		}
		// se tem que atualizar o buffer...
		if (((dwPlay >= dwMidBuffer) && (p_Music->uiLastPlayPos < dwMidBuffer)) || (dwPlay < p_Music->uiLastPlayPos))
		{
			dwStartOfs = (dwPlay >= dwMidBuffer)? 0: dwMidBuffer;
			
			// se um marco j� foi dado ao segmento, ent�o o dwplay est� no mesmo segmento para finalizar
			// enquanto isso, j� limpa o outro peda�o do segmento
			if (p_Music->uiEndMark)
			{
				p_Music->bSameSeg = true;
				continue;
			}
			// enquanto n�o travou toda a metade do buffer...
			while (dwTotalLocked < dwMidBuffer)				
			{
				// tranca a metade do buffer
				p_Music->p_Buffer->Lock(dwStartOfs+dwTotalLocked,
											dwMidBuffer - dwTotalLocked,
											&lpData,
											&dwBytesLocked,
											NULL,
											NULL,
											0);		
				// verifica se n�o chegou ao fim do arquivo
				if ((p_Music->uiWavCurPos + dwBytesLocked) < p_Music->GetDataSize())
				{
					fread((unsigned char *)lpData,dwBytesLocked,sizeof(unsigned char),p_Music->p_File);
					p_Music->uiWavCurPos += dwBytesLocked;
				}
				else // alcan�ou o fim
				{
					unsigned int uiRestBytes;
					// reseta uma metade do buffer
					memset((Byte *)lpData,0,sizeof(Byte)*dwBytesLocked);
					// pega a quantidade de bytes que faltam para fim de arquivo;
					uiRestBytes = p_Music->GetDataSize() - p_Music->uiWavCurPos;
					// le o peda�o de som da wave que faltava
					fread((unsigned char *)lpData,uiRestBytes,sizeof(unsigned char),p_Music->p_File);
					// faz o ponteiro do arquivo voltar para o inicio dos dados
					p_Music->SeekToWaveData();

					// musica deve estar em loop? sim - n�o retira da playMusic List.
					if (!p_Music->bMusicLoop)
					{
						p_Music->uiEndMark = dwStartOfs + p_Music->GetDataSize() - p_Music->uiWavCurPos;
					}
					else
					{
						// l� a primeira parte da musica para concatenar com o fim do som
						fread((unsigned char*)lpData + uiRestBytes,dwBytesLocked - uiRestBytes,sizeof(unsigned char),p_Music->p_File);
						// atualiza posi��o do cursor na wave
						p_Music->uiWavCurPos = dwBytesLocked - uiRestBytes;
					}
				}
				// destrava o peda�o de buffer trancado
				p_Music->p_Buffer->Unlock(lpData,dwBytesLocked,NULL,0);
				// soma ao total travado
				dwTotalLocked += dwBytesLocked;
			} // end while
		} // end if play half buffer
	// atualiza a ultima posicao do play cursor.
	p_Music->uiLastPlayPos = dwPlay;
	} //  end for
}
