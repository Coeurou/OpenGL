//
//  main.cpp
//  HeightColor
//
//  Created by Guillaume Trollé on 25/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>
#include "cbWindow.h"
#include "cbTriangle.h"
#include "cbShader.h"

int main(int argc, const char * argv[]) {
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 800, 600, "Height frag shader" );
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    glClearColor( 0.0f, 0.3f, 0.4f, 0.0f ); // Background color
    
    std::vector<glm::vec3> trianglePos;
    trianglePos.push_back( glm::vec3( -0.5f, -0.5f, 0.0f ) );
    trianglePos.push_back( glm::vec3( 0.5f, -0.5f, 0.0f ) );
    trianglePos.push_back( glm::vec3( 0.0f, 0.5f, 0.0f ) );
    
    Invocat::Core::cbShader* shader = new Invocat::Core::cbShader( "Resources/Shaders/heightColor.vert", "Resources/Shaders/heightColor.frag" );
    Invocat::Mesh::cbTriangle tri2( shader, trianglePos );
    
    glUseProgram( shader->GetProgram() );
    GLint windowLocation = glGetUniformLocation( shader->GetProgram(), "windowHeight" );
    glUniform1f( windowLocation, oglContext->GetHeight() );
    glUseProgram( 0 );
    
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        tri2.Draw();
        oglContext->Update();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( oglContext->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose( oglContext->GetWindow()) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
