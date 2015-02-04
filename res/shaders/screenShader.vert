#version 130

in vec2 screenCorner;
in vec4 color;
in vec2 squarePosition;

out vec2 squarePosition;
void main() {
    gl_Position.xy = screenCorner;
}
