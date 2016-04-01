//
//  intersectData.h
//  Game_Engine
//
//  Created by Craig Milby on 3/30/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __INTERSECT_DATA_H__
#define __INTERSECT_DATA_H__

#include "math3d.h"

class IntersectData {
	
private:
	const bool m_doesIntersect;
	const Vector3<float> m_direction;
	
public:
	IntersectData( const bool pDoesIntersect, const Vector3<float> &pDirection ) : m_doesIntersect( pDoesIntersect ), m_direction( pDirection ) {}
	
	inline bool DoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return m_direction.Length(); }
	inline const Vector3<float>& GetDirection() const { return m_direction; }
};

#endif /* intersectData_h */
