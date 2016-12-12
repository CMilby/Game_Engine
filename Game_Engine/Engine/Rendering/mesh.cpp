//
//  mesh.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "file_utility.h"

Mesh::Mesh() {
    std::vector<unsigned int> myIndices;
    std::vector<Vector3f> myVertices;
    std::vector<Vector2f> myUVs;
    std::vector<Vector3f> myNormals;
    
    LoadOBJ( "cube.obj", myIndices, myVertices, myUVs, myNormals );
    GenerateBuffers( myIndices, myVertices, myUVs, myNormals, false );
}

Mesh::Mesh( const std::string &pFilename, bool pInstance ) : m_filename( pFilename ) {
    std::vector<unsigned int> myIndices;
    std::vector<Vector3f> myVertices;
    std::vector<Vector2f> myUVs;
    std::vector<Vector3f> myNormals;
    
    LoadOBJ( pFilename, myIndices, myVertices, myUVs, myNormals );
    GenerateBuffers( myIndices, myVertices, myUVs, myNormals, pInstance );
}

Mesh::Mesh( const std::vector<unsigned int> &p_indices, const std::vector<Vector3f> &p_vertices, const std::vector<Vector2f> &p_uvs, const std::vector<Vector3f> &p_normals ) {
    m_entries.push_back( MeshEntry() );
    m_entries[ 0 ].m_baseIndex = 0;
    m_entries[ 0 ].m_baseVertex = 0;
    m_entries[ 0 ].m_numIndices = ( unsigned int ) p_indices.size();
    m_entries[ 0 ].m_materialIndex = 0xFFFFFFFF;
    
    GenerateBuffers( p_indices, p_vertices, p_uvs, p_normals, false );
}

Mesh::~Mesh() {
    glDeleteBuffers( NUM_BUFFERS, m_buffers );
    glDeleteVertexArrays( 1, &m_vao );
}

void Mesh::Render() {
    glBindVertexArray( m_vao );
    
    for ( unsigned int i = 0; i < m_entries.size(); i++ ) {
        glDrawElementsBaseVertex( GL_TRIANGLES, m_entries[ i ].m_numIndices, GL_UNSIGNED_INT, ( void* ) ( sizeof( unsigned short ) * m_entries[ i ].m_baseIndex ), m_entries[ i ].m_baseVertex );
    }
    
    glBindVertexArray( 0 );
}

void Mesh::Render( int pInstances, const Matrix4f* pWVPMats, const Matrix4f* pWorldMats ) {
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ WVP_MAT_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Matrix4f ) * pInstances, pWVPMats, GL_DYNAMIC_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ WORLD_MAT_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Matrix4f ) * pInstances, pWorldMats, GL_DYNAMIC_DRAW );
    
    glBindVertexArray( m_vao );
    
    for ( unsigned int i = 0; i < m_entries.size(); i++ ) {
        glDrawElementsInstancedBaseVertex( GL_TRIANGLES, m_entries[ i ].m_numIndices, GL_UNSIGNED_INT, ( void* ) ( sizeof( unsigned short ) * m_entries[ i ].m_baseIndex ), pInstances, m_entries[ i ].m_baseVertex );
    }
    
    glBindVertexArray( 0 );
}

void Mesh::LoadOBJ( const std::string &pFilename, std::vector<unsigned int> &pIndices, std::vector<Vector3f> &pVertices, std::vector<Vector2f> &pUVs, std::vector<Vector3f> &pNormals ) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( ( FileUtility::GetModelDirectory() + pFilename ).c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );
    
    if ( !scene ) {
        fprintf( stderr, "Cannot find mesh %s\n", pFilename.c_str() );
        return;
    }
    
    m_entries.resize( scene->mNumMeshes );
    
    unsigned int myNumVertices = 0;
    unsigned int myNumIndices = 0;
    for ( unsigned int i = 0; i < m_entries.size(); i++ ) {
        m_entries[ i ].m_materialIndex = 0xFFFFFFFF;
        m_entries[ i ].m_numIndices = scene->mMeshes[ i ]->mNumFaces * 3;
        m_entries[ i ].m_baseVertex = myNumVertices;
        m_entries[ i ].m_baseIndex = myNumIndices;
        
        myNumVertices += scene->mMeshes[ i ]->mNumVertices;
        myNumIndices += scene->mMeshes[ i ]->mNumFaces;
    }
    
    for ( unsigned int i = 0; i < m_entries.size(); i++ ) {
        InitMesh( scene->mMeshes[ i ], pIndices, pVertices, pUVs, pNormals );
    }
}

