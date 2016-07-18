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

#define NPC_HEIGHT ITEM_HEIGHT

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
	
	// Moving
	float m_moveSpeed;
	float m_sprintSpeed;
	
	Item *m_leftHand;
	Item *m_rightHand;
	
protected:
	virtual void Update( float pDelta );

public:
	NPC();
	NPC( const Vector2<float> &pPosition );
	virtual ~NPC();
	
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
	
	void SetLeftHandItem( Item *pItem );
	void SetRightHandItem( Item *pItem );
	
	inline float GetMoveSpeed() const { return m_moveSpeed; }
	inline float GetSprintSpeed() const { return m_sprintSpeed; }
	
	inline void SetMoveSpeed( float pSpeed ) { m_moveSpeed = pSpeed; }
	inline void SetSprintSpeed( float pSpeed ) { m_sprintSpeed = pSpeed; }
	
	inline Item* GetLeftHandItem() const { return m_leftHand; }
	inline Item* GetRightHandItem() const { return m_rightHand; }
};

#endif