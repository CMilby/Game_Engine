
#include "chunk.h"

#include "worldGenerator.h"

Chunk::Chunk( int pX, int pY ) {
	// memset( m_map, 0, sizeof( m_map ) );
	m_x = pX;
	m_y = pY;
	m_z = 0;
	
	m_elements = 0;
	m_hasChanged = true;
	
	glGenBuffers( 1, &m_vbo );
}

Chunk::~Chunk() {
	glDeleteBuffers( 1, &m_vbo );
}

void Chunk::Update() {
	m_hasChanged = false;
	
	Vector4<GLbyte> vertex[ CHUNK_X * CHUNK_Y * 6 ];
	
	int i = 0;
	for ( unsigned int x = 0; x < CHUNK_X; x++ ) {
		for ( unsigned int y = 0; y < CHUNK_Y; y++ ) {
			int myType = WorldGenerator::GetInstance()->GenerateTile( ( m_x * CHUNK_X ) + x, ( m_y * CHUNK_Y ) + y );
			
			vertex[ i++ ] = Vector4<GLbyte>( x,     y,     0, myType );
			vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     0, myType );
			vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, 0, myType );
			vertex[ i++ ] = Vector4<GLbyte>( x,     y + 1, 0, myType );
			vertex[ i++ ] = Vector4<GLbyte>( x + 1, y,     0, myType );
			vertex[ i++ ] = Vector4<GLbyte>( x + 1, y + 1, 0, myType );
		}
	}
	
	m_elements = i;
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBufferData( GL_ARRAY_BUFFER, m_elements * sizeof *vertex, vertex, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_BYTE, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );
}

void Chunk::Render() {
	if ( m_hasChanged ) {
		Update();
	}
	
	glEnableVertexAttribArray( 0 );
	
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glVertexAttribPointer( 0, 4, GL_BYTE, GL_FALSE, 0, 0 );
	glDrawArrays( GL_TRIANGLES, 0, m_elements );
	
	glDisableVertexAttribArray( 0 );
}

/*int Chunk::Get( int pX, int pY ) const {
	return m_map[ pX ][ pY ];
}

void Chunk::Set( int pX, int pY, int pType ) {
	m_map[ pX ][ pY ] = pType;
	m_hasChanged = true;
}*/



