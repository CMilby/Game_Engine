//
//  utility.h
//  Game_Engine_Test
//
//  Created by Craig Milby on 3/1/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>

namespace Utility {
    
    std::string DirectoryPath();
	
	bool EndsWith( const std::string &pStr, const std::string &pEnding );
	int LastIndexOf( const std::string &pStr, char pDelim );
	
	std::string ToUpper( const std::string &pStr );
}

#endif /* utility_h */
