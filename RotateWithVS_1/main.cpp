//
//  main.cpp
//  RotateWithVS_1
//
//  Created by Guillaume Trollé on 28/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>
#include <vector>

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

#include "cbShader.h"
#include "cbWindow.h"

#define PI                         3.14159265358979323
#define MEMBER_OFFSET( s, m )      ( (char*)NULL + offsetof( s, m ) )

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    
    Vertex( glm::vec3 p, glm::vec3 c )
    {
        pos = p;
        color = c;
    }
};

GLuint program;
GLuint vao;
GLuint vbo;

std::vector<Vertex> geometryData;

void ComputeOffsetPosition( float& xOffset, float& yOffset )
{
    const float duration = 4.0f;
    const float angle = ( 2.0f * PI ) / duration;
    
    float currentFrame = fmodf( glfwGetTime(), duration );
    
    xOffset = cosf( currentFrame * angle ) * 0.5f;
    yOffset = sinf( currentFrame * angle ) * 0.5f;
}

int main(int argc, const char * argv[]) {
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 800, 600, "Moving vertices With VS n°1" );
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    Invocat::Core::cbShader* shader = new Invocat::Core::cbShader( "Resources/Shaders/rotatingVertices_1.vert", "Resources/Shaders/rotatingVertices_1.frag" );
    
    if ( !shader->LoadShaders() ) {
        return -1;
    }
    
    program = shader->GetProgram();
    
    float xOffset, yOffset;
    
    glUseProgram( program );
    GLint offset = glGetUniformLocation( program, "offset" );
    GLint wHeight = glGetUniformLocation( program, "windowHeight" );
    glUniform1i( wHeight, oglContext->GetHeight() );
    glUseProgram( 0 );
    
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
        geometryData.push_back( Vertex( glm::vec3( -1.0f, -1.0f, 0.0f ), glm::vec3( 0.08f, 0.53f, 0.81f ) ) );
        geometryData.push_back( Vertex( glm::vec3( 1.0f, -1.0f, 0.0f ), glm::vec3( 0.2f, 1.0f, 0.1f ) ) );
        geometryData.push_back( Vertex( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.64f, 0.32f, 0.16f ) ) );
    glBufferData( GL_ARRAY_BUFFER, geometryData.size() * sizeof( Vertex ), &geometryData[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
    
    glClearColor( 0.4f, 0.4f, 0.4f, 1.0f );
    
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        glUseProgram( program );
        glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
            ComputeOffsetPosition( xOffset, yOffset );
            glUniform2f( offset, xOffset, yOffset );
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
    } while ( glfwGetKey( oglContext->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( oglContext->GetWindow() ) == 0 );
        
    glfwTerminate();
    glDeleteBuffers( 1, &vbo );
    glDeleteVertexArrays( 1, &vao );
    glDeleteProgram( program );
    
    return 0;
}
