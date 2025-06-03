// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <fstream>
// #include <sstream>
// #include <iostream>
// #include <cmath>
// #include <vector>

// const unsigned int WIDTH = 800, HEIGHT = 600;

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

// std::string readFile(const char* path) {
//     std::ifstream file(path);
//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     return buffer.str();
// }

// GLuint createShader(const char* vPath, const char* fPath) {
//     std::string vertexCode = readFile(vPath);
//     std::string fragmentCode = readFile(fPath);
//     const char* vShaderCode = vertexCode.c_str();
//     const char* fShaderCode = fragmentCode.c_str();

//     GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertex, 1, &vShaderCode, nullptr);
//     glCompileShader(vertex);

//     GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragment, 1, &fShaderCode, nullptr);
//     glCompileShader(fragment);

//     GLuint shader = glCreateProgram();
//     glAttachShader(shader, vertex);
//     glAttachShader(shader, fragment);
//     glLinkProgram(shader);

//     glDeleteShader(vertex);
//     glDeleteShader(fragment);

//     return shader;
// }

// std::vector<float> generateCircleVertices(float radius, int segments) {
//     std::vector<float> vertices;
//     vertices.push_back(0.0f);
//     vertices.push_back(0.0f);
//     vertices.push_back(0.0f);
//     for (int i = 0; i <= segments; ++i) {
//         float angle = 2.0f * M_PI * i / segments;
//         vertices.push_back(radius * cos(angle));
//         vertices.push_back(radius * sin(angle));
//         vertices.push_back(0.0f);
//     }
//     return vertices;
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// void uploadCircleToVAO(const std::vector<float>& data, GLuint& vao, GLuint& vbo) {
//     glGenVertexArrays(1, &vao);
//     glGenBuffers(1, &vbo);
//     glBindVertexArray(vao);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
// }

// void drawObject(GLuint shader, GLuint vao, int vertexCount, glm::mat4 mvp, float time) {
//     glUseProgram(shader);
//     glUniform1f(glGetUniformLocation(shader, "time"), time);
//     glUniformMatrix4fv(glGetUniformLocation(shader, "uMVP"), 1, GL_FALSE, &mvp[0][0]);
//     glBindVertexArray(vao);
//     glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
// }

// int main() {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mini Solar System", nullptr, nullptr);
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

//     GLuint vaoSun, vboSun, vaoP1, vboP1, vaoP2, vboP2, vaoMoon, vboMoon;

//     auto sun = generateCircleVertices(0.25f, 50);
//     auto p1  = generateCircleVertices(0.12f, 50);
//     auto p2  = generateCircleVertices(0.10f, 50);
//     auto moon = generateCircleVertices(0.05f, 50);

//     uploadCircleToVAO(sun, vaoSun, vboSun);
//     uploadCircleToVAO(p1, vaoP1, vboP1);
//     uploadCircleToVAO(p2, vaoP2, vboP2);
//     uploadCircleToVAO(moon, vaoMoon, vboMoon);

//     GLuint shader = createShader("shaders/vertex.glsl", "shaders/fragment.glsl");

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     while (!glfwWindowShouldClose(window)) {
//         float time = glfwGetTime();
//         glClearColor(0.02f, 0.02f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);
//         glm::mat4 view = glm::mat4(1.0f);

//         // Sun
//         glm::mat4 sunModel = glm::mat4(1.0f);
//         drawObject(shader, vaoSun, sun.size() / 3, proj * view * sunModel, time);

//         // Planet 1
//         float p1Angle = time * 0.6f;
//         glm::vec3 p1Pos(cos(p1Angle) * 1.1f, sin(p1Angle) * 1.1f, -0.01f);
//         glm::mat4 p1Model = glm::translate(glm::mat4(1.0f), p1Pos);
//         drawObject(shader, vaoP1, p1.size() / 3, proj * view * p1Model, time);

//         // Planet 2
//         float p2Angle = time * 0.3f;
//         glm::vec3 p2Pos(cos(p2Angle) * 1.6f, sin(p2Angle) * 1.6f, -0.01f);
//         glm::mat4 p2Model = glm::translate(glm::mat4(1.0f), p2Pos);
//         drawObject(shader, vaoP2, p2.size() / 3, proj * view * p2Model, time);

//         // Moon (relative to Planet 2)
//         float mAngle = time * 1.5f;
//         glm::vec3 moonOffset(cos(mAngle) * 0.25f, sin(mAngle) * 0.25f, -0.01f);
//         glm::mat4 moonModel = glm::translate(p2Model, moonOffset);
//         drawObject(shader, vaoMoon, moon.size() / 3, proj * view * moonModel, time);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glDeleteVertexArrays(1, &vaoSun);
//     glDeleteVertexArrays(1, &vaoP1);
//     glDeleteVertexArrays(1, &vaoP2);
//     glDeleteVertexArrays(1, &vaoMoon);
//     glfwTerminate();
//     return 0;
// }
// File: src/main.cpp

// File: src/main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// ————————————————
// Constants & Globals
// ————————————————
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Camera spherical coordinates & control state
static float cameraYaw    = 0.0f;   // left/right
static float cameraPitch  = 0.0f;   // up/down
static float cameraRadius = 5.0f;   // distance from origin
static bool  isDragging   = false;
static double lastX, lastY;         // previous mouse positions

// ————————————————
// Utility: Read entire file into string
// ————————————————
static std::string readFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file " << path << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// ————————————————
// Utility: Compile & link shaders into a program
// ————————————————
static GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    std::string vCode = readFile(vertPath);
    std::string fCode = readFile(fragPath);
    const char* vSrc = vCode.c_str();
    const char* fSrc = fCode.c_str();

    // Compile vertex shader
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vSrc, nullptr);
    glCompileShader(vert);
    GLint success;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(vert, 512, nullptr, log);
        std::cerr << "Vertex shader compile error:\n" << log << "\n";
    }

    // Compile fragment shader
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fSrc, nullptr);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(frag, 512, nullptr, log);
        std::cerr << "Fragment shader compile error:\n" << log << "\n";
    }

    // Link program
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(prog, 512, nullptr, log);
        std::cerr << "Shader link error:\n" << log << "\n";
    }

    // Cleanup
    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

