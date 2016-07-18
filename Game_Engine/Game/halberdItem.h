//
//  halberdItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __HALBERD_ITEM_H__
#define __HALBERD_ITEM_H__

#include "stabbingSwordItem.h"

class HalberdItem : public StabbingSwordItem {
	
private:
	
public:
	HalberdItem( eHand pHand );
	HalberdItem( const std::string &pItem, eHand pHand );
	virtual ~HalberdItem();
};

#endif /* halberdItem_h */
