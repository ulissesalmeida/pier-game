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
#ifndef _CNGLANIMATION_
#define _CNGLANIMATION_

//includes
#include "NGLTimeAccumulator.h"
#include "StlFiles.h"

//protótipos
class CNGLMain;

//!Classe CNGLAnimation
/*!
	Uma seqüência de animação de um sprite.
*/
class CNGLAnimation :	public CNGLObject
{
private:
	//!Acumulator de tempo (usado para trocar quadros de animação).
	CNGLTimeAccumulator TimeAccum;

	//!Número de quadros por segundo na animação.
	int iFramesPerSecond;

public:
	//!Indica se a animação deve reiniciar quando terminar (contínua ou finita).
	bool bRepeat;

	//!Índices dos quadros de animação na imagem.
	vector<int> Frames;

	//!Índice do quadro atual no vetor de quadros.
	int iCurrentFrame;

	//!Ponteiro para o main da NGL.
	CNGLMain *pr_Main;

public:

	/*!
	Construtor padrão.
	*/
	CNGLAnimation(void);

	/*!
	Destrutor padrão.
	*/
	virtual ~CNGLAnimation(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release(void);

	/*!
		Retorna se a animação terminou.	
		\return Retorna verdadeiro se a animação acabou. Para animações em loop, 
		o retorno é sempre falso.
	*/
	bool Ended(void);

	/*!
	Atualiza a animação.
	*/
	void Update(void);

	/*!
		Retorna o índice do quadro corrente na imagem.
		\return Índice do quadro corrente na imagem.
	*/
	int GetCurrentFrame(void);

	/*!
		Reinicia a animação.
	*/
	void Reset(void);

	/*!
		Cria um clone da animação atual. Essa função aloca um objeto CNGLAnimation e retorna
		um ponteiro para a mesma. Para deletar esse ponteiro, deve ser chamado o delete do C++.
		\return Ponteiro para uma animação clonada.
	*/
	CNGLAnimation *GetClone(void);
	/*!
		Configura o intervalo de tempo entre os quadros (em FPS).
		\param iFrameInterval: intervalo de tempo.
		\param uiTimeAccum: Tempo acumulado no acumulador de tempo.
	*/
	void SetFrameInterval(int iFrameInterval,unsigned int uiTimeAccum = 0);
};

#endif