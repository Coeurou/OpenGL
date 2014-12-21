//
//  cbWindow.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 06/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include "cbWindow.h"
using namespace Invocat::Core;

/*
 ===============================================================================
 
	OpenGL context window which initialize both GLEW & GLFW
 
 ===============================================================================
 */
cbWindow::cbWindow()
{
    wWidth = 1280;
    wHeight = 720;
    InitWindow();
}

cbWindow::cbWindow( GLint w, GLint h, std::string windowTitle )
{
    wWidth = w;
    wHeight = h;
    wTitle = windowTitle;
}

const GLFWwindow* cbWindow::GetWindow() const
{
    return oglWindow;
}

GLFWwindow* cbWindow::GetWindow()
{
    return oglWindow;
}

GLint cbWindow::GetWidth() const
{
    return wWidth;
}

GLint cbWindow::GetHeight() const
{
    return wHeight;
}

bool cbWindow::InitWindow()
{
    bool success = true;
    
    if ( !glfwInit() ) {
        // Throw new cbException cannot initialize
        fprintf( stderr, "Failed to init GLFW" );
        return false;
    }
    
    glfwWindowHint( GLFW_SAMPLES, 4 );                                  // 4x antialiasing
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );                    // OpenGL Version 4.1
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );              // Forward compatibility required for MacOSX
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    
    oglWindow = glfwCreateWindow( wWidth, wHeight, wTitle.c_str(), NULL, NULL );
    if ( oglWindow == NULL ) {
        // Throw new cbException
        fprintf( stderr, "Cannot create a window. You should verify your driver or your graphic card (Intel ???)" );
        glfwTerminate();
        success = false;
    }
    glfwMakeContextCurrent( oglWindow );
    
    glfwSetInputMode( oglWindow, GLFW_STICKY_KEYS, GL_TRUE );
    
    return success;
}

void cbWindow::Update()
{
    glfwSwapBuffers( oglWindow );
    glfwPollEvents();
}