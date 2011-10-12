/*NGL - Game Development Library 
Copyright (C) 2003, Nology Softwares. Todos os direitos reservados

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
#ifndef _CITEM_
#define _CITEM_

//Includes
#include "NGLObject.h"
#include "NGLTimeAccumulator.h"

class CNGLSprite;
class CLevel;
class CNGLSound;

//! Classe CItem
/*!
	Representa um item do jogo (diamante ou poção). Trata a interação do item com o jogador.
*/
class CItem :	public CNGLObject
{
public:
	//enumerando os tipos de item
	typedef enum eItemType
	{
		IT_YELLOW,
		IT_BLUE,
		IT_RED,
		IT_INVENCIBLE,
		IT_TOTAL
	} ItemType;

	//enumerando estados da classe CItem
	typedef enum eItemState
	{
		IS_IDLE,
		IS_RUN,
		IS_END
	} ItemState;

private:
	//! Tipo do item (IT_YELLOW, IT_BLUE, IT_RED ou IT_INVENCIBLE)
	ItemType Type;
	//! Estado corrente do item (IS_IDLE, IS_RUN ou IS_END)
	ItemState State;
	//! Ponteiro para sprite de escudo para invencibilidade
	CNGLSprite *p_SprShield;
	//! Ponteiro para som emitido quando jogador pega o item
	CNGLSound  *p_SndPickup;
	//! Acumulador de tempo de vida do item invencibilidade
	CNGLTimeAccumulator AccumInv;

public:
	//! Referência para a classe CLevel
	CLevel *pr_Level;
	//! Ponteiro para sprite do item
	CNGLSprite *p_Sprite;
	/*!
		Construtor padrão.
	*/
	CItem(void);
	/*!
		Destrutora padrão
	*/
	virtual ~CItem(void);
	/*!
		Libera recursos alocados pelo item (sprites e som).
	*/
	bool Release(void);
	/*!
		Inicializa os sprites e sons do item de acordo com o seu tipo.
		\param TypeParam: enumeração do tipo de item.
	*/
	bool Initialize(CItem::ItemType TypePam);
	/*!
		Método é chamado frequentemente. Ele executa os estados do item.
	*/
	void Execute(void);
	/*!
		Retorna o estado corrente do item.
		\return estado atual do item (IS_IDLE, IS_RUN, IS_END)
	*/
	CItem::ItemState GetState(void);
private:
	/*!
		Trata o estado IS_RUN. Este estado somente verifica se acabou a animação
		de item explodindo. Se terminou, então muda o estado para IS_END. A CLevel
		se encarregará  de remover este item de sua lista e desalocá-lo do jogo.
	*/
	void OnRun(void);
	/*!
		Soma pontos ao jogador de acordo com o item que foi pego.
	*/
	void AddPointsToPlayer(void);
	/*!
		Trata o estado IS_IDLE. Este estado ocorre quando o item está em espera no jogo.
		Se colidir com o jogador, então muda para o estado IS_RUN.
	*/
	void OnIdle(void);
	/*!
		Faz a troca de estados do item.
		\param NewState: Novo estado do item. pode ser IS_IDLE, IS_RUN, IS_END.
	*/
	void ChangeState(CItem::ItemState NewState);
};

#endif