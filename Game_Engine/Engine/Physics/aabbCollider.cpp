//
//  aabb.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "aabbCollider.h"

#include "planeCollider.h"
#include "sphereCollider.h"

AABBCollider::AABBCollider( const Vector3<float> &pMinExtents, const Vector3<float> &pMaxExtents ) : Collider( ColliderType::COLLIDER_AABB ) {
	m_minExtents = pMinExtents;
	m_maxExtents = pMaxExtents;
}

void AABBCollider::Transform( const Vector3<float> &pTraslation ) {
	m_minExtents += pTraslation;
	m_maxExtents += pTraslation;
}

Vector3<float> AABBCollider::GetCenter() const {
	return m_minExtents.Midpoint( m_maxExtents );
}

IntersectData AABBCollider::IntersectAABBCollider( const AABBCollider &pOther ) const {
	Vector3<float> myDistance1 = pOther.GetMinExtents() - m_maxExtents;
	Vector3<float> myDistance2 = m_minExtents - pOther.GetMaxExtents();
	
	Vector3<float> myDistances = Vector3<float>( myDistance1.Max( myDistance2 ) );
	float myMaxDistacnce = myDistances.Max();
	
	return IntersectData( myMaxDistacnce < 0, myDistances );
}

IntersectData AABBCollider::IntersectSphereCollider( const SphereCollider &pOther ) const {
	float myXMin = 0.0f;
	float myYMin = 0.0f;
	float myZMin = 0.0f;
	
	if ( pOther.GetCenter().GetX() < GetMinExtents().GetX() ) {
		myXMin += powf( pOther.GetCenter().GetX() - GetMinExtents().GetX(), 2.0f );
	} else if ( pOther.GetCenter().GetX() > GetMaxExtents().GetX() ) {
		myXMin += powf( pOther.GetCenter().GetX() - GetMaxExtents().GetX(), 2.0f );
	}
	
	if ( pOther.GetCenter().GetY() < GetMinExtents().GetY() ) {
		myYMin += powf( pOther.GetCenter().GetY() - GetMinExtents().GetY(), 2.0f );
	} else if ( pOther.GetCenter().GetY() > GetMaxExtents().GetY() ) {
		myYMin += powf( pOther.GetCenter().GetY() - GetMaxExtents().GetY(), 2.0f );
	}
	
	if ( pOther.GetCenter().GetZ() < GetMinExtents().GetZ() ) {
		myZMin += powf( pOther.GetCenter().GetZ() - GetMinExtents().GetZ(), 2.0f );
	} else if ( pOther.GetCenter().GetZ() > GetMaxExtents().GetZ() ) {
		myZMin += powf( pOther.GetCenter().GetZ() - GetMaxExtents().GetZ(), 2.0f );
	}
	
	return IntersectData( ( myXMin + myYMin + myZMin ) < powf( pOther.GetRadius(), 2.0f ), Vector3<float>( myXMin, myYMin, myZMin) );
}

IntersectData AABBCollider::IntersectPlaneCollider( const PlaneCollider &pOther ) const {
	Vector3<float> myCenter = ( GetMaxExtents() + GetMinExtents() ) * 0.5f;
	Vector3<float> myExtents = GetMaxExtents() - myCenter;
	
	float myRadius = myExtents.GetX() * fabsf( pOther.GetNormal().GetX() ) + myExtents.GetY() * fabsf( pOther.GetNormal().GetY() ) + myExtents.GetZ() * fabsf( pOther.GetNormal().GetZ() );
	float myS = pOther.GetNormal().Dot( myCenter ) - pOther.GetDistance();
	return IntersectData( fabsf( myS ) < myRadius, Vector3<float>( myS, myS, myS ) );
}






