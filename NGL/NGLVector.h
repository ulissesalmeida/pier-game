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
#ifndef _CNGLVECTOR_
#define _CNGLVECTOR_

#include "NGLObject.h"

//!CNGLVector
/*!
Classe utilizada para posicionamento de objetos e c�lculos matem�ticos.
*/
class CNGLVector : public CNGLObject
{
public:
	//!Eixo X do vetor.
	float fx;

	//!Eixo Y do vetor.
	float fy;

public:
	/*!
		Construtor com par�metros.
		\param ix: posi��o em X.
		\param iy: posi��o em Y.
	*/
	CNGLVector(int ix, int iy);

	/*!
		Construtor com par�metros.
		\param fxPam: posi��o em X.
		\param fyPam: posi��o em Y.
	*/
	CNGLVector(float fxPam, float fyPam);
	/*!
		Construtor padr�o.
	*/
	CNGLVector(void);

	/*!
		Destrutor padr�o.
	*/
	~CNGLVector(void);

	/*!
		Finaliza a classe. Deve ser implementada nas classes filhas.
		\return verdadeiro se a opera��o foi bem sucedida, caso contr�rio retorna falso.
	*/
	bool Release() { return true; };

	/*!
		Operador de compara��o por igualdade.
		\param cv: vetor a comparar.
	*/
	bool operator ==(const CNGLVector & cv);

	/*!
		Operador de compara��o por diferen�a.
		\param cv: vetor a comparar.
	*/
	bool operator !=(const CNGLVector & cv);

	/*!
		Calcula o m�dulo do vetor.
		\return M�dulo do vetor.
	*/
	float Magnitude(void);

	/*!
		Transforma este vetor em vetor unit�rio mantendo a dire��o.
	*/
	void Normalize(void);

	/*!
		Opera��o de subtra��o de dois vetores.
		\param cv: vetor a subtrair.
	*/
	CNGLVector operator-(const CNGLVector & cv);

	/*!
		Opera��o de soma de dois vetores.
		\param cv: vetor a somar.
	*/
	CNGLVector operator +(const CNGLVector & cv);

	/*!
		Soma outro vetor a este.
		\param cv: vetor a somar.
	*/
	void operator+=(const CNGLVector & cv);

	/*!
		Subtrai outro vetor deste.
		\param cv: vetor a subtrair.
	*/
	void operator -=(const CNGLVector & cv);
	/*!
		Opera��o de multiplica��o deste vetor por uma constante.
		\param cfVal: constante da multiplica��o.
	*/
	CNGLVector operator*(const float cfVal);

	/*!
		Opera��o de divis�o deste vetor por constante.
		\param cfVal: constante da divis�o.
	*/
	CNGLVector operator/(const float cfVal);

	/*!
		Multiplica o vetor por uma constante
		\param cfVal: constante da multiplica��o
	*/
	void operator *=(const float cfVal);

	/*!
		Divide este vetor por uma constante.
		\param cfVal: contante da divis�o.
	*/
	void operator /=(const float cfVal);

	/*!
		Retorna o produto escalar dos dois vetores.
		\param cv: vetor para calcular o produto escalar.
	*/
	float DotProduct(const CNGLVector & cv);

	/*!
		Elimina as casas decimais dos elementos do vetor.
	*/
	void Floor(void);

	/*!
		Arredonda para cima os elementos do vetor.
	*/
	void Ceil(void);	
};

#endif