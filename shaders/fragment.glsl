#version 330 core

out vec4 FragColor;
uniform float time;

// Use w coordinate to distinguish sun from planets
void main() {
    vec3 color;
    if (gl_FragCoord.w < 0.0) {
        color = vec3(1.0, 0.8, 0.1); // Yellow Sun
    } else {
        color = vec3(0.2 + 0.3 * sin(time), 0.6, 1.0); // Animated bluish planet
    }
    FragColor = vec4(color, 1.0);
}
