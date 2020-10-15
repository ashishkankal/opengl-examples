// glm::mat4 Projection = glm::perspective(glm::radians(30.0f), (float)100 / (float)100, 0.1f, 100.0f);

// //Ortho view
// //glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

// glm::mat4 View = glm::lookAt(
//     glm::vec3(0.000025, 0.008598, -0.999963),   // Camera is at (4,3,3), in World Space
//     glm::vec3(-1.000000, -0.000027, -0.000025), // and looks at the origin
//     glm::vec3(0.000027, -0.999963, -0.008598)   // Head is up (set to 0,-1,0 to look upside-down)
// );
// glm::mat4 Model = glm::mat4(1.0f);
// glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

glm::mat4 transform()
{
    // glm::vec2 const& Orientation =
    // glm::vec3 const& Translate=
    // glm::vec3 const& Up=
    glm::mat4 Projection = glm::perspective(glm::radians(30.0f), (float)100 / (float)100, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(0.000025, 0.008598, -0.999963),   // Camera is at (4,3,3), in World Space
        glm::vec3(-1.000000, -0.000027, -0.000025), // and looks at the origin
        glm::vec3(0.000027, -0.999963, -0.008598)   // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 Model = glm::mat4(1.0f);
    return Projection * View * Model; // Remember, matrix multiplication is the other way around
}