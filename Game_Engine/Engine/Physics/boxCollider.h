//
//  boxCollider.h
//  Game_Engine
//
//  Created by Craig Milby on 7/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __BOX_COLLIDER_H__
#define __BOX_COLLIDER_H__

#include "collider.h"

class CircleCollider;
class PointCollider;

class BoxCollider : public Collider {
	
private:
	Vector2<float> m_minExtents;
	Vector2<float> m_maxExtents;
	
public:
	BoxCollider( const Vector2<float> &pMinExtents, const Vector2<float> &pMaxExtents );
	
	IntersectData IntersectsBox( const BoxCollider &pOther ) const;
	IntersectData IntersectsCircle( const CircleCollider &pCircle ) const;
	IntersectData IntersectsPoint( const PointCollider &pPoint ) const;
	
	inline Vector2<float> GetMinExtents() const { return m_minExtents; }
	inline Vector2<float> GetMaxExtents() const { return m_maxExtents; }
};

#endif /* boxCollider_h */
