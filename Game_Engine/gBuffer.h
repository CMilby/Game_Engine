//
//  gBuffer.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GEOMETRY_BUFFER_H__
#define __GEOMETRY_BUFFER_H__

#include <GL/glew.h>

class GBuffer {
    
private:
    GLuint m_gBuffer;
    GLuint m_position;
    GLuint m_normal;
    GLuint m_specular;
    GLuint m_rboDepth;
    
public:
    GBuffer();
    virtual ~GBuffer();
    
    void Init();
};

#endif /* gBuffer_h */
