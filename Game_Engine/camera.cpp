//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "camera.h"

#include "renderingEngine.h"

void Camera::Init() {
    
}

void Camera::Input( float delta ) {
    if ( Input::IsKeyDown( Input::KEY_O ) ) {
        Input::SetDrawMode( 0 );
    }
    
    if ( Input::IsKeyDown( Input::KEY_P ) ) {
        Input::SetDrawMode( 1 );
    }
}














