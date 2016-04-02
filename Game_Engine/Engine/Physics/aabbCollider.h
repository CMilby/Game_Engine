//
//  aabb.h
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __AABB_H__
#define __AABB_H__

#include "collider.h"
#include "math3d.h"

class PlaneCollider;
class SphereCollider;

class AABBCollider : public Collider {
	
private:
	Vector3<float> m_minExtents;
	Vector3<float> m_maxExtents;
	
public:
	AABBCollider( const Vector3<float> &pMinExtents, const Vector3<float> &pMaxExtents );
	
	virtual void Transform( const Vector3<float> &pTraslation );
	virtual Vector3<float> GetCenter() const;
	
	IntersectData IntersectAABBCollider( const AABBCollider &pOther ) const;
	IntersectData IntersectSphereCollider( const SphereCollider &pOther ) const;
	IntersectData IntersectPlaneCollider( const PlaneCollider &pOther ) const;
	
	inline Vector3<float> GetMinExtents() const { return m_minExtents; }
	inline Vector3<float> GetMaxExtents() const { return m_maxExtents; }
};

#endif /* aabb_h */