void Mesh::InitMesh( const aiMesh *pMesh, std::vector<unsigned int> &pIndices, std::vector<Vector3f> &pVertices, std::vector<Vector2f> &pUVs, std::vector<Vector3f> &pNormals ) {
    const aiVector3D Zero3D( 0.0f, 0.0f, 0.0f );
    
    for ( unsigned int i = 0; i < pMesh->mNumVertices; i++ ) {
        const aiVector3D *pos = &( pMesh->mVertices[ i ] );
        const aiVector3D *normal = &( pMesh->mNormals[ i ] );
        
        const aiVector3D texCoord = pMesh->HasTextureCoords( 0 ) ? pMesh->mTextureCoords[ 0 ][ i ] : aiVector3D( 0, 0, 0 );
        
        pVertices.push_back( Vector3f( pos->x, pos->y, pos->z ) );
        pNormals.push_back( Vector3f( normal->x, normal->y, normal->z ) );
        pUVs.push_back( Vector2f( texCoord.x, texCoord.y ) );
    }
    
    for ( unsigned int i = 0; i < pMesh->mNumFaces; i++ ) {
        const aiFace &face = pMesh->mFaces[ i ];
        
        pIndices.push_back( face.mIndices[ 0 ] );
        pIndices.push_back( face.mIndices[ 1 ] );
        pIndices.push_back( face.mIndices[ 2 ] );
    }
}

void Mesh::GenerateBuffers( const std::vector<unsigned int> &pIndices, const std::vector<Vector3f> &pVertices, const std::vector<Vector2f> pUVs, const std::vector<Vector3f> pNormals, bool pInstance ) {
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray( m_vao );
    
    glGenBuffers( NUM_BUFFERS, m_buffers );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ VERTEX_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, pVertices.size() * sizeof( Vector3f ), &pVertices[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ TEX_COORD_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, pUVs.size() * sizeof( Vector2f ), &pUVs[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 1 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ NORMAL_BUFFER ] );
    glBufferData( GL_ARRAY_BUFFER, pNormals.size() * sizeof( Vector3f ), &pNormals[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 2 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffers[ INDEX_BUFFER ] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof( unsigned int ), &pIndices[ 0 ], GL_STATIC_DRAW );
    
    if ( pInstance ) {
        glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ WVP_MAT_BUFFER ] );
        for ( unsigned int i = 0; i < 4; i++ ) {
            glEnableVertexAttribArray( 4 + i );
            glVertexAttribPointer( 4 + i, 4, GL_FLOAT, GL_FALSE, sizeof ( Matrix4f ), ( void* ) ( sizeof( GLfloat ) * i * 4 ) );
            glVertexAttribDivisor( 4 + i, 1 );
        }
        
        glBindBuffer( GL_ARRAY_BUFFER, m_buffers[ WORLD_MAT_BUFFER ] );
        for ( unsigned int i = 0; i < 4; i++ ) {
            glEnableVertexAttribArray( 7 + i );
            glVertexAttribPointer( 7 + i, 4, GL_FLOAT, GL_FALSE, sizeof( Matrix4f ), ( void* ) ( sizeof( GLfloat ) * i * 4 ) );
            glVertexAttribDivisor( 7 + i, 1 );
        }
    }
    
    glBindVertexArray( 0 );
}

Mesh& Mesh::operator=( const Mesh &p_mesh ) {
    m_filename = p_mesh.m_filename;
    for ( int i = 0; i < 6; i++ ) {
        m_buffers[ i ] = p_mesh.m_buffers[ i ];
    }
    
    m_vao = p_mesh.m_vao;
    m_entries = p_mesh.m_entries;
    return *this;
}


