//
//  fl_fm_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FREE_LOOK_FREE_MOVE_COMPONENT_H__
#define __FREE_LOOK_FREE_MOVE_COMPONENT_H__

#include "free_move_component.h"
#include "free_look_component.h"

class FreeLookFreeMoveComponent : public FreeMoveComponent, public FreeLookComponent {
    
private:
    
public:
    FreeLookFreeMoveComponent();
    virtual ~FreeLookFreeMoveComponent();
    
    virtual void Execute( float p_delta );
};

#endif /* fl_fm_component_h */
