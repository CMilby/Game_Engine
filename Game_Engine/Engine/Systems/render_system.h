//
//  render_system.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "system.h"

class RenderSystem : public System {
    
private:
    static RenderSystem *s_instance;
    
public:
    static RenderSystem* GetInstance() {
        if ( s_instance == 0 ) {
            s_instance = new RenderSystem();
        }
        return s_instance;
    }
    
    virtual void Init();
    
    virtual void Execute( Entity *p_entity );
    
private:
    RenderSystem() : System( ComponentType::RENDER_COMPONENT ) {}
    void operator=( const RenderSystem &p_system );
};

#endif /* render_system_h */
