//
//  input_system.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "system.h"

class InputSystem : public System {
    
private:
    static InputSystem *s_instance;
    
public:
    static InputSystem* GetInstance() {
        if ( s_instance == 0 ) {
            s_instance = new InputSystem();
        }
        return s_instance;
    }
    
    virtual void Init();
    
    virtual void Execute( float p_delta );
    
private:
    InputSystem() : System( ComponentType::INPUT_COMPONENT ) {}
    void operator=( const InputSystem &p_system );
};

#endif /* input_system_h */
