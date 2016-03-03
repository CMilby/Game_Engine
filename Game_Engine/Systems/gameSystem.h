//
//  gameSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include "system.h"

class GameSystem : public System {
    
private:
    
public:
    GameSystem();
    
    virtual void Init();
    virtual void Update();
};

#endif /* gameSystem_h */
