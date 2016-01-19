//
//  logging.h
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <string>

class Logging {
    
public:
    enum LogLevel {
        LOGGING_INFO = 0,
        LOGGING_WARNING = 1,
        LOGGING_ERROR = 2
    };
    
    template<class T>
    static void Log( LogLevel level, const std::string &function, const std::string &message, const T &errors = 0 ) {
        printf( "%s: %s - %s : %o\n", function.c_str(), GetLogLevel( level ).c_str(), message.c_str(), errors );
    }
    
    template<class T>
    static void LogInfo( const std::string &function, const std::string &message, const T &errors = 0 ) {
        Log( LOGGING_INFO, function, message, errors );
    }
    
    /*static void LogInfo( const std::string &function, const std::string &message ) {
        Log( LOGGING_INFO, function, message, 0 );
    }*/
    
    template<class T>
    static void LogWarning( const std::string &function, const std::string &message, const T &errors = 0 ) {
        Log( LOGGING_WARNING, function, message, errors );
    }
    
    template<class T>
    static void LogError( const std::string &function, const std::string &message, const T &errors = 0 ) {
        Log( LOGGING_ERROR, function, message, errors );
    }
    
private:
    Logging() {}
    
    static std::string GetLogLevel( LogLevel level );
};

#endif /* logging_h */
