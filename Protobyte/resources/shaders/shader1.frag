#version 400

// no more gl_FragColor, so we need to declare ourself
// great shader tutorials: http://antongerdelan.net/opengl/texturemaps.html

in vec4 color;
in vec2 textureCoords;
in vec4 eyePosition;
in vec3 normal;

uniform vec3 light0Position;
uniform vec4 light0Diffuse;
uniform vec4 light0Ambient;
uniform vec4 light0Specular;


// active texture slot 0
//layout (binding = 0) uniform sampler2D basic_texture;
uniform sampler2D textureSampler;

layout (location = 0) out vec4 fragColor;


void main(){

	const vec3 lightColor = vec3(1, 1, 1);
    const vec3 globalAmbient = vec3(0.2, 0.2, 0.2);

  // Position in eye space
    vec3 P = vec3(eyePosition);

  // Normalize normal in eye space
    vec3 N = normalize(normal);

  // Compute the emissive term
    vec3 emissive = vec3(0,0,0);

  // Compute the ambient term
    //vec3 ambient = ambientColor * globalAmbient;
	vec3 ambient = vec3(.2, .2, .2) * globalAmbient ;

	
  // Compute the diffuse term
  // Normalized vector toward the light source
    vec3 L = normalize(light0Position - P);
    float diffuseLight = max(dot(N, L), 0);
	 vec4 tex = texture(textureSampler, textureCoords.st);
    vec3 diffuse = vec3(light0Diffuse) * vec3(tex) *  diffuseLight;

  // Compute the specular term
    vec3 V = normalize(-P);      // Normalized vector toward the viewpoint
    vec3 H = normalize(L + V);   // Normalized vector that is halfway between V and L
    float specularLight = pow(max(dot(N, H),0), 120);
    if(diffuseLight <= 0)
    specularLight = 0;
    vec3 specular = vec3(light0Specular * light0Diffuse) * specularLight;

  // Define the final vertex color

  
  gl_FragColor = vec4(emissive + ambient + diffuse + specular, 1);
	//gl_FragColor = sample;
}