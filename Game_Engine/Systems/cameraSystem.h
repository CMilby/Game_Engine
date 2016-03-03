//
//  cameraSystem.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CAMERA_SYSTEM_H__
#define __CAMERA_SYSTEM_H__

#include <vector>

#include "camera.h"
#include "system.h"

class CameraSystem : public System {
    
private:
	Entity *m_cameraRoot;
    
public:
    CameraSystem();
	CameraSystem( Camera *camera );
    virtual ~CameraSystem();
    
    virtual void Init();
    virtual void Update();
	
	void AddCamera( Camera* camera );
};

#endif /* cameraSystem_h */
