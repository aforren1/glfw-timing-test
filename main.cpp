#include <cstdio>
#include <stdlib.h>
#include <GLFW/glfw3.h>

static void esc_cb(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
}

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    // not super accurate, but good enough for figuring out if we're far
    // from the proper rate
    double period = 1.0 / mode->refreshRate;
    printf("period: %.3f\n", period);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(mode->width, mode->height, "BW timing test", primary, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    // exit on esc
    glfwSetKeyCallback(window, esc_cb);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );

    double t0 = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        float r = (float)rand() / RAND_MAX;
        float g = (float)rand() / RAND_MAX;
        float b = (float)rand() / RAND_MAX;
        glClearColor( r, g, b, 0.0f );


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Match PsychoPy's timestamping routine
        glBegin(GL_POINTS);
        glColor4f(0, 0, 0, 0);
        glVertex2i(10, 10);
        glEnd();
        glFinish();

        double t = glfwGetTime();
        double dt = t - t0;
        t0 = t;
        if (dt > 1.5*period) {
            printf("dt: %.3f\n", dt);
        }

        // make sure we're not getting any gl errors
        // GLenum err;
        // if ((err = glGetError()) != GL_NO_ERROR) {
        //     printf("err: %i\n", err);
        // }

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
