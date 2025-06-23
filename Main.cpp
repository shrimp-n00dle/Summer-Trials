

#define TINYOBJLOADER_IMPLEMENTATION

/*Shader implementation*/
#include <string>
#include <iostream>

/*P6 and Custom Classes inclusion*/
#include "P6/MyVector.h"
#include "P6/MyParticle.h"
#include "P6/PhysicsWorld.h"
#include "P6/DragForceGenerator.h"
#include "P6/GravityForceGenerator.h"

#include "RenderParticle.h"
#include "Classes/Model.h"
#include "Classes/Shader.h"

#include "P6/ParticleContact.h"
#include "P6/AnchorSprings.h"
#include "P6/ParticleSpring.h"
#include "P6/Rod.h";

/*Homework inclusion*/
#include "P6/HW3/Bungee.h"
#include "P6/HW3/Chain.h"

//Import the libraries
#include <chrono>
using namespace std::chrono_literals;
//This is going to be our time in between "frames"
constexpr std::chrono::nanoseconds timestep(16ms);



bool bPressed = false;
float initialPos = -0.6f;

void Key_Callback(GLFWwindow* window, int key, 
                    int scancode /*Physical position of the press*/,
                    int action /*Press/Release*/,
                    int mods /*Which key is held down*/)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        //Each “Space” input adds a force / acceleration on that fram
       
        bPressed = true;

       /* if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) bPressed = true;*/
    } 
    else { bPressed = false; }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Jan Elizabeth Vingno", NULL, NULL);
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
               800, //Width
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
    P6::MyVector sampleScale(1, 0.05f, 0.05f);
    P6::MyVector sampleRotate(0.5f, 1.0f, 0.5f);

    /*Model Binding*/
    model.bind();
    model.scaleModel(sampleScale);

    /*PHYSICS WORLD IMPLEMENTATION*/
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    /*RENDER PARTICLE IMPLEMENTATION*/
    std::list<RenderParticle*> rParticleList;

    /*PARTICLE IMPLEMETATION - BUNGEE*/
    P6::MyParticle pBungeeAnchor = P6::MyParticle();
    pBungeeAnchor.Position = P6::MyVector(-0.2, 0.5, 0);
    pBungeeAnchor.mass = 1;
    pBungeeAnchor.Velocity = P6::MyVector(0, 0, 0);
    pWorld.addParticle(&pBungeeAnchor);
    RenderParticle rBunA = RenderParticle("Pholder", &pBungeeAnchor, &model, P6::MyVector(0.0f, 0.0f, 0.0f));
    rParticleList.push_back(&rBunA);

    P6::MyParticle particle = P6::MyParticle();
    particle.Position = P6::MyVector(-0.2,0,0);
    particle.mass = 1;
    particle.addForce(P6::MyVector(0, 0.1, 0).scalarMultiplication(1.0));
    particle.Velocity = P6::MyVector(0, -0.4, 0);
    pWorld.addParticle(&particle);

    P6::Bungee pBungee = P6::Bungee(&pBungeeAnchor, 0.5, 0.25);
    pWorld.forceRegistry.Add(&particle, &pBungee);

    RenderParticle rParticle = RenderParticle("P1", &particle, &model, P6::MyVector(4.0f, 0.0f, 0.0f));
    rParticleList.push_back(&rParticle);


    /*SECOND PARITCLE - CHAIN*/
    P6::MyParticle pChainAnchor = P6::MyParticle();
    pChainAnchor.Position = P6::MyVector(0.4, 0.5, 0);
    pChainAnchor.mass = 1;
    pChainAnchor.Velocity = P6::MyVector(0, 0, 0);
    pWorld.addParticle(&pChainAnchor);
    RenderParticle rChainA = RenderParticle("CAnchor", &pChainAnchor, &model, P6::MyVector(0.0f, 0.0f, 0.0f));
    rParticleList.push_back(&rChainA);

    P6::MyParticle p2 = P6::MyParticle();
    p2.Position = P6::MyVector(0.4, 0, 0);
    p2.mass = 1;
    p2.addForce(P6::MyVector(0, 0.1, 0).scalarMultiplication(1.0));
    p2.Velocity = P6::MyVector(0, -0.4, 0);
    pWorld.addParticle(&p2);


    P6::Chain pChain = P6::Chain(&pChainAnchor, 0.5, 1);
    pWorld.forceRegistry.Add(&p2, &pChain);


    RenderParticle rp2 = RenderParticle("P2", &p2, &model, P6::MyVector(0.0f, 0.0f,1.0f));
    rParticleList.push_back(&rp2);



    /*KEYBOARD INPUT*/
    glfwSetKeyCallback(window, Key_Callback);

    /*TIME IMPLEMENTATION*/
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);
    std::chrono::milliseconds timer(0);
    int ranking = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
       
        /*TIME IMPLEMENTAITION*/
        curr_time = clock::now();

        //Duration checker
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);

        auto timeAdd = std::chrono::duration_cast<std::chrono::milliseconds> (curr_time - prev_time);
        timer += timeAdd;

        prev_time = curr_time;

        //add dur to last iteration to the time since our last frame
        curr_ns += dur;
        if (curr_ns >= timestep)
        {
            
            //ms converstion
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            //Reset
            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);
        }

      
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (std::list<RenderParticle*>::iterator i = rParticleList.begin();
            i != rParticleList.end(); i++)
        {
            (*i)->Draw();
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