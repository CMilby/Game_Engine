//
//  testTerrain.h
//  Game_Engine
//
//  Created by Craig Milby on 5/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TEST_TERRAIN_H__
#define __TEST_TERRAIN_H__

#include <string>
#include <vector>

#include "renderableEntity.h"
#include "terrainMesh.h"

#define GRID_SIZE 8

class TestTerrain : public RenderableEntity {
	
private:
	std::string m_filename;
	
	std::vector<float> m_textureData;
	
	Vector3<float> m_position;
	Vector3<float> m_realPosition;
	Vector3<float> m_lastOffset;
	
	Vector3<bool> m_splits;
	
	float m_direction;
	float m_radius;
	
	unsigned int m_size;
	unsigned int m_level;
	unsigned int m_maxLevel;
	
	bool m_split;
	
	std::vector<float> TextureXProcedure( const unsigned int pSize, const float pDirection, const int pSplit ) const;
	std::vector<float> TextureYProcedure( const unsigned int pSize, const float pDirection, const int pSplit ) const;
	std::vector<float> TextureZProcedure( const unsigned int pSize, const float pDirection, const int pSplit, const int pMultiplier, const float pScale, const Vector3<float> &pOffset, Vector3<float> &pLastOffset ) const;
	
	float SplitDistance( int pLevel ) const;
	
	void Split();
	void Join();
	
protected:
	virtual void Update();
	
public:
	TestTerrain( const std::string &pFilename, float pRadius, unsigned int pSize, unsigned int pLevel, const Vector3<bool> &pSplits, float pDirection, const Vector3<float> &pOffset, float pScale, const Vector3<float> &pLastPosition );
	
	void ColorizeTerrain();
};

#endif /* testTerrain_h */
