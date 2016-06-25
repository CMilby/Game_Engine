
#include "world.h"

#include <map>

#include "cameraSystem.h"

World::World() {
	m_mainCamera = CameraSystem::GetMainCamera();
	m_drawDistance = 10.0f;
}

World::~World() {
	
}

void World::Update() {
	for ( unsigned int i = 0; i < GetChildren().size(); i++ ) {
		RenderableChunk *chunk = ( RenderableChunk* ) GetChildren()[ i ];
		Vector3<float> cameraPos( m_mainCamera->GetPosition().GetX() / CHUNK_X, m_mainCamera->GetPosition().GetY() / CHUNK_Y, 0.0f );
		Vector3<float> chunkPos( chunk->GetPosition().GetX(), chunk->GetPosition().GetY(), chunk->GetPosition().GetZ() );
		
		if ( Math3D::Distance( cameraPos, chunkPos ) > m_drawDistance ) {
			
			for ( unsigned int j = 0; j < m_drawnPoints.size(); j++ ) {
				if ( m_drawnPoints[ j ] == chunk->GetPosition() ) {
					m_drawnPoints.erase( m_drawnPoints.begin() + j );
				}
			}
			
			RemoveChild( i );
		}
	}
	
	for ( int x = -m_drawDistance; x < m_drawDistance; x++ ) {
		for ( int y = -m_drawDistance; y < m_drawDistance; y++ ) {
			
			if ( x * x + y * y < m_drawDistance * m_drawDistance ) {
				
				int xPos = x + ( m_mainCamera->GetPosition().GetX() / CHUNK_X );
				int yPos = y + ( m_mainCamera->GetPosition().GetY() / CHUNK_Y );
				
				if ( std::find( m_drawnPoints.begin(), m_drawnPoints.end(), Vector3<int>( xPos, yPos, 0 ) ) == m_drawnPoints.end() ) {
					// Not found. Need to add this point
					
					RenderableChunk *chunk = new RenderableChunk( xPos, yPos );
					m_drawnPoints.emplace_back( chunk->GetPosition() );
					AddChild( chunk );
				}
			}
		}
	}
}

