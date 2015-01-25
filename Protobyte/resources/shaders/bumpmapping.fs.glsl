#version 430 core

in vec4 vertCol; // orig attribute color set in v. shader
out vec4 color;

// Texture maps
//layout (binding = 0) uniform sampler2D shadowMap;
//layout (binding = 0) uniform sampler2D diffuseMap;
//layout (binding = 1) uniform sampler2D bumpMap;

// Texture maps
uniform bool shadowPassFlag;
uniform sampler2DShadow shadowMap;
uniform sampler2D diffuseMap;
uniform sampler2D bumpMap;

in vec4 shadowMapCoords;


// max 8 lt srcs (fer now...)
struct Light {
	vec3 position;
	vec3 intensity;
	//vec4 diffuse;
	//vec4 ambient;
	//vec4 specular;
};

// currently max 8 lts
uniform Light lights[8];

// global ambient light
uniform vec3 globalAmbientLight;

// materials
uniform vec4 diffuseMaterial;
uniform vec4 ambientMaterial;
uniform vec4 specularMaterial;
uniform vec4 emissiveMaterial;
uniform float shininess;

//uniform bool isShadowEnabled;

// multiplier to null out lighting factors for 2D rendering
// diffuse, specular, ambientMat, globalAmbientLight
// avoids need for conditional testing
// 3D default: (1,1,1,1)
// 2D default: (0,0,0,0)
uniform vec4 lightRenderingFactors;




in VS_OUT
{
    vec2 texcoord;
    vec3 eyeDir;
    vec3 lightDir[8];
    vec3 normal;
} fs_in;



void main(void)
{

	// check for shadow pass
	if(shadowPassFlag){
		return;
	}
	
	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	for(int i=0; i<8; ++i){
		// Normalize our incomming view and light direction vectors.
		vec3 V = normalize(fs_in.eyeDir);
		vec3 L = normalize(fs_in.lightDir[i]); // ***********multi here
    
		// Calculate diffuse color with simple N dot L.
		// Read the normal from the normal map and normalize it.
		vec3 N = normalize(texture(bumpMap, fs_in.texcoord).rgb * 2.0 - vec3(1.0));
    
		// Uncomment this to use surface normals rather than the normal map
		// N = vec3(0.0, 0.0, 1.0);
    
		// Calculate R ready for use in Phong lighting.
		vec3 R = reflect(-L, N); // ***********multi here

		// Fetch the diffuse color from the texture.
		vec3 diffuse_color = texture(diffuseMap, fs_in.texcoord).rgb;
		diffuse += max(dot(N, L), 0.0) * diffuse_color * vec3(diffuseMaterial) * lights[i].intensity; // ***********multi here
		// Uncomment this to turn off diffuse shading
		// diffuse = vec3(0.0);

		// Assume that specular color is white - it could also come from a texture
		//vec3 specular_color = vec3(1.0);
		// Calculate Phong specular highlight
		specular += max(pow(dot(R, V), shininess), 0.0) * vec3(specularMaterial) * lights[i].intensity;
		// Uncomment this to turn off specular highlights
		// specular = vec3(0.0);
	}

	
	
	
	// shadow map
	if(shadowMapCoords.w>1) {
		//check the shadow map texture to see if the fragment is in shadow
		float shadow = textureProj(shadowMap, shadowMapCoords);
		//darken the diffuse component apprpriately


		diffuse = mix(diffuse, diffuse*shadow, 0.4); 
	}

    // Final color is diffuse + specular + ambient with lightRendering Factors enabling/disabling lighting effects for 2D rendering

	color = vertCol*lightRenderingFactors.w + vec4(diffuse*lightRenderingFactors.x + specular*lightRenderingFactors.y + (vec3(ambientMaterial)*globalAmbientLight)*lightRenderingFactors.z, 1.0);

	color.a = vertCol.a;


}
