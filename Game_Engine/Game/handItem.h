//
//  handItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __HAND_ITEM_H__
#define __HAND_ITEM_H__

#include "item.h"

class HandItem : public Item {
	
private:
	
protected:
	Entity *m_forward;
	
	virtual void Update( float pDelta );
	
public:
	HandItem( eHand pHand );
	HandItem( const std::string &pItem, eHand pHand );
	virtual ~HandItem();
	
	virtual bool Use();
};

#endif /* handItem_h */
