//
//  gameSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include "entity.h"
#include "system.h"

class GameSystem : public System {
    
private:
	void HandleLoadGame( const std::vector<MessagePayload> &payload );
	
protected:
	void AddToScene( Entity *entity );
	
public:
    GameSystem();
    
    virtual void Init();
	virtual void Input( float pDelta );
    virtual void Update( float pDelta );
	
	virtual void LoadGame() {}
};

#endif /* gameSystem_h */
