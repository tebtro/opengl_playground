#include <iostream>
// #define _ALLOW_KEYWORD_MACROS

#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "winmm")
// #define WIN32_LEAN_AND_MEAN
#include <windows.h>
// #include <mmsystem.h> // @note excluded in lean and mean, used for timeBeginPeriod to set scheduler granularity

#pragma comment(lib, "opengl32")
// #include <gl/gl.h>
// #pragma comment(lib, "glu32")
// #include <gl/glu.h>


#include <glad/glad.h>
#pragma comment(lib, "glfw3")
#include <GLFW/glfw3.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef assert


#include "iml_general.h"
#include "iml_types.h"


#include "shader.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


int main() {
    glfwInit();
    defer {
        glfwTerminate();
    };
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Playground", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }
    
    glViewport(0, 0, 800, 600);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    u32 vao; // @note Vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    
#if 0
    // @note: Draw Triangle
    // Normalized Device Coordinates (NDC)
    f32 vertices[] = {
        // positions         // colors
        -0.5, -0.5,  0.0f,  1.0f, 0.0f, 0.0f, // Vertex containing one 3D position
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
            
            /*
                    0.0f, 0.0f,  0.0f,
                    0.5f, 0.0f, 0.0f,
                    0.5f, 0.5f, 0.0f
            */
    };
#else
    // @note: Draw Texture
    f32 vertices[] = {
        // positions         // colors          // texture coordinates
        0.5f,   0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left
    };
#endif
    
    u32 vbo; // @note Vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    u32 indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    u32 ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // @note: Vertex shader
    const char *vertex_shader_source = R"FOO(
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            #version 330 core
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            layout (location = 0) in vec3 aPos;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        layout (location = 1) in vec3 aColor;
                                                                                                                                                                                                                                                                                                                                                            layout (location = 2) in vec2 aTexCoord;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            out vec3 our_color;
                                                                                                                                                                                                    out vec2 tex_coord;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            void main() {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                gl_Position = vec4(aPos, 1.0);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    our_color = aColor;
                                                                                                                tex_coord = aTexCoord;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    )FOO";
    // @note: Fragment shader
    const char *fragment_shader_source = R"FOO(
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                #version 330 core
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    // uniform vec4 our_color; // Set in c++ code
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    in vec3 our_color;
                                                                                                                                                                                                                                                                                                                                                                            in vec2 tex_coord;
                                                                                                                                                                                                                                                                                                uniform sampler2D our_texture;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    out vec4 frag_color;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                void main() {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // frag_color = vec4(our_color, 1.0);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        frag_color = texture(our_texture, tex_coord);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        )FOO";
    Shader shader = create_shader(vertex_shader_source, fragment_shader_source);
    use_shader(shader);
    
    // @note: Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)0);
    glEnableVertexAttribArray(0);
    
    // @note: Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    
    // @note: Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(6 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    
    
    //
    // @note: Wireframe
    //
#if 0
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
    
    //
    // @note: Textures
    //
    int width, height, nr_channels;
    u8 *data = stbi_load("../assets/container.jpg", &width, &height, &nr_channels, 0);
    defer {
        stbi_image_free(data);
    };
    
    // @note: Generating a texture
    u32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    //
    // @note: Texture Wrapping
    //
#if 0
    // GL_REPEAT   default
    // GL_MIRRORED_REPEAT
    // GL_CLAMP_TO_EDGE
    // GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    f32 border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
#endif
    
    //
    // @note: Texture Filtering
    //
#if 0
    // GL_NEAREST = best for pixel art
    // GL_LINEAR  = (bi)linear
    //
    // Can be set for minifying and magnifying
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
    
    //
    // @note: Mipmaps
    //
#if 0
    // GL_NEAREST_MIPMAP_NEAREST
    // GL_LINEAR_MIPMAP_NEAREST
    // GL_NEAREST_MIPMAP_LINEAR
    // GL_LINEAR_MIPMAP_LINEAR
    // These are only used for downscaling!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
    
    
    while (!glfwWindowShouldClose(window)) {
        // @note: Handle events / input
        glfwPollEvents();
        process_input(window);
        
        // @note: Update and Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        use_shader(shader);
        
        f32 time_value = glfwGetTime();
        f32 green_value = (sin(time_value) / 2.0f) + 0.5f;
        int vertex_color_location = glGetUniformLocation(shader.id, "our_color");
        glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glBindVertexArray(vao);
        defer {
            glBindVertexArray(0);
        };
#if 0
        glDrawArrays(GL_TRIANGLES, 0, 6);
#else
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
        
        glfwSwapBuffers(window);
    }
    
    
    return 0;
}
