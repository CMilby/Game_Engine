//
//  shieldItem.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "shieldItem.h"

ShieldItem::ShieldItem( eHand pHand ) : Item( "Shield", pHand ) {
	
}

ShieldItem::ShieldItem( const std::string &pItem, eHand pHand ) : Item( pItem, pHand ) {
	// Used for subclasses
}

ShieldItem::~ShieldItem() {
	
}