//
//  superChunk.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "superChunk.h"

#include "cameraSystem.h"
#include "renderingSystem.h"
#include "worldGenerator.h"

SuperChunk::SuperChunk() : Entity( EntityType::ENTITY_GAME_OBJECT ) {
	m_texture = new Texture( "Tiles" );
	m_shader = 0;
	
	WorldGenerator *generator = WorldGenerator::GetInstance();
	
	for ( unsigned int x = 0; x < S_CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < S_CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < S_CHUNK_Z; z++ ) {
				m_chunk[ x ][ y ][ z ] = generator->GenerateChunk( x, y, z );
			}
		}
	}
}

SuperChunk::~SuperChunk() {
	for ( unsigned int x = 0; x < S_CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < S_CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < S_CHUNK_Z; z++ ) {
				if ( m_chunk[ x ][ y ][ z ] != 0 ) {
					delete m_chunk[ x ][ y ][ z ];
				}
			}
		}
	}
}

void SuperChunk::Render() {
	if ( m_shader == 0 ) {
		m_shader = ( VoxelShader* ) RenderingSystem::GetShaders()[ ShaderType::SHADER_VOXEL ];
	}
	
	Matrix4<float> model;
	Matrix4<float> view = CameraSystem::GetMainCamera()->GetView();
	Matrix4<float> projection = Transform::GetProjection();
	
	for ( unsigned int x = 0; x < S_CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < S_CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < S_CHUNK_Z; z++ ) {
				if ( !m_chunk[ x ][ y ][ z ] ) {
					continue;
				}
				
				model = Matrix4<float>().InitTranslation( Vector3<float>( x * CHUNK_X, y * CHUNK_Y, z * CHUNK_Z ) );
				
				m_shader->Bind();
				
				m_shader->Enable();
				m_shader->UpdateUniforms( model, view, projection, m_texture );
				m_shader->Disable();
				
				m_chunk[ x ][ y ][ z ]->Render();
			}
		}
	}
}

void SuperChunk::Set( int pX, int pY, int pZ, block_t pType ) {
	int cx = pX / CHUNK_X;
	int cy = pY / CHUNK_Y;
	int cz = pZ / CHUNK_Z;
	
	int mx = pX % CHUNK_X;
	int my = pY % CHUNK_Y;
	int mz = pZ % CHUNK_Z;
	
	if( !m_chunk[ cx ][ cy ][ cz ] ) {
		m_chunk[ cx ][ cy ][ cz ] = new Chunk();
	}
	
	m_chunk[ cx ][ cy ][ cz ]->Set( mx, my, mz, pType );
}

block_t SuperChunk::Get( int pX, int pY, int pZ ) const {
	int cx = pX / CHUNK_X;
	int cy = pY / CHUNK_Y;
	int cz = pZ / CHUNK_Z;
	
	int mx = pX % CHUNK_X;
	int my = pY % CHUNK_Y;
	int mz = pZ % CHUNK_Z;
	
	if( !m_chunk[ cx ][ cy ][ cz ] ) {
		return block_t();
	}
	
	return m_chunk[ cx ][ cy ][ cz ]->Get( mx, my, mz );
}








