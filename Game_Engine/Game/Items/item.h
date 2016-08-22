//
//  item.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ITEM_H__
#define __ITEM_H__

#include "logger.h"
#include "entity.h"
#include "renderableComponent.h"

#define ITEM_HEIGHT 1.0f

enum eHand {
	HAND_LEFT,
	HAND_RIGHT
};

class Item : public Entity {
	
private:
	std::string m_item;
	eHand m_hand;
	
	int m_useTime;
	int m_timeSinceUse;
	
	int m_cooldown;
	int m_currentCooldown;
	bool m_isCoolingDown;
	
protected:
	Vector3<float> m_handLeftOffset;
	Vector3<float> m_handRightOffset;
	
	RenderableComponent* GetRenderer() const;
	
	virtual void Update( float pDelta );

public:
	Item();
	Item( const std::string &pItem, eHand pHand );
	
	virtual bool Use();
	virtual void Collided( Entity *pOther );
	
	void SetPosition( const Vector3<float> &pPosition );
	void SetPosition();
	
	inline int GetUseTime() const { return m_useTime; }
	inline void SetUseTime( int pUseTime ) { m_useTime = pUseTime; }
	
	inline int GetTimeSinceUse() const { return m_timeSinceUse; }
	inline void SetTimeSinceUse( int pTimeSinceUse ) { m_timeSinceUse = pTimeSinceUse; }
	
	inline bool IsCoolingDown() const { return m_isCoolingDown; }
	inline void SetIsCoolingDown( bool pIsCoolingDown ) { m_isCoolingDown = pIsCoolingDown; }
	
	inline int GetCurrentCooldown() const { return m_currentCooldown; }
	inline void SetCurrentCooldown( int pCurrentCooldown ) { m_currentCooldown = pCurrentCooldown; }

	inline int GetCooldown() const { return m_cooldown; }
	inline void SetCooldown( int pCooldown ) { m_cooldown = pCooldown; }
	
	inline Vector3<float> GetHandOffset() const { return ( m_hand == HAND_LEFT ) ? m_handLeftOffset : m_handRightOffset; }
	
	inline eHand GetHand() const { return m_hand; }
	
	inline std::string GetItemName() const { return m_item; }
	inline void SetItemName( const std::string &pItem ) { m_item = pItem; }
};

#endif