#version 330 core 

out vec4 FragColor; //Returns a color
//Simple shader that colors red

uniform sampler2D tex0;

in vec2 texCoord;

uniform vec3 currColor;

void main(){
	//FragColor = vec4(currColor, 1.0f); //Ranges from 0 -1

	FragColor = texture(tex0, texCoord);
}