// ————————————————
// Utility: Generate vertices for a filled circle (triangle fan)
//   radius: circle radius
//   segments: how many subdivisions (higher = smoother)
// Returns {cx,cy,cz, x1,y1,z1, x2,y2,z2, …}
// ————————————————
static std::vector<float> generateCircle(float radius, int segments) {
    std::vector<float> verts;
    // Center point
    verts.push_back(0.0f);
    verts.push_back(0.0f);
    verts.push_back(0.0f);
    // Perimeter points
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        verts.push_back(radius * cos(angle));
        verts.push_back(radius * sin(angle));
        verts.push_back(0.0f);
    }
    return verts;
}

// ————————————————
// Utility: Upload a circle’s vertex data into a VAO/VBO
//   vao, vbo passed by reference, so caller can delete later
// ————————————————
static void uploadToVAO(const std::vector<float>& data, GLuint& vao, GLuint& vbo) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    // aPos = location 0, 3 floats/vertex, tightly packed
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ————————————————
// Draw a circle VAO with a given MVP and time (for shader pulsing).
// ————————————————
static void drawObject(GLuint shader, GLuint vao, int vertexCount, const glm::mat4& mvp, float time) {
    glUseProgram(shader);
    GLint locTime = glGetUniformLocation(shader, "time");
    glUniform1f(locTime, time);
    GLint locMVP = glGetUniformLocation(shader, "uMVP");
    glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    glBindVertexArray(0);
}

// ————————————————
// GLFW Callbacks for resizing, mouse, scroll
// ————————————————
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        isDragging = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isDragging = false;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!isDragging) return;
    float dx = float(xpos - lastX);
    float dy = float(ypos - lastY);
    cameraYaw   += dx * 0.25f;
    cameraPitch += dy * 0.25f;
    // Clamp pitch
    if (cameraPitch > 89.0f)  cameraPitch = 89.0f;
    if (cameraPitch < -89.0f) cameraPitch = -89.0f;
    lastX = xpos; lastY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    cameraRadius -= float(yoffset) * 0.3f;
    if (cameraRadius < 1.5f)  cameraRadius = 1.5f;
    if (cameraRadius > 20.0f) cameraRadius = 20.0f;
}

