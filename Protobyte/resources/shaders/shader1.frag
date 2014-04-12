#version 400

// no more gl_FragColor, so we need to declare ourself
// great shader tutorials: http://antongerdelan.net/opengl/texturemaps.html

in vec4 color;
in vec2 textureCoords;
in vec4 eyePosition;
in vec3 normal;

in vec4 shadowMapCoords;

//Lighting uniforms
struct Light {
	vec3 position;
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
};

uniform Light lights[8];


// active texture slot 0
//layout (binding = 0) uniform sampler2D basic_texture;
uniform sampler2D textureSampler;
uniform sampler2DShadow shadowMapTexture;  //shadowmap texture

layout (location = 0) out vec4 fragColor;


void main(){

	const vec3 lightColor = vec3(1, 1, 1);
    const vec3 globalAmbient = vec3(.3, .3, .3);

  // Position in eye space
    vec3 P = vec3(eyePosition);

  // Normalize normal in eye space
    vec3 N = normalize(normal);

  // Compute the emissive term
    vec3 emissive = vec3(0,0,0);

  // Compute the ambient term
    //vec3 ambient = ambientColor * globalAmbient;
	vec3 ambient = vec3(lights[0].ambient) * globalAmbient ;

	
  // Compute the diffuse term
  // Normalized vector toward the light source
	vec3 L = normalize(lights[0].position - P);
    float diffuseLight = max(dot(N, L), 0);
	vec4 tex = texture(textureSampler, textureCoords.st)*color;
	vec3 diffuse = vec3(lights[0].diffuse) * vec3(tex) *  diffuseLight;

  // Compute the specular term
    vec3 V = normalize(-P);      // Normalized vector toward the viewpoint
    vec3 H = normalize(L + V);   // Normalized vector that is halfway between V and L
    float specularLight = pow(max(dot(N, H),0), 120);
    if(diffuseLight <= 0){ specularLight = 0; }

	vec3 specular = vec3(lights[0].specular * lights[0].diffuse) * specularLight;

  // Define the final vertex color

 // shadow mapping
  if(shadowMapCoords.w > 1) {
    float shadow = textureProj(shadowMapTexture, shadowMapCoords);
    //darken the diffuse component apprpriately
    diffuse = mix(diffuse, diffuse*shadow, 0.5); 
  }

  gl_FragColor = vec4(emissive + ambient + diffuse + specular, 1);
  gl_FragColor.a = color.a;
}