#include <glad/glad.h> /*This helps with simplifying runtime when dealing with pointers*/
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    /*Initial definition of verticies array*/
    GLfloat verticiesSetUp[]
    { -0.5f,-0.5f,0,0,0.5f,0,0.5f,-0.5f,0 };

    /*Vertex Array Object* - It stores the format of the vertex data as well as the Buffer Objects (see below) providing the vertex data arrays
    Vertex Buffer Object - store an array of unformatted memory allocated by the OpenGL context (AKA the GPU). These can be used to store vertex data,
    Element Buffer Object - This will reduce the number of vertices by removing redundant ones*/

    /*VAO VBO Intialization*/
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    /*Bind the VAO so all other funtions after this will follow the VAO*/
    glBindVertexArray(VAO);

    /*Assigning the Array Buffers to store the added positions*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*Converting VAO into bytes
    Paramater names - What data is the buffer located
    The size of the whole buffer
    the vertext array
    renderer*/
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticiesSetUp), verticiesSetUp, GL_STATIC_DRAW);


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
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /*Clean the vertex annd buffers*/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}