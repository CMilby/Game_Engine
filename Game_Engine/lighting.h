//
//  lighting.h
//  Game_Engine
//
//  Created by Craig Milby on 11/26/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LIGHTING_H__
#define __LIGHTING_H__

#include "math3d.h"

struct BaseLight {
    Vector3<float> m_color;
    float m_intensity;
    
    BaseLight( const Vector3<float> &color = Vector3<float>( 0.0f, 0.0f, 0.0f ), float intensity = 0 ) {
        m_color = color;
        m_intensity = intensity;
    }
};

struct DirectionalLight {
    BaseLight m_baseLight;
    Vector3<float> m_direction;
    
    DirectionalLight( const BaseLight &baseLight = BaseLight(), const Vector3<float> &direction = Vector3<float>( 0.0f, 0.0f, -1.0f ) ) {
        m_baseLight = baseLight;
        m_direction = direction;
    }
};

struct Attenuation {
    float m_constant;
    float m_linear;
    float m_exponent;
    
    Attenuation( float constant = 0.0f, float linear = 0.0f, float exponent = 1.0f ) {
        m_constant = constant;
        m_linear = linear;
        m_exponent = exponent;
    }
};

struct PointLight {
    BaseLight m_baseLight;
    Attenuation m_atten;
    Vector3<float> m_position;
    float m_range;
    
    PointLight( const BaseLight &baseLight = BaseLight(), const Attenuation &atten = Attenuation(), const Vector3<float> &position = Vector3<float>( 0.0f, 0.0f, 0.0f ), float range = 0 ) {
        m_baseLight = baseLight;
        m_atten = atten;
        m_position = position;
        m_range = range;
    }
};

struct SpotLight {
    PointLight m_pointLight;
    Vector3<float> m_direction;
    float m_cutoff;
    
    SpotLight( const PointLight &pointLight = PointLight(), const Vector3<float> &direction = Vector3<float>( 0.0, 0.0, -1.0f ), float cutoff = 0 ) {
        m_pointLight = pointLight;
        m_direction = direction;
        m_cutoff = cutoff;
    }
};

#endif /* lighting_h */
