//
//  collider.hpp
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "intersectData.h"
#include "math3d.h"

namespace ColliderType {
	
	enum {
		COLLIDER_SPHERE,
		COLLIDER_AABB,
		COLLIDER_PLANE,
		NUM_COLLIDERS
	};
}

class Collider {
	
private:
	int m_type;
	
public:
	Collider( int pType );
	
	IntersectData Intersect( const Collider &pCollider ) const;

	virtual void Transform( const Vector3<float> &pTraslation ) {}
	virtual Vector3<float> GetCenter() const { return Vector3<float>( 0.0f, 0.0f, 0.0f ); }
	
	inline int GetType() const { return m_type; }
};

#endif /* collider_hpp */
