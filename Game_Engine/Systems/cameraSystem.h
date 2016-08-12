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

#include "cameraEntity.h"
#include "system.h"

class CameraSystem : public System {
    
private:
	static CameraEntity *s_mainCamera;
    
public:
    CameraSystem();
	CameraSystem( CameraEntity *camera );
    virtual ~CameraSystem();
    
    virtual void Init();
	virtual void Input( float pDelta );
    virtual void Update( float pDelta );
	
	void AddCamera( CameraEntity* pCamera );
	
	static CameraEntity* GetMainCamera() { return s_mainCamera; }
	static void SetMainCamera( CameraEntity *pMainCamera ) { s_mainCamera = pMainCamera; }
};

#endif /* cameraSystem_h */
