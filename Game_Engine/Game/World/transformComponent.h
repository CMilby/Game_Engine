//
//  transformComponent.h
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "component.h"

#include "transform.h"

class TransformComponent : public Component {
	
private:
	Transform m_transform;
	
public:
	TransformComponent();
	TransformComponent( ComponentType pType );
	TransformComponent( const Vector3<float> &pPosition, const Quaternion &pRotation = Quaternion(), const Vector3<float> &pScale = Vector3<float>( 1.0f, 1.0f, 1.0f ) );
	virtual ~TransformComponent();
	
	inline void SetPosition( const Vector3<float> &pPosition ) { m_transform.SetPosition( pPosition ); }
	inline Vector3<float> GetPosition() const { return m_transform.GetPosition(); }
	
	inline void SetRotation( const Quaternion &pRotation ) { m_transform.SetRotation( pRotation ); }
	inline Quaternion GetRotation() const { return m_transform.GetRotation(); }
	
	inline void SetScale( const Vector3<float> &pScale ) { m_transform.SetScale( pScale ); }
	inline Vector3<float> GetScale() const { return m_transform.GetScale(); }
	
	Matrix4<float> GetModelMatrix() const;
};

#endif /* transformComponent_h */
