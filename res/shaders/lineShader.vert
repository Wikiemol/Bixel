#version 130

in vec2 position;
void main() {
    gl_Position.xy = position;
    gl_Position.zw = vec2(0, 1);
}
