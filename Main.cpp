

#define TINYOBJLOADER_IMPLEMENTATION

/*Shader implementation*/
#include <string>
#include <iostream>

/*Physics and Custom Classes inclusion*/
#include "Physics/MyVector.h"
#include "Classes/Model.h"


/*
* TO DO LIST:
* Move model transformations to the Model Class
* Push
* Remove all old code
* push
* Move all model initialization to contructor
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

float x = -0.0f, y = -0.0f, z = 0.f;
glm::mat4 identity_matrix = glm::mat4(1.0f);

float scale_x = 0.5f;
float scale_y = 0.5f;
float scale_z = 0.5f;

float theta = 0.0f;

float axis_x = 0.f;
float axis_y = 1.f;
float axis_z = 0.f;

int main(void)
{

    /*shaders are programs that the GPU executes to control how graphics are rendered*/
    /*Vertex shaders process vertex data, affecting object geometry,*/
    std::fstream vertSrc("Shaders/Cake.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    /*Fragments are the individual samples of pixels that are covered by a primitive (like a triangle), and fragment shaders process each fragment to determine its final color and depth.*/
    /*fragment shaders determine pixel colors, adding shading and texture details. */
    std::fstream fragSrc("Shaders/Cake.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*Model*/
    Model model = Model();
    Physics::MyVector sample(0, 0, 0);
    Physics::MyVector sampleScale(0.5f, 0.5f, 0.5f);
    Physics::MyVector sampleRotate(0.5f, 1.0f, 0.5f);


    /*OBJ INITIALIZATION*/
    std::string path = "3D/sphere.obj";
    std::vector<tinyobj::shape_t> objShapes;
    std::vector<tinyobj::material_t> objMeshShapes;

    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(&attributes, &objShapes, &objMeshShapes, &warning, &error, path.c_str());

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



    //glfwSetKeyCallback(window, Key_Callback);

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Get the variable named transform _matrix

        model.MoveModel(sample);

       // glm::mat4 transformation_matrix = glm::translate(
         //   identity_matrix,
           // glm::vec3(sample.x,sample.y,sample.z));

        model.scaleModel(sampleScale);

        //transformation_matrix = glm::scale(
          //  transformation_matrix,
            //glm::vec3(scale_x, scale_y, scale_z));

        model.rotateModel(sampleRotate, theta);

        model.renderModel(shaderProg);

        //transformation_matrix = glm::rotate(
          //  transformation_matrix,
            //glm::radians(theta),
            //glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));

        //Setting the projection 
        //unsigned int projLoc = glGetUniformLocation(shaderProg, "projection");
        //glUniformMatrix4fv(projLoc, //Address of the variable
          //                  1, //How many value are we modifying
            //                GL_FALSE, 
              //              glm::value_ptr(transformation_matrix)); //Projection Matrix

        //Get the variable named transform from one of the shaders
       //attached to the shaderProg
       // unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");

        //assign the matrix
       // glUniformMatrix4fv(transformLoc, //Address to the transform variable
         //   1, //How many matrices to assign
           // GL_FALSE, //Transpose
           // glm::value_ptr(transformation_matrix)); // pointer to the matrix

        //Get x in the shader file
        //unsigned int xLoc = glGetUniformLocation(shaderProg, "x");
        //assign x by usingits address
        //glUniform1f(xLoc, x_mod);

        /*Triangle Rendering*/
        //Call binder for renderer
        glBindVertexArray(VAO);
        //draw

        //instead of glDrawArrays(GL_TRIANGLES,0,3) you can simplify things by replacing it with the one below
        /*parameters - type of primitive to use, number of vertices, datat type of index*/
        glDrawElements(GL_TRIANGLES,mesh_indicies.size(), GL_UNSIGNED_INT, 0);

/********************DO NOT TOUCH CODE BELOW*******************************8/
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