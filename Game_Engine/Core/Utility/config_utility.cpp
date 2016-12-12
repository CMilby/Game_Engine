//
//  config_utility.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "config_utility.h"

#include <fstream>

#include "config.h"
#include "file_utility.h"
#include "input_utility.h"
#include "logger.h"
#include "string_utility.h"

void ConfigUtility::LoadConfigFile() {
    LoadConfigFile( "config.ini" );
}

void ConfigUtility::LoadConfigFile( const std::string &pFilepath ) {
    const std::string kFunction = "LoadConfigFile";
    
    std::ifstream file( FileUtility::GetConfigDirectory() + pFilepath );
    if ( file.is_open() ) {
        std::string line;
        while( std::getline( file, line ) ) {
            StringUtility::Trim( line );
            
            if ( line.size() == 0 ) {
                continue;
            }
            
            if ( line[ 0 ] == '#' ) {
                continue;
            }
            
            std::vector<std::string> tokens = StringUtility::Split( line, '=' );
            if ( m_callbacks.count( tokens[ 0 ] ) ) {
                m_callbacks[ tokens[ 0 ] ]( tokens[ 1 ] );
            } else {
                Logger::LogWarning( kFunction, "Unknown value in config.ini", tokens[ 0 ] );
            }
        }
        
        file.close();
    } else {
        Logger::LogError( kFunction, "Could not find config.ini", "" );
    }
}

void ConfigUtility::PopulateCallbacks() {
    m_callbacks[ "Version" ] = std::bind( &ConfigUtility::VersionCallback, this, std::placeholders::_1 );
    
    m_callbacks[ "Error" ] = std::bind( &ConfigUtility::ErrorCallback, this, std::placeholders::_1 );
    m_callbacks[ "Warning" ] = std::bind( &ConfigUtility::WarningCallback, this, std::placeholders::_1 );
    m_callbacks[ "Info" ] = std::bind( &ConfigUtility::InfoCallback, this, std::placeholders::_1 );
    m_callbacks[ "Debug" ] = std::bind( &ConfigUtility::DebugCallback, this, std::placeholders::_1 );
    m_callbacks[ "Crash" ] = std::bind( &ConfigUtility::CrashCallback, this, std::placeholders::_1 );
    m_callbacks[ "Severe" ] = std::bind( &ConfigUtility::SevereCallback, this, std::placeholders::_1 );
    
    m_callbacks[ "KeyUp" ] = std::bind( &ConfigUtility::KeyUpCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyLeft" ] = std::bind( &ConfigUtility::KeyLeftCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyDown" ] = std::bind( &ConfigUtility::KeyDownCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyRight" ] = std::bind( &ConfigUtility::KeyRightCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyNext" ] = std::bind( &ConfigUtility::KeyNextCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyLast" ] = std::bind( &ConfigUtility::KeyLastCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeyInventory" ] = std::bind( &ConfigUtility::KeyInventoryCallback, this, std::placeholders::_1 );
    m_callbacks[ "KeySprint" ] = std::bind( &ConfigUtility::KeySprintCallback, this, std::placeholders::_1 );
    
    m_callbacks[ "ButtonUseLeft" ] = std::bind( &ConfigUtility::ButtonUseLeftCallback, this, std::placeholders::_1 );
    m_callbacks[ "ButtonUseRight" ] = std::bind( &ConfigUtility::ButtonUseRightCallback, this, std::placeholders::_1 );
    
    m_callbacks[ "ScreenWidth" ] = std::bind( &ConfigUtility::ScreenWidthCallback, this, std::placeholders::_1 );
    m_callbacks[ "ScreenHeight" ] = std::bind( &ConfigUtility::ScreenHeightCallback, this, std::placeholders::_1 );
    m_callbacks[ "Fullscreen" ] = std::bind( &ConfigUtility::FullscreenCallback, this, std::placeholders::_1 );
    
    m_callbacks[ "ZNear" ] = std::bind( &ConfigUtility::ZNearCallback, this, std::placeholders::_1 );
    m_callbacks[ "ZFar" ] = std::bind( &ConfigUtility::ZFarCallback, this, std::placeholders::_1 );
    m_callbacks[ "FOV" ] = std::bind( &ConfigUtility::FOVCallback, this, std::placeholders::_1 );
}

void ConfigUtility::VersionCallback( const std::string &pValue ) {
    std::vector<std::string> myElems = StringUtility::Split( pValue, '.' );
    Config::SetVersion( std::stoi( myElems[ 0 ] ), std::stoi( myElems[ 1 ] ), std::stoi( myElems[ 2 ] ) );
}

void ConfigUtility::ErrorCallback( const std::string &pValue ) {
    Config::SetError( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::WarningCallback( const std::string &pValue ) {
    Config::SetWarning( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::InfoCallback( const std::string &pValue ) {
    Config::SetInfo( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::DebugCallback( const std::string &pValue ) {
    Config::SetDebug( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::CrashCallback( const std::string &pValue ) {
    Config::SetCrash( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::SevereCallback( const std::string &pValue ) {
    Config::SetSevere( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::KeyUpCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyUp( key );
    }
}

void ConfigUtility::KeyLeftCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyLeft( key );
    }
}

void ConfigUtility::KeyDownCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyDown( key );
    }
}

void ConfigUtility::KeyRightCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyRight( key );
    }
}

void ConfigUtility::KeyNextCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyNext( key );
    }
}

void ConfigUtility::KeyLastCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyLast( key );
    }
}

void ConfigUtility::KeyInventoryCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeyInventory( key );
    }
}

void ConfigUtility::KeySprintCallback( const std::string &pValue ) {
    int key = InputUtility::StringToKey( StringUtility::ToUpper( pValue ) );
    if ( key != -1 ) {
        Config::SetKeySprint( key );
    }
}

void ConfigUtility::ButtonUseLeftCallback( const std::string &pValue ) {
    int button = InputUtility::StringToButton( StringUtility::ToUpper( pValue ) );
    if ( button != -1 ) {
        Config::SetButtonUseLeft( button );
    }
}

void ConfigUtility::ButtonUseRightCallback( const std::string &pValue ) {
    int button = InputUtility::StringToButton( StringUtility::ToUpper( pValue ) );
    if ( button != -1 ) {
        Config::SetButtonUseRight( button );
    }
}

void ConfigUtility::ScreenWidthCallback( const std::string &pValue ) {
    Config::SetScreenWidth( std::stoi( pValue ) );
}

void ConfigUtility::ScreenHeightCallback( const std::string &pValue ) {
    Config::SetScreenHeight( std::stoi( pValue ) );
}

void ConfigUtility::FullscreenCallback( const std::string &pValue ) {
    Config::SetFullscreen( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigUtility::ZNearCallback( const std::string &pValue ) {
    Config::SetZNear( std::stof( pValue ) );
}

void ConfigUtility::ZFarCallback( const std::string &pValue ) {
    Config::SetZFar( std::stof( pValue ) );
}

void ConfigUtility::FOVCallback( const std::string &pValue ) {
    Config::SetFOV( std::stof( pValue ) );
}

