//
//  main.cpp
//  VertexColorAttribute
//
//  Created by Guillaume Trollé on 25/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl3.h>
#include "cbShader.h"
#include "cbWindow.h"
#include <glm/glm.hpp>

#define MEMBER_OFFSET(s, m) ( (char*)NULL + offsetof(s, m) )

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};


int main(int argc, const char * argv[]) {
    Invocat::Core::cbWindow* oglContext = new Invocat::Core::cbWindow( 800, 600, "Vertex color Attribute" );
    
    if ( !oglContext->InitWindow() ) {
        return -1;
    }
    
    Vertex data[3] = { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.8f, 0.0f, 0.1f),
                       glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.2f, 0.7f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
    
    GLuint vbo;
    GLuint vao;
    GLuint program;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    Invocat::Core::cbShader* shader = new Invocat::Core::cbShader("Resources/Shaders/colorAttribute.vert", "Resources/Shaders/colorAttribute.frag");
    shader->LoadShaders();
    program = shader->GetProgram();
    
    glClearColor(0.7f, 0.6f, 0.0f, 1.0f);
    
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram(program);
        
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), MEMBER_OFFSET(Vertex, color));
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(0);
        
        glUseProgram(0);
        
        oglContext->Update();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( oglContext->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose( oglContext->GetWindow()) == 0 );
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
