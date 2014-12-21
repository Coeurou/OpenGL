//
//  main.cpp
//  RotateVertices
//
//  Created by Guillaume Trollé on 26/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>
#include <vector>

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

#include "cbShader.h"
#include "cbWindow.h"

#define PI 3.14159265358979323
#define MEMBER_OFFSET(s, m) ( (char*)NULL + offsetof(s, m) )

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    
    Vertex( glm::vec3 p, glm::vec3 c )
    {
        pos = p;
        color = c;
    }
};

GLuint vbo;
GLuint vao;
GLuint program;

std::vector<Vertex> geometryData;

void ComputePositionOffsets( float& xOffset, float& yOffset )
{
    const float duration = 4.0f;
    const float angle = ( 2.0f * PI ) / duration;
    
    float currentFrame = fmodf( glfwGetTime(), duration );
    
    xOffset = cosf( currentFrame * angle ) * 0.5f;
    yOffset = sinf( currentFrame * angle ) * 0.5f;
}

void ApplyOffsetToPosition( float xOffset, float yOffset )
{
    std::vector<Vertex> newVertices( geometryData );
    
    for ( auto& vertex : newVertices ) {
        vertex.pos.x += xOffset;
        vertex.pos.y += yOffset;
    }

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferSubData( GL_ARRAY_BUFFER, 0, geometryData.size() * sizeof( Vertex ), &newVertices[0] );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

int main(int argc, const char * argv[]) {
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 800, 600, "Height & Color Attrib Combined" );
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    Invocat::Core::cbShader* shader = new Invocat::Core::cbShader( "Resources/Shaders/hvca.vert", "Resources/Shaders/hvca.frag" );
    shader->LoadShaders();
    
    program = shader->GetProgram();
    
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    
    geometryData.push_back( Vertex( glm::vec3( -1.0f, -1.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ) ) );
    geometryData.push_back( Vertex( glm::vec3( 1.0f, -1.0f, 0.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) ) );
    geometryData.push_back( Vertex( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) ) );
    
    glBufferData( GL_ARRAY_BUFFER, geometryData.size() * sizeof( Vertex ), &geometryData[0], GL_STREAM_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
    
    glUseProgram( program );
    GLint wh = glGetUniformLocation( program, "windowHeight" );
    glUniform1i( wh, oglContext->GetHeight() );
    glUseProgram( 0 );
    
    float xOffset;
    float yOffset;
    
    glClearColor( 0.0f, 0.3f, 0.8f, 0.8f );
    
    do {
        ComputePositionOffsets( xOffset, yOffset );
        ApplyOffsetToPosition( xOffset, yOffset );
        
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram( program );
        
        glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), MEMBER_OFFSET( Vertex, pos ) );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), MEMBER_OFFSET( Vertex, color ) );
        
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 0 );
        
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindVertexArray( 0 );
        
        glUseProgram( 0 );
        
        oglContext->Update();
    } while ( glfwWindowShouldClose( oglContext->GetWindow() ) == 0 && glfwGetKey( oglContext->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS );
    
    glDeleteBuffers( 1, &vbo );
    glDeleteVertexArrays( 1, &vao );
    glDeleteProgram( program );

    glfwTerminate();
    
    return 0;
}
