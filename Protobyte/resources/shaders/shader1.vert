#version 400

// attibutes in memory
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;
layout (location = 3) in vec2 vertexTextureCoords;

// passed to frag shader
out vec4 color;
out vec2 textureCoords;
out vec4 eyePosition;
out vec3 normal;
out vec4 shadowMapCoords;

// Lighting
// all uniforms delcared in fragment shader

//struct Light {
	//vec3 position;
	//vec4 diffuse;
	//vec4 ambient;
//	vec4 specular;
//};

//uniform Light lights[8];

// coord transforms
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 lightModelViewProjectionMatrix;


void main(){
  
  textureCoords = vertexTextureCoords;

  shadowMapCoords = lightModelViewProjectionMatrix * vec4(vertexPosition, 1);
  
  // Position in clip space
  gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1);

  
  // Position in eye space
    eyePosition = modelViewMatrix * vec4(vertexPosition, 1);

  // Normal in eye space
    normal = mat3(modelViewMatrix) * vertexNormal;

	color = vertexColor;

}