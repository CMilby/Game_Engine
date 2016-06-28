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
	static Camera *s_mainCamera;
    
public:
    CameraSystem();
	CameraSystem( Camera *camera );
    virtual ~CameraSystem();
    
    virtual void Init();
	virtual void Input( float pDelta );
    virtual void Update( float pDelta );
	
	void AddCamera( Camera* camera );
	
	static Camera* GetMainCamera() { return s_mainCamera; }
	static void SetMainCamera( Camera *mainCamera ) { s_mainCamera = mainCamera; }
};

#endif /* cameraSystem_h */
