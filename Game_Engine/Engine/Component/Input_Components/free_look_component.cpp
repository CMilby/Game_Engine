//
//  free_look_component.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "free_look_component.h"

#include "input.h"
#include "entity.h"

FreeLookComponent::FreeLookComponent() {
    m_sensitivity = 2.5f;
}

FreeLookComponent::~FreeLookComponent() {
    
}

void FreeLookComponent::Execute( float p_delta ) {
    if ( Input::IsKeyDown( Key::KEY_UP_ARROW ) ) {
        Rotate( GetParent()->GetRotation().GetLeft(), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Key::KEY_DOWN_ARROW ) ) {
        Rotate( GetParent()->GetRotation().GetRight(), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Key::KEY_LEFT_ARROW ) ) {
        Rotate( Vector3<float>( 0, -1, 0 ), m_sensitivity );
    }
    
    if ( Input::IsKeyDown( Key::KEY_RIGHT_ARROW ) ) {
        Rotate( Vector3<float>( 0, 1, 0 ), m_sensitivity );
    }
}

void FreeLookComponent::Rotate( const Quaternion &p_quat ) {
    GetParent()->GetTransform().Rotate( p_quat );
}

void FreeLookComponent::Rotate( const Vector3<float> &p_axis, float p_angle ) {
    Rotate( Quaternion( p_axis, p_angle ) );
}



