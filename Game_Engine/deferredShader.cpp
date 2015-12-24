//
//  deferredShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/22/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "deferredShader.h"

DeferredShader::DeferredShader() {
    m_gBuffer = new GBuffer();
    m_geomShader = new GeometryShader();
    m_pointLightShader = new PointLightShader();
    m_dirLightShader = new DirectionalLightShader();
    m_nullShader = new NullShader();
}

DeferredShader::~DeferredShader() {
    if ( m_gBuffer ) delete m_gBuffer;
    if ( m_geomShader ) delete m_geomShader;
    if ( m_pointLightShader ) delete m_pointLightShader;
    if ( m_dirLightShader ) delete m_dirLightShader;
    if ( m_nullShader ) delete m_nullShader;
}

void DeferredShader::Init() {
    m_gBuffer->Init();
    
    m_geomShader->Init();
    m_geomShader->Bind();
    m_geomShader->Uniform1i( "gColorMap", COLOR_TEXTURE_UNIT_INDEX );
    
    m_pointLightShader->Init();
    m_pointLightShader->Bind();
    m_pointLightShader->Uniform1i( "gPositionMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION );
    m_pointLightShader->Uniform1i( "gColorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE );
    m_pointLightShader->Uniform1i( "gNormalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL );
    m_pointLightShader->Uniform2f( "gScreenSize", Config::GetScreenWidth(), Config::GetScreenHeight() );
    
    m_dirLightShader->Init();
    m_dirLightShader->Bind();
    m_dirLightShader->Uniform1i( "gPositionMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION );
    m_dirLightShader->Uniform1i( "gColorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE );
    m_dirLightShader->Uniform1i( "gNormalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL );
    m_dirLightShader->Uniform2f( "gScreenSize", Config::GetScreenWidth(), Config::GetScreenHeight() );
    m_dirLightShader->UniformMatrix4f( "gWVP", Matrix4<float>() );
    m_dirLightShader->SetDirectionalLight( DirectionalLight( BaseLight( Vector3<float>( 0, 0, 0 ), 0.1f, 0.5f ), Vector3<float>( 1.0f, 0.0f, 0.0f ) ) );
    
    m_nullShader->Init();
    
    m_quad = new Mesh( "quad.obj" );
    m_sphere = new Mesh( "sphere.obj" );
}

void DeferredShader::Render( const Camera &camera, const RenderableEntity &entity ) {
    m_gBuffer->StartFrame();
    GeometryPass( camera, entity );
    
    glEnable( GL_STENCIL_TEST );
    for ( unsigned int i = 0; m_pointLights.size(); i++ ) {
        StencilPass( i, camera );
        PointLightPass( i, camera );
    }
    glDisable( GL_STENCIL_TEST );
    
    DirectionalLightPass( camera );
    FinalPass();
}

void DeferredShader::GeometryPass( const Camera &camera, const RenderableEntity &entity ) {
    m_geomShader->Bind();
    m_gBuffer->BindGeom();
    
    glDepthMask( GL_TRUE );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );
    
    m_geomShader->UniformMatrix4f( "gWVP", Transform::GetProjection() * camera.GetView() * entity.GetModelMatrix() );
    m_geomShader->UniformMatrix4f( "gWorld", entity.GetModelMatrix() );
    
    m_geomShader->Enable();
    entity.GetMesh().Render();
    m_geomShader->Disable();
    
    glDepthMask( GL_FALSE );
}

void DeferredShader::StencilPass( unsigned int index, const Camera &camera ) {
    m_nullShader->Bind();
    m_gBuffer->BindStencil();
    
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glClear( GL_STENCIL_BUFFER_BIT );
    
    glStencilFunc( GL_ALWAYS, 0, 0 );
    
    glStencilOpSeparate( GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP );
    glStencilOpSeparate( GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP );
    
    float boxScale = CalcPointLightBSphere( m_pointLights[ index ] );
    m_nullShader->UniformMatrix4f( "gWVP", Transform::GetProjection() * camera.GetView() * Matrix4<float>().Model( m_pointLights[ index ].m_position, Vector3<float>( boxScale, boxScale, boxScale ) ) );
    
    m_nullShader->Enable();
    m_sphere->Render();
    m_nullShader->Disable();
}

void DeferredShader::PointLightPass( unsigned int index, const Camera &camera ) {
    m_gBuffer->BindLight();
    
    m_pointLightShader->Bind();
    m_pointLightShader->UniformVector3f( "gEyeWorldPos", camera.GetPosition() );
    
    glStencilFunc( GL_NOTEQUAL, 0, 0xFF );
    
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc( GL_ONE, GL_ONE );
    
    glEnable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    
    float boxScale = CalcPointLightBSphere( m_pointLights[ index ] );
    m_pointLightShader->UniformMatrix4f( "gWVP", Transform::GetProjection() * camera.GetView() * Matrix4<float>().Model( m_pointLights[ index ].m_position, Vector3<float>( boxScale, boxScale, boxScale ) ) );
    m_pointLightShader->SetPointLight( m_pointLights[ index ] );
    
    m_pointLightShader->Enable();
    m_sphere->Render();
    m_pointLightShader->Disable();
    
    glCullFace( GL_BACK );
    glDisable( GL_BLEND );
}

void DeferredShader::DirectionalLightPass( const Camera &camera ) {
    m_gBuffer->BindLight();
    
    m_dirLightShader->Bind();
    m_dirLightShader->UniformVector3f( "gEyeWorldPos", camera.GetPosition() );
    
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc( GL_ONE, GL_ONE );
    
    m_dirLightShader->Enable();
    m_quad->Render();
    m_dirLightShader->Disable();
    
    glDisable( GL_BLEND );
}

void DeferredShader::FinalPass() {
    m_gBuffer->BindFinal();
    glBlitFramebuffer( 0, 0, Config::GetScreenWidth(), Config::GetScreenHeight(), 0, 0, Config::GetScreenWidth(), Config::GetScreenHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR );
}

float DeferredShader::CalcPointLightBSphere( const PointLight &light ) {
    float maxChannel = light.m_baseLight.m_color.Max();
    float ret = ( -light.m_atten.m_linear + sqrtf( light.m_atten.m_linear * light.m_atten.m_linear - 4 * light.m_atten.m_exponent * ( light.m_atten.m_exponent - 256 * maxChannel * light.m_baseLight.m_diffuseIntensity ) ) ) / 2 * light.m_atten.m_exponent;
    return ret;
}



















