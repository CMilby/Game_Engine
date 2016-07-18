//
//  swingingSword.h
//  Game_Engine
//
//  Created by Craig Milby on 7/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __SWINGING_SWORD_H__
#define __SWINGING_SWORD_H__

#include "item.h"

class SwingingSword : public Item {
	
private:
	float m_swingAngle;
	
	virtual void Update( float pDelta );
	
public:
	SwingingSword( eHand pHand );
	SwingingSword( const std::string &pItem, eHand pHand );
	virtual ~SwingingSword();
	
	inline void SetSwingAngle( float pSwingAngle ) { m_swingAngle = pSwingAngle; }
	inline float GetSwingAngle() const { return m_swingAngle; }
	
	virtual bool Use();
};

#endif /* swingingSword_h */
