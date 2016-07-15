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
	
public:
	HandItem( const Vector3<float> &pPosition, eHand pHand );
};

#endif /* handItem_h */
