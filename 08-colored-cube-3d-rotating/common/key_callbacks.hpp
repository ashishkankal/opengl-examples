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

// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     if (firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos;
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.1f;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw += xoffset;
//     pitch += yoffset;

//     if (pitch > 89.0f)
//         pitch = 89.0f;
//     if (pitch < -89.0f)
//         pitch = -89.0f;
// }
