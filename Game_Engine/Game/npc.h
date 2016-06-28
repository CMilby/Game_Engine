//
//  npc.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __NPC_H__
#define __NPC_H__

#include "item.h"
#include "renderableEntity.h"

class NPC : public RenderableEntity {

private:
	// Base Powers
	int m_maxHealth;
	int m_maxMana;
	int m_maxStamina;
	
	// Currents
	int m_currentHealth;
	int m_currentMana;
	int m_currentStamina;
	
	Item *m_leftHand;
	Item *m_rightHand;
	
protected:
	virtual void Update( float pDelta );

public:
	NPC();
	NPC( const Vector2<float> &pPosition );
	
	inline void SetMaxHealth( int pHealth ) { m_maxHealth = pHealth; }
	inline void SetMaxMana( int pMana ) { m_maxMana = pMana; }
	inline void SetMaxStamina( int pStamina ) { m_maxStamina = pStamina; }
	
	inline int GetMaxHealth() const { return m_maxHealth; }
	inline int GetMaxMana() const { return m_maxMana; }
	inline int GetMaxStamina() const { return m_maxStamina; }
	
	inline void SetCurrentHealth( int pHealth ) { m_currentHealth = pHealth; }
	inline void SetCurrentMana( int pMana ) { m_currentMana = pMana; }
	inline void SetCurrentStamina( int pStamina ) { m_currentStamina = pStamina; }
	
	inline int GetCurrentHealth() const { return m_currentHealth; }
	inline int GetCurrentMana() const { return m_currentMana; }
	inline int GetCurrentStamina() const { return m_currentStamina; }
	
	inline void SetLeftHandItem( Item *pItem ) { m_leftHand = pItem; }
	inline void SetRightHandItem( Item *pItem ) { m_rightHand = pItem; }
	
	inline Item* GetLeftHandItem() const { return m_leftHand; }
	inline Item* GetRightHandItem() const { return m_rightHand; }
};

#endif