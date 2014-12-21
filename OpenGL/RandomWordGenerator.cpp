//
//  RandomWordGenerator.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 10/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include "RandomWordGenerator.h"

#include <fstream>
#include <utility>
#include <random>
#include <algorithm>
#include <math.h>

using namespace Invocat::Tools;

RandomWordGenerator::RandomWordGenerator()
{
    
}

RandomWordGenerator::RandomWordGenerator( std::string database )
{
    wordDatabase = ReadFile( database );
}

std::vector<std::string> RandomWordGenerator::ReadFile( std::string data ) const
{
    std::ifstream stream( data );
    
    std::vector<std::string> dataSplitted;
    std::string word;
    
    if ( stream ) {
        while ( std::getline( stream, word ) ) {
            dataSplitted.push_back( word );
        }
    } else {
        fprintf( stderr, "File doesn't handled by the generator." );
    }
    
    return dataSplitted;
}

void RandomWordGenerator::Init()
{
    ComputeTransitions();
}

const std::string RandomWordGenerator::GenerateWord() const
{
    std::string wordGenerated;
    
    std::string state = "^^";
    std::string nextState;
    
    while ( state.find( "$" ) == std::string::npos ) {
        nextState = BuildWord( state );
        wordGenerated += nextState;
        state = state.substr( state.length() - 2 ) + nextState;
    }
    
    std::replace( wordGenerated.begin(), wordGenerated.end(), '\\', char() );
    
    if (wordGenerated.length() > 10 ) {
        wordGenerated = wordGenerated.substr( 0, 11 );
    }
    
    return wordGenerated.substr( 0, wordGenerated.length() - 1 );
}

void RandomWordGenerator::ComputeTransitions()
{
    for ( auto word : wordDatabase ) {
        std::string prev = "^^";
        std::string next;
        
        for ( int letter_i = 0; letter_i < word.length(); letter_i++ ) {
            next = word.substr( letter_i, 1 );
            UpdateTransitions( prev, next );
            prev = prev.substr( prev.length() - 2 ) + next;
        }
        next = "$";
        UpdateTransitions( prev, next );
    }
}

void RandomWordGenerator::UpdateTransitions( const std::string &prev, const std::string &next )
{
    std::string transition = prev + next;
    
    std::map<std::string, unsigned int>::iterator it = transitions.find( transition );
    
    if ( it != transitions.end() ) {
        transitions[transition]++;
    } else {
        transitions[transition] = 1;
    }
}

const std::string RandomWordGenerator::BuildWord( const std::string state ) const // rename findnextstate
{
    std::vector<std::pair<std::string, unsigned int>> cumulativeDistFunc;
    unsigned int sum = 0;
    
    for ( auto pair : transitions ) {
        std::string transition = pair.first;
        if ( transition.substr( 0, state.length() ) == state ) {
            std::string nextState = transition.substr( state.length() );
            sum += pair.second;
            
            cumulativeDistFunc.push_back(std::pair<std::string, unsigned int>( nextState, sum ) );
        }
    }
    
    std::random_device rd;
    std::mt19937 generator( rd() );
    std::uniform_real_distribution<float> distribution( 0.0f, 1.0f );
    
    int random = floor( distribution( generator ) * sum );
    
    for ( auto pair : cumulativeDistFunc ) {
        if ( random <= pair.second ) {
            return pair.first;
        }
    }
    
    if ( cumulativeDistFunc.size() > 0 ) {
        return cumulativeDistFunc.back().first;
    }
    
    return wordDatabase[random] + "$";
}