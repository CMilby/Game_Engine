//
//  skybox.h
//  Game_Engine
//
//  Created by Craig Milby on 12/17/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "cubemapTexture.h"
#include "shader.h"

class Skybox : public Shader {
    
private:
    CubeMapTexture *m_cubemapTexture;
    Mesh *m_skybox;
    
public:
    Skybox( const std::string &directory,
           const std::string &posX,
           const std::string &negX,
           const std::string &posY,
           const std::string &negY,
           const std::string &posZ,
           const std::string &negZ );
    virtual ~Skybox();
    
    virtual void Init();
    
    virtual void Enable() const;
    virtual void Disable() const;
    
    virtual void UpdateUniforms( const Matrix4<float> &world, const Matrix4<float> &projected,  const Camera &camera, const Material &material );
};

#endif /* skybox_h */
