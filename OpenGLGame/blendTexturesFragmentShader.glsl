#version 330 core

out vec4 pixelColor;

uniform vec4 tintColor;
uniform sampler2D diffuseTexture;
uniform sampler2D blendTexture;

// 0. we have loaded the first texture to texture unit 0
// 1. we have loaded the second texture to texture unit 1
// 2. we have created a new shader which takes two texture unit inputs and blends them
// 3. we need to load and use the newly created shader (in main)
// 4a. we should set the uniform `diffuseTexture` to texture unit 0 (in Triangle.h)
// 4b. we need to set the uniform `blendTexture` to texture unit 1 (in Triangle.h)

in vec4 vertexColor;
in vec2 texCoord;

void main()
{
    //pixelColor = vertexColor * texture(diffuseTexture, texCoord);
    pixelColor = mix(texture(diffuseTexture, texCoord),
                     texture(blendTexture, texCoord), 0.5);
    //pixelColor = vertexColor;
}
