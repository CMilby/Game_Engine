//
//  config.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

#include "transform.h"

class Config {
    
private:
	static int s_majorVersion;
	static int s_minorVersion;
	static int s_subVersion;
	
	static bool s_error;
	static bool s_warning;
	static bool s_info;
	static bool s_debug;
	static bool s_crash;
	static bool s_severe;
	
	static int s_keyUp;
	static int s_keyLeft;
	static int s_keyDown;
	static int s_keyRight;
	static int s_keyNext;
	static int s_keyLast;
	static int s_keyInventory;
	static int s_keySprint;
	
	static int s_buttonUseLeft;
	static int s_buttonUseRight;
	
    static unsigned int s_screenWidth;
    static unsigned int s_screenHeight;
    static bool s_fullscreen;
	
	static float s_top;
	static float s_bottom;
	static float s_left;
	static float s_right;
	
    static float s_fieldOfView;
    static float s_zNear;
    static float s_zFar;
    static float s_aspectRatio;
	
    Config() {}
public:
	inline static void SetVersion( int pMajor, int pMinor, int pSub ) {
		s_majorVersion = pMajor;
		s_minorVersion = pMinor;
		s_subVersion = pSub;
	}
	
	inline static std::string GetVersion() {
		return std::to_string( s_majorVersion ) + "." + std::to_string( s_minorVersion ) + "." + std::to_string( s_subVersion );
	}
	
	inline static void SetMajorVersion( int pMajor ) { 
		s_majorVersion = pMajor;
	}
	
	inline static int GetMajorVersion() { return s_majorVersion; }
	
	inline static void SetMinorVersion( int pMinor ) {
		s_minorVersion = pMinor;
	}
	
	inline static int GetMinorVersion() { return s_minorVersion; }
	
	inline static void SetSubVersion( int pSub ) {
		s_subVersion = pSub;
	}
	
	inline static int GetSubVersion() { return s_subVersion; }

	inline static void SetError( bool pError ) {
		s_error = pError;
	}
	
	inline static bool Error() { return s_error; }
	
	inline static void SetWarning( bool pWarning ) {
		s_warning = pWarning;
	}
	
	inline static bool Warning() { return s_warning; }
	
	inline static void SetInfo( bool pInfo ) { 
		s_info = pInfo;
	}
	
	inline static bool Info() { return s_info; }
	
	inline static void SetDebug( bool pDebug ) {
		s_debug = pDebug;
	}
	
	inline static bool Debug() { return s_debug; }
	
	inline static void SetCrash( bool pCrash ) {
		s_crash = pCrash;
	}
	
	inline static bool Crash() { return s_crash; }
	
	inline static void SetSevere( bool pSevere ) {
		s_severe = pSevere;
	}
	
	inline static bool Severe() { return s_severe; }
	
	inline static void SetKeyUp( int pKey ) {
		s_keyUp = pKey;
	}
	
	inline static int GetKeyUp() { return s_keyUp; }
	
	inline static void SetKeyLeft( int pKey ) { 
		s_keyLeft = pKey;
	}
	
	inline static int GetKeyLeft() { return s_keyLeft; }
	
	inline static void SetKeyDown( int pKey ) {
		s_keyDown = pKey;
	}
	
	inline static int GetKeyDown() { return s_keyDown; }
	
	inline static void SetKeyRight( int pKey ) {
		s_keyRight = pKey;
	}
	
	inline static int GetKeyRight() { return s_keyRight; }
	
	inline static void SetKeyNext( int pKey ) {
		s_keyNext = pKey;
	}
	
	inline static int GetKeyNext() { return s_keyNext; }
	
	inline static void SetKeyLast( int pKey ) {
		s_keyLast = pKey;
	}
	
	inline static int GetKeyLast() { return s_keyLast; }
	
	inline static void SetKeyInventory( int pKey ) {
		s_keyInventory = pKey;
	}
	
	inline static int GetKeyInventory() { return s_keyInventory; }
	
	inline static void SetKeySprint( int pKey ) {
		s_keySprint = pKey;
	}
	
	inline static int GetKeySprint() { return s_keySprint; }
	
	inline static void SetButtonUseLeft( int pButton ) {
		s_buttonUseLeft = pButton;
	}
	
	inline static int GetButtonUseLeft() { return s_buttonUseLeft; }
	
	inline static void SetButtonUseRight( int pButton ) {
		s_buttonUseRight = pButton;
	}
	
	inline static int GetButtonUseRight() { return s_buttonUseRight; }
	
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
    
	inline static void SetFullscreen( bool pFullscreen ) {
		s_fullscreen = pFullscreen;
	}
	
	inline static bool GetFullscreen() { return s_fullscreen; }
	
	inline static void SetTop( float pTop ) {
		s_top = pTop;
	}
	
	inline static float GetTop() { return s_top; }
	
	inline static void SetBottom( float pBottom ) {
		s_bottom = pBottom;
	}
	
	inline static float GetBottom() { return s_bottom; }
	
	inline static void SetLeft( float pLeft ) {
		s_left = pLeft;
	}
	
	inline static float GetLeft() { return s_left; }
	
	inline static void SetRight( float pRight ) {
		s_right = pRight;
	}
	
	inline static float GetRight() { return s_right; }
	
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
		Transform::SetOrthographicProjection( GetLeft(), GetRight(), GetTop(), GetBottom(), GetZNear(), GetZFar() );
    }
    
    inline static float GetZNear() { return s_zNear; }
    
    inline static void SetZFar( float zFar ) {
        s_zFar = zFar;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
		Transform::SetOrthographicProjection( GetLeft(), GetRight(), GetTop(), GetBottom(), GetZNear(), GetZFar() );
    }
    
    inline static float GetZFar() { return s_zFar; }
	
	inline static void SetFOV( float fov ) {
        s_fieldOfView = fov;
        Transform::SetPerspectiveProjection( s_fieldOfView, s_aspectRatio, s_zNear, s_zFar );
    }
    
    inline static float GetFOV() { return s_fieldOfView; }
};

#endif /* config_h */