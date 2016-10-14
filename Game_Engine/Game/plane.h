//
//  plane.h
//  Game_Engine
//
//  Created by Craig Milby on 10/5/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __PLANE_H__
#define __PLANE_H__

#include "mesh.h"

class Plane : public Mesh {
	
private:
	
public:
	Plane( float p_xOffset, float p_yOffset, float p_zOffset );
	virtual ~Plane();
};

#endif /* plane_h */
