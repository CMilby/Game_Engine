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
#include "renderableEntity.h"

enum eHand {
	HAND_LEFT,
	HAND_RIGHT
};

class Item : public RenderableEntity {
	
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
	
	virtual void Update( float pDelta );

public:
	Item();
	Item( const std::string &pItem, eHand pHand );
	Item( const Vector3<float> &pPosition, const std::string &pItem );
	Item( const Vector3<float> &pPosition, const std::string &pItem, eHand pHand );
	
	virtual bool Use();
	
	void SetPosition( const Vector3<float> &pPosition, bool pHandOffset = true );
	
	inline int GetUseTime() const { return m_useTime; }
	inline void SetUseTime( int pUseTime ) { m_useTime = pUseTime; }
	
	inline int GetTimeSinceUse() const { return m_timeSinceUse; }
	inline void SetTimeSinceUse( int pTimeSinceUse ) { m_timeSinceUse = pTimeSinceUse; }
	
	inline bool IsCoolingDown() const { return m_isCoolingDown; }
	inline void SetIsCoolingDown( bool pIsCoolingDown ) { m_isCoolingDown = pIsCoolingDown; }
	
	inline int GetCurrentCooldown() const { return m_currentCooldown; }
	inline void SetCurrentCooldown( int pCurrentCooldown ) { m_currentCooldown = pCurrentCooldown; }

	inline int GetCooldown() const { return m_cooldown; }
	
	inline std::string GetItemName() const { return m_item; }
	inline void SetItemName( const std::string &pItem ) { m_item = pItem; }
};

#endif