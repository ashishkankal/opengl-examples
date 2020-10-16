

const char *filePtr = "m399.off";

struct Shape readOffFile()
{
    string line;
    ifstream myfile(filePtr);
    int i = 0;
    int vertexCount, edgeCount, faceCount;

    vector<Vector3f> vertices;
    vector<Vector3i> edges;
    vector<Vector3f> faces;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (i == 0)
            {
                i++;
                continue;
            }
            if (i == 1)
            {
                sscanf(line.c_str(), "%d %d %d", &vertexCount, &edgeCount, &faceCount);
            }
            else if (i - 2 < vertexCount)
            {
                float temp_x, temp_y, temp_z;
                sscanf(line.c_str(), "%f %f %f", &temp_x, &temp_y, &temp_z);
                vertices.push_back(Vector3f(temp_x, temp_y, temp_z));
            }
            else if (i - 2 - vertexCount < edgeCount)
            {
                int skip_var;
                unsigned int temp_x, temp_y, temp_z;
                sscanf(line.c_str(), "%d %u %u %u", &skip_var, &temp_x, &temp_y, &temp_z);
                edges.push_back(Vector3i(temp_x, temp_y, temp_z));
            }
            else
            {
                break;
            }

            i++;
        }
        myfile.close();
    }
    struct Shape shape = Shape(vertices, edges, faces);

    return shape;
}