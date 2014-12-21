//
//  cbShader.h
//  OpenGL
//
//  Created by Guillaume Trollé on 13/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef __OpenGL__cbShader__
#define __OpenGL__cbShader__

#include <OpenGL/gl3.h>
#include <string>

namespace Invocat {
    
namespace Core {
    
    class cbShader {
        
    public:
        cbShader();
        cbShader( const char* vs, const char* fs );
        cbShader( std::string vs, std::string fs );
        ~cbShader();
        
        GLuint GetProgram() const;
        
        bool LoadShaders();
        
    private:
        GLuint program;
        const char* vertexShaderFile;
        const char* fragShaderFile;
        
        GLuint vertexShaderID;
        GLuint fragShaderID;
        
        GLuint LoadShader( GLenum shaderType, const char* shaderFile );
        bool LinkProgram();
    };
}
    
}

#endif /* defined(__OpenGL__cbShader__) */
