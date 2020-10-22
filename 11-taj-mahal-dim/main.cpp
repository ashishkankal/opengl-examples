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

float scale = 0.0f;
float loop_var = 0.0f;
int screen_width = 1024, screen_height = 768;
float zNear = 0.1f, zFar = 40.0f;
// MOUSE
bool firstMouse = false;
float lastX, lastY, yaw, pitch;
struct Camera
{
    float x;
    float y;
    float z;
    float up_x;
    float up_y;
    float up_z;
    Camera()
    {
        x = 0.19f;
        y = -0.1f;
        z = -8.39f;

        up_x = 0.300007;
        up_y = 0.175135;
        up_z = 0.501496;
    }
};

struct Camera camera = Camera();

struct Translate
{
    float x;
    float y;
    float z;
    Translate()
    {
        x = -0.29f;
        y = -0.5f;
        z = -6.8f;
    }
    Translate(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};
struct Translate translate = Translate();
struct Translate rotateCo = Translate(0.0f, 0.0f, 0.0f);
#include "./common/perspective.hpp"

GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
GLuint vertexArray, vertexBuffer, elementBuffer;
GLuint colorbuffer;

GLuint gWorldLocation;
GLuint MatrixID;
//Matrix4f mvp;

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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        camera.y += 0.10f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        camera.y -= 0.10f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        camera.x += 0.10f;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        camera.x -= 0.10f;
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        camera.z += 0.10f;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        camera.z -= 0.10f;
    }
    // TRANSLATE
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        translate.x += 0.10f;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        translate.x -= 0.10f;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        translate.y += 0.10f;
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        translate.y -= 0.10f;
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        translate.z += 0.10f;
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        translate.z -= 0.10f;
    }
    // Z FAR
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        zFar += 0.10f;
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        zFar -= 0.10f;
    }
    // Z NEAR

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        zNear += 0.10f;
    }
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
    {
        zNear -= 0.10f;
    }
    // ROTATE
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        rotateCo.x += 0.10f;
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        rotateCo.x -= 0.10f;
    }
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
    {
        rotateCo.y += 0.10f;
    }
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
    {
        rotateCo.y -= 0.10f;
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        rotateCo.z += 0.10f;
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        rotateCo.z -= 0.10f;
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
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
    glfwSetKeyCallback(window, key_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(window, mouse_callback);

    do
    {

        loop_var += 0.01;

        // // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vertexArray);
        mvp = transform();
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glDrawElements(GL_TRIANGLES, shape.edges.size() * 3, GL_UNSIGNED_INT, 0);
        //glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);

        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    cout << "CAMERA\n";
    cout << camera.x << " " << camera.y << " " << camera.z;
    cout << "\nTRANSLATE\n";
    cout << translate.x << " " << translate.y << " " << translate.z;
    cout << "\n Z Near Z Far\n";
    cout << zNear << " " << zFar;
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    return 0;
}