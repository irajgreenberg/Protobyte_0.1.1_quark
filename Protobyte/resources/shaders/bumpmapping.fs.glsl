#version 420 core

out vec4 color;

// Color and normal maps
//layout (binding = 0) uniform sampler2D diffuseMap;
//layout (binding = 1) uniform sampler2D bumpMap;

uniform sampler2D diffuseMap;
uniform sampler2D bumpMap;

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


in VS_OUT
{
    vec2 texcoord;
    vec3 eyeDir;
    vec3 lightDir;
    vec3 normal;
} fs_in;

void main(void)
{
    // Normalize our incomming view and light direction vectors.
    vec3 V = normalize(fs_in.eyeDir);
    vec3 L = normalize(fs_in.lightDir);
    // Read the normal from the normal map and normalize it.
    vec3 N = normalize(texture(bumpMap, fs_in.texcoord).rgb * 2.0 - vec3(1.0));
    // Uncomment this to use surface normals rather than the normal map
    // N = vec3(0.0, 0.0, 1.0);
    // Calculate R ready for use in Phong lighting.
    vec3 R = reflect(-L, N);

    // Fetch the diffuse albedo from the texture.
    vec3 diffuse_albedo = texture(diffuseMap, fs_in.texcoord).rgb;
    // Calculate diffuse color with simple N dot L.
    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo * vec3(diffuseMaterial) * lights[0].intensity;
    // Uncomment this to turn off diffuse shading
    // diffuse = vec3(0.0);

    // Assume that specular albedo is white - it could also come from a texture
    //vec3 specular_albedo = vec3(1.0);
    // Calculate Phong specular highlight
    vec3 specular = max(pow(dot(R, V), shininess), 0.0) * vec3(specularMaterial);
    // Uncomment this to turn off specular highlights
    // specular = vec3(0.0);

    // Final color is diffuse + specular
    color = vec4(diffuse + specular + vec3(ambientMaterial)*globalAmbientLight, 1.0);
}
