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

class Item : public RenderableEntity {
	
private:
	std::string m_item;
	
	int m_cooldown;
	int m_currentCooldown;
	bool m_isCoolingDown;
	
protected:
	virtual void Update( float pDelta );
	
public:
	Item();
	Item( const Vector3<float> &pPosition, const std::string &pItem );
	
	virtual bool Use();

	inline std::string GetItemName() const { return m_item; }
	inline void SetItemName( const std::string &pItem ) { m_item = pItem; }
};

#endif