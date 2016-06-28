//
//  transform.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "math3d.h"

class Transform {
	
private:
	static Matrix4<float> s_projection;
	static Matrix4<float> s_ortho;
	
	Vector3<float> m_position;
	Vector3<float> m_scale;
	Quaternion m_rotation;
	
public:
	Transform( const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), const Vector3<float> &scale = Vector3<float>( 1.0f, 1.0f, 1.0f ), const Quaternion &rotation = Quaternion() );
	
	inline Vector3<float> GetPosition() const { return m_position; }
	inline Vector3<float> GetScale() const { return m_scale; }
	inline Quaternion GetRotation() const { return m_rotation; }
	
	inline void SetPosition( const Vector3<float> &position ) { m_position = position; }
	inline void SetScale ( const Vector3<float> &scale ) { m_scale = scale; }
	inline void SetRotation( const Quaternion &rotation ) { m_rotation = rotation; }
	
	Matrix4<float> GetModelMatrix() const;
	
	void Move( const Vector3<float> &direction, float amount );
	void Rotate( const Quaternion &quat );
	void Rotate( const Vector3<float> &axis, float angle );
	
	static void SetPerspectiveProjection( const Matrix4<float> &projection ) { s_projection = projection; }
	static void SetPerspectiveProjection( float fov, float aspectRatio, float zNear, float zFar ) { SetPerspectiveProjection( Matrix4<float>().Perspective( fov, aspectRatio, zNear, zFar ) );
	}
	
	static void SetOrthographicProjection( const Matrix4<float> &pOrtho ) { s_ortho = pOrtho; }
	static void SetOrthographicProjection( const float pLeft, const float pRight, const float pTop, const float pBottom, const float pZNear, const float pZFar ) {
		SetOrthographicProjection( Matrix4<float>().Ortho( pLeft, pRight, pTop, pBottom, pZNear, pZFar ) );
	}
	
	static Matrix4<float> GetProjection() { return s_projection; }
};

#endif /* transform_h */









