

#define TINYOBJLOADER_IMPLEMENTATION

/*Shader implementation*/
#include <string>
#include <iostream>

/*P6 and Custom Classes inclusion*/
#include "P6/MyVector.h"
#include "P6/MyParticle.h"
#include "P6/PhysicsWorld.h"
#include "P6/DragForceGenerator.h"

#include "RenderParticle.h"
#include "Classes/Model.h"
#include "Classes/Shader.h"

//Import the libraries
#include <chrono>
using namespace std::chrono_literals;
//This is going to be our time in between "frames"
constexpr std::chrono::nanoseconds timestep(16ms);

/*CURRENT ISSUES

--multiple aprticles
--paticle whould have an id bc they overlap
--delere when they reach a certain point
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
   Model model = Model("3D/sphere.obj",modelShader);

    /*Model Transformations*/
    P6::MyVector sample(0, 0, 0);
    P6::MyVector sampleScale(0.5f, 0.5f, 0.5f);
    P6::MyVector sampleRotate(0.5f, 1.0f, 0.5f);

    /*Model Binding*/
    model.bind();

    /*PHYSICS WORLD IMPLEMENTATION*/
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    /*RENDER PARTICLE IMPLEMENTATION*/
    std::list<RenderParticle*> rParticleList;

    /*PARTICLE IMPLEMETATION*/
    P6::MyParticle particle = P6::MyParticle();
    particle.Velocity = P6::MyVector(0, 0, 0);
    particle.Position = P6::MyVector(0,0, 0);
    particle.Acceleration = P6::MyVector(0, 0, 0);
    particle.damping = 0;
    particle.mass = 1;


    particle.addForce(P6::MyVector(0, 0, 0));
    pWorld.addParticle(&particle);

    /*GRAVITY IMPLEMENTATION*/
   // P6::DragForceGenerator drag = P6::DragForceGenerator(0.14, 0.1);
    //pWorld.forceRegistry.Add(&particle, &drag);

    RenderParticle rParticle = RenderParticle(&particle, &model, P6::MyVector(4.0f, 1.0f, 0.0f));
    rParticleList.push_back(&rParticle);

    //fontain time

    //for (int i = 0; i <= 2; i++)
    //{
      

        //P6::MyParticle particle2 = P6::MyParticle();
        //particle2.Velocity = P6::MyVector(0, 0, 0);
        //particle2.Position = P6::MyVector(0, 0.1f, 0);
        //particle2.Acceleration = P6::MyVector(0, 0, 0);
        //pWorld.addParticle(&particle2);

        //RenderParticle rParticle2 = RenderParticle(&particle2, &model, P6::MyVector(2.0f, 0.0f, 0.0f));
        //rParticleList.push_back(&rParticle2);
      
    //}


    //glfwSetKeyCallback(window, Key_Callback);

    /*TIME IMPLEMENTATION*/
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /*TIME IMPLEMENTAITION*/
        curr_time = clock::now();

        //Duration checker
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);

        prev_time = curr_time;

        //add dur to last iteration to the time since our last frame
        curr_ns += dur;
        if (curr_ns >= timestep)
        {
            //ms converstion
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
           // std::cout << "MS: " << (float)ms.count() << "\n";

            //Reset
            curr_ns -= curr_ns;

           pWorld.Update((float)ms.count() / 1000);
         
        }

        //std::cout << "NORMAL" << std::endl;


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*Model Modifications*/
      // model.moveModel(particle.Position);
      // model.scaleModel(sampleScale);
      // model.rotateModel(sampleRotate, 0.0f /*theta*/);

      //model.renderModel();
        /*Model Modifications*/

        for (std::list<RenderParticle*>::iterator i = rParticleList.begin();
            i != rParticleList.end(); i++)
        {
            //std::cout << "counter: " << *i << std::endl;
            (*i)->Draw();
            //std::cout << "P6" << std::endl;
        }

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