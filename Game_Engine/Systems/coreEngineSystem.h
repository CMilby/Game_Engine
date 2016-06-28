//
//  coreEngineSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 2/28/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CORE_ENGINE_SYSTEM_H__
#define __CORE_ENGINE_SYSTEM_H__

#include "system.h"

class CoreEngineSystem : public System {
    
private:
    bool m_isRunning;
    
    void HandleCoreEngineStart( const std::vector<MessagePayload>& payload );
    void HandleCoreEngineStop( const std::vector<MessagePayload>& payload );
    
public:
    CoreEngineSystem();
    
    virtual void Init();
    virtual void Update( float pDelta );
};

#endif /* coreEngineSystem_h */
