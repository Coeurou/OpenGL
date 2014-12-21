//
//  cbTriangle.h
//  OpenGL
//
//  Created by Guillaume Trollé on 13/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef __OpenGL__cbTriangle__
#define __OpenGL__cbTriangle__

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <vector>

#include "cbShader.h"

namespace Invocat {

namespace Mesh {
    
class cbTriangle {
    
public:
    cbTriangle();
    cbTriangle( Core::cbShader* program, const std::vector<glm::vec3> data );
    ~cbTriangle();
    
    void                    Draw();
    
protected:
    Core::cbShader*         shader;
    std::vector<glm::vec3>  vertexBufferData;
    GLuint                  vao;
    GLuint                  vbo;
    GLuint                  vsPositionAttrib;
    
private:
    void                    CreateVAO();
    void                    CreateVBO();
    
};

}

}
#endif /* defined(__OpenGL__cbTriangle__) */
