//
//  hash_utility.hpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __HASH_UTILITY_H__
#define __HASH_UTILITY_H__

#include <cstdio>

struct EnumHash {
    
    template<typename T>
    std::size_t operator()( T t ) const {
        return static_cast<std::size_t>( t );
    }
};

#endif /* hash_utility_hpp */
