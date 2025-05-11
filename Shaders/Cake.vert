#version 330 core

//Gets the data at Attrib Index 0 
//Converts it and stores it into a Vec3
layout(location = 0) in vec3 aPos;

//Creates a transform variable
//We'll assign the transformation matrix here later
uniform mat4 transform;

void main(){
	//gl_Position is predefined
	//this denotes the final position of the vertex / point
	gl_Position = transform * vec4(aPos,1.0); //Turns vec3 into vec4
}