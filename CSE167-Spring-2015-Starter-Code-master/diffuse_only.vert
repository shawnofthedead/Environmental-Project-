#version 120

varying vec4 position;
varying vec3 normal;
varying vec4 vertex;

uniform float myShaderVar;
uniform float myShaderWhite;
void main()
{
    //Transform the normal into world coordinates
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
	position = gl_Vertex;
	vertex = gl_Vertex;
	
	if(position.y >= 0 && position.y < myShaderVar){
		position.y = myShaderVar;
		normal = vec3(0.0, 1.0, 0.0);
	}
	
	
    //Transform the vertex into world coordinates
    position = gl_ModelViewMatrix * position;
	 
    //Set the gl position of this vertex
    //gl_Position = ftransform();
	gl_Position = gl_ProjectionMatrix * position;
}
