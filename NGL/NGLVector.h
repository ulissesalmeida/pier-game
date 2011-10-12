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
#ifndef _CNGLVECTOR_
#define _CNGLVECTOR_

#include "NGLObject.h"

//!CNGLVector
/*!
Classe utilizada para posicionamento de objetos e cálculos matemáticos.
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
		Construtor com parâmetros.
		\param ix: posição em X.
		\param iy: posição em Y.
	*/
	CNGLVector(int ix, int iy);

	/*!
		Construtor com parâmetros.
		\param fxPam: posição em X.
		\param fyPam: posição em Y.
	*/
	CNGLVector(float fxPam, float fyPam);
	/*!
		Construtor padrão.
	*/
	CNGLVector(void);

	/*!
		Destrutor padrão.
	*/
	~CNGLVector(void);

	/*!
		Finaliza a classe. Deve ser implementada nas classes filhas.
		\return verdadeiro se a operação foi bem sucedida, caso contrário retorna falso.
	*/
	bool Release() { return true; };

	/*!
		Operador de comparação por igualdade.
		\param cv: vetor a comparar.
	*/
	bool operator ==(const CNGLVector & cv);

	/*!
		Operador de comparação por diferença.
		\param cv: vetor a comparar.
	*/
	bool operator !=(const CNGLVector & cv);

	/*!
		Calcula o módulo do vetor.
		\return Módulo do vetor.
	*/
	float Magnitude(void);

	/*!
		Transforma este vetor em vetor unitário mantendo a direção.
	*/
	void Normalize(void);

	/*!
		Operação de subtração de dois vetores.
		\param cv: vetor a subtrair.
	*/
	CNGLVector operator-(const CNGLVector & cv);

	/*!
		Operação de soma de dois vetores.
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
		Operação de multiplicação deste vetor por uma constante.
		\param cfVal: constante da multiplicação.
	*/
	CNGLVector operator*(const float cfVal);

	/*!
		Operação de divisão deste vetor por constante.
		\param cfVal: constante da divisão.
	*/
	CNGLVector operator/(const float cfVal);

	/*!
		Multiplica o vetor por uma constante
		\param cfVal: constante da multiplicação
	*/
	void operator *=(const float cfVal);

	/*!
		Divide este vetor por uma constante.
		\param cfVal: contante da divisão.
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