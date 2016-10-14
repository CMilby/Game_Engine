//
//  renderablePlane.h
//  Game_Engine
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDERABLE_PLANE_H__
#define __RENDERABLE_PLANE_H__

#include "entity.h"

class RenderablePlane : public Entity {
	
private:
	// Vector3<float> m_position;
	
public:
	RenderablePlane( float p_xOffset, float p_yOffset, float p_zOffset );
	virtual ~RenderablePlane();

	// inline Vector3<float> GetPosition() const { return m_position; }
};

#endif /* renderablePlane_h */
