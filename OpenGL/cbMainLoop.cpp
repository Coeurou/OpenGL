//
//  cbMainLoop.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 07/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include "cbMainLoop.h"
#include <iostream>


cbMainLoop::cbMainLoop()
{
    std::cout << " cbMainLoop unique instance " << std::endl;
}

void cbMainLoop::InitGLFWCallback( GLFWwindow* window )
{
    glfwSetKeyCallback( window, KeyboardGLFW );
    glfwSetMouseButtonCallback( window, MouseGLFW );
    glfwSetCursorPosCallback( window, CursorPosGLFW );
    glfwSetCursorEnterCallback( window, CursorEnterGLFW );
    glfwSetScrollCallback( window, ScrollGLFW );
}

void cbMainLoop::Update() const
{
    
}

void cbMainLoop::KeyboardGLFW( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    GetInstance().KeyboardGLFWImpl( window, key, scancode, action, mods );
}

void cbMainLoop::CursorPosGLFW( GLFWwindow* window, double xpos, double ypos )
{
    GetInstance().CursorPosGLFWImpl( window, xpos, ypos );
}

void cbMainLoop::CursorEnterGLFW( GLFWwindow* window, int entered )
{
    GetInstance().CursorEnterGLFWImpl( window, entered );
}

void cbMainLoop::MouseGLFW( GLFWwindow* window, int button, int actions, int mods )
{
    GetInstance().MouseGLFWImpl( window, button, actions, mods );
}

void cbMainLoop::ScrollGLFW( GLFWwindow* window, double xoffset, double yoffset )
{
    GetInstance().ScrollGLFWImpl( window, xoffset, yoffset );
}

void cbMainLoop::KeyboardGLFWImpl( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    std::cout << "Key" << std::endl;
}

void cbMainLoop::CursorPosGLFWImpl( GLFWwindow* window, double xpos, double ypos )
{
    std::cout << "Cursor position" << std::endl;
}

void cbMainLoop::CursorEnterGLFWImpl( GLFWwindow* window, int entered )
{
    std::cout << "Cursor entered" << std::endl;
}

void cbMainLoop::MouseGLFWImpl( GLFWwindow* window, int button, int actions, int mods )
{
    std::cout << "Mouse button" << std::endl;
}

void cbMainLoop::ScrollGLFWImpl( GLFWwindow* window, double xoffset, double yoffset )
{
    std::cout << "Scroll" << std::endl;
}

