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
		m_block = pValue;
		
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
		Math3D::SetBits( m_block, 1, 56, 63 );
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
		return Math3D::GetBits( m_block, 56, 63 );
	}
};

class Chunk : public Mesh {
	
private:
	block_t m_chunk[ CHUNK_X ][ CHUNK_Y ][ CHUNK_Z ];
	
	GLuint m_vbo;
	GLuint m_vao;
	
	unsigned int m_elements;
	bool m_hasChanged;
	
	void Update();
	
public:
	Chunk();
	virtual ~Chunk();
	
	virtual void Render();
	
	inline void Set( int pX, int pY, int pZ, block_t pType ) {
		m_chunk[ pX ][ pY ][ pZ ] = pType;
		m_hasChanged = true;
	}

	inline block_t Get( int pX, int pY, int pZ ) const {
		return m_chunk[ pX ][ pY ][ pZ ];
	}
};

#endif /* chunk_h */
