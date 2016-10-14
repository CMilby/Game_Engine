//
//  world.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "world.h"

#include <algorithm>

#include "cameraSystem.h"
#include "renderablePlane.h"

World::World() : Entity( EntityType::ENTITY_GAME_OBJECT ) {
	m_mainCamera = CameraSystem::GetMainCamera();
	m_drawDistance = 10.0f;
}

World::~World() {
	
}

void World::Update( float p_delta ) {
	if ( m_mainCamera->GetPosition() == m_lastPosition ) {
		return;
	}
	
	m_lastPosition = m_mainCamera->GetPosition();
	
	for ( unsigned int i = 0; i < GetChildren().size(); i++ ) {
		RenderablePlane *plane = ( RenderablePlane* ) GetChildren()[ i ];
		Vector3<float> cameraPos( m_mainCamera->GetPosition().GetX(), 0.0f, m_mainCamera->GetPosition().GetZ() );
		Vector3<float> chunkPos( plane->GetPosition().GetX(), 0.0f, plane->GetPosition().GetZ() );
		
		if ( Math3D::Distance( cameraPos, chunkPos ) > m_drawDistance ) {
			
			for ( unsigned int j = 0; j < m_drawnPoints.size(); j++ ) {
				if ( m_drawnPoints[ j ] == plane->GetPosition() ) {
					m_drawnPoints.erase( m_drawnPoints.begin() + j );
				}
			}
			
			RemoveChild( i );
		}
	}
	
	for ( int x = -m_drawDistance; x < m_drawDistance; x++ ) {
		for ( int y = -m_drawDistance; y < m_drawDistance; y++ ) {
			
			if ( x * x + y * y < m_drawDistance * m_drawDistance ) {
				
				int xPos = x + ( int ) ( m_mainCamera->GetPosition().GetX() );
				int yPos = 0;
				int zPos = y + ( int ) ( m_mainCamera->GetPosition().GetZ() );
				
				if ( std::find( m_drawnPoints.begin(), m_drawnPoints.end(), Vector3<float>( xPos, yPos, zPos ) ) == m_drawnPoints.end() ) {
					RenderablePlane *plane = new RenderablePlane( xPos, yPos, zPos );
					m_drawnPoints.emplace_back( Vector3<float>( xPos, yPos, zPos ) );
					AddChild( plane );
				}
			}
		}
	}
}
