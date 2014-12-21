//
//  cbTriangle.cpp
//  OpenGL
//
//  Created by Guillaume Trollé on 13/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include "cbTriangle.h"

using namespace Invocat::Mesh;

cbTriangle::cbTriangle()
{
    shader = new Core::cbShader();
    shader->LoadShaders();
    vsPositionAttrib = glGetAttribLocation( shader->GetProgram(), "position" );
    CreateVAO();
    vertexBufferData.push_back( glm::vec3( -1.0f, -1.0f, 0.0f ) );
    vertexBufferData.push_back( glm::vec3( 1.0f, -1.0f, 0.0f ) );
    vertexBufferData.push_back( glm::vec3( 0.0f, 1.0f, 0.0f ) );
    CreateVBO();
}

cbTriangle::cbTriangle( Core::cbShader* program, std::vector<glm::vec3> data )
{
    shader = program;
    shader->LoadShaders();
    vsPositionAttrib = glGetAttribLocation( shader->GetProgram(), "position" );
    CreateVAO();
    vertexBufferData = data;
    CreateVBO();
}

cbTriangle::~cbTriangle()
{
    glDeleteVertexArrays( 1, &vao );
    delete shader;
}

void cbTriangle::Draw()
{
    glUseProgram( shader->GetProgram() );
    
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glEnableVertexAttribArray( vsPositionAttrib );
    
    glVertexAttribPointer( vsPositionAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 3 );
    
    glDisableVertexAttribArray( vsPositionAttrib );
    glBindVertexArray( 0 );
}

void cbTriangle::CreateVAO()
{
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
}

void cbTriangle::CreateVBO()
{
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( glm::vec3 ), &vertexBufferData[0], GL_STATIC_DRAW );
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}