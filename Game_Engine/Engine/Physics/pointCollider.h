//
//  pointCollider.h
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __POINT_COLLIDER_H__
#define __POINT_COLLIDER_H__

#include "collider.h"

class BoxCollider;
class CircleCollider;
class LineCollider;

class PointCollider : public Collider {
	
private:
	Vector2<float> m_position;
	
public:
	PointCollider( const Vector2<float> &pPosition );
	
	virtual void Transform( const Vector3<float> &pTraslation );
	virtual Vector3<float> GetCenter() const { return Vector3<float>( m_position, 1.0f ); }
	
	IntersectData IntersectsBox( const BoxCollider &pOther ) const;
	IntersectData IntersectsCircle( const CircleCollider &pCircle ) const;
	IntersectData IntersectsLine( const LineCollider &pLine ) const;
	IntersectData IntersectsPoint( const PointCollider &pPoint ) const;
	
	inline Vector2<float> GetPosition() const { return m_position; }
};

#endif /* pointCollider_h */
