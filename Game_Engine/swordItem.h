//
//  swordItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/13/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SWORD_ITEM_H__
#define __SWORD_ITEM_H__

#include "item.h"

class SwordItem : public Item {

private:
	
public:
	SwordItem( const Vector3<float> &pPosition, eHand pHand );
};

#endif /* swordItem_h */
