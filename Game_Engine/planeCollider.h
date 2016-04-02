//
//  planeCollider.h
//  Game_Engine
//
//  Created by Craig Milby on 4/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANE_COLLIDER_H__
#define __PLANE_COLLIDER_H__

#include "collider.h"
#include "math3d.h"

class AABBCollider;
class SphereCollider;

class PlaneCollider : public Collider {

private:
	Vector3<float> m_normal;
	float m_distance;
	
public:
	PlaneCollider( const Vector3<float> &pNormal, float pDistance );
	
	virtual void Transform( const Vector3<float> &traslation );
	
	PlaneCollider Normalize() const;
	
	IntersectData IntersectSphereCollider( const SphereCollider &pCollider ) const;
	IntersectData IntersectAABBCollider( const AABBCollider &pCollider ) const;
	
	inline Vector3<float> GetNormal() const { return m_normal; }
	inline float GetDistance() const { return m_distance; }
};

#endif /* planeCollider_h */
