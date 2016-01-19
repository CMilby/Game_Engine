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
#include "profiler.h"
#include "renderingEngine.h"
#include "textShader.h"
#include "window.h"

class CoreEngine {
    
private:
    bool m_isRunning;
    
    RenderingEngine *m_renderingEngine;
    TextShader *m_textShader;
    
    Game *m_game;
    Window *m_window;
    
    Profiler *m_profiler;
    
public:
    CoreEngine( Window *window, Game *game );
    virtual ~CoreEngine();
    
    void Init();
    void Start();
    void Stop();
};

#endif /* coreEngine_h */
