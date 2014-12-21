//
//  main.cpp
//  Combine_HVCA
//
//  Created by Guillaume Trollé on 26/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

#include "cbShader.h"
#include "cbWindow.h"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};

#define MEMBER_OFFSET( s, m ) ( (char*)NULL + offsetof( s, m ) )

int main(int argc, const char * argv[]) {
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 800, 600, "Height & Color Attrib Combined" );
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    Invocat::Core::cbShader* shader = new Invocat::Core::cbShader( "Resources/Shaders/hvca.vert", "Resources/Shaders/hvca.frag" );
    shader->LoadShaders();
    
    GLuint vbo;
    GLuint vao;
    GLuint program;
    
    program = shader->GetProgram();
    
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    
    Vertex data[3] = { glm::vec3( -1.0f, -1.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ),
                       glm::vec3( 1.0f, -1.0f, 0.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ),
                       glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) };
    
    glBufferData( GL_ARRAY_BUFFER, sizeof( data ), &data, GL_STATIC_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
    
    glUseProgram( program );
    GLint wh = glGetUniformLocation( program, "windowHeight" );
    glUniform1i( wh, oglContext->GetHeight() );
    glUseProgram( 0 );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.8f );
    
    do {
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
