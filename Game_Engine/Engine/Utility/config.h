//
//  config.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "transform.h"

class Config {
    
private:
    static unsigned int s_screenWidth;
    static unsigned int s_screenHeight;
    
    static float s_fieldOfView;
    static float s_aspectRatio;
    static float s_zNear;
    static float s_zFar;
    
    static bool s_debug;
    
    Config() {}
public:
    inline static void SetScreenWidth( unsigned int screenWidth ) {
        s_screenWidth = screenWidth;
        SetAspectRatio( s_screenWidth, s_screenHeight );
		Transform::SetOrthographicProjection( 0.0f, GetScreenWidth(), GetScreenHeight(), 0.0f, GetZNear(), GetZFar() );
    }
    
    inline static unsigned int GetScreenWidth() { return s_screenWidth; }
    
    inline static void SetScreenHeight( unsigned int screenHeight ) {
        s_screenHeight = screenHeight;
        SetAspectRatio( s_screenWidth, s_screenHeight );
		Transform::SetOrthographicProjection( 0.0f, GetScreenWidth(), GetScreenHeight(), 0.0f, GetZNear(), GetZFar() );
    }
    
    inline static unsigned int GetScreenHeight() { return s_screenHeight; }
    
    inline static void SetFieldOfView( float fov ) {
        s_fieldOfView = fov;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
    }
    
    inline static float GetFieldOfView() { return s_fieldOfView; }
    
    inline static void SetAspectRatio( float aspectRatio ) {
        s_aspectRatio = aspectRatio;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
    }
    
    inline static void SetAspectRatio( float width, float height ) {
        s_aspectRatio = width / height;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
    }
    
    inline static float GetAspectRatio() { return s_aspectRatio; }
    
    inline static void SetZNear( float zNear ) {
        s_zNear = zNear;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
		Transform::SetOrthographicProjection( 0.0f, GetScreenWidth(), GetScreenHeight(), 0.0f, GetZNear(), GetZFar() );
    }
    
    inline static float GetZNear() { return s_zNear; }
    
    inline static void SetZFar( float zFar ) {
        s_zFar = zFar;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
		Transform::SetOrthographicProjection( 0.0f, GetScreenWidth(), GetScreenHeight(), 0.0f, GetZNear(), GetZFar() );
    }
    
    inline static float GetZFar() { return s_zFar; }
    
    inline static bool Debug() {
        return s_debug;
    }
};

#endif /* config_h */
