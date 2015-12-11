//
//  gBuffer.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "gBuffer.h"

#include "utility.h"

GBuffer::GBuffer() {
    m_fbo = 0;
    m_depthTexture = 0;
    ZERO_MEM( m_textures );
}

GBuffer::~GBuffer() {
    if ( m_fbo != 0 ) {
        glDeleteFramebuffers( 1, &m_fbo );
    }
    
    if ( m_textures[ 0 ] != 0 ) {
        glDeleteTextures( ARRAY_SIZE_IN_ELEMENTS( m_textures ), m_textures );
    }
    
    if ( m_depthTexture != 0 ) {
        glDeleteTextures( 1, &m_depthTexture );
    }
}

void GBuffer::Init( unsigned int width, unsigned int height ) {
    glGenFramebuffers( 1, &m_fbo );
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbo );
    
    glGenTextures( ARRAY_SIZE_IN_ELEMENTS( m_textures ), m_textures );
    glGenTextures( 1, & m_depthTexture );
    
    for ( unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS( m_textures ); i++ ) {
        glBindTexture( GL_TEXTURE_2D, m_textures[ i ] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[ i ], 0 );
    }
    
    glBindTexture( GL_TEXTURE_2D, m_depthTexture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0 );

    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0,
                             GL_COLOR_ATTACHMENT1,
                             GL_COLOR_ATTACHMENT2 };
    glDrawBuffers( ARRAY_SIZE_IN_ELEMENTS( drawBuffers ), drawBuffers );
    
    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    if ( status != GL_FRAMEBUFFER_COMPLETE ) {
        fprintf( stderr, "Framebuffer Error: 0x%x\n", status );
        return;
    }
    
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
}

void GBuffer::BindWrite() {
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_fbo );
}

void GBuffer::BindRead() {
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
    
    for ( unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS( m_textures ); i++ ) {
        glActiveTexture( GL_TEXTURE0 + i );
        glBindTexture( GL_TEXTURE_2D, m_textures[ GBUFFER_TEXTURE_TYPE_POSITION + i ] );
    }
}












