//
//  free_move_component.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "free_move_component.h"

#include "config.h"
#include "entity.h"
#include "input.h"

FreeMoveComponent::FreeMoveComponent() {
    m_speed = 2.5f;
    m_forwardKey = Key::KEY_W;
    m_backKey = Key::KEY_S;
    m_leftKey = Key::KEY_A;
    m_rightKey = Key::KEY_D;
}

FreeMoveComponent::~FreeMoveComponent() {
    
}

void FreeMoveComponent::Execute( float p_delta ) {
    float movAmt = m_speed * p_delta;

    if ( Input::IsKeyDown( Key::KEY_TAB ) ) {
        movAmt *= 2;
    }
    
    if ( Input::IsKeyDown( m_forwardKey ) ) {
        Move( GetParent()->GetRotation().GetForward(), movAmt );
    }
    
    if ( Input::IsKeyDown( m_backKey ) ) {
        Move( GetParent()->GetRotation().GetBack(), movAmt );
    }
    
    if ( Input::IsKeyDown( m_leftKey ) ) {
        Move( GetParent()->GetRotation().GetLeft(), movAmt );
    }
    
    if ( Input::IsKeyDown( m_rightKey ) ) {
        Move( GetParent()->GetRotation().GetRight(), movAmt );
    }
    
    if ( Input::IsKeyDown( Key::KEY_SPACE ) ) {
        Move( GetParent()->GetRotation().GetUp(), movAmt );
    }
    
    if ( Input::IsKeyDown( Key::KEY_LEFT_ALT ) ) {
        Move( GetParent()->GetRotation().GetDown(), movAmt );
    }
}

void FreeMoveComponent::Move( const Vector3f &p_direction, float p_amt ) {
    GetParent()->GetTransform().Move( p_direction, p_amt );
}


