//
//  logger.cpp
//  Game_Engine
//
//  Created by Craig Milby on 7/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "logger.h"

#include "config.h"

void Logger::Log( const std::string &pLevel, const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( pContext != "" ) {
		std::cout << pLevel << ": " << pOrigin << " | " << pMessage << " - " << pContext << std::endl;
	} else {
		std::cout << pLevel << ": " << pOrigin << " | " << pMessage << std::endl;
	}
}

void Logger::LogError( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Error() ) {
		Logger::Log( "ERROR", pOrigin, pMessage, pContext );
	}
}

void Logger::LogWarning( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Warning() ) {
		Logger::Log( "WARNING", pOrigin, pMessage, pContext );
	}
}

void Logger::LogInfo( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Info() ) {
		Logger::Log( "INFO", pOrigin, pMessage, pContext );
	}
}

void Logger::LogDebug( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Debug() ) {
		Logger::Log( "DEBUG", pOrigin, pMessage, pContext );
	}
}

void Logger::LogCrash( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Crash() ) {
		Logger::Log( "CRASH", pOrigin, pMessage, pContext );
	}
}

void Logger::LogSevere( const std::string &pOrigin, const std::string &pMessage, const std::string &pContext ) {
	if ( Config::Severe() ) {
		Logger::Log( "SEVERE", pOrigin, pMessage, pContext );
	}
}