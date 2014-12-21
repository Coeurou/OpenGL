//
//  cbWindow.h
//  OpenGL
//
//  Created by Guillaume Trollé on 06/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef __OpenGL__cbWindow__
#define __OpenGL__cbWindow__

#include <stdio.h>
#include <string>

#include <GLFW/glfw3.h>

namespace Invocat {
    
namespace Core {
    
    class cbWindow {
        
    public:
        cbWindow();
        cbWindow( GLint w, GLint h, std::string windowTitle);

        GLFWwindow*                             GetWindow();
        const GLFWwindow*                       GetWindow() const;
        GLint                                   GetWidth() const;
        GLint                                   GetHeight() const;
        
        bool                                    InitWindow();

        void                                    Update();
        void                                    Resize();

    protected:
        GLFWwindow*                             oglWindow;
        GLint                                   wWidth;
        GLint                                   wHeight;
        std::string                             wTitle;
    };
    
}
    
}

#endif /* defined(__OpenGL__cbWindow__) */
