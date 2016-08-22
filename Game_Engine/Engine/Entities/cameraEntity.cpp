//
//  camera.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "cameraEntity.h"

#include "drawModeComponent.h"
#include "freeLookComponent.h"
#include "freeMoveComponent.h"

CameraEntity::CameraEntity() : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent() );
	AddComponent( new FreeMoveComponent() );
	AddComponent( new DrawModeComponent() );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition ) : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent() );
	AddComponent( new FreeMoveComponent( pPosition ) );
	AddComponent( new DrawModeComponent() );
	
	SetPosition( pPosition );
}

CameraEntity::CameraEntity( const Vector3<float> &pPosition, const Quaternion &pRotation ) : Entity( EntityType::ENTITY_CAMERA ) {
	AddComponent( new FreeLookComponent( pRotation ) );
	AddComponent( new FreeMoveComponent( pPosition ) );
	AddComponent( new DrawModeComponent() );
	
	SetPosition( pPosition );
	SetRotation( pRotation );
}

CameraEntity::~CameraEntity() {
	
}

void CameraEntity::Update( float pDelta ) {
	SetView( GetRotation().ToRotationMatrix() * Matrix4<float>().Transform( GetPosition() * -1 ) );
}

