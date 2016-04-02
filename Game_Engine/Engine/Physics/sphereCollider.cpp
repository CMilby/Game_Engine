//
//  boundingSphere.cpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "sphereCollider.h"

#include "aabbCollider.h"
#include "planeCollider.h"

SphereCollider::SphereCollider( const Vector3<float> &pCenter, float pRadius ) : Collider( ColliderType::COLLIDER_SPHERE ) {
	m_center = pCenter;
	m_radius = pRadius;
}

void SphereCollider::Transform( const Vector3<float> &pTranslation ) {
	m_center += pTranslation;
}

IntersectData SphereCollider::IntersectSphereCollider( const SphereCollider &pOther ) const {
	float myRadiusDistance = m_radius + pOther.GetRadius();
	Vector3<float> myDirection = pOther.GetCenter() - m_center;
	float myCenterDistance = myDirection.Length();
	myDirection /= myCenterDistance;
	
	float myDistance = myCenterDistance - myRadiusDistance;
	return IntersectData( myDistance < 0, myDirection * myDistance );
}

IntersectData SphereCollider::IntersectAABBCollider( const AABBCollider &pOther ) const {
	float myXMin = 0.0f;
	float myYMin = 0.0f;
	float myZMin = 0.0f;
	
	if ( GetCenter().GetX() < pOther.GetMinExtents().GetX() ) {
		myXMin += powf( GetCenter().GetX() - pOther.GetMinExtents().GetX(), 2.0f );
	} else if ( GetCenter().GetX() > pOther.GetMaxExtents().GetX() ) {
		myXMin += powf( GetCenter().GetX() - pOther.GetMaxExtents().GetX(), 2.0f );
	}
	
	if ( GetCenter().GetY() < pOther.GetMinExtents().GetY() ) {
		myYMin += powf( GetCenter().GetY() - pOther.GetMinExtents().GetY(), 2.0f );
	} else if ( GetCenter().GetY() > pOther.GetMaxExtents().GetY() ) {
		myYMin += powf( GetCenter().GetY() - pOther.GetMaxExtents().GetY(), 2.0f );
	}
	
	if ( GetCenter().GetZ() < pOther.GetMinExtents().GetZ() ) {
		myZMin += powf( GetCenter().GetZ() - pOther.GetMinExtents().GetZ(), 2.0f );
	} else if ( GetCenter().GetZ() > pOther.GetMaxExtents().GetZ() ) {
		myZMin += powf( GetCenter().GetZ() - pOther.GetMaxExtents().GetZ(), 2.0f );
	}
	
	return IntersectData( ( myXMin + myYMin + myZMin ) < powf( GetRadius(), 2.0f ), Vector3<float>( myXMin, myYMin, myZMin) );
}

IntersectData SphereCollider::IntersectPlaneCollider( const PlaneCollider &pOther ) const {
	float myDistanceFromSphereCenter = fabsf( pOther.GetNormal().Dot( GetCenter() ) + pOther.GetDistance() );
	float myDistanceFromSphere = myDistanceFromSphereCenter - GetRadius();
	
	return IntersectData( myDistanceFromSphere < 0, pOther.GetNormal() * myDistanceFromSphere );
}



