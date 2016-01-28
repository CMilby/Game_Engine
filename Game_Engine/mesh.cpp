//
//  mesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "mesh.h"

#include <cassert>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "input.h"
#include "utility.h"

Mesh::Mesh() {
    
}

Mesh::Mesh( const std::string &filename ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + filename );
    GenerateBuffers();
}

Mesh::~Mesh() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_uvBuffer );
    glDeleteBuffers( 1, &m_normalBuffer );
    glDeleteBuffers( 1, &m_elementBuffer );
}

void Mesh::Render() const {
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 1 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    glEnableVertexAttribArray( 2 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
    
    if ( Input::GetDrawMode() == 0 ) {
        glDrawElements( GL_TRIANGLES, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
    } else if ( Input::GetDrawMode() == 1 ) {
        glDrawElements( GL_LINE_STRIP, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
    }
    
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
}

void Mesh::LoadOBJ( const std::string &filename ) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );
    
    if ( !scene ) {
        fprintf( stderr, "Cannot find mesh %s\n", filename.c_str() );
        return;
    }
    
    const aiMesh *model = scene->mMeshes[ 0 ];
    for ( unsigned int i = 0; i < model->mNumVertices; i++ ) {
        const aiVector3D pos = model->mVertices[ i ];
        const aiVector3D normal = model->mNormals[ i ];
      
        const aiVector3D texCoord = model->HasTextureCoords( 0 ) ? model->mTextureCoords[ 0 ][ i ] : aiVector3D( 0, 0, 0 );
        
        m_vertices.push_back( Vector3<float>( pos.x, pos.y, pos.z ) );
        m_normals.push_back( Vector3<float>( normal.x, normal.y, normal.z ) );
        m_uvs.push_back( Vector2<float>( texCoord.x, texCoord.y ) );
    }
    
    for ( unsigned int i = 0; i < model->mNumFaces; i++ ) {
        const aiFace &face = model->mFaces[ i ];
        
        m_indices.push_back( face.mIndices[ 0 ] );
        m_indices.push_back( face.mIndices[ 1 ] );
        m_indices.push_back( face.mIndices[ 2 ] );
    }
}

void Mesh::GenerateBuffers() {
    glGenBuffers( 1, &m_vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof( Vector3<float> ), &m_vertices[ 0 ], GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_uvBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_uvs.size() * sizeof( Vector2<float> ), &m_uvs[ 0 ], GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_normalBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_normals.size() * sizeof( Vector3<float> ), &m_normals[ 0 ], GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_elementBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof( unsigned short ), &m_indices[ 0 ], GL_STATIC_DRAW );
}


