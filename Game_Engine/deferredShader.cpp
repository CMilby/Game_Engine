//
//  deferredShader.cpp
//  Game_Engine
//
//  Created by Craig Milby on 12/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "deferredShader.h"

DeferredShader::DeferredShader() {
    m_geomPass = new GeometryPassTech();
    m_pointLightPass = new PointLightPassTech();
    m_dirLightPass = new DirLightPassTech();
    m_nullTech = new NullTech();
    m_gBuffer = new GBuffer();
}

DeferredShader::~DeferredShader() {
    
}

void DeferredShader::Init() {
    m_gBuffer->Init( 1024, 768 );
    
    m_geomPass->Init();
    m_geomPass->Bind();
    m_geomPass->SetColorTextureUint( COLOR_TEXTURE_UNIT_INDEX );
    
    m_pointLightPass->Init();
    m_pointLightPass->Bind();
    m_pointLightPass->SetPositionTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_POSITION );
    m_pointLightPass->SetColorTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE );
    m_pointLightPass->SetNormalTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL );
    m_pointLightPass->SetScreenSize( 1024, 768 );
    
    m_dirLightPass->Init();
    m_dirLightPass->Bind();
    m_dirLightPass->SetPositionTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_POSITION );
    m_dirLightPass->SetColorTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE );
    m_dirLightPass->SetNormalTextureUnit( GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL );
    m_dirLightPass->SetDirectionalLight( DirectionalLight( BaseLight(), Vector3<float>( 0, 0, -10 ) ) );
    m_dirLightPass->SetScreenSize( 1024, 768 );
    m_dirLightPass->SetWVP( Matrix4<float>().InitIdentity() );
    
    m_nullTech->Init();
    
    m_sphere = new RenderableEntity( new Mesh( "sphere.obj" ), new Material( new Texture( "test.png", TYPE_PNG ) ) );
    m_quad = new RenderableEntity( new Mesh( "quad.obj" ), new Material( new Texture( "test.png", TYPE_PNG ) ) );
}

void DeferredShader::UpdateUniforms(const Matrix4<float> &world, const Matrix4<float> &projected, const Camera &camera, const Material &material, const Mesh &mesh ) {
    
    m_gBuffer->StartFrame();
    GeometryPass( world, projected, mesh );
    
    glEnable( GL_STENCIL_TEST );
    for ( unsigned int i = 0; i < m_pointLights.size(); i++ ) {
        StencilPass( i, camera );
        PointLightPass( i, camera );
    }
    
    glDisable( GL_STENCIL_TEST );
    
    DirectionaLightPass( camera.GetPosition() );
    FinalPass();
}

void DeferredShader::GeometryPass( const Matrix4<float> &world, const Matrix4<float> &projected, const Mesh &mesh ) {
    m_geomPass->Bind();
    m_gBuffer->BindGeom();
    
    glDepthMask( GL_TRUE );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable( GL_BLEND );
    
    m_geomPass->SetWVP( projected );
    m_geomPass->SetWorldMatrix( world );
    
    mesh.Render();
    
    glDepthMask( GL_FALSE );
}

void DeferredShader::StencilPass( unsigned int index, const Camera &camera ) {
    m_nullTech->Bind();
    m_gBuffer->BindStencil();
    
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glClear( GL_STENCIL_BUFFER_BIT );
    
    glStencilFunc( GL_ALWAYS, 0, 0 );
    glStencilOpSeparate( GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP );
    glStencilOpSeparate( GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP );
    
    float boxScale = CalcPointLightSphere( *m_pointLights[ index ] );
    m_sphere->GetTransform()->SetScale( Vector3<float>( boxScale, boxScale, boxScale ) );
    
    m_nullTech->SetWVP( Transform::GetProjection() * camera.GetView() * m_sphere->GetModelMatrix() );
    m_sphere->GetMesh().Render();
}

void DeferredShader::PointLightPass( unsigned int index, const Camera &camera ) {
    m_gBuffer->BindLight();
    
    m_pointLightPass->Bind();
    m_pointLightPass->SetEyeWorldPos( camera.GetPosition() );
    
    glStencilFunc( GL_NOTEQUAL, 0, 0xFF );
    
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc( GL_ONE, GL_ONE );
    
    glEnable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    
    float boxScale = CalcPointLightSphere( *m_pointLights[ index ] );
    m_sphere->GetTransform()->SetScale( Vector3<float>( boxScale, boxScale, boxScale ) );
    
    m_pointLightPass->SetWVP( Transform::GetProjection() * camera.GetView() * m_sphere->GetModelMatrix() );
    m_pointLightPass->SetPointLight( *m_pointLights[ index ] );
    m_sphere->GetMesh().Render();
    
    glCullFace( GL_BACK );
    glDisable( GL_BLEND );
}

void DeferredShader::DirectionaLightPass( const Vector3<float> &eyePos ) {
    m_gBuffer->BindLight();
    
    m_dirLightPass->Bind();
    m_dirLightPass->SetEyeWorldPos( eyePos );
    
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc( GL_ONE, GL_ONE );
    
    m_quad->GetMesh().Render();
    
    glDisable( GL_BLEND );
}

void DeferredShader::FinalPass() {
    int width = 1024;
    int height = 768;
    
    m_gBuffer->BindFinal();
    glBlitFramebuffer( 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR );
}

float DeferredShader::CalcPointLightSphere( const PointLight &light ) {
    float maxChannel = fmaxf( fmax( light.m_baseLight.m_color.GetX(), light.m_baseLight.m_color.GetY() ), light.m_baseLight.m_color.GetZ() );
    float ret = ( -light.m_atten.m_linear + sqrtf( light.m_atten.m_linear * light.m_atten.m_linear - 4 * light.m_atten.m_exponent * ( light.m_atten.m_exponent - 256 * maxChannel * light.m_baseLight.m_diffuseIntensity ) ) ) / 2.0f * light.m_atten.m_exponent;
    return ret;
}

















