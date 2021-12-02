#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPos;
} ubo;

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 vertNormal;
layout(location = 2) out vec3 lightDir;
layout(location = 3) out vec3 eyeDir; 

void main() {
    fragTexCoord = texCoord;
    mat3 normalMatrix = mat3(transpose(inverse(ubo.model)));

    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(ubo.view * ubo.model * vec4(vVertex, 1.0)); /// This is the position of the vertex from the origin
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir = normalize(ubo.lightPos.xyz - vertPos); /// Create the light direction. I do the math within class 

    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(vVertex, 1.0);
}