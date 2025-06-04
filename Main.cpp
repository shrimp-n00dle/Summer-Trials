

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



bool bPressed = false;

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
    window = glfwCreateWindow(800, 600, "Jan Vingno", NULL, NULL);
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
    particle.Velocity = P6::MyVector(0, 0, 0);
    particle.Position = P6::MyVector(-0.5f,0.4f,0);
    particle.damping = 1;
    particle.mass = 1;
    /*FORCE IMPLEMENTATION*/
    P6::ForceGenerator force;   
    particle.Acceleration = P6::MyVector(force.randomForce(), 0, 0);
    particle.addForce(P6::MyVector(1, 0, 0));
    force.updateForce(&particle, 0.1);
    pWorld.forceRegistry.Add(&particle, &force);
    pWorld.addParticle(&particle);

    RenderParticle rParticle = RenderParticle("P1", &particle, &model, P6::MyVector(4.0f, 0.0f, 0.0f));
    rParticleList.push_back(&rParticle);

    /*SECOND*/
    P6::MyParticle p2 = P6::MyParticle();
    p2.Velocity = P6::MyVector(0, 0, 0);
    p2.Position = P6::MyVector(-0.5f, 0.2f, 0);
    p2.damping = 1;
    p2.mass = 1;
    P6::ForceGenerator f2;
    p2.Acceleration = P6::MyVector(f2.randomForce(), 0, 0);
    p2.addForce(P6::MyVector(1, 0, 0));
    f2.updateForce(&p2, 0.1);
    pWorld.forceRegistry.Add(&p2, &f2);
    pWorld.addParticle(&p2);
    RenderParticle rp2 = RenderParticle("P2", &p2, &model, P6::MyVector(0.0f, 0.0f, 4.0f));
    rParticleList.push_back(&rp2);

    /*THIRD*/
    P6::MyParticle p3 = P6::MyParticle();
    p3.Velocity = P6::MyVector(0, 0, 0);
    p3.Position = P6::MyVector(-0.5f,0.0f, 0);
    p3.damping = 1;
    p3.mass = 1;
    P6::ForceGenerator f3;
    p3.Acceleration = P6::MyVector(f3.randomForce(), 0, 0);
    p3.addForce(P6::MyVector(1, 0, 0));
    f3.updateForce(&p3, 0.1);
    pWorld.forceRegistry.Add(&p3, &f3);
    pWorld.addParticle(&p3);
    RenderParticle rp3 = RenderParticle("P3", &p3, &model, P6::MyVector(0.0f, 4.0f, 0.0f));
    rParticleList.push_back(&rp3);


    /*PLAYER*/
    P6::MyParticle p = P6::MyParticle();
    p.Velocity = P6::MyVector(0, 0, 0);
    p.Position = P6::MyVector(-0.5f, -0.4f, 0);
    p.damping = 1;
    p.mass = 1;
    P6::ForceGenerator f;
    p.Acceleration = P6::MyVector(1, 0, 0);
    p.addForce(P6::MyVector(1, 0, 0));
    f.updateForce(&p, 0.1);
    pWorld.forceRegistry.Add(&p, &f);
    pWorld.addParticle(&p);
    RenderParticle rp = RenderParticle("P4 (Player)" ,&p, &model, P6::MyVector(2.0f, 0.0f, 2.0f));
    rParticleList.push_back(&rp);

    /*KEYBOARD INPUT*/
    glfwSetKeyCallback(window, Key_Callback);

    /*TIME IMPLEMENTATION*/
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);
    std::chrono::nanoseconds timer(0);
    int ranking = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /*TIME IMPLEMENTAITION*/
        curr_time = clock::now();

        //Duration checker
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);

        //auto timer = std::chrono::duration_cast<std::chrono::milliseconds>(curr_time - prev_time);

        prev_time = curr_time;

        timer += curr_ns;

        //accumulate the force based on the no of times you press the space
        if (bPressed) {
            p.addForce(P6::MyVector(1, 0, 0)); bPressed = false;
        }

        //add dur to last iteration to the time since our last frame
        curr_ns += dur;
        if (curr_ns >= timestep)
        {
            
            //ms converstion
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            //Reset
            curr_ns -= curr_ns;

           pWorld.Update((float)ms.count() / 1000);

           //afterwhich total acceleration goes back to 0
           p.resetForce();
        }
       

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (std::list<RenderParticle*>::iterator i = rParticleList.begin();
            i != rParticleList.end(); i++)
        {
            if ((*i)->PhysicsParticle->Position.x >= 0.5) (*i)->PhysicsParticle->Destroy();

            if (((*i)->PhysicsParticle->IsDestroyed())) 
                {
                   ranking = (*i)->recordTime((float)timer.count() / 1000, ranking);
                } 
           
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