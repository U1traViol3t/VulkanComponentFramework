#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;


layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 lightDir;
layout(location = 3) in vec3 eyeDir; 

layout(location = 0) out vec4 fragColor;

void main() {
    vec4 ks = vec4(0.6, 0.6, 0.6, 0.0);
	vec4 kd = texture(texSampler, fragTexCoord); /// const means it cannot be changed just like C++
	vec4 ka = 0.1 * kd;

    float diff = max(dot(vertNormal, lightDir), 0.0);

    vec3 reflection = normalize(reflect(-lightDir, vertNormal));
    float spec = max(dot(eyeDir, reflection), 0.0);
	spec = pow(spec,14.0);

    fragColor = ka + (diff * kd) + (spec * ks);
}