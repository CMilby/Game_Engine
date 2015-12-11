//
//  mesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "input.h"
#include "utility.h"

Mesh::Mesh( const std::string &filename ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + filename );
    
    float radius = 5.0f;
    for ( unsigned int i = 0; i < m_vertices.size(); i++ ) {
        float x = m_vertices[ i ].GetX();
        float y = m_vertices[ i ].GetY();
        float z = m_vertices[ i ].GetZ();
        
        float dx = x * sqrtf( 1.0f - ( y * y / 2.0f ) - ( z * z / 2.0f ) + ( y * y * z * z / 3.0f ) );
        float dy = y * sqrtf( 1.0f - ( z * z / 2.0f ) - ( x * x / 2.0f ) + ( z * z * x * x / 3.0f ) );
        float dz = z * sqrtf( 1.0f - ( x * x / 2.0f ) - ( y * y / 2.0f ) + ( x * x * y * y / 3.0f ) );
        
        m_vertices[ i ] = Vector3<float>( dx, dy, dz ).Normalized() * radius;
    }
    
    /*std::vector<Vector3<float>> vertices;
    std::vector<Vector2<float>> uvs;
    std::vector<Vector3<float>> normals;
    IndexVBO( m_indices, vertices, uvs, normals );
    
    m_vertices = vertices;
    m_uvs = uvs;
    m_normals = normals;*/
    
    /*Vector3<float> planeNormal( Random::InRangeF( -1.0f, 1.0f ), Random::InRangeF( -1.0f, 1.0f ), Random::InRangeF( -1.0f, 1.0f ) );
    float scale = 0.995f;
    unsigned int iterations = 1000;
    
    for ( unsigned int j = 0; j < iterations; j++ ) {
        
        planeNormal = Vector3<float>( Random::InRangeF( -1.0f, 1.0f ), Random::InRangeF( -1.0f, 1.0f ), Random::InRangeF( -1.0f, 1.0f ) );
        
        for ( unsigned int i = 0; i < m_vertices.size(); i++ ) {
            float dot = m_vertices[ i ].Dot( planeNormal );
            
            if ( dot > 0 ) {
                m_vertices[ i ] /= scale;
            }
            if ( dot < 0 ) {
                m_vertices[ i ] *= scale;
            }
        }
    }*/
    
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

Mesh::~Mesh() {
    glDeleteBuffers( 1, &m_vertexBuffer );
    glDeleteBuffers( 1, &m_uvBuffer );
    glDeleteBuffers( 1, &m_normalBuffer );
    glDeleteBuffers( 1, &m_elementBuffer );
}

void Mesh::Render() const {
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
    
    if ( Input::GetDrawMode() == 0 ) {
        glDrawElements( GL_TRIANGLES, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
    } else if ( Input::GetDrawMode() == 1 ) {
        glDrawElements( GL_LINES, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
    }
}

void Mesh::LoadOBJ( const std::string &filename ) {
    
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );
    
    if ( !scene ) {
        fprintf( stderr, "Cannot find mesh" );
        return;
    }
    
    const aiMesh *model = scene->mMeshes[ 0 ];
    for ( unsigned int i = 0; i < model->mNumVertices; i++ ) {
        const aiVector3D pos = model->mVertices[ i ];
        const aiVector3D normal = model->mNormals[ i ];
        const aiVector3D texCoord = model->mTextureCoords[ 0 ][ i ];
        
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

void Mesh::IndexVBO( std::vector<unsigned short> &outIndices, std::vector<Vector3<float>> &outVertices, std::vector<Vector2<float>> &outUVs, std::vector<Vector3<float>> &outNormals ) {
    std::map<Vertex, unsigned short> vertexToOut;
    
    for ( unsigned int i = 0; i < m_vertices.size(); i++ ) {
        Vertex vertex = { m_vertices[ i ], m_uvs[ i ], m_normals[ i ] };
        
        unsigned short index;
        bool found = GetSimilarVertexIndex( vertex, vertexToOut, index );
        if ( found ) {
            outIndices.push_back( index );
        } else {
            outVertices.push_back( m_vertices[ i ] );
            outUVs.push_back( m_uvs[ i ] );
            outNormals.push_back( m_normals[ i ] );
            
            unsigned short newIndex = ( unsigned short ) outVertices.size() - 1;
            outIndices.push_back( newIndex );
            vertexToOut[ vertex ] = newIndex;
        }
    }
}

bool Mesh::GetSimilarVertexIndex( Vertex &vertex, std::map<Vertex, unsigned short> vertexToOut, unsigned short &result ) {
    std::map<Vertex, unsigned short>::iterator it = vertexToOut.find( vertex );
    if ( it == vertexToOut.end() ) {
        return false;
    } else {
        result = it->second;
        return true;
    }
}







