#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform CameraUniformBufferObject {
    mat4 view;
    mat4 proj;
} cameraUBO;

layout(binding = 1) uniform ModelUniformBufferObject {
    mat4 model;
    vec4 lightPos[2];
} modelUBO;

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 texCoord;


layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 vertNormal;
layout(location = 2) out vec3 lightDir[2];
layout(location = 4) out vec3 eyeDir; 

void main() {
    fragTexCoord = texCoord;
    
    mat3 normalMatrix = mat3(transpose(inverse(modelUBO.model)));
    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation 
    
    vec3 vertPos = vec3(cameraUBO.view * modelUBO.model * vec4(vVertex, 1.0)); /// This is the position of the vertex from the origin
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;

    for (int i = 0; i < 2; ++i) {
          lightDir[i] = normalize(modelUBO.lightPos[i].xyz - vertPos); /// Create the light direction. I do the math with in class 
    }

    gl_Position = cameraUBO.proj * cameraUBO.view * modelUBO.model * vec4(vVertex, 1.0);
}