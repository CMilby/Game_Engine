//
//  planeCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 4/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "planeCollider.h"

#include "aabbCollider.h"
#include "sphereCollider.h"

PlaneCollider::PlaneCollider( const Vector3<float> &pNormal, float pDistance ) : Collider( ColliderType::COLLIDER_PLANE ) {
	m_normal = pNormal;
	m_distance = pDistance;
}

void PlaneCollider::Transform( const Vector3<float> &traslation ) {
	
}

PlaneCollider PlaneCollider::Normalize() const {
	float myMagnitude = m_normal.Length();
	return PlaneCollider( m_normal / myMagnitude, m_distance / myMagnitude );
}

IntersectData PlaneCollider::IntersectSphereCollider( const SphereCollider &pCollider ) const {
	float myDistanceFromSphereCenter = fabsf( m_normal.Dot( pCollider.GetCenter() ) + m_distance );
	float myDistanceFromSphere = myDistanceFromSphereCenter - pCollider.GetRadius();
	
	return IntersectData( myDistanceFromSphere < 0, m_normal * myDistanceFromSphere );
}

IntersectData PlaneCollider::IntersectAABBCollider( const AABBCollider &pCollider ) const {
	Vector3<float> myMidpoint = ( pCollider.GetMaxExtents() - pCollider.GetMinExtents() ) / 2.0f;
	Vector3<float> myCenter = pCollider.GetMinExtents() + myMidpoint;

	float myRadius = fabsf( GetNormal().GetX() * myMidpoint.GetX() ) + fabsf( GetNormal().GetY() + myMidpoint.GetY() ) + fabsf( GetNormal().GetZ() + myMidpoint.GetZ() );
	return IntersectSphereCollider( SphereCollider( myCenter, myRadius ) );
}









