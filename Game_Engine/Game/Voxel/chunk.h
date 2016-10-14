//
//  chunk.h
//  Game_Engine
//
//  Created by Craig Milby on 8/21/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <cstdint>
#include <vector>

#include <GL/glew.h>

#include "mesh.h"

#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16

#define CHUNK_MEMORY_SIZE ( CHUNK_X * CHUNK_Y * CHUNK_Z * 6 * 6 )

#define TRANSPARENCY_BIT 48
#define INITIALIZED_BIT 49

// HOW IT WORKS
// Block data is stored in a 64 bit integer
// Bits:
// 0 - 7: Top Texture
// 8 -15: Bottom Texture
// 16-23: Left Texture
// 24-31: Right Texture
// 32-39: Front Texture
// 40-47: Back Texture
// 48: Transparent Bit ( 0 = Opaque, 1 = Transparent )
// 63: Initialized Bit ( 0 = Not Init, 1 = Init )
struct block_t {
	
private:
	uint64_t m_block;
	
	inline void Set( uint8_t pValue, unsigned int a, unsigned int b ) {
		Math3D::SetBits( m_block, pValue, a, b );
		Initialize();
	}
	
public:
	block_t() {
		m_block = 0;
	}
	
	block_t( uint64_t pValue, bool pInitialize = true ) {
		SetTop( pValue );
		SetBottom( pValue );
		SetLeft( pValue );
		SetRight( pValue );
		SetFront( pValue );
		SetBack( pValue );
		
		if ( pInitialize ) {
			Initialize();
		}
	}
	
	block_t( uint8_t pTop, uint8_t pBottom, uint8_t pLeft, uint8_t pRight, uint8_t pFront, uint8_t pBack ) {
		SetTop( pTop );
		SetBottom( pBottom );
		SetLeft( pLeft );
		SetRight( pRight );
		SetFront( pFront );
		SetBack( pBack );
		
		Initialize();
	}
	
	inline void SetTop( uint8_t pTop ) {
		Set( pTop, 0, 7 );
	}
	
	inline void SetBottom( uint8_t pBottom ) {
		Set( pBottom, 8, 15 );
	}
	
	inline void SetLeft( uint8_t pLeft ) {
		Set( pLeft, 16, 23 );
	}
	
	inline void SetRight( uint8_t pRight ) {
		Set( pRight, 24, 31 );
	}
	
	inline void SetFront( uint8_t pFront ) {
		Set( pFront, 32, 39 );
	}
	
	inline void SetBack( uint8_t pBack ) {
		Set( pBack, 40, 47 );
	}
	
	inline void Initialize() {
		Math3D::SetBit( m_block, INITIALIZED_BIT, 1 );
	}
	
	inline void SetTransparent( uint8_t pTransparent ) {
		Math3D::SetBit( m_block, TRANSPARENCY_BIT, pTransparent );
	}
	
	inline uint8_t GetTop() const {
		return Math3D::GetBits( m_block, 0, 7 );
	}
	
	inline uint8_t GetBottom() const {
		return Math3D::GetBits( m_block, 8, 15 );
	}
	
	inline uint8_t GetLeft() const {
		return Math3D::GetBits( m_block, 16, 23 );
	}
	
	inline uint8_t GetRight() const {
		return Math3D::GetBits( m_block, 24, 31 );
	}
	
	inline uint8_t GetFront() const {
		return Math3D::GetBits( m_block, 32, 39 );
	}
	
	inline uint8_t GetBack() const {
		return Math3D::GetBits( m_block, 40, 47 );
	}
	
	inline bool Initialized() const {
		return Math3D::GetBit( m_block, INITIALIZED_BIT );
	}
	
	inline bool Transparent() const {
		return Math3D::GetBit( m_block, TRANSPARENCY_BIT );
	}
};

class Chunk : public Mesh {
	
private:
	block_t m_chunk[ CHUNK_X ][ CHUNK_Y ][ CHUNK_Z ];
	Chunk *m_left;
	Chunk *m_right;
	Chunk *m_above;
	Chunk *m_below;
	Chunk *m_front;
	Chunk *m_back;
	
	GLuint m_buffers[ 2 ];
	GLuint m_vao;
	
	unsigned int m_elements;
	unsigned int m_textures;
	bool m_hasChanged;
	
	void Update();
	bool IsBlocked( int pX1, int pY1, int pZ1, int pX2, int pY2, int pZ2 ) const;
	
	void PositiveXFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	void NegativeXFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	void PositiveYFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	void NegativeYFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	void PositiveZFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	void NegativeZFace( Vector4<GLbyte> ( &pVertex )[ CHUNK_MEMORY_SIZE ], Vector2<float> ( &pTexture )[ CHUNK_MEMORY_SIZE ], int& i, int& j );
	
public:
	Chunk();
	virtual ~Chunk();
	
	virtual void Render();
	
	void Set( int pX, int pY, int pZ, block_t pType );
	block_t Get( int pX, int pY, int pZ ) const;
	
	inline void SetChanged( bool pChanged ) { m_hasChanged = pChanged; }
	
	inline void SetLeft( Chunk *pLeft ) { m_left = pLeft; }
	inline void SetRight( Chunk *pRight ) { m_right = pRight; }
	inline void SetAbove( Chunk *pAbove ) { m_above = pAbove; }
	inline void SetBelow( Chunk *pBelow ) { m_below = pBelow; }
	inline void SetFront( Chunk *pFront ) { m_front = pFront; }
	inline void SetBack( Chunk *pBack ) { m_back = pBack; }
};

#endif /* chunk_h */
