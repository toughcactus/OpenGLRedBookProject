//
//  main.cpp
//  test
//
//  Created by Robin on 2021/11/9.
//

#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void
init(void)
{
    static const GLfloat vertices[NumVertices][2] =
    {
        { -0.90, -0.90},
        {  0.85, -0.90},
        { -0.90,  0.85},
        {  0.90, -0.85},
        {  0.90,  0.90},
        { -0.85,  0.90}
    };

    /* glCreateBuffers and glNamedBufferStorage is API of openGL4.5 */
//    glCreateBuffers(NumBuffers, Buffers);
//    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices),
//                         vertices, 0);
    
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW);
    
    ShaderInfo  shaders[] =
    {
        { GL_VERTEX_SHADER, "/Volumes/OpenGL/Projects/test/test/triangles.vert" },
        { GL_FRAGMENT_SHADER, "/Volumes/OpenGL/Projects/test/test/triangles.frag" },
        { GL_NONE, NULL }
    };
    
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

#if 0
void
init( void )
{
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Triangles] );
    GLfloat  vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
    };

    //glCreateBuffers is API of openGL4.5
    //refer to https://stackoverflow.com/questions/31841494/difference-in-glgenbuffers-and-glcreatebuffers
    glGenBuffers( NumBuffers, Buffers );
    
    glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
    
    //glBufferStorage is API of openGL4.5
    //glBufferStorage( GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW);
    
    ShaderInfo  shaders[] =
    {
        { GL_VERTEX_SHADER, "/Volumes/OpenGL/Projects/test/test/triangles.vert" },
        { GL_FRAGMENT_SHADER, "/Volumes/OpenGL/Projects/test/test/triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( vPosition, 2, GL_FLOAT,
                           GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vPosition );
}
#endif
void
display(void)
{
    static const float black[] { 0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);
    
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int main(int argc, const char* argv[]) {
    glfwInit();
    /* those glfwWindowHint must add */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles", NULL,
                                          NULL);

    glfwMakeContextCurrent(window);
    gl3wInit();
    
    init();
    
    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    return 0;
}
