//
//  monster.h
//  Game_Engine
//
//  Created by Craig Milby on 7/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "npc.h"

class Monster : public NPC {
	
private:
	
protected:
	virtual void Update( float pDelta );

public:
	Monster();
	Monster( const Vector2<float> &pPosition );
	virtual ~Monster();
};

#endif /* monster_h */
