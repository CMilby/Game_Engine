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

class Camera : public Entity {
    
private:
	Matrix4<float> m_view;
	
protected:
	virtual void Input();
	
public:
	Camera();
	Camera( const Vector3<float> &position );
	virtual ~Camera();

	inline void SetPosition( const Vector3<float> &position ) { Entity::SetPosition( position ); }
	inline Vector3<float> GetPosition() const { return Entity::GetPosition(); }
	
	inline Matrix4<float> GetView() const { return m_view; }
	inline void SetView( const Matrix4<float> &view ) { m_view = view; }
};

#endif /* camera_h */
