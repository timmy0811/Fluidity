//shader vertex
#version 430 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec2 u_TileSize;
uniform ivec2 u_GridDim;

flat out int v_InstanceID;

void main()
{
	vec2 pos = a_Position.xy + vec2(u_TileSize.x * (gl_InstanceID % u_GridDim.x), u_TileSize.y * floor(gl_InstanceID / u_GridDim.x));
	gl_Position = u_ViewProjection * u_Transform * vec4(pos, 0.0, 1.0);
	v_InstanceID = gl_InstanceID;
};