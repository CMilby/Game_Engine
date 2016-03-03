//
//  entitySystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __ENTITY_SYSTEM_H__
#define __ENTITY_SYSTEM_H__

#include "system.h"

class EntitySystem : public System {
    
private:
    
    
public:
    EntitySystem();
    virtual ~EntitySystem();
    
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

#endif /* entitySystem_h */
