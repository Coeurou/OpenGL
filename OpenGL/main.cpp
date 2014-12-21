//
//  main.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 05/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

// Include standard headers
#include <iostream>
#include "cbWindow.h"
#include "cbMainLoop.h"
#include "cbTriangle.h"
#include "cbShader.h"
#include "RandomWordGenerator.h"


int main( void )
{
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 1000, 768, "First Window" );
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    cbMainLoop::GetInstance().InitGLFWCallback( oglContext->GetWindow() );
    
    glClearColor( 0.0f, 0.3f, 0.4f, 0.0f ); // Background color
    
    Invocat::Mesh::cbTriangle tri;
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        tri.Draw();
        oglContext->Update();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( oglContext->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose( oglContext->GetWindow()) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}