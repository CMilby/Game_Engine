//
//  item.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ITEM_H__
#define __ITEM_H__

class Item {
	
private:
	int m_cooldown;
	int m_currentCooldown;
	bool m_isCoolingDown;
	
public:
	Item();
	
	virtual void Update();
	virtual void Use();
};

#endif