
#ifndef __CHUNK_H__
#define __CHUNK_H__

#define CHUNK_X 16
#define CHUNK_Y 16

#include "mesh.h"
#include "math3d.h"

class Chunk : public Mesh {

private:
	// uint8_t m_map[ CHUNK_X ][ CHUNK_Y ];
	int m_x;
	int m_y;
	int m_z;
	
	GLuint m_vbo;
	
	int m_elements;
	bool m_hasChanged;
	
	void Update();

public:
	Chunk( int pX, int pY );
	virtual ~Chunk();
	
	virtual void Render();
	
	// int Get( int pX, int pY ) const;
	// void Set( int pX, int pY, int pType );
	
	inline int GetX() const { return m_x;; }
	inline int GetY() const { return m_y; }
	inline int GetZ() const { return m_z; }
	inline Vector3<int> GetPosition() const { return Vector3<int>( GetX(), GetY(), GetZ() ); }
};

#endif