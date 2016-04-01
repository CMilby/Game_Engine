//
//  collider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "collider.h"

#include "aabbCollider.h"
#include "sphereCollider.h"

Collider::Collider( int pType ) {
	m_type = pType;
}

IntersectData Collider::Intersect( const Collider &pCollider ) const {
	if ( m_type == ColliderType::COLLIDER_SPHERE && pCollider.GetType() == ColliderType::COLLIDER_SPHERE ) {
		SphereCollider *self = ( SphereCollider* ) this;
		return self->IntersectSphereCollider( ( SphereCollider& ) pCollider );
	}
	
	if ( m_type == ColliderType::COLLIDER_SPHERE && pCollider.GetType() == ColliderType::COLLIDER_AABB ) {
		SphereCollider *self = ( SphereCollider* ) this;
		return self->IntersectAABBCollider( ( AABBCollider& ) pCollider );
	}
	
	if ( m_type == ColliderType::COLLIDER_AABB && pCollider.GetType() == ColliderType::COLLIDER_AABB ) {
		AABBCollider *self = ( AABBCollider* ) this;
		return self->IntersectAABBCollider( ( AABBCollider& ) pCollider );
	}
	
	if ( m_type == ColliderType::COLLIDER_AABB && pCollider.GetType() == ColliderType::COLLIDER_SPHERE ) {
		AABBCollider *self = ( AABBCollider* ) this;
		return self->IntersectSphereCollider( ( SphereCollider& ) pCollider );
	}
	
	fprintf( stderr, "Collision type not implemented" );
	return IntersectData( false, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
}