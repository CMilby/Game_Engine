//
//  player.h
//  Game_Engine
//
//  Created by Craig Milby on 6/27/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "npc.h"
// #include "renderableEntity.h"

class Player : public NPC {

private:
	
protected:
	virtual void Input( float pDelta );

public:
	Player();
	Player( const Vector2<float> &pPosition );
};

#endif