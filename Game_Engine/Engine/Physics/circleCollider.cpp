//
//  circleCollider.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "circleCollider.h"

#include "boxCollider.h"
#include "pointCollider.h"

CircleCollider::CircleCollider( const Vector2<float> &pCenter, float pRadius ) : Collider( ColliderType::COLLIDER_CIRCLE ) {
	m_center = pCenter;
	m_radius = pRadius;
}

IntersectData CircleCollider::IntersectsBox( const BoxCollider &pOther ) const {
	return IntersectData( false );
}

IntersectData CircleCollider::IntersectsCircle( const CircleCollider &pCircle ) const {
	return IntersectData( false );
}

IntersectData CircleCollider::IntersectsPoint( const PointCollider &pPoint ) const {
	return IntersectData( false );
}