//
//  cbShader.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 13/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include "cbShader.h"
#include <fstream>
#include <vector>

using namespace Invocat::Core;

cbShader::cbShader()
{
    vertexShaderFile = "Resources/Shaders/simpleVS.vert";
    fragShaderFile = "Resources/Shaders/simpleFS.frag";
}

cbShader::cbShader( const char* vs, const char* fs )
{
    vertexShaderFile = vs;
    fragShaderFile = fs;
}

cbShader::cbShader( std::string vs, std::string fs )
{
    vertexShaderFile = vs.c_str();
    fragShaderFile = fs.c_str();
}

cbShader::~cbShader()
{
    vertexShaderFile = "";
    fragShaderFile = "";
    glDeleteShader( vertexShaderID );
    glDeleteShader( fragShaderID );
    glDeleteProgram( program );
}

GLuint cbShader::GetProgram() const
{
    return program;
}

bool cbShader::LoadShaders()
{
    bool loaded = true;
    
    vertexShaderID = LoadShader( GL_VERTEX_SHADER, vertexShaderFile );
    fragShaderID = LoadShader( GL_FRAGMENT_SHADER, fragShaderFile );
    
    if ( !LinkProgram() ) {
        loaded = false;
        fprintf( stderr, "Cannot load shaders this program will render nothing. Please verify your shaders files." );
    }
    
    glDetachShader( program, vertexShaderID );
    glDetachShader( program, fragShaderID );
    
    return loaded;
}

GLuint cbShader::LoadShader( GLenum shaderType, const char* shaderFile )
{
    GLuint shaderID;
    
    shaderID = glCreateShader( shaderType );
    
    // Read vs file
    std::string shaderCode;
    std::ifstream shaderStream( shaderFile, std::ios::in );
    
    if ( shaderStream.is_open() ) {
        std::string line = "";
        while ( std::getline( shaderStream, line ) ) {
            shaderCode += "\n" + line;
        }
        shaderStream.close();
    } else {
        fprintf( stderr, "Cannot read vertex shader file: %s", shaderFile );
        return false;
    }
    
    // Compile vs
    printf( "Compiling vertex shader %s\n", shaderFile );
    const char* constVSCode = shaderCode.c_str();
    glShaderSource(shaderID, 1, &constVSCode, NULL );
    glCompileShader( shaderID );
    
    GLint compileStatus;
    int infoLogLength;
    
    // Check vs
    glGetShaderiv( shaderID, GL_COMPILE_STATUS, &compileStatus );
    glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH, &infoLogLength );
    std::vector<char> shaderErrorMessage( infoLogLength );
    glGetShaderInfoLog( shaderID, infoLogLength, NULL, &shaderErrorMessage[0] );
    fprintf( stdout, "%s\n", &shaderErrorMessage[0] );
    
    return shaderID;
}

bool cbShader::LinkProgram()
{
    bool success;
    
    // Link the program
    program = glCreateProgram();
    glAttachShader( program, vertexShaderID );
    glAttachShader( program, fragShaderID );
    glLinkProgram( program );
    
    GLint linkStatus;
    int infoLogLength;
    
    // Check the program
    glGetProgramiv( program, GL_LINK_STATUS, &linkStatus );
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );
    std::vector<char> programErrorMessage( infoLogLength );
    glGetProgramInfoLog( program, infoLogLength, NULL, &programErrorMessage[0] );
    fprintf( stdout, "%s\n", &programErrorMessage[0] );
    
    success = linkStatus;
    return success;
}