//
//  fl_fm_component.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "fl_fm_component.h"

#include <GL/glew.h>

#include "config.h"
#include "input.h"
#include "entity.h"
#include "render_framework.h"

FreeLookFreeMoveComponent::FreeLookFreeMoveComponent() {
    
}

FreeLookFreeMoveComponent::~FreeLookFreeMoveComponent() {
    
}

void FreeLookFreeMoveComponent::Execute( float p_delta ) {
    FreeMoveComponent::Execute( p_delta );
    FreeLookComponent::Execute( p_delta );

    if ( Input::IsButtonDown( MouseButton::MOUSE_BUTTON_LEFT ) ) {
        
    }
    
    if ( Input::IsKeyDown( Key::KEY_P ) ) {
        RenderFramework::SetDrawMode( 2 );
    } else if ( Input::IsKeyDown( Key::KEY_O ) ) {
        RenderFramework::SetDrawMode( 1 );
    }
}
