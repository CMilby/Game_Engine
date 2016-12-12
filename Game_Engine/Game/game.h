//
//  game.hpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __GAME_H__
#define __GAME_H__

#include "entity.h"

class Game {
    
private:
    Entity *m_root;
    Entity *m_camera;
    
protected:
    void AddToScene( Entity *p_entity );
    void SetCamera( Entity *p_camera );
    
public:
    Game();
    virtual ~Game();

    virtual void Init();
    
    inline Entity* GetCamera() const { return m_camera; }
};

#endif /* game_hpp */
