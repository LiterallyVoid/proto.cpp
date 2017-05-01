#include <GL/glew.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

int width = 100, height = 100;
double mouseX = 0, mouseY = 0;
double pmouseX = 0, pmouseY = 0;
bool mouseIsPressed;
double seconds;
double delta;

int color(int r, int g, int b, int a) {
    return (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((a & 0xFF) << 24);
};

int red(int c) {
    return c & 0xFF;
};

int green(int c) {
    return (c >> 8) & 0xFF;
};

int blue(int c) {
    return (c >> 16) & 0xFF;
};

int alpha(int c) {
    return (c >> 24) & 0xFF;
};

void size(int x, int y) {
    width = x;
    height = y;
};

void background(int c) {
    glClearColor(red(c) / 255.0, green(c) / 255.0, blue(c) / 255.0, alpha(c) / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
};

void fill(int c) {
    glColor4ub(red(c), green(c), blue(c), alpha(c));
};

void rect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
};

void circle(float x, float y, float s) {
    glBegin(GL_POLYGON);
    for(float r = 0; r < M_PI * 2; r += M_PI * 0.125) {
	glVertex2f(sin(r) * s + x, cos(r) * s + y);
    }
    glEnd();
};

void strokeCircle(float x, float y, float s, float w) {
    glBegin(GL_QUAD_STRIP);
    float step = M_PI * 0.125;
    for(float r = 0; r < M_PI * 2 + step; r += step) {
	glVertex2f(sin(r) * (s + w) + x, cos(r) * (s + w) + y);
	glVertex2f(sin(r) * s + x, cos(r) * s + y);
    }
    glEnd();
};

void beginShape() {
    glBegin(GL_POLYGON);
};

void vertex(float x, float y) {
    glVertex2f(x, y);
};

void endShape() {
    glEnd();
};

void pushMatrix() {
    glPushMatrix();
};

void popMatrix() {
    glPopMatrix();
};

void translate(float x, float y) {
    glTranslatef(x, y, 0.0);
};

void rotate(float r) {
    glRotatef((r * 180) / M_PI, 0, 0, 1);
};

extern void setup();
extern void draw();

GLFWwindow *window;

static int init_glfw() {
    if(!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(width, height, "Current project", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_MULTISAMPLE);

    return 0;
};

static void deinit_glfw() {
    glfwDestroyWindow(window);
    glfwTerminate();
};

int main(int argc, char **argv) {
    setup();

    if(init_glfw()) return 1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    seconds = glfwGetTime();

    while(!glfwWindowShouldClose(window)) {
	pmouseX = mouseX;
	pmouseY = mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	mouseIsPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

        double new_time = glfwGetTime();
        delta = new_time - seconds;
        seconds = new_time;

        glViewport(0, 0, width, height);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();
	
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deinit_glfw();
    return 0;
};
