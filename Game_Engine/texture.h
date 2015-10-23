//
//  texture.h
//  Game_Engine
//
//  Created by Craig Milby on 10/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include <GL/glew.h>

class Texture {
    
private:
    GLuint m_texture;
    
    GLuint LoadDDS( const std::string &filename );
    GLuint LoadTGA( const std::string &filename );
public:
    Texture( const std::string &filename );
    virtual ~Texture();
    
    void Bind() const;
};

#endif /* texture_h */
