//
//  cube.h
//  Game_Engine
//
//  Created by Craig Milby on 11/21/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CUBE_H__
#define __CUBE_H__

class Cube {
    
private:
    void GenerateCube( float width, float height, float depth );
    
public:
    Cube( unsigned int segments, int size );
    
};

#endif /* cube_h */

