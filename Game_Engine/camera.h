//
//  camera.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "entity.h"
#include "math3d.h"
#include "transform.h"

class Camera : public Entity {
    
private:
    Matrix4<float> m_view;
    
    float m_speed;
    float m_sensitivity;
    bool m_mouseLocked;
    
protected:
    virtual void Init();
    virtual void Input( float delta );
    
public:
    Camera( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Quaternion &rotation = Quaternion( 0, 0, 0, 1 ) ) {
        SetPosition( position );
        SetRotation( rotation );
        
        m_view = GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 );
        
        m_speed = 0.3f;
        m_sensitivity = 0.05f;
        
        m_mouseLocked = false;
    }
    
    void Move( const Vector3<float> &direction, float amount );
    
    
    
    inline Matrix4<float> GetView() const { return m_view; };
    
    inline void SetPosition( const Vector3<float> &position ) { GetTransform()->SetPosition( position); }
    inline Vector3<float> GetPosition() const { return GetTransform()->GetPosition(); }
    
    inline void SetRotation( const Quaternion &rotation ) { GetTransform()->SetRotation( rotation ); }
    inline Quaternion GetRotation() const { return GetTransform()->GetRotation(); }
};

#endif /* camera_h */
