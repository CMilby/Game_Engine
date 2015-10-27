//
//  coreEngine.h
//  Game_Engine
//
//  Created by Craig Milby on 10/25/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef __CORE_ENGINE_H__
#define __CORE_ENGINE_H__

#include "game.h"
#include "input.h"
#include "renderingEngine.h"
#include "text2d.h"
#include "window.h"

class CoreEngine {
    
private:
    bool m_isRunning;
    
    RenderingEngine *m_renderingEngine;
    Text2D *m_text2d;
    
    Game *m_game;
    Window *m_window;
    
public:
    CoreEngine( Window *window, Game *game );
    virtual ~CoreEngine();
    
    void Init();
    void Start();
    void Stop();
};

#endif /* coreEngine_h */
