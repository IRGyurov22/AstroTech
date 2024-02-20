#version 330 core

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;

// Uniforms
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

void main()
{
    // Pass vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragNormal = normalize(mat3(transpose(inverse(matModel))) * vertexNormal);
    fragWorldPos = (matModel * vec4(vertexPosition, 1.0)).xyz;

    // Calculate final vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
