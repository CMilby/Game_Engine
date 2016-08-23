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
	
	m_left = m_right = m_above = m_below = m_front = m_back = 0;
	
	m_vao = 0;
	m_buffers[ 0 ] = 0;
	m_buffers[ 1 ] = 0;
	
	m_elements = 0;
	m_hasChanged = true;
	
	glGenVertexArrays( 1, &m_vao );
}

Chunk::~Chunk() {
	if ( m_buffers[ 0 ] != 0 ) {
		glDeleteBuffers( 2, m_buffers );
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
	Vector2<GLfloat> texture[ CHUNK_X * CHUNK_Y * CHUNK_Z * 6 * 6 ];
	
	int i = 0;
	int j = 0;
	
	int merged = 0;
	bool visible = false;
	
	// Negative X ( LEFT )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
				if ( IsBlocked( x, y, z, x - 1, y, z ) ) {
					visible = false;
					continue;
				}
				
				uint8_t myLeft = m_chunk[ x ][ y ][ z ].GetLeft();
				
				if( visible && z != 0 && m_chunk[ x ][ y ][ z ].GetLeft() == m_chunk[ x ][ y ][ z - 1 ].GetLeft() ) {
					vertex[ i - 5 ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
					vertex[ i - 2 ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
					vertex[ i - 1 ] = Vector4<GLbyte>( x,     y + 1, z + 1, myLeft );
					
					texture[ j - 5 ] = Vector2<GLfloat>( merged + 2, 1 );
					texture[ j - 2 ] = Vector2<GLfloat>( merged + 2, 1 );
					texture[ j - 1 ] = Vector2<GLfloat>( merged + 2, 0 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z,     myLeft );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myLeft );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myLeft );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myLeft );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myLeft );
					
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	// Positive X ( RIGHT )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
				if ( IsBlocked( x, y, z, x + 1, y, z ) ) {
					visible = false;
					continue;
				}
				
				uint8_t myRight = m_chunk[ x ][ y ][ z ].GetRight();
				
				if( visible && z != 0 && m_chunk[ x ][ y ][ z ].GetRight() == m_chunk[ x ][ y ][ z - 1 ].GetRight() ) {
					vertex[ i - 4 ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
					vertex[ i - 2 ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myRight );
					vertex[ i - 1 ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
					
					texture[ j - 4 ] = Vector2<GLfloat>( merged + 2, 1 );
					texture[ j - 2 ] = Vector2<GLfloat>( merged + 2, 0 );
					texture[ j - 1 ] = Vector2<GLfloat>( merged + 2, 1 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myRight );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myRight );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myRight );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myRight );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myRight );
					
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	// Negative Y ( BOTTOM )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
				if ( IsBlocked( x, y, z, x, y - 1, z ) ) {
					visible = false;
					continue;
				}
				
				uint8_t myBottom = m_chunk[ x ][ y ][ z ].GetBottom();
				
				if ( visible && z != 0 && m_chunk[ x ][ y ][ z ].GetBottom() == m_chunk[ x ][ y ][ z - 1 ].GetBottom() ) {
					vertex[ i - 4 ] = Vector4<GLbyte>( x,     y, z + 1, myBottom );
					vertex[ i - 2 ] = Vector4<GLbyte>( x + 1, y, z + 1, myBottom );
					vertex[ i - 1 ] = Vector4<GLbyte>( x,     y, z + 1, myBottom );
					
					texture[ j - 6 ] = Vector2<GLfloat>( 1, merged + 2 );
					texture[ j - 5 ] = Vector2<GLfloat>( 0, merged + 2 );
					texture[ j - 3 ] = Vector2<GLfloat>( 0, merged + 2 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z,     myBottom );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBottom );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myBottom );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z,     myBottom );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myBottom );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myBottom );
					
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	// Positive Y ( TOP )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
				if ( IsBlocked( x, y, z, x, y + 1, z ) ) {
					visible = false;
					continue;
				}
				
				uint8_t myTop = m_chunk[ x ][ y ][ z ].GetTop();
				
				if ( visible && z != 0 && m_chunk[ x ][ y ][ z ].GetTop() == m_chunk[ x ][ y ][ z - 1 ].GetTop() ) {
					vertex[ i - 5 ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
					vertex[ i - 2 ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
					vertex[ i - 1 ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myTop );
					
					texture[ j - 6 ] = Vector2<GLfloat>( 1, merged + 2 );
					texture[ j - 4 ] = Vector2<GLfloat>( 0, merged + 2 );
					texture[ j - 3 ] = Vector2<GLfloat>( 0, merged + 2 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z,     myTop );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myTop );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z,     myTop );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myTop );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myTop );
					
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	// Negative Z ( BACK )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
			for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
				if ( IsBlocked( x, y, z, x, y, z - 1 ) ) {
					visible = false;
					continue;
				}

				uint8_t myBack = m_chunk[ x ][ y ][ z ].GetBack();
				
				if( visible && y != 0 && m_chunk[ x ][ y ][ z ].GetBack() == m_chunk[ x ][ y - 1 ][ z ].GetBack() ) {
					vertex[ i - 5 ] = Vector4<GLbyte>( x,     y + 1, z, myBack);
					vertex[ i - 3 ] = Vector4<GLbyte>( x,     y + 1, z, myBack);
					vertex[ i - 2 ] = Vector4<GLbyte>( x + 1, y + 1, z, myBack);
					
					texture[ j - 6 ] = Vector2<GLfloat>( 1, merged + 2 );
					texture[ j - 4 ] = Vector2<GLfloat>( 0, merged + 2 );
					texture[ j - 1 ] = Vector2<GLfloat>( 0, merged + 2 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z, myBack );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z, myBack );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z, myBack );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z, myBack );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z, myBack );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z, myBack );
					
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	// Positive Z ( FRONT )
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int z = 0; z < CHUNK_Z; z++ ) {
			for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
				if ( IsBlocked( x, y, z, x, y, z + 1 ) ) {
					visible = false;
					continue;
				}
				
				uint8_t myFront = m_chunk[ x ][ y ][ z ].GetFront();
				
				if( visible && y != 0 && m_chunk[ x ][ y ][ z ].GetFront() == m_chunk[ x ][ y - 1 ][ z ].GetFront() ) {
					vertex[ i - 4 ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
					vertex[ i - 3 ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
					vertex[ i - 1 ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myFront );
					
					texture[ j - 6 ] = Vector2<GLfloat>( 1, merged + 2 );
					texture[ j - 5 ] = Vector2<GLfloat>( 0, merged + 2 );
					texture[ j - 2 ] = Vector2<GLfloat>( 0, merged + 2 );
					
					merged++;
				} else {
					vertex[ i++ ] = Vector4<GLbyte>( x,     y,     z + 1, myFront );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myFront );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
					vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, z + 1, myFront );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     z + 1, myFront );
					vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, z + 1, myFront );
					
					texture[ j++ ] = Vector2<GLfloat>( 1, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 1, 0 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 1 );
					texture[ j++ ] = Vector2<GLfloat>( 0, 0 );
					
					merged = 0;
				}
				
				visible = true;
			}
		}
	}
	
	m_elements = i;
	m_textures = j;
	
	if ( m_buffers[ 0 ] != 0 ) {
		glDeleteBuffers( 2, m_buffers );
	}
	
	glBindVertexArray( m_vao );
	glGenBuffers( 2, m_buffers );
	
	glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ 0 ] );
	glBufferData( GL_ARRAY_BUFFER, m_elements * sizeof *vertex, vertex, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_BYTE, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );
	
	glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ 1 ] );
	glBufferData( GL_ARRAY_BUFFER, m_textures * sizeof *texture, texture, GL_STATIC_DRAW );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 1 );
	
	glBindVertexArray( 0 );
}

