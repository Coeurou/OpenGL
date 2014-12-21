//
//  cbMainLoop.h
//  OpenGL
//
//  Created by Guillaume Trollé on 07/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef __OpenGL__cbMainLoop__
#define __OpenGL__cbMainLoop__

#include <GLFW/glfw3.h>
#include "cbSingleton.h"

class cbMainLoop : public Invocat::Tools::cbSingleton<cbMainLoop>
{
public:
    cbMainLoop();
    
    void                Update() const;
    void                InitGLFWCallback( GLFWwindow* window );
    
protected:
    static void         KeyboardGLFW( GLFWwindow*, int, int, int, int );
    static void         CursorPosGLFW( GLFWwindow*, double, double );
    static void         CursorEnterGLFW( GLFWwindow*, int );
    static void         MouseGLFW( GLFWwindow*, int, int, int );
    static void         ScrollGLFW( GLFWwindow*, double, double );
    
    void                KeyboardGLFWImpl( GLFWwindow*, int, int, int, int );
    void                CursorPosGLFWImpl( GLFWwindow*, double, double );
    void                CursorEnterGLFWImpl( GLFWwindow*, int );
    void                MouseGLFWImpl( GLFWwindow*, int, int, int );
    void                ScrollGLFWImpl( GLFWwindow*, double, double );
};

#endif /* defined(__OpenGL__cbMainLoop__) */
