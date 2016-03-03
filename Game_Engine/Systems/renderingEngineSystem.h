//
//  renderingEngineSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERING_ENGINE_SYSTEM_H__
#define __RENDERING_ENGINE_SYSTEM_H__

#include "system.h"

class RenderingEngineSystem : public System {
    
private:
    
public:
    RenderingEngineSystem();
    
    virtual void Init();
    virtual void Render();
};

#endif /* renderingEngineSystem_h */
