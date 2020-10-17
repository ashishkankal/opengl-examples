#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include "shared/file_utils.h"
#include "shared/math_utils.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

float rotation = 0.0f;
int screen_width = 1024, screen_height = 768;

#include "./common/perspective.hpp"

GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
GLuint vertexArray, vertexBuffer, elementBuffer;
GLuint colorbuffer;

GLuint gWorldLocation;
GLuint MatrixID;
glm::mat4 mvp;

struct Shape
{
    vector<Vector3f> vertices;
    vector<Vector3i> edges;
    vector<Vector3f> faces;

    Shape() {}
    Shape(vector<Vector3f> v, vector<Vector3i> e, vector<Vector3f> f)
    {
        vertices = v;
        edges = e;
        faces = f;
    }
};
struct Shape shape;

const char *pVSFileName = "shader.vs";
const char *pFSFileName = "shader.fs";

#include "./common/shader.hpp"

#include "./fileReader.hpp"

static void createWindow()
{
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(screen_width, screen_height, "OpenGL - Ashish", NULL, NULL);
}

static void createVertexBuffer()
{
    glGenBuffers(1, &elementBuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.edges.size() * sizeof(Vector3i), &shape.edges.front(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &vertexArray);
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(Vector3f), &shape.vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(vertexArray);
}

int main(int argc, char *argv[])
{
    shape = readOffFile();

    cout << shape.vertices.size() << "\n";
    cout << shape.edges.size() << "\n";

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    createWindow();
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW

    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    printf("GL version: %s\n", glGetString(GL_VERSION));
    createVertexBuffer();
    glBindVertexArray(vertexArray);
    compileShaders();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    do
    {

        rotation += 0.01;

        // // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vertexArray);
        mvp = transform(rotation);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glDrawElements(GL_TRIANGLES, shape.edges.size() * 3, GL_UNSIGNED_INT, 0);
        //glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    return 0;
}