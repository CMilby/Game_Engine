//
//  circleCollider.h
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CIRCLE_COLLIDER_H__
#define __CIRCLE_COLLIDER_H__

#include "collider.h"

class BoxCollider;
class LineCollider;
class PointCollider;

class CircleCollider : public Collider {
	
private:
	Vector2<float> m_center;
	float m_radius;
	
public:
	CircleCollider( const Vector2<float> &pCenter, float pRadius );
	
	virtual void Transform( const Vector3<float> &pTraslation );
	
	IntersectData IntersectsBox( const BoxCollider &pOther ) const;
	IntersectData IntersectsCircle( const CircleCollider &pCircle ) const;
	IntersectData IntersectsLine( const LineCollider &pLine ) const;
	IntersectData IntersectsPoint( const PointCollider &pPoint ) const;
	
	virtual Vector3<float> GetCenter() const { return Vector3<float>( m_center, 1.0f ); }
	inline float GetRadius() const { return m_radius; }
};

#endif /* circleCollider_h */
