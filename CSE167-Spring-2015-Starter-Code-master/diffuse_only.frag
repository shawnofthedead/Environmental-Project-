#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 position;
varying vec3 normal;
varying vec4 vertex;

uniform float myShaderVar;
uniform float myShaderYellow;
uniform float myShaderGreen;
uniform float myShaderGrey;
uniform float myShaderWhite;

void main()
{
    //Declare variables for intermediate calculations
    vec4 finalColor;
    vec3 lightDir;
    float attenuation;
    float distance;

    
    //Declare and initialize variables for storing lighting results
    vec3 finalLighting = vec3(gl_FrontMaterial.emission);
    vec3 ambientReflection = vec3(0.0,0.0,0.0);
    vec3 diffuseReflection = vec3(0.0,0.0,0.0);

	vec3 ambient = vec3(0.2, 0.2, 0.2);
	vec3 diffuse = vec3(0.0, 0.0, 0.0);


	if(vertex.y <= myShaderVar){
		ambient = vec3(0.0, 0.0, 0.2);
		diffuse = vec3(0.0, 0.0, 0.8);
	}
	else if(vertex.y > myShaderVar && vertex.y <= myShaderYellow){
		ambient = vec3(0.0, 0.0, 0.2);
		diffuse = vec3(0.8, 0.8, 0.0);
	}
	else if(vertex.y > myShaderYellow && vertex.y <= myShaderGreen){
		ambient = vec3(0.0, 0.2, 0.0);
		diffuse = vec3(0.0, 0.9, 0.0);
	}
	else if(vertex.y > myShaderGreen && vertex.y <= myShaderGrey){
		ambient = vec3(0.4, 0.4, 0.4);
		diffuse = vec3(0.6, 0.6, 0.6);
	}
	else if(vertex.y > myShaderGrey && vertex.y <= myShaderWhite){
		ambient = vec3(0.2, 0.2, 0.2);
		diffuse = vec3(1.0, 1.0, 1.0);
	}
    
    //Loop through all 8 lights that the OpenGL fixed function pipeline supports
    for (int i = 0; i < 8; ++i)
    {
        //Calculate the light direction
        lightDir = gl_LightSource[i].position.xyz - position.xyz;
        
        //Add the ambient light factor to the ambient accumulator
	
		ambientReflection += ambient * vec3(gl_LightSource[i].ambient);
			
        //If the light is behind the surface, continue
        if(dot(normal, lightDir) < 0.0)
            continue;
        
        //Set the default attenuation to none (by the multiplicative identity, this is 1.0)
        attenuation = 1.0;
        
        //If the light is not a directional light, then apply the appropriate attenuation
        if (0.0 != gl_LightSource[i].position.w)
        {
            distance = length(lightDir);
            attenuation = 1.0 / (gl_LightSource[i].constantAttenuation
                                 + gl_LightSource[i].linearAttenuation * distance
                                 + gl_LightSource[i].quadraticAttenuation * distance * distance);
        }
        
        //Calculate the diffuse reflectance and add it to the diffuse accumulator
        diffuseReflection += attenuation * vec3(gl_LightSource[i].diffuse) * diffuse * max(0.0, dot(normal, normalize(lightDir)));
    }
    
    //Sum all of the lighting together
    finalLighting = finalLighting + ambientReflection + diffuseReflection;
    
    //Return the final lighting
	//------------------------------------------

    gl_FragColor = vec4(finalLighting, 1.0);
	

	

}