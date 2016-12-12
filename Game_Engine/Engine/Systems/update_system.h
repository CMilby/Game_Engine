//
//  update_system.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __UPDATE_SYSTEM_H__
#define __UPDATE_SYSTEM_H__

#include "system.h"

class UpdateSystem : public System {
    
private:
    static UpdateSystem* s_instance;
    
public:
    static UpdateSystem* GetInstance() {
        if ( s_instance == 0 ) {
            s_instance = new UpdateSystem();
        }
        
        return s_instance;
    }
    
    virtual void Init();
    
private:
    UpdateSystem() : System( ComponentType::UPDATE_COMPONENT ) {}
    void operator=( const UpdateSystem &p_system );
};

#endif /* update_system_h */
