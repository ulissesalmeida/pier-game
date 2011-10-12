#ifndef _CNGLTIMEACCUMULATOR_
#define _CNGLTIMEACCUMULATOR_


#include "nglobject.h"

class CNGLTimeHandler;

//!CNGLTimeAccumulator
/*!
Classe utilizada para acumular tempo até o limite definido
*/
class CNGLTimeAccumulator :	public CNGLObject
{
	//!Ponteiro para gerenciador de tempo
	CNGLTimeHandler *pr_TimeHandler;

public:

	//!Tempo Limite
	unsigned int uiTimeLimit;

	//!Acumulador de tempo
	unsigned int uiTimeAccum;

public:

	/*
		!Inicia o acumulador de tempo
		\param pr_TimeHandlerPam: ponteiro de referência para gerenciador de tempo.
		\param uiTimeLimitPam: limite de tempo do acumulador.
	*/
	void Init(CNGLTimeHandler *pr_TimeHandlerPam, unsigned int uiTimeLimitPam);

	/*
		!Atualiza o acumulador de tempo.
	*/
	void Update(void);

	/*
		!Reinicia o acumulador de tempo.
	*/
	void Restart(void);

	/*!Retorna verdadeiro se o acumulador de tempo já excedeu o limite.
	  \return verdadeiro se acumulador excedeu o limite, senão retorna falso.
	*/
	bool Ended(void);

	/*!
		Construtor padrão.
	*/
	CNGLTimeAccumulator(void);

	/*!
		Destrutor padrão.
	*/
	~CNGLTimeAccumulator(void);

	/*! 
		Finaliza a classe.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release(void);
};

#endif