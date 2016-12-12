//
//  material.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "math3d.h"
#include "texture.h"

struct Material {
    Texture *m_texture;
    Vector3<float> m_color;
    
    float m_specularPower;
    float m_specularIntensity;
    
    Material( Texture *p_texture = new Texture( "test.png" ), const Vector3<float> &p_color = Vector3<float>( 1.0f, 1.0f, 1.0f ), float p_specularIntensity = 1.0f, float p_specularPower = 32.0f ) {
        m_texture = p_texture;
        m_color = p_color;
        m_specularIntensity = p_specularIntensity;
        m_specularPower = p_specularPower;
    }
    
    Material( const std::string &p_texture, const Vector3<float> &p_color = Vector3<float>( 1.0f, 1.0f, 1.0f ), float p_specularIntensity = 1.0f, float p_specularPower = 32.0f ) {
        m_texture = new Texture( p_texture );
        m_color = p_color;
        m_specularIntensity = p_specularIntensity;
        m_specularPower = p_specularPower;
    }
};

#endif /* material_h */
