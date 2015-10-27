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
    RenderableEntity m_renderRoot;
    
protected:
    inline void AddToScene( RenderableEntity* entity ) { m_renderRoot.AddEntity( entity ); }
    
public:
    Game() {}
    virtual ~Game() {}
    
    virtual void Init() {}
    void ProcessInput() const;
    void ProcessUpdate() const;
    void ProcessRender( RenderingEngine *renderingEngine ) const;
};

#endif /* game_h */
