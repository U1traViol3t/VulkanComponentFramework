#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 lightDir;
layout(location = 3) in vec3 eyeDir; 

layout(location = 0) out vec4 fragColor;

void main() {
    vec4 ks[2] = vec4[] (vec4(0.6, 0.0, 0.0, 0.0), vec4(0.0, 0.6, 0.0, 0.0));
    vec4 kd[2] = vec4[] (vec4(texture(texSampler, fragTexCoord)), vec4(texture(texSampler, fragTexCoord)));
    vec4 ka = 0.1 * kd[0];
    float diff[2];
    float spec[2];
    for (int i = 0; i <2; ++i) {
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0); /// not the direction to the light source
		vec3 reflection = normalize(reflect(-lightDir[i], vertNormal)); /// Reflection is based incedent which means a vector from the light source
		spec[i] = max(dot(eyeDir, reflection), 0.0);
		if(diff[i] > 0.0) spec[i] = pow(spec[i],14.0);
	}
	fragColor =  ka + (diff[0] * kd[0]) + (diff[1] * kd[1]) + (spec[0] * ks[0]) + (spec[1] * ks[1]);	
}