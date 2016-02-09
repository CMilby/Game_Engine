//
//  terrain.h
//  Game_Engine
//
//  Created by Craig Milby on 1/23/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <vector>

#include "camera.h"
#include "entity.h"
#include "shader.h"
#include "terrainMesh.h"

#define GRID_SIZE 8

class Terrain : public RenderableEntity {
  
private:
    std::string m_file;
    
    unsigned int m_level;
    unsigned int m_maxLevel;
    bool m_split;
    
    bool m_splitX;
    bool m_splitY;
    bool m_splitZ;
    
    float m_radius;
    float m_direction;
	
	float m_lastXOffset;
	float m_lastYOffset;
	float m_lastZOffset;
    
    Vector3<float> m_position;
    Vector3<float> m_realPosition;
    
    void Split();
    void Join();

    float SplitDistance( int level );
    void GenerateTexture();
    
public:
    Terrain( const std::string &file, float radius, unsigned int level, float direction, bool x, bool y, bool z, float xOffset, float yOffset, float zOffset, float scale, const std::string &position, float lastX, float lastY, float lastZ );
    virtual ~Terrain();
    
    virtual void RenderAll( const std::vector<Shader*> &shaders, const Camera &camera );
    
    void SetPosition( const Vector3<float> &position ) { m_position = position; }
};

#endif /* terrain_h */
