//
//  input_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "component.h"

class InputComponent : public Component {
    
private:
    
public:
    InputComponent();
    InputComponent( ComponentType::ComponentType p_type );
    virtual ~InputComponent();
    
    virtual void Execute();
    virtual void Execute( float p_delta );
    virtual void Execute( Entity *p_entity );
};

#endif /* input_component_h */
