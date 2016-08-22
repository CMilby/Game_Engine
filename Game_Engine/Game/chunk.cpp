//
//  chunk.cpp
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "chunk.h"

Chunk::Chunk() {
	memset( m_chunk, 0, sizeof m_chunk );
	
	m_vao = 0;
	m_vbo = 0;
	
	m_elements = 0;
	m_hasChanged = true;
	
	glGenVertexArrays( 1, &m_vao );
}

Chunk::~Chunk() {
	if ( m_vbo != 0 ) {
		glDeleteBuffers( 1, &m_vbo );
	}
	
	if ( m_vao != 0 ) {
		glDeleteVertexArrays( 1, &m_vao );
	}
}

void Chunk::Render() {
	if ( m_hasChanged ) {
		Update();
	}
	
	glBindVertexArray( m_vao );
	glDrawArrays( GL_TRIANGLES, 0, m_elements );
	glBindVertexArray( 0 );
}

void Chunk::Update() {
	m_hasChanged = false;
	
	Vector4<GLbyte> vertex[ CHUNK_X * CHUNK_Y * CHUNK_Z * 6 * 6 ];
	int i = 0;
	
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
				block_t myBlock = m_chunk[ x ][ y ][ z ];
				
				if ( !myBlock.Initialized() ) {
					continue;
				}
				
				uint8_t myTop = myBlock.GetTop();
				uint8_t myBottom = myBlock.GetBottom();
				uint8_t myLeft = myBlock.GetLeft();
				uint8_t myRight = myBlock.GetRight();
				uint8_t myFront = myBlock.GetFront();
				uint8_t myBack = myBlock.GetBack();
				
				// Negative X ( LEFT )
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z,     myLeft );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myLeft );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myLeft );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myLeft );
				
				// Positive X ( RIGHT )
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myRight );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myRight );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myRight );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myRight );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
				
				// Negative Y ( BOTTOM )
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z,     myBottom );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBottom );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myBottom );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBottom );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myBottom );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myBottom );
				
				// Positive Y ( TOP )
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myTop );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myTop );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myTop );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myTop );
				
				// Negative Z ( Back )
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z,     myBack );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myBack );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBack );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myBack );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myBack );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBack );
				
				// Positive Z ( Front )
				vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myFront );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myFront );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
				vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myFront );
				vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myFront );
			}
		}
	}
	
	m_elements = i;
	
	if ( m_vbo != 0 ) {
		glDeleteBuffers( 1, &m_vbo );
	}
	
	glBindVertexArray( m_vao );
	glGenBuffers( 1, &m_vbo );
	
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBufferData( GL_ARRAY_BUFFER, m_elements * sizeof *vertex, vertex, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_BYTE, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );
	
	glBindVertexArray( 0 );
}















