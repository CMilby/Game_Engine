//
//  axeItem.h
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __AXE_ITEM_H__
#define __AXE_ITEM_H__

#include "swingingSword.h"

class AxeItem : public SwingingSword {
	
private:
	
public:
	AxeItem( eHand pHand );
	AxeItem( const std::string &pItem, eHand pHand );
	virtual ~AxeItem();
};

#endif /* axeItem_h */
