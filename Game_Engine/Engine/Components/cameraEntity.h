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

class CameraEntity : public Entity {
	
private:
	Matrix4<float> m_view;

public:
	CameraEntity();
	CameraEntity( const Vector3<float> &pPosition );
	CameraEntity( const Vector3<float> &pPosition, const Quaternion &pRotation );
	virtual ~CameraEntity();
	
	virtual void Update( float pDelta );
	
	inline Matrix4<float> GetView() const { return m_view; }
	inline void SetView( const Matrix4<float> &view ) { m_view = view; }
};

/*#include "entity.h"
#include "transform.h"

class CameraEntity : public Entity {
    
private:
	Matrix4<float> m_view;
	Transform m_transform;
	
protected:
	virtual void Input( float pDelta );
	
public:
	CameraEntity();
	CameraEntity( const Vector3<float> &position );
	CameraEntity( const Vector3<float> &pPosition, const Quaternion &pRotation );
	virtual ~CameraEntity();

	inline void SetPosition( const Vector3<float> &position ) { m_transform.SetPosition( position ); }
	inline Vector3<float> GetPosition() const { return m_transform.GetPosition(); }
	
	inline void SetRotation( const Quaternion &pRotation ) { m_transform.SetRotation( pRotation ); }
	inline Quaternion GetRotation() const { return m_transform.GetRotation(); }
	
	inline Matrix4<float> GetView() const { return m_view; }
	inline void SetView( const Matrix4<float> &view ) { m_view = view; }
};*/

#endif /* camera_h */
