//
//  core_engine.h
//  Game_Engine_New
//
//  Created by Craig Milby on 10/16/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __CORE_ENGINE_H__
#define __CORE_ENGINE_H__

#include "game.h"
#include "window.h"

class CoreEngine {
    
private:
    Window *m_window;
    Game *m_game;
    Entity *m_mainCamera;
    
    bool m_isRunning;
    
public:
    CoreEngine( Window *p_window, Game *p_game );
    virtual ~CoreEngine();
    
    void Init();
    
    void Start();
    void Stop();
};

#endif /* core_engine_h */
