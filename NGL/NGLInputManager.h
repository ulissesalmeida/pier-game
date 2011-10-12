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
#ifndef _CNGLINPUTMANAGER_
#define _CNGLINPUTMANAGER_

#ifndef DIRECTINPUT_VERSION
	#define DIRECTINPUT_VERSION         0x0300
#endif

#include "dinput.h"
#include "NGLobject.h"
#include "NGLVector.h"

class CNGLMain;

//!N�mero de teclas do teclado
#define NGLNUM_KEYS													256

//!Classe CNGLInputManager
/*!
	Gerencia as atividades de Input (teclado e mouse).
*/
class CNGLInputManager : public CNGLObject
{
public:

	//!Ponteiro de refer�ncia para a CNGLMain
	CNGLMain						*pr_Main;
	
	/*!
		Construtor padr�o.
	*/
	CNGLInputManager(void);

	/*!
		Destrutor padr�o.
	*/
	virtual ~CNGLInputManager(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);

	/*!
		Inicia o teclado e mouse, usando DirectInput.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Initialize(void);

	/*!
		L� entradas do teclado e mouse.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/	
	bool Read(void);

	/*!
		Retorna posi��o atual do cursor mouse.
		\return CNGLVector contedo a posi��o do cursor do mouse.
	*/	
	inline CNGLVector GetMousePos() { return MousePos; };

private:
	/*!
		L� dados do teclado.
		\return verdadeiro se conseguiu ler, sen�o retorna falso.
	*/
	bool ReadKeyboard(void);
	/*!
		L� dados do mouse.
		\return verdadeiro se conseguiu ler, sen�o retorna falso.
	*/
	bool ReadMouse(void);

private:
	//!Objeto do DirectInput.
	IDirectInput					*p_DInput;

	//!Dispositivo de teclado do DirectInput.
	IDirectInputDevice		*p_DevKeyboard;

	//!Dispositivo de mouse do DirectInput.
	IDirectInputDevice		*p_DevMouse;

	//!Estrutura de dados que guarda estado atual do teclado.
	Byte KeyboardState[NGLNUM_KEYS];

	//!Estrutura de dados que guarda estado anterior do teclado. Usada para verificar se uma tecla foi rec�m pressionada ou largada.
	Byte LastKeyboardState[NGLNUM_KEYS];

	//!Estrutura de dados que guarda estado atual do mouse.
	DIMOUSESTATE MouseState;

	//!Estrutura de dados que guarda estado anterior do mouse.  Usada para verificar se um bot�o foi rec�m pressionado ou largado.
	DIMOUSESTATE LastMouseState;

	//!Posi��o atual do mouse.
	CNGLVector MousePos;

	//!Posi��o do mouse vinda da aplica��o Windows.
	CNGLVector MouseWindowsPos;

public:
	/*!
		Cria o dispositivo de teclado.
		\return verdadeiro se criou com sucesso, sen�o retorna falso.
	*/
	bool CreateKeyboard(void);

	/*!
		Cria o dispositivo de mouse.
		\return verdadeiro se criou com sucesso, sen�o retorna falso.
	*/
	bool CreateMouse(void);

	/*!
		Verifica se o mouse est� ligado.
		\return verdadeiro se o mouse estiver ligado, sen�o retorna falso.
	*/
	bool IsMouseOn(void);

	/*!
		Verifica se uma tecla est� pressionada.
		\param cbyKeyCode: c�digo da tecla. Usar tabela de constantes de teclas do DirectInput.
		\return verdadeiro se a tecla estiver pressionada, sen�o retorna falso.
	*/
	bool KeyDown(const Byte cbyKeyCode);

	/*!
		Verifica se uma tecla foi pressionada neste instante.
		\param cbyKeyCode: c�digo da tecla. Usar tabela de constantes de teclas do DirectInput.
		\return verdadeiro se a tecla foi pressionada neste instante, sen�o retorna falso.
	*/
	bool KeyPressed(const Byte cbyKeyCode);

	/*!
		Verifica se uma tecla foi largada neste instante.
		\param cbyKeyCode: c�digo da tecla. Usar tabela de constantes de teclas do DirectInput.
		\return verdadeiro se a tecla foi largada neste instante, sen�o retorna falso.
	*/
	bool KeyReleased(const Byte cbyKeyCode);

	/*!
		Verifica se um bot�o do mouse est� pressionado.
		\param cbyBtnCode: c�digo do bot�o (ex: 0, 1, 2)
		\return verdadeiro se o bot�o estiver pressionado, sen�o retorna falso.
	*/
	bool MouBtnDown(const Byte cbyBtnCode);

	/*!
		Verifica se um bot�o do mouse foi pressionado neste instante.
		\param cbyBtnCode: c�digo do bot�o (ex: 0, 1, 2).
		\return verdadeiro se o bot�o foi pressionado neste instante, sen�o retorna falso.
	*/
	bool MouBtnPressed(const Byte cbyBtnCode);

	/*!
		Verifica se um bot�o do mouse foi largado neste instante.
		\param cbyBtnCode: c�digo do bot�o (ex: 0, 1, 2).
		\return verdadeiro se o bot�o foi largado neste instante, sen�o retorna falso.
	*/
	bool MouBtnReleased(const Byte cbyBtnCode);	

	/*!
		Ajusta a nova posi��o do mouse vinda da aplica��o Windows.
		\param cNewPos: CNGLVector contendo a nova posi��o do mouse.
	*/
	void SetWindowsMousePos(const CNGLVector &cNewPos);
};

#endif