
#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>

#include "cameraSystem.h"
#include "entity.h"

class World : public Entity {

private:
	Camera *m_mainCamera;
	int m_drawDistance;
	
	std::vector<Vector3<int>> m_drawnPoints;
	
protected:
	virtual void Init();
	virtual void Update( float pDelta );
	
public:
	World();
	virtual ~World();
};

#endif