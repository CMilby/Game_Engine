//
//  collider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "collider.h"

#include "aabbCollider.h"
#include "boxCollider.h"
#include "circleCollider.h"
#include "planeCollider.h"
#include "pointCollider.h"
#include "sphereCollider.h"

#include "logger.h"

Collider::Collider( int pType ) {
	m_type = pType;
}

IntersectData Collider::Intersect( const Collider &pCollider ) const {
	if ( m_type == ColliderType::COLLIDER_BOX ) {
		BoxCollider *self = ( BoxCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_BOX ) {
			return self->IntersectsBox( ( BoxCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_CIRCLE ) {
			return self->IntersectsCircle( ( CircleCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_POINT ) {
			return self->IntersectsPoint( ( PointCollider& ) pCollider );
		}
	}
	
	if ( m_type == ColliderType::COLLIDER_CIRCLE ) {
		CircleCollider *self = ( CircleCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_BOX ) {
			return self->IntersectsBox( ( BoxCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_CIRCLE ) {
			return self->IntersectsCircle( ( CircleCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_POINT ) {
			return self->IntersectsPoint( ( PointCollider& ) pCollider );
		}
	}
	
	if ( m_type == ColliderType::COLLIDER_POINT ) {
		PointCollider *self = ( PointCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_BOX ) {
			return self->IntersectsBox( ( BoxCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_CIRCLE ) {
			return self->IntersectsCircle( ( CircleCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_POINT ) {
			return self->IntersectsPoint( ( PointCollider& ) pCollider );
		}
	}
	
	
	if ( m_type == ColliderType::COLLIDER_SPHERE ) {
		SphereCollider *self = ( SphereCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_SPHERE ) {
			return self->IntersectSphereCollider( ( SphereCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_AABB ) {
			return self->IntersectAABBCollider( ( AABBCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_PLANE ) {
			return self->IntersectPlaneCollider( ( PlaneCollider& ) pCollider );
		}
	}
	
	if ( m_type == ColliderType::COLLIDER_AABB ) {
		AABBCollider *self = ( AABBCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_AABB ) {
			return self->IntersectAABBCollider( ( AABBCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_SPHERE ) {
			return self->IntersectSphereCollider( ( SphereCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_PLANE ) {
			return self->IntersectPlaneCollider( ( PlaneCollider& ) pCollider );
		}
	}
	
	if ( m_type == ColliderType::COLLIDER_PLANE ) {
		PlaneCollider *self = ( PlaneCollider* ) this;
		if ( pCollider.GetType() == ColliderType::COLLIDER_AABB ) {
			return self->IntersectAABBCollider( ( AABBCollider& ) pCollider );
		}
		
		if ( pCollider.GetType() == ColliderType::COLLIDER_SPHERE ) {
			return self->IntersectSphereCollider( ( SphereCollider& ) pCollider );
		}
	}
	
	Logger::LogError( "Collider - Intersect", "Collision Type Not Implemented" );
	return IntersectData( false, Vector3<float>( 0.0f, 0.0f, 0.0f ) );
}





