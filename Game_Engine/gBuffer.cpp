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
    
}

void GBuffer::Init() {
    glGenTextures( 1, &m_gBuffer );
    glBindFramebuffer( GL_FRAMEBUFFER, m_gBuffer );
    
    glGenTextures( 1, &m_position );
    glBindTexture( GL_TEXTURE_2D, m_position );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB16F, Config::GetScreenWidth(), Config::GetScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_position, 0 );
    
    glGenTextures( 1, &m_normal );
    glBindTexture( GL_TEXTURE_2D, m_normal );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB16F, Config::GetScreenWidth(), Config::GetScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normal, 0 );
    
    glGenTextures( 1, &m_specular );
    glBindTexture( GL_TEXTURE_2D, m_specular );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Config::GetScreenWidth(), Config::GetScreenHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_specular, 0 );
   
    GLuint attachments[ 3 ] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers( 3, attachments );
    
    glGenRenderbuffers( 1, &m_rboDepth );
    glBindRenderbuffer( GL_RENDERBUFFER, m_rboDepth );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Config::GetScreenWidth(), Config::GetScreenHeight() );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rboDepth );
    
    if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ) {
        fprintf( stderr, "GBuffer: Framebuffer errror\n" );
    }
    
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

















