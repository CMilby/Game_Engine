//
//  lineCollider.h
//  Game_Engine
//
//  Created by Craig Milby on 7/19/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __LINE_COLLIDER_H__
#define __LINE_COLLIDER_H__

#include "collider.h"

class BoxCollider;
class CircleCollider;
class PointCollider;

class LineCollider : public Collider {
	
private:
	Vector2<float> m_point1;
	Vector2<float> m_point2;
	
public:
	LineCollider( const Vector2<float> &pPoint1, const Vector2<float> &pPoint2 );
	virtual ~LineCollider();
	
	virtual void Transform( const Vector3<float> &pTraslation );
	
	IntersectData IntersectsBox( const BoxCollider &pOther ) const;
	IntersectData IntersectsCircle( const CircleCollider &pCircle ) const;
	IntersectData IntersectsLine( const LineCollider &pLine ) const;
	IntersectData IntersectsPoint( const PointCollider &pPoint ) const;
};

#endif /* lineCollider_h */
