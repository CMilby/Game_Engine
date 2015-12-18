//
//  cubemapTexture.h
//  Game_Engine
//
//  Created by Craig Milby on 12/17/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CUBEMAP_TEXTURE_H__
#define __CUBEMAP_TEXTURE_H__

#include <string>

#include <GL/glew.h>

class CubeMapTexture {
    
private:
    std::string m_filenames[ 6 ];
    GLuint m_textureObj;
    
public:
    CubeMapTexture( const std::string &dirctory,
                   const std::string &posX,
                   const std::string &negX,
                   const std::string &posY,
                   const std::string &negY,
                   const std::string &posZ,
                   const std::string &negZ );
    virtual ~CubeMapTexture();
    
    bool Load();
    void Bind( GLenum unitTexture );
};

#endif /* cubemapTexture_h */
