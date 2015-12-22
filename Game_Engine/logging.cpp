//
//  logging.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "logging.h"

void Logging::Log( LogLevel level, const std::string &function, const std::string &message, const std::string &errors = "" ) {
    if ( errors != "" ) {
        printf( "%s: %s - %s : %s", function.c_str(), GetLogLevel( level ).c_str(), message.c_str(), errors.c_str() );
    } else {
        printf( "%s: %s - %s", function.c_str(), GetLogLevel( level ).c_str(), message.c_str() );
    }
}

void Logging::LogInfo( const std::string &function, const std::string &message, const std::string &errors ) {
    Log( LogLevel::LOGGING_INFO, function, message, errors );
}

void Logging::LogWarning( const std::string &function, const std::string &message, const std::string &errors ) {
    Log( LogLevel::LOGGING_WARNING, function, message, errors );
}

void Logging::LogError( const std::string &function, const std::string &message, const std::string &errors ) {
    Log( LogLevel::LOGGING_ERROR, function, message, errors );
}

std::string Logging::GetLogLevel( LogLevel level ) {
    switch ( level ) {
        case LOGGING_INFO:
            return "Info";
        case LOGGING_WARNING:
            return "Warning";
        case LOGGING_ERROR:
            return "Error";
    }
    return "";
}