//
//  lineCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/19/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "lineCollider.h"

#include "boxCollider.h"
#include "circleCollider.h"
#include "pointCollider.h"

LineCollider::LineCollider( const Vector2<float> &pPoint1, const Vector2<float> &pPoint2 ) : Collider( ColliderType::COLLIDER_LINE ) {
	m_point1 = pPoint1;
	m_point2 = pPoint2;
}

LineCollider::~LineCollider() {
	
}

void LineCollider::Transform( const Vector3<float> &pTraslation ) {
	
}

IntersectData LineCollider::IntersectsBox( const BoxCollider &pOther ) const {
	return IntersectData( false );
}

IntersectData LineCollider::IntersectsCircle( const CircleCollider &pCircle ) const {
	return IntersectData( false );
}

IntersectData LineCollider::IntersectsLine( const LineCollider &pLine ) const {
	return IntersectData( false );
}

IntersectData LineCollider::IntersectsPoint( const PointCollider &pPoint ) const {
	return IntersectData( false );
}












