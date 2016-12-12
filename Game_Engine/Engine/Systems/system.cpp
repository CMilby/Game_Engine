//
//  system.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/15/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "system.h"

void System::Execute() {
    for ( unsigned int i = 0; i < m_entities.size(); i++ ) {
        m_entities[ i ]->GetComponent( m_type )->Execute();
    }
}

void System::Execute( float p_delta ) {
    for ( unsigned int i = 0; i < m_entities.size(); i++ ) {
        m_entities[ i ]->GetComponent( m_type )->Execute( p_delta );
    }
}

void System::Execute( Entity *p_entity ) {
    for ( unsigned int i = 0; i < m_entities.size(); i++ ) {
        m_entities[ i ]->GetComponent( m_type )->Execute( p_entity );
    }
}

void System::AddEntity( Entity *p_entity ) {
    m_entities.push_back( p_entity );
}

void System::RemoveEntity( Entity *p_entity ) {
    for ( unsigned int i = 0; i < m_entities.size(); i++ ) {
        if ( m_entities[ i ] == p_entity ) {
            m_entities.erase( m_entities.begin() + i );
            break;
        }
    }
}





