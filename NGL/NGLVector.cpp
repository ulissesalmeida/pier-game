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
#include "NGLvector.h"
#include "math.h"

//---------------------------------------------------------------------------- 
// Nome: CNGLVector(void)
// Desc: construtor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLVector::CNGLVector(void)
{
	fx = fy = 0.0f;
}

//---------------------------------------------------------------------------- 
// Nome: ~CNGLVector(void)
// Desc: destrutor padrão
// Pams: nenhum
//---------------------------------------------------------------------------- 
CNGLVector::~CNGLVector(void)
{
}
//---------------------------------------------------------------------------- 
// Nome: CNGLVector(float fxPam, float fyPam)
// Desc: inicializa o vetor com parâmetros
// Pams: fx,fy
//---------------------------------------------------------------------------- 
CNGLVector::CNGLVector(float fxPam, float fyPam)
{
	fx = fxPam;
	fy = fyPam;
}

//---------------------------------------------------------------------------- 
// Nome: operator ==(const CNGLVector & v)
// Desc: compara este vetor com outro
// Pams: outro vetor
//---------------------------------------------------------------------------- 
bool CNGLVector::operator ==(const CNGLVector & cv)
{
	return (fx == cv.fx && fy == cv.fy);
}

//---------------------------------------------------------------------------- 
// Nome: operator ==(const CNGLVector & v)
// Desc: compara o vetor
// Pams: outro vector
//---------------------------------------------------------------------------- 
bool CNGLVector::operator !=(const CNGLVector & cv)
{
	return ((fx != cv.fx) || (fy != cv.fy));
}

//---------------------------------------------------------------------------- 
// Nome: Magnitude(void)
// Desc: retorna o módulo do vetor
// Pams: nenhum
//---------------------------------------------------------------------------- 
float CNGLVector::Magnitude(void)
{
	return (float)sqrt((fx * fx) + (fy * fy));
}

//---------------------------------------------------------------------------- 
// Nome: Normalize(void)
// Desc: trasforma este vetor em vetor unitário
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLVector::Normalize(void)
{
	float fMag = Magnitude();
	fx /= fMag;
	fy /= fMag;
}

//---------------------------------------------------------------------------- 
// Nome: operator-(const CNGLVector & v)
// Desc: retorna a subtração do vetor
// Pams: outro vetor
//---------------------------------------------------------------------------- 
CNGLVector CNGLVector::operator-(const CNGLVector & cv)
{
	return CNGLVector(fx - cv.fx, fy - cv.fy);
}

//---------------------------------------------------------------------------- 
// Nome: operator +(const CNGLVector & v)
// Desc: retorna a soma deste vetor com outro
// Pams: outro vetor
//---------------------------------------------------------------------------- 
CNGLVector CNGLVector::operator +(const CNGLVector & cv)
{
	return CNGLVector(fx + cv.fx, fy + cv.fy);
}

//---------------------------------------------------------------------------- 
// Nome: operator+=(const CNGLVector & v)
// Desc: soma outro vetor a este
// Pams: outro vetor
//---------------------------------------------------------------------------- 
void CNGLVector::operator+=(const CNGLVector & cv)
{
	fx += cv.fx;
	fy += cv.fy;
}

//---------------------------------------------------------------------------- 
// Nome: operator -=(const CNGLVector & v)
// Desc: subtrai outro vetor deste 
// Pams: outro vetor
//---------------------------------------------------------------------------- 
void CNGLVector::operator -=(const CNGLVector & cv)
{
	fx -= cv.fx;
	fy -= cv.fy;
}

//---------------------------------------------------------------------------- 
// Nome: operator*(float fVal)
// Desc: retorna a multiplicação do vetor pela constante
// Pams: constante
//---------------------------------------------------------------------------- 
CNGLVector CNGLVector::operator*(const float cfVal)
{
	return CNGLVector(fx*cfVal,fy*cfVal);
}

//---------------------------------------------------------------------------- 
// Nome: operator/(float fVal)
// Desc: retorna a divisão do vetor pela constante
// Pams: constante
//---------------------------------------------------------------------------- 
CNGLVector CNGLVector::operator/(const float cfVal)
{
	return CNGLVector(fx/cfVal,fy/cfVal);
}

//---------------------------------------------------------------------------- 
// Nome: operator *=(const float fVal)
// Desc: multiplica o vetor pela constante
// Pams: constante
//---------------------------------------------------------------------------- 
void CNGLVector::operator *=(const float cfVal)
{
	fx *= cfVal;
	fy *= cfVal;
}

//---------------------------------------------------------------------------- 
// Nome: operator /=(const float fVal)
// Desc: divide o vetor pela constante
// Pams: constante
//---------------------------------------------------------------------------- 
void CNGLVector::operator /=(const float cfVal)
{
	fx /= cfVal;
	fy /= cfVal;
}

//---------------------------------------------------------------------------- 
// Nome: DotProduct(const CNGLVector & v)
// Desc: Retorna o produto escalar de dois vetores.
// Pams: vetor
//---------------------------------------------------------------------------- 
float CNGLVector::DotProduct(const CNGLVector & cv)
{
	return ( (fx*cv.fx) + (fy*cv.fy) );
}

//---------------------------------------------------------------------------- 
// Nome: Floor(void)
// Desc: elimina as casa descimais das componentes do vetor
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLVector::Floor(void)
{
	fx = (float)floor(fx);
	fy = (float)floor(fy);
}

//---------------------------------------------------------------------------- 
// Nome: Ceil(void)
// Desc: Faz os valores do vetor receberem o seu próximo maior inteiro (teto). Por exemplo, para fX = 1.3f e fY = 3.5f, após esse método, estarão com os valores fX = 2.0f e fY = 4.0f.
// Pams: nenhum
//---------------------------------------------------------------------------- 
void CNGLVector::Ceil(void)
{
	fx = (float)ceil(fx);
	fy = (float)ceil(fy);
}

//---------------------------------------------------------------------------- 
// Nome: CNGLVector(int ix, int iy)
// Desc: inicializao vetor com parâmetros inteiros
// Pams: componente x, conponente y
//---------------------------------------------------------------------------- 
CNGLVector::CNGLVector(int ix, int iy)
{
	fx = (float)ix;
	fy = (float)iy;
}
