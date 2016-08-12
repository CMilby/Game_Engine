//
//  transformComponent.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/11/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "transformComponent.h"

#include "entity.h"

TransformComponent::TransformComponent() : Component( ComponentType::TRANSFORM_COMPONENT ) {
	
}

TransformComponent::TransformComponent( ComponentType pType ) : Component( pType ) {
	
}

TransformComponent::TransformComponent( const Vector3<float> &pPosition, const Quaternion &pRotation, const Vector3<float> &pScale ) : Component( ComponentType::TRANSFORM_COMPONENT ) {
	m_transform.SetPosition( pPosition );
	m_transform.SetRotation( pRotation );
	m_transform.SetScale( pScale );
}

TransformComponent::~TransformComponent() {
	
}

Matrix4<float> TransformComponent::GetModelMatrix() const {
	if ( GetParent() != 0 ) {
		// return m_parent->GetModelMatrix() * m_transform.GetModelMatrix();
	}
	return m_transform.GetModelMatrix();
}
