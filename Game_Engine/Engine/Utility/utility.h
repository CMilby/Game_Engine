//
//  utility.h
//  Game_Engine
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>
#include <vector>

namespace Utility {
    
    std::string DirectoryPath();
	
	bool EndsWith( const std::string &pStr, const std::string &pEnding );
	int LastIndexOf( const std::string &pStr, char pDelim );
	
	std::string ToUpper( const std::string &pStr );
	std::vector<std::string> Split( const std::string &pStr, char pDelim );
	std::vector<std::string> Split( const std::string &pStr, char pDelim, std::vector<std::string> &pElems );

	int StringToKey( const std::string &pKey );
	int StringToButton( const std::string &pButton );
	
	void Trim( std::string &pStr );
	void LTrim( std::string &pStr );
	void RTrim( std::string &pStr) ;
	
	std::string KeyToString( int pKey );
	std::string ButtonToString( int pButton );
}

#endif /* utility_h */