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
#ifndef _CNGLTIMEHANDLER_
#define _CNGLTIMEHANDLER_

#include "NGLobject.h"
#include "stlfiles.h"

//!Classe CNGLTimeHandler
/*!
	Esta classe controla o rel�gio do jogo.
*/
class CNGLTimeHandler :	public CNGLObject
{
	
private:

	//!Armazena o �ltimo tempo obtido (em milisegundos).
	unsigned int uiLastTime;

	//!Tempo acumulado desde o �ltimo tempo obtido (em milisegundos).
	int iTimeAcum;

	//!N�mero de quadros que se passaram durante este per�odo ou o n�mero de chamadas da rotina Update().
	int	iFrameCount;

	//!N�mero de quadros por segundos.
	int	iFPS;

public:
	
	//!Ligar esse flag para prevenir slowdown.
	bool bPreventLowdown;

	//!Armazena o tempo passado desde o �ltimo quadro (em milisegundos).
	int iFrameTime;

	//!Armazena o tempo passado desde o �ltimo quadro (em segundos).
	float fFrameTime;

	/*!
		Recome�a a contagem de tempo.
	*/
	void Reset();

	/*! 
		Retorna o n�mero de frames por segundo.
		\return N�mero de frames por segundo.
	*/
	int	GetFPS();
	
	/*!
		Atualiza o tempo. Este m�todo deve ser chamado a cada quadro da aplica��o.
	*/
	void Update();
	
	/*!
		Inicializa vari�veis internas.
	*/
	void Initialize();
  
	/*! 
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);
	
	/*! 
		Construtor padr�o.
	*/
	CNGLTimeHandler(void);

	/*!
		Destrutor padr�o.
	*/
	virtual ~CNGLTimeHandler(void);
};

#endif