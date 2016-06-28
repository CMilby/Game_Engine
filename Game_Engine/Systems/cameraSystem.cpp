//
//  cameraSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "cameraSystem.h"

Camera* CameraSystem::s_mainCamera = 0;

CameraSystem::CameraSystem() : System( SYSTEM_CAMERA ) {
	s_mainCamera = new Camera();
}

CameraSystem::CameraSystem( Camera *camera ) : System( SYSTEM_CAMERA ) {
	s_mainCamera = camera;
}

CameraSystem::~CameraSystem() {
	if ( s_mainCamera ) delete s_mainCamera;
}

void CameraSystem::Init() {
	System::Init();
}

void CameraSystem::Input( float pDelta ) {
	s_mainCamera->InputAll( pDelta );
}

void CameraSystem::Update( float pDelta ) {
	s_mainCamera->UpdateAll( pDelta );
}

void CameraSystem::AddCamera( Camera *camera ) {
	// m_cameraRoot->AddChild( camera );
}
