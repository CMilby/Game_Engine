//
//  transform.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "transform.h"

Transform::Transform( const Vector3<float> &position, const Vector3<float> &scale, const Quaternion &rotation ) {
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;
}
