//
//  gBuffer.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "gBuffer.h"

#include <iostream>

#include "config.h"

GBuffer::GBuffer() {
    
}

GBuffer::~GBuffer() {
    if ( m_fbo != 0 ) {
        glDeleteFramebuffers( 1, &m_fbo );
        glDeleteTextures( 1, &m_position );
        glDeleteTextures( 1, &m_normal );
        glDeleteTextures( 1, &m_color );
        glDeleteTextures( 1, &m_light );
        glDeleteTextures( 1, &m_depth );
        glDeleteTextures( 1, &m_effect1 );
        glDeleteTextures( 1, &m_effect2 );
    }
}

void GBuffer::Init() {
    glGenFramebuffers( 1, &m_fbo );
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    
    glGenTextures( 1, &m_position );
    glGenTextures( 1, &m_normal );
    glGenTextures( 1, &m_color );
    glGenTextures( 1, &m_light );
    glGenTextures( 1, &m_depth );
    glGenTextures( 1, &m_effect1 );
    glGenTextures( 1, &m_effect2 );
    
    unsigned int width = Config::GetScreenWidth();
    unsigned int height = Config::GetScreenHeight();
    
    glBindTexture( GL_TEXTURE_2D, m_position );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Normal
    glBindTexture( GL_TEXTURE_2D, m_normal );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Color
    glBindTexture( GL_TEXTURE_2D, m_color );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Light buffer
    glBindTexture( GL_TEXTURE_2D, m_light );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Create first post process effect buffer
    glBindTexture( GL_TEXTURE_2D, m_effect1 );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Create second post process effect buffer
    glBindTexture( GL_TEXTURE_2D, m_effect1 );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    //Create depth texture
    glBindTexture( GL_TEXTURE_2D, m_depth );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE );
    
    //Attach textures to FBO
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_position, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normal, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_color, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_light, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_effect1, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, m_effect2, 0 );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0 );
    
    for ( int i = 0; i < 3; i++ ) {
        m_drawBuffers[ i ] = GL_COLOR_ATTACHMENT0 + i;
    }
    
    glDrawBuffers( 3, m_drawBuffers );
    
    //Unbind
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void GBuffer::SetDrawBuffers() {
    glDrawBuffers( 3, m_drawBuffers );
}

void GBuffer::SetDrawLight() {
    glDrawBuffer( GL_COLOR_ATTACHMENT3 );
}

void GBuffer::SetDrawEffect() {
    glDrawBuffer( GL_COLOR_ATTACHMENT4 );
}

void GBuffer::SetDrawNone() {
    glDrawBuffer( GL_NONE );
}

void GBuffer::SetReadEffect() {
    glReadBuffer( GL_COLOR_ATTACHMENT4 );
}

void GBuffer::Bind() {
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
}

void GBuffer::BindDraw() {
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_fbo );
}

void GBuffer::BindRead() {
    glBindFramebuffer( GL_READ_FRAMEBUFFER, m_fbo );
}

void GBuffer::Unbind() {
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void GBuffer::UnbindDraw() {
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
}

void GBuffer::UnbindRead() {
    glBindFramebuffer( GL_READ_FRAMEBUFFER, 0 );
}

void GBuffer::SetGeomTextures() {
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_position );
    
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, m_normal );
    
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, m_color );
    
    glActiveTexture( GL_TEXTURE3 );
    glBindTexture( GL_TEXTURE_2D, m_depth );
}


















