//
//  world.h
//  Game_Engine
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __WORLD_H__
#define __WORLD_H__

#include "cameraEntity.h"
#include "entity.h"

class World : public Entity {
	
private:
	CameraEntity *m_mainCamera;
	Vector3<float> m_lastPosition;
	
	int m_drawDistance;
	
	std::vector<Vector3<float>> m_drawnPoints;

protected:
	virtual void Update( float pDelta );
	
public:
	World();
	virtual ~World();
};

#endif /* world_h */
