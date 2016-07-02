//
//  configLoader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "configLoader.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "config.h"
#include "logger.h"
#include "utility.h"

void ConfigLoader::LoadConfigFile() {
	LoadConfigFile( Utility::DirectoryPath() + "config/config.ini" );
}

void ConfigLoader::LoadConfigFile( const std::string &pFilepath ) {
	const std::string kFunction = "LoadConfigFile";
	
	std::ifstream file( pFilepath );
	if ( file.is_open() ) {
		std::string line;
		while( std::getline( file, line ) ) {
			Utility::Trim( line );
			
			if ( line.size() == 0 ) {
				continue;
			}
			
			if ( line[ 0 ] == '#' ) {
				continue;
			}
			
			std::vector<std::string> tokens = Utility::Split( line, '=' );
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

void ConfigLoader::PopulateCallbacks() {
	m_callbacks[ "Version" ] = std::bind( &ConfigLoader::VersionCallback, this, std::placeholders::_1 );
	
	m_callbacks[ "Error" ] = std::bind( &ConfigLoader::ErrorCallback, this, std::placeholders::_1 );
	m_callbacks[ "Warning" ] = std::bind( &ConfigLoader::WarningCallback, this, std::placeholders::_1 );
	m_callbacks[ "Info" ] = std::bind( &ConfigLoader::InfoCallback, this, std::placeholders::_1 );
	m_callbacks[ "Debug" ] = std::bind( &ConfigLoader::DebugCallback, this, std::placeholders::_1 );
	m_callbacks[ "Crash" ] = std::bind( &ConfigLoader::CrashCallback, this, std::placeholders::_1 );
	m_callbacks[ "Severe" ] = std::bind( &ConfigLoader::SevereCallback, this, std::placeholders::_1 );
	
	m_callbacks[ "KeyUp" ] = std::bind( &ConfigLoader::KeyUpCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyLeft" ] = std::bind( &ConfigLoader::KeyLeftCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyDown" ] = std::bind( &ConfigLoader::KeyDownCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyRight" ] = std::bind( &ConfigLoader::KeyRightCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyNext" ] = std::bind( &ConfigLoader::KeyNextCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyLast" ] = std::bind( &ConfigLoader::KeyLastCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeyInventory" ] = std::bind( &ConfigLoader::KeyInventoryCallback, this, std::placeholders::_1 );
	m_callbacks[ "KeySprint" ] = std::bind( &ConfigLoader::KeySprintCallback, this, std::placeholders::_1 );
	
	m_callbacks[ "ButtonUseLeft" ] = std::bind( &ConfigLoader::ButtonUseLeftCallback, this, std::placeholders::_1 );
	m_callbacks[ "ButtonUseRight" ] = std::bind( &ConfigLoader::ButtonUseRightCallback, this, std::placeholders::_1 );
	
	m_callbacks[ "ScreenWidth" ] = std::bind( &ConfigLoader::ScreenWidthCallback, this, std::placeholders::_1 );
	m_callbacks[ "ScreenHeight" ] = std::bind( &ConfigLoader::ScreenHeightCallback, this, std::placeholders::_1 );
	m_callbacks[ "Fullscreen" ] = std::bind( &ConfigLoader::FullscreenCallback, this, std::placeholders::_1 );
	
	m_callbacks[ "ZNear" ] = std::bind( &ConfigLoader::ZNearCallback, this, std::placeholders::_1 );
	m_callbacks[ "ZFar" ] = std::bind( &ConfigLoader::ZFarCallback, this, std::placeholders::_1 );
	m_callbacks[ "FOV" ] = std::bind( &ConfigLoader::FOVCallback, this, std::placeholders::_1 );
}

void ConfigLoader::VersionCallback( const std::string &pValue ) {
	std::vector<std::string> myElems = Utility::Split( pValue, '.' );
	Config::SetVersion( std::stoi( myElems[ 0 ] ), std::stoi( myElems[ 1 ] ), std::stoi( myElems[ 2 ] ) );
}

void ConfigLoader::ErrorCallback( const std::string &pValue ) {
	Config::SetError( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::WarningCallback( const std::string &pValue ) {
	Config::SetWarning( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::InfoCallback( const std::string &pValue ) {
	Config::SetInfo( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::DebugCallback( const std::string &pValue ) {
	Config::SetDebug( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::CrashCallback( const std::string &pValue ) {
	Config::SetCrash( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::SevereCallback( const std::string &pValue ) {
	Config::SetSevere( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::KeyUpCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyUp( key );
	}
}

void ConfigLoader::KeyLeftCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyLeft( key );
	}
}

void ConfigLoader::KeyDownCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyDown( key );
	}
}

void ConfigLoader::KeyRightCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyRight( key );
	}
}

void ConfigLoader::KeyNextCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyNext( key );
	}
}

void ConfigLoader::KeyLastCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyLast( key );
	}
}

void ConfigLoader::KeyInventoryCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeyInventory( key );
	}
}

void ConfigLoader::KeySprintCallback( const std::string &pValue ) {
	int key = Utility::StringToKey( Utility::ToUpper( pValue ) );
	if ( key != -1 ) {
		Config::SetKeySprint( key );
	}
}

void ConfigLoader::ButtonUseLeftCallback( const std::string &pValue ) {
	int button = Utility::StringToButton( Utility::ToUpper( pValue ) );
	if ( button != -1 ) {
		Config::SetButtonUseLeft( button );
	}
}

void ConfigLoader::ButtonUseRightCallback( const std::string &pValue ) {
	int button = Utility::StringToButton( Utility::ToUpper( pValue ) );
	if ( button != -1 ) {
		Config::SetButtonUseRight( button );
	}
}

void ConfigLoader::ScreenWidthCallback( const std::string &pValue ) {
	Config::SetScreenWidth( std::stoi( pValue ) );
}

void ConfigLoader::ScreenHeightCallback( const std::string &pValue ) {
	Config::SetScreenHeight( std::stoi( pValue ) );
}

void ConfigLoader::FullscreenCallback( const std::string &pValue ) {
	Config::SetFullscreen( ( bool ) ( std::stoi( pValue ) ) );
}

void ConfigLoader::ZNearCallback( const std::string &pValue ) {
	Config::SetZNear( std::stof( pValue ) );
}

void ConfigLoader::ZFarCallback( const std::string &pValue ) {
	Config::SetZFar( std::stof( pValue ) );
}

void ConfigLoader::FOVCallback( const std::string &pValue ) {
	Config::SetFOV( std::stof( pValue ) );
}














