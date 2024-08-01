//shader fragment
#version 430 core

layout(location = 0) out vec4 o_Color;

layout(std430, binding = 1) buffer DensityArrayBuffer {
	int densArray[];
};

flat in int v_InstanceID;

void main() {
	o_Color = vec4(vec3(float(densArray[v_InstanceID] * 0.01)), 1.f);
}