void Chunk::Set( int pX, int pY, int pZ, block_t pType ) {
	if ( pX < 0 ) {
		if ( m_left ) {
			m_left->Set( pX + CHUNK_X, pY, pZ, pType );
		}
		return;
	}
	
	if ( pX >= CHUNK_X ) {
		if ( m_right ) {
			m_right->Set( pX - CHUNK_X, pY, pZ, pType );
		}
		return;
	}
	
	if ( pY < 0 ) {
		if ( m_below ) {
			m_below->Set( pX, pY + CHUNK_Y, pZ, pType );
		}
		return;
	}
	
	if ( pY >= CHUNK_Y ) {
		if ( m_above ) {
			m_above->Set( pX, pY - CHUNK_Y, pZ, pType );
		}
		return;
	}
	
	if ( pZ < 0 ) {
		if ( m_front ) {
			m_front->Set( pX, pY, pZ + CHUNK_Z, pType );
		}
		return;
	}
	
	if ( pZ >= CHUNK_Z ) {
		if ( m_back ) {
			m_back->Set( pX, pY, pZ - CHUNK_Z, pType );
		}
		return;
	}
	
	m_chunk[ pX ][ pY ][ pZ ] = pType;
	m_hasChanged = true;
	
	if ( pX == 0 && m_left ) {
		m_left->SetChanged( true );
	}
	
	if ( pX == CHUNK_X - 1 && m_right ) {
		m_right->SetChanged( true );
	}
	
	if ( pY == 0 && m_below ) {
		m_below->SetChanged( true );
	}
	
	if ( pY == CHUNK_Y - 1 && m_above ) {
		m_above->SetChanged( true );
	}
	
	if ( pZ == 0 && m_front ) {
		m_front->SetChanged( true );
	}
	
	if ( pZ == CHUNK_Z - 1 && m_back ) {
		m_back->SetChanged( true );
	}
}

block_t Chunk::Get( int pX, int pY, int pZ ) const {
	if ( pX < 0 ) {
		return m_left ? m_left->Get( pX + CHUNK_X, pY, pZ ) : block_t();
	}
	
	if ( pX >= CHUNK_X ) {
		return m_right ? m_right->Get( pX - CHUNK_X, pY, pZ ) : block_t();
	}
	
	if ( pY < 0 ) {
		return m_below ? m_below->Get( pX, pY + CHUNK_Y, pZ ) : block_t();
	}
	
	if ( pY >= CHUNK_Y ) {
		return m_above ? m_above->Get( pX, pY - CHUNK_Y, pZ ) : block_t();
	}
	
	if ( pZ < 0 ) {
		return m_front ? m_front->Get( pX, pY, pZ + CHUNK_Z ) : block_t();
	}
	
	if ( pZ >= CHUNK_Z ) {
		return m_back ? m_back->Get( pX, pY, pZ - CHUNK_Z ) : block_t();
	}
	
	return m_chunk[ pX ][ pY ][ pZ ];
}

bool Chunk::IsBlocked( int pX1, int pY1, int pZ1, int pX2, int pY2, int pZ2 ) const {
	if ( !m_chunk[ pX1 ][ pY1 ][ pZ1 ].Initialized() ) {
		return true;
	}
	
	block_t block = Get( pX2, pY2, pZ2 );
	
	if ( block.Transparent() == 1 ) {
		return false;
	}
	
	return block.Initialized();
}














