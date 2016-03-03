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
    
protected:
    virtual void HandleUpdate( const std::vector<MessagePayload> &payload );
    
public:
    RenderingEngineSystem();
    
    virtual void Init();
    virtual void Update();
    virtual void Render();
};

#endif /* renderingEngineSystem_h */
