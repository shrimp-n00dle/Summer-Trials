#version 330 core 

out vec4 FragColor; //Returns a color
//Simple shader that colors red

in mat3 currColor;

void main(){
	FragColor = vec4(currColor, 1.0f); //Ranges from 0 -1
}