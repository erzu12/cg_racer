# version 330 core
out vec4 FragColor;

uniform sampler2D image;

in vec2 pos;

void main() {
    vec4 texColor = texture(image, pos);
    if(texColor.a < 0.1)
        discard;
	FragColor = texColor;
}
