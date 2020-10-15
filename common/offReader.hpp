

#include <vector>
const char *offFile = "/Users/ashishkankal/technical/learngl/m399.off";

void processOffFile()
{
    int vertexCount, edgeCount, faceCount;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    // if (!ReadFile(offFile, off))
    // {
    //     std::cerr << "Error loading file" << std::endl;
    //     return -1;
    // }
    vertexCount = 0;
    edgeCount = 0;
    faceCount = 0;
    ifstream f(offFile);
    f.is_open();
    string line;
    while (getline(f, line))
    {

        char lineHeader[3];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        //cout << lineHeader << "\n";
        if (res == EOF)
            break;
        if (strcmp(lineHeader, "OFF") == 0)
            continue;
        if (vertexCount == 0)
            fscanf(file, "%d %d %d\n", &vertexCount, &edgeCount, &faceCount);

        break;
        //read vertices
        // while ()
        // {
        //     glm::vec3 vertex;
        //     fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        //     temp_vertices.push_back(vertex);
        // }
        //read edges
    }

    cout << vertexCount << "\n"
         << edgeCount << "\n"
         << faceCount << "\n";

    // vector<string> result;
    // size_t pos = 0;
    // std::string token;
    // int i = 0;
    // std::string s = off;
    // std::string newLine = "\n";
    // std::string spaceDl = " ";

    // unsigned long nvertices, nfaces, nedges;
    // unsigned long counts[3];
    // while ((pos = s.find(newLine)) != std::string::npos)
    // {
    //     token = s.substr(0, pos);
    //     result.push_back(token);
    //     s.erase(0, pos + newLine.length());
    //     i++;
    // }

    // i = 0;
    // s = *(result.begin() + 1);
    // while ((pos = s.find(spaceDl)) != std::string::npos)
    // {

    //     token = s.substr(0, pos);
    //     counts[i] = std::stoul(token);
    //     s.erase(0, pos + spaceDl.length());
    //     i++;
    // }
    // nvertices = counts[0];
    // nfaces = counts[1];
    // nedges = counts[2];

    // int vertices_start = result.begin() + 2;
    // for (int i = vertices_start; i < vertices_start + nvertices; i++)
    // {
    // }
    // int faces_start = vertices_start + nvertices;
    // for (int i = faces_start; i < faces_start + nfaces; i++)
    // {
    // }
    // int edges_start = faces_start + nfaces;
    // for (int i = edges_start; i < edges_start + nedges; i++)
    // {
    // }

    f.close();
}