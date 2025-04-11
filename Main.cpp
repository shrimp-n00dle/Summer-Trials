#include <glad/glad.h> /*This helps with simplifying runtime when dealing with pointers*/
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

/*Shader implementation*/
#include <string>
#include <iostream>

int main(void)
{
    std::fstream vertSrc("Shaders/Cake.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();


    std::fstream fragSrc("Shaders/Cake.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*OBJ INITIALIZATION*/
    std::string path = "3D/bunny.obj";
    std::vector<tinyobj::shape_t> objShapes;
    std::vector<tinyobj::material_t> objMeshShapes;

    std::string warning, error;

    /*Basic Attributes related to mesh*/
    tinyobj::attrib_t attributes;

    /*Load Mesh*/
    bool success = tinyobj::LoadObj(&attributes, &objShapes, &objMeshShapes, &warning, &error, path.c_str());

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Summer Trials", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*calling the initializing of glad*/
    gladLoadGL();

    //Vertex
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to vertex shader
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    //Fragment
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1 , &f, NULL);
    glCompileShader(fragmentShader);

    /*Create the shader program*/
    GLuint shaderProg = glCreateProgram();
    //Attach the compiled Vertex Shader
    glAttachShader(shaderProg, vertexShader);
    //Attach the compiled Fragment Shader
    glAttachShader(shaderProg, fragmentShader);

    glLinkProgram(shaderProg);








    /*Initial definition of verticies array*/
    GLfloat verticiesSetUp[]
    { -0.5f,-0.5f,0,0,0.5f,0,0.5f,-0.5f,0 };

    /*Vertex Array Object* - It stores the format of the vertex data as well as the Buffer Objects (see below) providing the vertex data arrays
    Vertex Buffer Object - store an array of unformatted memory allocated by the OpenGL context (AKA the GPU). These can be used to store vertex data,
    Element Buffer Object - This will reduce the number of vertices by removing redundant ones*/

    //EBO Index Array
    GLuint indicies[]{ 0,1,2 };

    /*VAO VBO Intialization*/
    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /*EBO Bind*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::vector<GLuint> mesh_indicies;
    for (int i = 0; i < objShapes[0].mesh.indices.size(); i++)
    {
        mesh_indicies.push_back(objShapes[0].mesh.indices[i].vertex_index);
    }


    glUseProgram(shaderProg);
    /*Bind the VAO so all other funtions after this will follow the VAO*/
    glBindVertexArray(VAO);

    /*Assigning the Array Buffers to store the added positions*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*Converting VAO into bytes
    Paramater names - What data is the buffer located
    The size of the whole buffer
    the vertext array
    renderer*/
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(), &attributes.vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(verticiesSetUp), verticiesSetUp, GL_STATIC_DRAW);

    /*Create Element Array Buffer to store the indicies*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    /*Parameters - Gets the data insied the buffer variable, size of the whole buffer in bytes, index array, rendererer*/
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indicies.size(), mesh_indicies.data(), GL_STATIC_DRAW);

    /*How can the VAO interpte VBO? 
    Parameters - VAO Id number, 3 bc XYZ, what datat do u want it to return, not sure, the size of the vertex data
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    /*VAO to use the data above*/
    glEnableVertexAttribArray(0);

    /*Binding the buffer and the Id number of VAO*/
    /*gl BindBuffer is acalled twice bc the first glBindBuffer has been formatted and overwritten by glBufferData/glVertexAttribPointer*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*Overwritten by the  glBufferData/glVertexAttribPointer*/
    glBindVertexArray(0);

  





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*Triangle Rendering*/
        //Call binder for renderer
        glBindVertexArray(VAO);
        //draw

        //instead of glDrawArrays(GL_TRIANGLES,0,3) you can simplify things by replacing it with the one below
        /*parameters - type of primitive to use, number of vertices, datat type of index*/
        glDrawElements(GL_TRIANGLES,mesh_indicies.size(), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /*Clean the vertex annd buffers*/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}