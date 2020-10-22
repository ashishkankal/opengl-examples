

float aspectaxis()
{
    float outputzoom = 1.0f;
    float aspectorigin = 16.0f / 9.0f;
    int aspectconstraint = 1;
    switch (aspectconstraint)
    {
    case 1:
        if ((screen_width / screen_height) < aspectorigin)
        {
            outputzoom *= (((float)screen_width / screen_height) / aspectorigin);
        }
        else
        {
            outputzoom *= ((float)aspectorigin / aspectorigin);
        }
        break;
    case 2:
        outputzoom *= (((float)screen_width / screen_height) / aspectorigin);
        break;
    default:
        outputzoom *= ((float)aspectorigin / aspectorigin);
    }
    return outputzoom;
}

float recalculatefov()
{
    return 2.0f * glm::atan(glm::tan(glm::radians(45.0f / 2.0f)) / aspectaxis());
}

float findMod(float a, float b)
{
    float mod;
    // Handling negative values
    if (a < 0)
        mod = -a;
    else
        mod = a;
    if (b < 0)
        b = -b;

    // Finding mod by repeated subtraction

    while (mod >= b)
        mod = mod - b;

    // Sign of result typically depends
    // on sign of a.
    if (a < 0)
        return -mod;

    return mod;
}

glm::mat4 transform()
{

    float angle = findMod((loop_var * 10), 360); // 45° per second
    int numFs = 5;
    int radius = 0.5;
    glm::vec3 axis(0, 1, 0);
    // glm::mat4 cameraRotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    // glm::vec3 cameraVec(radius * glm::cos(glm::radians(angle)), camera.y, radius * glm::sin(glm::radians(angle)));
    // float camX = sin(glfwGetTime()) * radius;
    // float camZ = cos(glfwGetTime()) * radius;
    glm::vec3 cameraPos(camera.x, camera.y, camera.z);
    // glm::mat4 cameraMatrix = glm::translate(cameraRotMatrix, cameraVec);

    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), 1.0f * screen_width / screen_height, zNear, zFar);

    glm::vec3 cameraTarget(camera.up_x, camera.up_y, camera.up_z);

    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // glm::mat4 View = glm::inverse(cameraMatrix * cameraRotMatrix);

    glm::mat4 View = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    glm::mat4 ViewProjection = Projection * View;

    glm::mat4 ViewProjectionModel = glm::translate(ViewProjection, glm::vec3(translate.x, translate.y, translate.z));

    glm::mat4 ViewProjectionModelScale = glm::scale(ViewProjectionModel, glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), axis);

    return ViewProjectionModelScale * anim; // Remember, matrix multiplication is the other way around
}

// Matrix4f transform()
// {
//     Matrix4f rotationMat;
//     rotationMat.InitRotateTransform(rotateCo.x, rotateCo.y, rotateCo.z);

//     const PersProjInfo *perspective = new PersProjInfo(45.0f, (float)screen_width, (float)screen_height, zNear, zFar);
//     Matrix4f persMat;
//     persMat.InitPersProjTransform(*perspective);

//     Matrix4f translateMat;
//     translateMat.InitTranslationTransform(translate.x, translate.y, translate.z);

//     Matrix4f scaleMat;
//     scaleMat.InitScaleTransform(2.0, 2.0, 2.0);

//     Vector3f *target = new Vector3f(camera.x, camera.y, camera.z);
//     Vector3f *up = new Vector3f(camera.up_x, camera.up_y, camera.up_z);

//     Matrix4f cameraMat;
//     cameraMat.InitCameraTransform(*target, *up);

//     GLenum errorCode = glGetError();
//     if (errorCode == GL_NO_ERROR)
//     {
//     }
//     else
//     {
//         fprintf(stderr, "OpenGL rendering error %d\n", errorCode);
//     }
//     return persMat * cameraMat * translateMat * scaleMat * rotationMat;
// }
