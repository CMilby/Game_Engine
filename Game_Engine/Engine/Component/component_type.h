//
//  component_type.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COMPONENT_TYPE_H__
#define __COMPONENT_TYPE_H__

#include <cstdio>

namespace ComponentType {
    
    enum ComponentType {
        RENDER_COMPONENT,
        INPUT_COMPONENT,
        UPDATE_COMPONENT,
        NUM_COMPONENTS
    };
}

#endif /* component_type_h */
