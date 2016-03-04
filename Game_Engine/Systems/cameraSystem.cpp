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
	// m_cameraRoot = new Entity();
	s_mainCamera = new Camera();
}

CameraSystem::CameraSystem( Camera *camera ) : System( SYSTEM_CAMERA ) {
	// m_cameraRoot = new Entity();
	// AddCamera( camera );
	s_mainCamera = camera;
}

CameraSystem::~CameraSystem() {
	// if ( m_cameraRoot ) delete m_cameraRoot;
	if ( s_mainCamera ) delete s_mainCamera;
}

void CameraSystem::Init() {
	System::Init();
}

void CameraSystem::Input() {
	s_mainCamera->InputAll();
}

void CameraSystem::Update() {
	// m_cameraRoot->InputAll();
	s_mainCamera->UpdateAll();
}

void CameraSystem::AddCamera( Camera *camera ) {
	// m_cameraRoot->AddChild( camera );
}
