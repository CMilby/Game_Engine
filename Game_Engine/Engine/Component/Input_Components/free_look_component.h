//
//  free_look_component.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __FREE_LOOK_COMPONENT_H__
#define __FREE_LOOK_COMPONENT_H__

#include "input_component.h"

class FreeLookComponent : public virtual InputComponent {
    
private:
    float m_sensitivity;
    
public:
    FreeLookComponent();
    virtual ~FreeLookComponent();
    
    virtual void Execute( float p_delta );
    
private:
    void Rotate( const Quaternion &p_quat );
    void Rotate( const Vector3<float> &p_axis, float p_angle );
};

#endif /* free_look_component_h */
