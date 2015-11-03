//
//  game.h
//  Game_Engine
//
//  Created by Craig Milby on 10/27/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __GAME_H__
#define __GAME_H__

#include "entity.h"
#include "renderingEngine.h"

class Game {
  
private:
    Entity m_root;
    
protected:
    inline void AddToScene( Entity* entity ) { m_root.AddChild( entity ); }
    
public:
    Game() {}
    virtual ~Game() {}
    
    virtual void Init();
    void ProcessInput( float delta );
    void ProcessUpdate( float delta );
    void ProcessRender( RenderingEngine *renderingEngine );
};

#endif /* game_h */
