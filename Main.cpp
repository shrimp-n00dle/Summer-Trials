

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

#include "P6/ParticleContact.h"
#include "P6/AnchorSprings.h"
#include "P6/ParticleSpring.h"

#include "P6/Rod.h";

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

    /*PARTICLE IMPLEMETATION*/
    P6::MyParticle particle = P6::MyParticle();
    particle.Position = P6::MyVector(0,0,0);
    particle.mass = 1;
    pWorld.addParticle(&particle);

    RenderParticle rParticle = RenderParticle("P1", &particle, &model, P6::MyVector(4.0f, 0.0f, 0.0f));
    rParticleList.push_back(&rParticle);

    /*SECOND*/
    P6::MyParticle p2 = P6::MyParticle();
    p2.Position = P6::MyVector(0.1, 0, 0);
    p2.mass = 1;
    pWorld.addParticle(&p2);

    RenderParticle rp2 = RenderParticle("P2", &p2, &model, P6::MyVector(0.0f, 1.0f,0.0f));
    rParticleList.push_back(&rp2);

    /*DRAG FORCE IMPLEMENTATION*/
    P6::DragForceGenerator drag = P6::DragForceGenerator(0.014, 0.01);
    pWorld.forceRegistry.Add(&particle, &drag);
    pWorld.forceRegistry.Add(&p2, &drag);

    /*PARTICLE CONTACT IMPLEMENTATION*/
    /*P6::ParticleContact contact = P6::ParticleContact();
    contact.particles[0] = &particle;
    contact.particles[1] = &p2;

    contact.contactNormal = particle.Position - p2.Position;
    contact.contactNormal.magnitude = contact.contactNormal.Magnitude();
    contact.contactNormal = contact.contactNormal.Direction();
    contact.restitution = 1;*/

    /*ADD CONTACTS PWORLD IMPLEMENTATION*/
    particle.Velocity = P6::MyVector(0, 0, 0);
    p2.Velocity = P6::MyVector(-0.1, 0, 0);
    P6::MyVector dir = particle.Position - p2.Position;
    dir.Direction();

    pWorld.AddContact(&particle, &p2, 1, dir);





    /*KEYBOARD INPUT*/
    glfwSetKeyCallback(window, Key_Callback);

    /*TIME IMPLEMENTATION*/
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);
    std::chrono::milliseconds timer(0);
    int ranking = 0;

    /*PARTICLE CONTACT IMPLEMENTATION*/
  /*  P6::ParticleContact contact = P6::ParticleContact();
    contact.particles[0] = &particle;*/
   //contact.particles[1] = &p2;

    /*contact.contactNormal = particle.Position - p2.Position;
    contact.contactNormal = contact.contactNormal.Direction();
    contact.restitution = 0;

    particle.Velocity = P6::MyVector(-0.60,0,0);
    p2.Velocity = P6::MyVector(0.15, 0, 0);

    P6::MyVector dir = particle.Position - p2.Position;
    dir.Direction();

    pWorld.AddContact(&particle, &p2, 1, dir);*/

 /*  P6::AnchorSprings aSpring = P6::AnchorSprings(P6::MyVector(20,0,0), 5, 0.5f);

   pWorld.forceRegistry.Add(&p2, &aSpring);

   p2.mass = 50;*/


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

           contact.resolve((float)ms.count() / 1000);
        }

       //std::cout << "PARTICLE 1 POSIION X " << particle.Position.x << std::endl;
       //std::cout << "PARTICLE 2 POSIION X " << p2.Position.x << std::endl;
       

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (std::list<RenderParticle*>::iterator i = rParticleList.begin();
            i != rParticleList.end(); i++)
        {
            /*RESOLVING INTEPRENETRATION*/

           

           
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