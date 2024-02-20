#version 330 core

in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform float ambientStrength;
uniform vec2 lightPos;
uniform float lightIntensity;
uniform vec3 lightColor;

void main() {
    vec4 texColor = texture(texture0, fragTexCoord);
    vec2 fragPos = fragTexCoord * vec2(900.0, 950.0);
    float distanceToLight = distance(fragPos, lightPos);
    float attenuation = 1.0 / (1.0 + 0.1 * distanceToLight);
    vec3 lightEffect = lightColor * lightIntensity * attenuation;
    vec3 finalColor = texColor.rgb + lightEffect;
    finalColor *= ambientStrength;
    fragColor = vec4(finalColor, texColor.a);
}
