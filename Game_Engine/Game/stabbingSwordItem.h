//
//  stabbingSwordItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __STABBING_SWORD_ITEM_H__
#define __STABBING_SWORD_ITEM_H__

#include "handItem.h"

class StabbingSwordItem : public HandItem {
	
private:
	
public:
	StabbingSwordItem( const Vector3<float> &pPosition, eHand pHand );
};

#endif /* stabbingSword_h */
