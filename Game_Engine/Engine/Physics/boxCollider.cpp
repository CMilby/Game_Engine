//
//  boxCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "boxCollider.h"

#include "circleCollider.h"
#include "lineCollider.h"
#include "pointCollider.h"

BoxCollider::BoxCollider( const Vector2<float> &pMinExtents, const Vector2<float> &pMaxExtents ) : Collider( ColliderType::COLLIDER_BOX ) {
	m_minExtents = pMinExtents;
	m_maxExtents = pMaxExtents;
}

void BoxCollider::Transform( const Vector3<float> &pTraslation ) {
	
}

IntersectData BoxCollider::IntersectsBox( const BoxCollider &pOther ) const {
	return IntersectData( ( GetMinExtents().GetX() < pOther.GetMaxExtents().GetX() ) &&
						  ( GetMaxExtents().GetX() > pOther.GetMinExtents().GetX() ) &&
						  ( GetMinExtents().GetY() < pOther.GetMaxExtents().GetY() ) &&
						  ( GetMaxExtents().GetY() > pOther.GetMinExtents().GetY() ) );
}

IntersectData BoxCollider::IntersectsCircle( const CircleCollider &pCircle ) const {
	return IntersectData( false );
}

IntersectData BoxCollider::IntersectsLine( const LineCollider &pLine ) const {
	return IntersectData( false );
}

IntersectData BoxCollider::IntersectsPoint( const PointCollider &pPoint ) const {
	bool inX = false;
	bool inY = false;
	if ( pPoint.GetPosition().GetX() >= GetMinExtents().GetX() && pPoint.GetPosition().GetX() <= GetMaxExtents().GetX() ) {
		inX = true;
	}
	
	if ( pPoint.GetPosition().GetY() >= GetMinExtents().GetY() && pPoint.GetPosition().GetY() <= GetMaxExtents().GetY() ) {
		inY = true;
	}
	
	return IntersectData( inX && inY );
}
