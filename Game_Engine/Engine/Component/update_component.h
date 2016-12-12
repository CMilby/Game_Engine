//
//  update_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __UPDATE_COMPONENT_H__
#define __UPDATE_COMPONENT_H__

#include "component.h"

class UpdateComponent : public Component {
    
private:
    
public:
    UpdateComponent();
    virtual ~UpdateComponent();
    
    virtual void Execute();
    virtual void Execute( float p_delta );
    virtual void Execute( Entity *p_entity );
};

#endif /* update_component_h */
