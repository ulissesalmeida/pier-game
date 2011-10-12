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
#ifndef _CNGLANIMATION_
#define _CNGLANIMATION_

//includes
#include "NGLTimeAccumulator.h"
#include "StlFiles.h"

//prot�tipos
class CNGLMain;

//!Classe CNGLAnimation
/*!
	Uma seq��ncia de anima��o de um sprite.
*/
class CNGLAnimation :	public CNGLObject
{
private:
	//!Acumulator de tempo (usado para trocar quadros de anima��o).
	CNGLTimeAccumulator TimeAccum;

	//!N�mero de quadros por segundo na anima��o.
	int iFramesPerSecond;

public:
	//!Indica se a anima��o deve reiniciar quando terminar (cont�nua ou finita).
	bool bRepeat;

	//!�ndices dos quadros de anima��o na imagem.
	vector<int> Frames;

	//!�ndice do quadro atual no vetor de quadros.
	int iCurrentFrame;

	//!Ponteiro para o main da NGL.
	CNGLMain *pr_Main;

public:

	/*!
	Construtor padr�o.
	*/
	CNGLAnimation(void);

	/*!
	Destrutor padr�o.
	*/
	virtual ~CNGLAnimation(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);

	/*!
		Retorna se a anima��o terminou.	
		\return Retorna verdadeiro se a anima��o acabou. Para anima��es em loop, 
		o retorno � sempre falso.
	*/
	bool Ended(void);

	/*!
	Atualiza a anima��o.
	*/
	void Update(void);

	/*!
		Retorna o �ndice do quadro corrente na imagem.
		\return �ndice do quadro corrente na imagem.
	*/
	int GetCurrentFrame(void);

	/*!
		Reinicia a anima��o.
	*/
	void Reset(void);

	/*!
		Cria um clone da anima��o atual. Essa fun��o aloca um objeto CNGLAnimation e retorna
		um ponteiro para a mesma. Para deletar esse ponteiro, deve ser chamado o delete do C++.
		\return Ponteiro para uma anima��o clonada.
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