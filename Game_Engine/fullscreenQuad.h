//
//  fullscreenQuad.h
//  Game_Engine
//
//  Created by Craig Milby on 12/23/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __FULLSCREEN_QUAD_H__
#define __FULLSCREEN_QUAD_H__

#include <GL/glew.h>

class FullscreenQuad {
    
private:
    GLuint m_vao;
    GLuint m_positionBuffer;
    GLuint m_indexBuffer;
    
    int m_numIndices;
    
public:
    FullscreenQuad();
    virtual ~FullscreenQuad();
    
    void Render();
};

#endif /* fullscreenQuad_h */
