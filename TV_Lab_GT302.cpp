// TV LAB GT302 //
// KELOMPOK  //
// VINCENT TUA EUREAL SARAGIH, NRP : 5222600022 //
// MOCHAMMAD NAUFAL SYAFFRUDDIN, NRP : 5222600027//

#include <GL/glut.h>
#include <cmath>

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat translateZ = 15.0f;
bool isRotating = false;
int prevX = 0;
int prevY = 0;

void drawTV() {
    // Draw TV body
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -3.0f, 0.0f);
    glVertex3f(5.0f, -3.0f, 0.0f);
    glVertex3f(5.0f, 3.0f, 0.0f);
    glVertex3f(-5.0f, 3.0f, 0.0f);
    glEnd();

    // Draw TV screen
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, -2.3f, 0.1f);
    glVertex3f(3.0f, -2.3f, 0.1f);
    glVertex3f(3.0f, 2.3f, 0.1f);
    glVertex3f(-3.0f, 2.3f, 0.1f);
    glEnd();

    // Draw TV base
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, -3.6f, 0.0f);
    glVertex3f(3.0f, -3.6f, 0.0f);
    glVertex3f(3.0f, -3.3f, 0.0f);
    glVertex3f(-3.0f, -3.3f, 0.0f);
    glEnd();

    // Draw TV stand
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-0.25f, -3.3f, 0.0f);
    glVertex3f(0.25f, -3.3f, 0.0f);
    glVertex3f(0.25f, -2.0f, 0.0f);
    glVertex3f(-0.25f, -2.0f, 0.0f);
    glEnd();
}

void drawSpeaker(float x, float y, float radius) {
    const int segments = 50;

    // Draw speaker
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.1f);  // Center of the circle
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.14f * i / segments;
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex3f(x + dx, y + dy, 0.1f);
    }
    glEnd();
}

void drawSpeaker(float x, float y) {
    drawSpeaker(x, y, 0.3f);
}

void display() {
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, translateZ,
        0.0, 0.0, 0.0,
        0.0, 5.0, 0.0);

    // Rotate TV
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    drawTV();

    // Draw left speaker
    drawSpeaker(-4.3f, -1.0f);
    drawSpeaker(-4.3f, 0.0f);
    drawSpeaker(-4.3f, 1.0f);
    drawSpeaker(-3.9f, 2.25f, 0.5f);

    // Draw right speaker
    drawSpeaker(4.3f, -1.0f);
    drawSpeaker(4.3f, 0.0f);
    drawSpeaker(4.3f, 1.0f);
    drawSpeaker(3.9f, 2.25f, 0.5f);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isRotating = true;
        prevX = x;
        prevY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isRotating = false;
    }
}

void motion(int x, int y) {
    if (isRotating) {
        rotateX -= (y - prevY);
        rotateY += (x - prevX);
        prevX = x;
        prevY = y;
        glutPostRedisplay(); // Redraw the scene
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D TV with Speakers");

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
