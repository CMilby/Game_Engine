//
//  lockedCamera.h
//  Game_Engine
//
//  Created by Craig Milby on 6/5/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __LOCKED_CAMERA_H__
#define __LOCKED_CAMERA_H__

#include "cameraSystem.h"

class LockedCamera : public CameraEntity {
	
private:
	int m_keyForward;
	int m_keyBack;
	int m_keyLeft;
	int m_keyRight;
	int m_keyUp;
	int m_keyDown;
	
protected:
	virtual void Input( float pDelta );
	
public:
	LockedCamera( const Vector3<float> &pPosition, const Quaternion &pRotation );
	virtual ~LockedCamera();
};

#endif /* lockedCamera_h */
