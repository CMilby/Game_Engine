//
//  transform.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "math3d.h"

class Transform {
    
private:
    Vector3<float> m_position;
    Vector3<float> m_scale;
    
public:
    Transform( Vector3<float> position = Vector3<float>( 0.0f, 0.0f, 0.0f ), Vector3<float> scale = Vector3<float>( 1.0f, 1.0f, 1.0f ) ) {
        m_position = position;
        m_scale = scale;
    }
    
    inline void SetPosition( const Vector3<float> &position ) { m_position = position; }
    inline void SetScale( const Vector3<float> &scale ) { m_scale = scale; }
    
    inline Vector3<float> GetPosition() const { return m_position; }
    inline Vector3<float> GetScale() const { return m_scale; }
};

#endif /* transform_h */
