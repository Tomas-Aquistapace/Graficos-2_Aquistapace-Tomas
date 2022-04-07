#version 330 core

uniform sampler2D ourTexture;
//uniform vec3 lightColor;
//uniform vec3 objectColor;

in vec2 TexCoord;

void main()
{
	gl_FragColor = texture(ourTexture, TexCoord);

    // -------------------------------
    // Lighting:

    //float ambientStrength = 0.1;
    //vec3 ambient = ambientStrength * lightColor;
    //
    //vec3 result = ambient * objectColor;
    //FragColor = vec4(result, 1.0);
}