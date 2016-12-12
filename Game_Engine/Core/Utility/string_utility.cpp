//
//  string_utility.cpp
//  Game_Engine_New
//
//  Created by Craig Milby on 10/14/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "string_utility.h"

#include <sstream>

bool StringUtility::EndsWith( const std::string &pStr, const std::string &pEnding ) {
    if ( pStr.length() >= pEnding.length() ) {
        return ( 0 == pStr.compare( pStr.length() - pEnding.length(), pEnding.length(), pEnding ) );
    }
    return false;
}

int StringUtility::LastIndexOf( const std::string &pStr, char pDelim ) {
    for ( int i = ( int ) pStr.size() - 1; i >= 0; i-- ) {
        if ( pStr[ i ] == pDelim ) {
            return i;
        }
    }
    return -1;
}

std::string StringUtility::ToUpper( const std::string &pStr ) {
    std::string ret = "";
    for ( unsigned int i = 0; i < pStr.size(); i++ ) {
        ret += toupper( pStr[ i ] );
    }
    return ret;
}

std::vector<std::string> StringUtility::Split( const std::string &pStr, char pDelim, std::vector<std::string> &pElems ) {
    std::stringstream ss( pStr );
    std::string item;
    while ( std::getline( ss, item, pDelim ) ) {
        pElems.push_back( item );
    }
    return pElems;
}


std::vector<std::string> StringUtility::Split( const std::string &pStr, char pDelim ) {
    std::vector<std::string> elems;
    Split( pStr, pDelim, elems );
    return elems;
}

void StringUtility::LTrim( std::string &pStr ) {
    pStr.erase( pStr.begin(), std::find_if( pStr.begin(), pStr.end(), std::not1( std::ptr_fun<int, int>( std::isspace ) ) ) );
}

void StringUtility::RTrim( std::string &pStr ) {
    pStr.erase( std::find_if( pStr.rbegin(), pStr.rend(), std::not1( std::ptr_fun<int, int>( std::isspace ) ) ).base(), pStr.end() );
}

void StringUtility::Trim( std::string &pStr ) {
    StringUtility::LTrim( pStr );
    StringUtility::RTrim( pStr );
}
