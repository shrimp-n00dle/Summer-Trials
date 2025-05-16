#include "Shader.h"

Shader::Shader()
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

    //Vertex
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Assign the source to vertex shader
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    //Fragment
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f, NULL);
    glCompileShader(fragmentShader);

    /*Create the shader program*/
    shaderProg = glCreateProgram();
    //Attach the compiled Vertex Shader
    glAttachShader(shaderProg, vertexShader);
    //Attach the compiled Fragment Shader
    glAttachShader(shaderProg, fragmentShader);

    glLinkProgram(shaderProg);
}
