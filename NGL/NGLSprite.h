#ifndef _CNGLSPRITE_
#define _CNGLSPRITE_

//includes
#include "NGLobject.h"
#include "NGLvector.h"
#include "NGLanimation.h"
#include "NGLimage.h"

//prot�tipos
class CNGLMain;
class CNGLLayer;

//!Classe CNGLSprite
/*! 
	Esta classe cont�m o sprite configurado, com posi��o, anima��es e espelhamentos.
*/
class CNGLSprite :	public CNGLObject
{
public:

	//!Indica se o sprite est� vis�vel ou n�o.
	bool			bVisible;

	//!Ponteiro para o CNGLMain.
	CNGLMain	*pr_Main;

	//!Refer�ncia para a layer � qual este sprite pertence.
	CNGLLayer	*pr_Layer;

	//!Posi��o (x,y) do sprite na layer.
	CNGLVector Position;

	//!Lista de anima��es.
	vector<CNGLAnimation*> Animations;

	//!Indica a anima��o corrente do sprite.
	short sCurrentAnim;

	//!Refer�ncia para a imagem utilizada pelo sprite.
	CNGLImage *pr_Image;

	//!Indica o tipo de espelhamento (NGLMIRROR_NONE, NGLMIRROR_LEFTRIGHT, NGLMIRROR_UPDOWN).
	Byte byMirror;

public:
	/*!
	Construtor padr�o.
	*/
	CNGLSprite(void);

	/*!
	Destrutor padr�o.
	*/
	virtual ~CNGLSprite(void);

	/*!
		Finaliza a classe.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release(void);

	/*!
		Cria o sprite.
		\param pc_FileName: Nome do arquivo da imagem fonte.
		\param cFrameSize: Tamanho do quadro na imagem fonte.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Create(const char *pc_FileName,const CNGLVector &cFrameSize);

	/*!
		Desenha o sprite no BackBuffer.
	*/
	void Draw(void);

	/*!
		Atualiza o sprite
	*/
	void Update(void);

	/*!
	Adiciona uma anima��o ao sprite.
	\param iFPS: N�mero de quadros por segundo.
	\param bRepeat: Indica se a anima��o � cont�nua ou finita.
	\param iFrameCount: N�mero de quadros da anima��o.
	\param ...: �ndices dos quadros da anima��o.
	*/
	void AddAnimation(int iFPS, bool bRepeat, int iFrameCount,...);

	/*!
	Reinicia a anima��o corrente.
	*/
	void ResetAnimation(void);

	/*!
	Ajusta a anima��o corrente.
	\param sAnim: Indice da nova anima��o.
	*/
	void SetCurrentAnimation(short sAnim);

	/*!
	Exclui todas as anima��es do vetor "Animations".
	*/
	void ClearAnimations(void);

	/*!
	Retorna um clone do sprite.
	\param bAddToLayer: Flag indicando que o sprite deve ser adicionado a layer. Caso seja verdadeiro
	a layer automaticamente desalocar� este clone. Sen�o deve-se deletar este clone usando "delete".
	\return Retorna um ponteiro para o sprite clonado.
	*/
	CNGLSprite *GetClone(bool bAddToLayer);

	/*!
		Retorna o frame atual do sprite.
		\return Retorna um CNGLFrame contendo o frame atual.
	*/
	CNGLFrame GetFrame(void);
};

#endif