

#define TINYOBJLOADER_IMPLEMENTATION

/*Shader implementation*/
#include <string>
#include <iostream>

/*Physics and Custom Classes inclusion*/
#include "Physics/MyVector.h"
#include "Classes/Model.h"
#include "Classes/Shader.h"


/*
* TO DO LIST:
* Move model transformations to the Model Class - DONE
* Push - DONE
* Remove all old code - DONE
* push - DONE
* Move all model initialization to contructor
* 
* shader inital class
* push 
* 
* bind all models
*/

//Modifier for model's x Position
float x_mod = 0.0f;

void Key_Callback(GLFWwindow* window, int key, 
                    int scancode /*Physical position of the press*/,
                    int action /*Press/Release*/,
                    int mods /*Which key is held down*/)
{
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        x_mod += 0.1f;
    }

}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*OBJ INITIALIZATION*/
    ///std::string path = "3D/sphere.obj";
    //std::vector<tinyobj::shape_t> objShapes;
    //std::vector<tinyobj::material_t> objMeshShapes;

    //std::string warning, error;

    /*Basic Attributes related to mesh*/
    //tinyobj::attrib_t attributes;

    /*Load Mesh*/
    //bool success = tinyobj::LoadObj(&attributes, &objShapes, &objMeshShapes, &warning, &error, path.c_str());

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Jan Vingno", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*calling the initializing of glad*/
    gladLoadGL();

    glViewport(0, //Min X
               0, //Min Y
               600, //Width
               600); //Height
    

    glm::mat4 projection = glm::ortho(-2.0f, //left most point
        2.0f, //right most point
        -2.0f, //bottom most point
        2.0f, //top most poinr
        -1.f, // Z Near
        1.0f); //Z Far

    /*Shader*/
    Shader modelShader = Shader();

    /*Model*/
    Model model = Model("3D/sphere.obj");

    /*Model Transformations*/
    Physics::MyVector sample(0, 0, 0);
    Physics::MyVector sampleScale(0.5f, 0.5f, 0.5f);
    Physics::MyVector sampleRotate(0.5f, 1.0f, 0.5f);

    /*Model Binding*/
    model.bind(modelShader);

    //glfwSetKeyCallback(window, Key_Callback);

    //Vertex
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to vertex shader
    //glShaderSource(vertexShader, 1, &v, NULL);
    //glCompileShader(vertexShader);

    //Fragment
    //GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1 , &f, NULL);
    //glCompileShader(fragmentShader);

    /*Create the shader program*/
    //GLuint shaderProg = glCreateProgram();
    //Attach the compiled Vertex Shader
    //glAttachShader(shaderProg, vertexShader);
    //Attach the compiled Fragment Shader
    //glAttachShader(shaderProg, fragmentShader);

    //glLinkProgram(shaderProg);

    /*Vertex Array Object* - It stores the format of the vertex data as well as the Buffer Objects (see below) providing the vertex data arrays
    Vertex Buffer Object - store an array of unformatted memory allocated by the OpenGL context (AKA the GPU). These can be used to store vertex data,
    Element Buffer Object - This will reduce the number of vertices by removing redundant ones*/

    /*VAO VBO Intialization*/
   // GLuint VAO, VBO, EBO;

    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    /*EBO Bind*/
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //std::vector<GLuint> mesh_indicies;
    //for (int i = 0; i < objShapes[0].mesh.indices.size(); i++)
    //{
      //  mesh_indicies.push_back(objShapes[0].mesh.indices[i].vertex_index);
    //}


    //glUseProgram(shaderProg);

    /*BINDING*/
    /*Bind the VAO so all other funtions after this will follow the VAO*/
   // glBindVertexArray(VAO);

    /*Assigning the Array Buffers to store the added positions*/
   // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*Converting VAO into bytes
    Paramater names - What data is the buffer located
    The size of the whole buffer
    the vertext array
    renderer*/
    
   // glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes.vertices.size(), &attributes.vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(verticiesSetUp), verticiesSetUp, GL_STATIC_DRAW);

    /*Create Element Array Buffer to store the indicies*/
  ///  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    /*Parameters - Gets the data insied the buffer variable, size of the whole buffer in bytes, index array, rendererer*/
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indicies.size(), mesh_indicies.data(), GL_STATIC_DRAW);

    /*How can the VAO interpte VBO? 
    Parameters - VAO Id number, 3 bc XYZ, what datat do u want it to return, not sure, the size of the vertex data
    */
 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    /*VAO to use the data above*/
 //   glEnableVertexAttribArray(0);

    /*Binding the buffer and the Id number of VAO*/
    /*gl BindBuffer is acalled twice bc the first glBindBuffer has been formatted and overwritten by glBufferData/glVertexAttribPointer*/
  //  glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*Overwritten by the  glBufferData/glVertexAttribPointer*/
  //  glBindVertexArray(0);
//
  ///  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*Model Modifications*/
        model.MoveModel(sample);

        model.scaleModel(sampleScale);

        model.rotateModel(sampleRotate, 0.0f /*theta*/);

        model.renderModel(modelShader);
        /*Model Modifications*/

        /*Triangle Rendering*/
        //Call binder for renderer
        //glBindVertexArray(VAO);

        //instead of glDrawArrays(GL_TRIANGLES,0,3) you can simplify things by replacing it with the one below
        /*parameters - type of primitive to use, number of vertices, datat type of index*/
        //glDrawElements(GL_TRIANGLES,mesh_indicies.size(), GL_UNSIGNED_INT, 0);

/********************DO NOT TOUCH CODE BELOW*******************************8/
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


   
    /*Clean the vertex annd buffers*/

    model.cleanUp();

    glfwTerminate();
    return 0;
}