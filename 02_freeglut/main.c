#include <stdio.h>

#define assert(expr) if(!(expr)) { printf("%s:%d %s() %s\n",__FILE__,__LINE__, __func__, #expr); *(volatile int *)0 = 0; }

#define STB_IMAGE_IMPLEMENTATION
// automatically loads glew.h
#define GLEW_INCLUDE <GL/glew.h>
#include "c__/glew.c"
// glut files come from freeglut-3.2.1
// requires OpenGL/gl.h
// requires OpenGL/glu.h
#include <GL/freeglut_std.h>
#include <GL/freeglut_ext.h>
#include <math.h>


typedef struct {
    float x;
    float y;
    float z;
} V3f;

enum { vbo_vertex, vbo_count };
GLuint vbo[vbo_count];
enum { l_scale, l_count  };
GLuint location[l_count];

enum {t_map, t_count };

enum { a_scale, a_count };
float attrib[a_count];

void main_loop() {
    glClear(GL_COLOR_BUFFER_BIT); 

    // sending in vertex position to the fixed function pipeline (Default header
    {
        int attribIdx = 0;
        int verticeCount = 3;
        glEnableVertexAttribArray(attribIdx); // attribute index 0
        attrib[a_scale] += 0.001f;

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glUniform1f(location[l_scale], sin(attrib[a_scale]));
            glVertexAttribPointer(attribIdx, verticeCount, GL_FLOAT, GL_FALSE, 0, 0); 
            glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(attribIdx);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glutSwapBuffers();
}

void create_shader(const GLchar * shader_str, GLuint * shader, GLenum type, const char * debug_str){
    *shader = glCreateShader(type);
    glShaderSource( *shader, 1, &shader_str, NULL );
    glCompileShader(*shader );

    GLint shaderCompiled = 0;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderCompiled);

    if (!shaderCompiled) {
        GLint maxLength;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
        char error_log[maxLength];
        glGetShaderInfoLog(*shader, maxLength, &maxLength, &error_log[0]);
        printf("%s failed to compile:\n%s\n", debug_str, error_log);
        assert(0 && "shader failed to compile");
    }
}



int main(int argc, char ** argv) {
    int width = 1300;
    int height = 1000;
    glutInit(&argc, argv);
    glutInitWindowSize( width, height);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
 
    glutInitContextVersion(3,2);
    glutInitContextFlags(GLUT_CORE_PROFILE);
    glutCreateWindow("test");
    assert(GLEW_OK == glewInit());
    glutDisplayFunc(main_loop);
    glutIdleFunc(main_loop);
    glClearColor( 0., 0.0, 0., 0 );

    // get buffer ids
    glGenBuffers(3, vbo);
    /*
    AMD Radeon R9 M370X OpenGL Engine
    2.1 ATI-2.11.23
    1.20
    */
    printf("%s\n%s\n%s\n", 
        glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
        glGetString(GL_VERSION),    // e.g. 3.2 INTEL-8.0.61
        glGetString(GL_SHADING_LANGUAGE_VERSION)    // e.g. 3.2 INTEL-8.0.61
    );
    
    // Create Vertex Buffer
    {
        V3f vertices[6]; 
        vertices[0] = (V3f) {-1., -1., 0.};
        vertices[1] = (V3f) {1., -1., 0.};
        vertices[2] = (V3f) {1., 1., 0.};
        vertices[3] = (V3f) {-1., -1., 0.};
        vertices[4] = (V3f) {1., 1., 0.};
        vertices[5] = (V3f) {-1., 1., 0.};
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Compile Shaders
    {
        GLuint vert_shader;
        const char* vertex_shader_str =
            "#version 120\n"
            "attribute vec3 aPos;"
            "uniform float gScale;"
            "void main () {"
            "  gl_Position = vec4(gScale * aPos.xy, aPos.z, 1.0);"
            "}";
        create_shader(vertex_shader_str, &vert_shader, GL_VERTEX_SHADER, "Vertex Shader");

        GLuint frag_shader;
        const char * fragment_shader_str = 
            "#version 120\n"
            "uniform float gScale;"
            "void main() {"
            "  gl_FragColor = vec4(1.0, 0.0, 0.5, 1.0);"
            "}";
        create_shader(fragment_shader_str, &frag_shader, GL_FRAGMENT_SHADER, "Fragment Shader");

        GLuint shader_program = glCreateProgram();
        assert(shader_program);
        glAttachShader(shader_program, vert_shader);
        glAttachShader(shader_program, frag_shader);

        GLint success;
        GLchar error_log[1024] = { 0 };

        glLinkProgram(shader_program);
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(shader_program, sizeof(error_log), NULL, error_log);
            printf("error: %s\n", error_log);
            assert(0 && "error linking shader program");
        }

        glValidateProgram(shader_program);
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (success == 0) {
            glGetProgramInfoLog(shader_program, sizeof(error_log), NULL, error_log);
            printf("error: %s\n", error_log);
            assert(0 && "error linking shader program");
        }

        glUseProgram(shader_program);

        location[l_scale] = glGetUniformLocation(shader_program, "gScale");
    }

    glutMainLoop();
    return 0;
}
