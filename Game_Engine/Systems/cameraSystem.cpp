//
//  cameraSystem.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/3/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "cameraSystem.h"

CameraSystem::CameraSystem() : System( SYSTEM_CAMERA ) {
	m_cameraRoot = new Entity();
}

CameraSystem::CameraSystem( Camera *camera ) : System( SYSTEM_CAMERA ) {
	m_cameraRoot = new Entity();
	AddCamera( camera );
}

CameraSystem::~CameraSystem() {
	if ( m_cameraRoot ) delete m_cameraRoot;
}

void CameraSystem::Init() {
	System::Init();
}

void CameraSystem::Update() {
	m_cameraRoot->InputAll();
}

void CameraSystem::AddCamera( Camera *camera ) {
	m_cameraRoot->AddChild( camera );
}
