

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

glm::mat4 getLookAt()
{
    glm::vec3 cameraPos(camera.x, camera.y, camera.z);
    glm::vec3 cameraTarget(camera.up_x, camera.up_y, camera.up_z);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //? Below Calculation is already done by look At
    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);// Camera Z Axis
    //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));  // Camera X Axis
    //glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);// Camera Y Axis
    //?
    glm::mat4 View = glm::lookAt(cameraPos, cameraTarget, up);
    return glm::inverse(View);
}
glm::mat4 getPerspective()
{
    return glm::perspective(glm::radians(fov), 1.0f * screen_width / screen_height, zNear, zFar);
}

glm::mat4 getTranslation()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(translate.x, translate.y, translate.z));
}

Matrix4f toMatrix4f(glm::mat4 glmMat)
{
    Matrix4f Mat;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Mat.m[i][j] = glmMat[i][j];
        }
    }
    return Mat;
}

glm::mat4 transform_()
{

    glm::mat4 Projection = getPerspective();
    glm::mat4 View = getLookAt();
    glm::mat4 Model = getTranslation();
    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    return Projection * View * Model * Scale; // Remember, matrix multiplication is the other way around
}

Matrix4f transform()
{
    Matrix4f Projection;
    glm::mat4 GlmPers = getPerspective();
    Projection = toMatrix4f(GlmPers);

    glm::mat4 GlmView = getLookAt();
    Matrix4f View = toMatrix4f(GlmView);

    glm::mat4 GlmTrans = getTranslation();
    Matrix4f translateMat;
    translateMat = toMatrix4f(GlmTrans);

    Matrix4f scaleMat;
    scaleMat.InitScaleTransform(1.0, 1.0, 1.0);

    Matrix4f Result;

    Result = Projection.Transpose() * View.Transpose() * translateMat.Transpose();
    return Result.Transpose();
}
