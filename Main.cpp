

#define TINYOBJLOADER_IMPLEMENTATION

/*Shader implementation*/
#include <string>
#include <iostream>

/*Physics and Custom Classes inclusion*/
#include "Physics/MyVector.h"
#include "Classes/Model.h"
#include "Classes/Shader.h"

/*TO DO
*View Class
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