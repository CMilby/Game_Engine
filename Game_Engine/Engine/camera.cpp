//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "camera.h"

#include "inputSystem.h"

Camera::Camera() {
	
}

Camera::Camera( const Vector3<float> &position ) {
	SetPosition( position );
}

Camera::~Camera() {
	
}

void Camera::Input() {
	if ( InputSystem::IsKeyDown( Key::KEY_O ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_SHADED );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_P ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_WIREFRAME );
	}
}













