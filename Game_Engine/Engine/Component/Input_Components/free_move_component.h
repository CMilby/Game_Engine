//
//  free_move_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FREE_MOVE_COMPONENT_H__
#define __FREE_MOVE_COMPONENT_H__

#include "input_component.h"

class FreeMoveComponent : public virtual InputComponent {
    
private:
    float m_speed;
    int m_forwardKey;
    int m_backKey;
    int m_leftKey;
    int m_rightKey;
    
public:
    FreeMoveComponent();
    virtual ~FreeMoveComponent();
    
    virtual void Execute( float p_delta );
    
private:
    void Move( const Vector3f& p_direction, float p_amt );
};

#endif /* free_move_component_h */
