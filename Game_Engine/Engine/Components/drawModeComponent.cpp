//
//  drawModeComponent.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/12/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "drawModeComponent.h"

DrawModeComponent::DrawModeComponent() : InputComponent( ComponentType::DRAW_MODE_COMPONENT ) {
	
}

DrawModeComponent::~DrawModeComponent() {
	
}

void DrawModeComponent::Input( float pDelta ) {
	if ( InputSystem::IsKeyDown( Key::KEY_O ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_SHADED );
	}
	
	if ( InputSystem::IsKeyDown( Key::KEY_P ) ) {
		InputSystem::SetDrawMode( DRAW_MODE_WIREFRAME );
	}
}