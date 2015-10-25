//
//  mesh.cpp
//  Game_Engine
//
//  Created by Craig Milby on 10/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "mesh.h"

#include "utility.h"

Mesh::Mesh( const std::string &filename ) {
    LoadOBJ( Utility::DirectoryPath() + "models/" + filename );
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    IndexVBO( m_indices, vertices, uvs, normals );
    
    m_vertices = vertices;
    m_uvs = uvs;
    m_normals = normals;
    
    glGenBuffers( 1, &m_vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof( glm::vec3 ), &m_vertices[ 0 ], GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_uvBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_uvs.size() * sizeof( glm::vec2 ), &m_uvs[ 0 ], GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_normalBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glBufferData( GL_ARRAY_BUFFER, m_normals.size() * sizeof( glm::vec3 ), &m_normals[ 0 ], GL_STATIC_DRAW );
    
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
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_uvBuffer );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_normalBuffer );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer );
    glDrawElements( GL_TRIANGLES, ( unsigned int ) m_indices.size(), GL_UNSIGNED_SHORT, ( void* ) 0 );
}

void Mesh::LoadOBJ( const std::string &filename ) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    FILE *file = fopen( filename.c_str(), "r" );
    if ( file == NULL ) {
        fprintf( stderr, "Unable to open OBJ file\n" );
        getchar();
        return;
    }
    
    while ( true ) {
        char lineHeader[ 128 ];
        int res = fscanf( file, "%s", lineHeader );
        if ( res == EOF ) {
            break;
        }
        
        if ( strcmp( lineHeader, "v" ) == 0 ) {
            glm::vec3 vertex;
            fscanf( file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            vertices.push_back( vertex );
        } else if ( strcmp( lineHeader, "vt" ) == 0 ) {
            glm::vec2 uv;
            fscanf( file, "%f %f\n", &uv.x, &uv.y );
            uv.y = -uv.y;
            uvs.push_back( uv );
        } else if ( strcmp( lineHeader, "vn" ) == 0 ) {
            glm::vec3 normal;
            fscanf( file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            normals.push_back( normal );
        } else if ( strcmp( lineHeader, "f" ) == 0 ) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[ 3 ], uvIndex[ 3 ], normalIndex[ 3 ];
            int matches = fscanf( file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if ( matches != 9 ) {
                fprintf( stderr, "File can't be read. Problem with faces." );
                return;
            }
            
            vertexIndices.push_back( vertexIndex[ 0 ] );
            vertexIndices.push_back( vertexIndex[ 1 ] );
            vertexIndices.push_back( vertexIndex[ 2 ] );
            uvIndices.push_back( uvIndex [ 0 ] );
            uvIndices.push_back( uvIndex [ 1 ] );
            uvIndices.push_back( uvIndex [ 2 ] );
            normalIndices.push_back( normalIndex[ 0 ] );
            normalIndices.push_back( normalIndex[ 1 ] );
            normalIndices.push_back( normalIndex[ 2 ] );
        } else {
            char commentBuffer[ 1000 ];
            fgets( commentBuffer, 1000, file );
        }
    }
    
    for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) {
        unsigned int vertexIndex = vertexIndices [ i ];
        unsigned int uvIndex = uvIndices[ i ];
        unsigned int normalIndex = normalIndices[ i ];
        
        glm::vec3 vertex = vertices[ vertexIndex - 1 ];
        glm::vec2 uv = uvs[ uvIndex - 1 ];
        glm::vec3 normal = normals[ normalIndex - 1 ];
        
        m_vertices.push_back( vertex );
        m_uvs.push_back( uv );
        m_normals.push_back( normal );
    }
}

void Mesh::IndexVBO( std::vector<unsigned short> &outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals ) {
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







