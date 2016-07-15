//
//  item.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ITEM_H__
#define __ITEM_H__

#include "renderableEntity.h"

enum eHand {
	HAND_LEFT,
	HAND_RIGHT
};

class Item : public RenderableEntity {
	
private:
	std::string m_item;
	eHand m_hand;
	
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
	
	void SetPosition( const Vector3<float> &pPosition );

	inline std::string GetItemName() const { return m_item; }
	inline void SetItemName( const std::string &pItem ) { m_item = pItem; }
};

#endif