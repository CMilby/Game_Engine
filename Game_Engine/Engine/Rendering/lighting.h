//
//  lighting.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __LIGHTING_H__
#define __LIGHTING_H__

#include "math3d.h"

struct BaseLight {
    Vector3f m_color;
    float m_intensity;
    
    BaseLight( const Vector3f &p_color = Vector3f( 0.0f, 0.0f, 0.0f ), float p_intensity = 0.5f ) {
        m_color = p_color;
        m_intensity = p_intensity;
    }
};

struct DirectionalLight {
    BaseLight m_baseLight;
    Vector3f m_direction;
    
    DirectionalLight( const BaseLight &p_baseLight = BaseLight(), const Vector3f &p_direction = Vector3f( 0.0f, 0.0f, -1.0f ) ) {
        m_baseLight = p_baseLight;
        m_direction = p_direction;
    }
};

struct Attenuation {
    float m_constant;
    float m_linear;
    float m_exponent;
    
    Attenuation( float p_constant = 0.0f, float p_linear = 0.0f, float p_exponent = 1.0f ) {
        m_constant = p_constant;
        m_linear = p_linear;
        m_exponent = p_exponent;
    }
};

struct PointLight {
    BaseLight m_baseLight;
    Attenuation m_atten;
    Vector3f m_position;
    float m_range;
    
    PointLight( const BaseLight &p_baseLight = BaseLight(), const Attenuation &p_atten = Attenuation(), const Vector3f &p_position = Vector3f( 0.0f, 0.0f, 0.0f ), float p_range = 10.0f ) {
        m_baseLight = p_baseLight;
        m_atten = p_atten;
        m_position = p_position;
        m_range = p_range;
    }
};

struct SpotLight {
    PointLight m_pointLight;
    Vector3f m_direction;
    float m_cutoff;
    
    SpotLight( const PointLight &p_pointLight = PointLight(), const Vector3f &p_direction = Vector3f( 0.0, 0.0, -1.0f ), float p_cutoff = 10.0f ) {
        m_pointLight = p_pointLight;
        m_direction = p_direction;
        m_cutoff = p_cutoff;
    }
};

#endif /* lighting_h */
