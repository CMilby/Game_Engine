//
//  boundingSphere.hpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __BOUNDING_SPHERE_H__
#define __BOUNDING_SPHERE_H__

#include "collider.h"
#include "math3d.h"

class AABBCollider;
class PlaneCollider;

class SphereCollider : public Collider {
	
private:
	Vector3<float> m_center;
	float m_radius;
	
public:
	SphereCollider( const Vector3<float> &pCenter, float pRadius );
	
	virtual void Transform( const Vector3<float> &traslation );
	virtual Vector3<float> GetCenter() const { return m_center; }
	
	IntersectData IntersectSphereCollider( const SphereCollider &pOther ) const;
	IntersectData IntersectAABBCollider( const AABBCollider &pOther ) const;
	IntersectData IntersectPlaneCollider( const PlaneCollider &pOther ) const;
	
	inline float GetRadius() const { return m_radius; }
};

#endif /* boundingSphere_hpp */
