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
	Vector3<float> myCenter = ( pCollider.GetMaxExtents() + pCollider.GetMinExtents() ) * 0.5f;
	Vector3<float> myExtents = pCollider.GetMaxExtents() - myCenter;

	float myRadius = myExtents.GetX() * fabsf( GetNormal().GetX() ) + myExtents.GetY() * fabsf( GetNormal().GetY() ) + myExtents.GetZ() * fabsf( GetNormal().GetZ() );
	float myS = GetNormal().Dot( myCenter ) - GetDistance();
	return IntersectData( fabsf( myS ) < myRadius, m_normal * myS );
}