// ————————————————
// MAIN ENTRY
// ————————————————
int main() {
    // 1) Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2) Create Window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mini Solar System", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3) Load OpenGL via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // 4) Set viewport and callbacks
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 5) Generate circle data for Sun, Planet1, Planet2, Moon
    //    Radii chosen so nothing overlaps
    std::vector<float> sunVerts  = generateCircle(0.25f, 64);
    std::vector<float> p1Verts   = generateCircle(0.12f, 64);
    std::vector<float> p2Verts   = generateCircle(0.10f, 64);
    std::vector<float> moonVerts = generateCircle(0.05f, 64);

    // 6) Create VAOs/VBOs
    GLuint vaoSun,  vboSun;
    GLuint vaoP1,  vboP1;
    GLuint vaoP2,  vboP2;
    GLuint vaoMoon, vboMoon;

    uploadToVAO(sunVerts,  vaoSun,  vboSun);
    uploadToVAO(p1Verts,   vaoP1,   vboP1);
    uploadToVAO(p2Verts,   vaoP2,   vboP2);
    uploadToVAO(moonVerts, vaoMoon, vboMoon);

    // 7) Compile & link shaders
    GLuint shaderProg = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    // 8) Disable depth (2D layering) + enable alpha blending
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 9) Main loop
    while (!glfwWindowShouldClose(window)) {
        float t = static_cast<float>(glfwGetTime());

        // Clear screen
        glClearColor(0.02f, 0.02f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- CAMERA SETUP (spherical → cartesian) ---
        float yawRad   = glm::radians(cameraYaw);
        float pitchRad = glm::radians(cameraPitch);
        glm::vec3 camPos;
        camPos.x = cameraRadius * cos(pitchRad) * cos(yawRad);
        camPos.y = cameraRadius * sin(pitchRad);
        camPos.z = cameraRadius * cos(pitchRad) * sin(yawRad);
        glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        float aspect = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
        float orthoSize = 4.0f;
        glm::mat4 proj = glm::ortho(-orthoSize * aspect, orthoSize * aspect,
                                    -orthoSize,           orthoSize,
                                    -10.0f, 10.0f);

        // —————————— DRAW SUN ——————————
        glm::mat4 sunModel = glm::mat4(1.0f);

        // Force a static test planet to the right of the Sun
glm::mat4 debugModel = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
debugModel[3][3] = +1.0f;  // mark as non-Sun
glm::mat4 debugMVP = proj * view * debugModel;
drawObject(shaderProg, vaoP1, static_cast<int>(p1Verts.size() / 3), debugMVP, t);

        // Pulsing scale
        float pulse = 1.0f + 0.2f * sin(t * 2.0f);
        sunModel = glm::scale(sunModel, glm::vec3(0.25f * pulse));
        // Mark w < 0 so fragment shader knows “this is Sun”
        sunModel[3][3] = -1.0f;
        glm::mat4 sunMVP = proj * view * sunModel;
        drawObject(shaderProg, vaoSun, static_cast<int>(sunVerts.size() / 3), sunMVP, t);

        // —————————— DRAW PLANET 1 ——————————
        float p1Angle = t * 0.6f;
        glm::vec3 p1Pos3D(cos(p1Angle) * 1.0f, sin(p1Angle) * 1.0f, 0.0f);
        glm::mat4 p1Model = glm::translate(glm::mat4(1.0f), p1Pos3D);
        // Planet 1 spins on its axis:
        p1Model = glm::rotate(p1Model, t * 2.0f, glm::vec3(0, 0, 1));
        p1Model[3][3] = +1.0f;  // w > 0 → “planet” in fragment shader
        glm::mat4 p1MVP = proj * view * p1Model;
        drawObject(shaderProg, vaoP1, static_cast<int>(p1Verts.size() / 3), p1MVP, t);

        // —————————— DRAW PLANET 2 ——————————
        float p2Angle = t * 0.3f;
        glm::vec3 p2Pos3D(cos(p2Angle) * 1.6f, sin(p2Angle) * 1.6f, 0.0f);
        glm::mat4 p2Model = glm::translate(glm::mat4(1.0f), p2Pos3D);
        p2Model = glm::rotate(p2Model, t * 1.0f, glm::vec3(0, 0, 1));  // slower spin
        p2Model[3][3] = +1.0f;  // w > 0 → “planet”
        glm::mat4 p2MVP = proj * view * p2Model;
        drawObject(shaderProg, vaoP2, static_cast<int>(p2Verts.size() / 3), p2MVP, t);

        // —————————— DRAW MOON (around Planet 2) ——————————
        float mAngle = t * 1.5f;
        glm::vec3 moonOffset(cos(mAngle) * 0.25f, sin(mAngle) * 0.25f, 0.0f);
        glm::mat4 moonModel = glm::translate(p2Model, moonOffset);
        moonModel[3][3] = +1.0f;  // w > 0 → “planet” color
        glm::mat4 moonMVP = proj * view * moonModel;
        drawObject(shaderProg, vaoMoon, static_cast<int>(moonVerts.size() / 3), moonMVP, t);

        // Swap buffers + poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &vaoSun);
    glDeleteBuffers(1, &vboSun);
    glDeleteVertexArrays(1, &vaoP1);
    glDeleteBuffers(1, &vboP1);
    glDeleteVertexArrays(1, &vaoP2);
    glDeleteBuffers(1, &vboP2);
    glDeleteVertexArrays(1, &vaoMoon);
    glDeleteBuffers(1, &vboMoon);
    glDeleteProgram(shaderProg);

    glfwTerminate();
    return 0;
}
