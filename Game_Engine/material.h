//
//  material.h
//  Game_Engine
//
//  Created by Craig Milby on 11/26/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
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
    
    Material( Texture *texture = NULL, const Vector3<float> &color = Vector3<float>( 1.0f, 1.0f, 1.0f ), float specularIntensity = 2, float specularPower = 32 ) {
        m_texture = texture;
        m_color = color;
        m_specularIntensity = specularIntensity;
        m_specularPower = specularPower;
    }
};

#endif /* material_h */
