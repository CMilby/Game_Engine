//
//  utility.cpp
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "utility.h"

std::string Utility::DirectoryPath() {

#ifdef __APPLE__
    return "/Users/Craig/Xcode/Game_Engine/Game_Engine/Resources/";
#endif
#ifdef _WIN32
    return "C:\\Users\\Craig";
#endif
    return "";
}

bool Utility::EndsWith( const std::string &pStr, const std::string &pEnding ) {
	if ( pStr.length() >= pEnding.length() ) {
		return ( 0 == pStr.compare( pStr.length() - pEnding.length(), pEnding.length(), pEnding ) );
	}
	return false;
}

int Utility::LastIndexOf( const std::string &pStr, char pDelim ) {
	for ( int i = ( int ) pStr.size() - 1; i >= 0; i-- ) {
		if ( pStr[ i ] == pDelim ) {
			return i;
		}
	}
	return -1;
}

std::string Utility::ToUpper( const std::string &pStr ) {
	std::string ret = "";
	for ( unsigned int i = 0; i < pStr.size(); i++ ) {
		ret += toupper( pStr[ i ] );
	}
	return ret;
}







