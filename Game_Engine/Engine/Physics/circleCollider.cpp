//
//  circleCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "circleCollider.h"

#include "boxCollider.h"
#include "lineCollider.h"
#include "pointCollider.h"

CircleCollider::CircleCollider( const Vector2<float> &pCenter, float pRadius ) : Collider( ColliderType::COLLIDER_CIRCLE ) {
	m_center = pCenter;
	m_radius = pRadius;
}

void CircleCollider::Transform( const Vector3<float> &pTraslation ) {
	m_center += pTraslation.GetXY();
}

IntersectData CircleCollider::IntersectsBox( const BoxCollider &pOther ) const {
	return IntersectData( false );
}

IntersectData CircleCollider::IntersectsCircle( const CircleCollider &pCircle ) const {
	return IntersectData( sqrtf( powf( pCircle.GetCenter().GetX() - GetCenter().GetX(), 2.0f ) + powf( pCircle.GetCenter().GetY() - GetCenter().GetY(), 2.0f ) ) < ( pCircle.GetRadius() + GetRadius() ) );
}

IntersectData CircleCollider::IntersectsLine( const LineCollider &pLine ) const {
	return IntersectData( false );
}

IntersectData CircleCollider::IntersectsPoint( const PointCollider &pPoint ) const {
	return IntersectData( powf( pPoint.GetPosition().GetX() - GetCenter().GetX(), 2.0f ) + powf( pPoint.GetPosition().GetY() - GetCenter().GetY(), 2.0f ) < powf( GetRadius(), 2.0f ) );
}