//
//  renderer.h
//  Game_Engine
//
//  Created by Craig Milby on 2/18/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __RENDER_FRAMEWORK_H__
#define __RENDER_FRAMEWORK_H__

#include "drawMode.h"

namespace RenderFramework {

    void InitRenderer();
    void ClearScreen();
	
	void SetDrawMode( const DrawMode &mode );
};

#endif /* renderer_h */
