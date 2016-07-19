//
//  pointCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "pointCollider.h"

#include "boxCollider.h"
#include "circleCollider.h"

PointCollider::PointCollider( const Vector2<float> &pPosition ) : Collider( ColliderType::COLLIDER_POINT ) {
	m_position = pPosition;
}

IntersectData PointCollider::IntersectsBox( const BoxCollider &pOther ) const {
	bool inX = false;
	bool inY = false;
	if ( m_position.GetX() >= pOther.GetMinExtents().GetX() && m_position.GetX() <= pOther.GetMaxExtents().GetX() ) {
		inX = true;
	}
	
	if ( m_position.GetY() >= pOther.GetMinExtents().GetY() && m_position.GetY() <= pOther.GetMaxExtents().GetY() ) {
		inY = true;
	}
	
	return IntersectData( inX && inY );
}

IntersectData PointCollider::IntersectsCircle( const CircleCollider &pCircle ) const {
	return IntersectData( powf( m_position.GetX() - pCircle.GetCenter().GetX(), 2.0f ) + powf( m_position.GetY() - pCircle.GetCenter().GetY(), 2.0f ) < powf( pCircle.GetRadius(), 2.0f ) );
}

IntersectData PointCollider::IntersectsPoint( const PointCollider &pPoint ) const {
	return IntersectData( m_position == pPoint.GetPosition() );
}