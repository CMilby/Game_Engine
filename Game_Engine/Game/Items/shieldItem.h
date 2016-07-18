//
//  shieldItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SHIELD_ITEM_H__
#define __SHIELD_ITEM_H__

#include "item.h"

class ShieldItem : public Item {
	
private:
	
public:
	ShieldItem( eHand pHand );
	ShieldItem( const std::string &pItem, eHand pHand );
	virtual ~ShieldItem();
};

#endif /* shieldItem_h */
