

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

glm::mat4 transform(float rotation)
{
    float angle = findMod((rotation * 10), 360); // 45° per second

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f * screen_width / screen_height, 0.1f, 10.0f);

    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0, 2.0, 2.0));

    glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2, 0, -5.0));

    glm::mat4 View = glm::lookAt(glm::vec3(1.2, 0.8, -9), glm::vec3(0.300007, 0.175135, 0.501496), glm::vec3(0.0, 1.0, 0.0));

    glm::vec3 axis(0, 1, 0);

    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(355.0f), axis);

    return Projection * View * Model * Scale * anim; // Remember, matrix multiplication is the other way around
}
