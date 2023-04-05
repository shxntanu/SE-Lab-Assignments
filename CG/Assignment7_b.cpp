#include <iostream>
#include <GLUT/GLUT.h>
#include <cmath>

int sWidth = 800;
int sHeight = 600;

int x = 0;
int y = 0;
int res = 50;
int xSpeed = 3;
int radius = 25;
int amplitude = 200;
int frequency = 10;

void moveBall() {
    if ((xSpeed > 0 && x >= sWidth / 2 - radius) || (xSpeed < 0 && x <= -sWidth / 2 + radius)) {
        xSpeed *= -1;
    }
    x += xSpeed;
    
    y = sin((float) x * frequency / sWidth) * ((float) amplitude);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    
    float pi = 3.14159;
    float angle = 0;
    float increment = pi * 2 / (float) res;
    
    for (int i = 0; i < res; i++) {
        glVertex3f((float) x + sin(angle) * ((float) radius), (float) y + cos(angle) * ((float) radius), 0);
        angle += increment;
    }
    
    moveBall();
    
    glEnd();
    glutSwapBuffers();
}

void timer(int _) {
    renderScene();
    glutTimerFunc(1, timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(sWidth, sHeight);
    glutCreateWindow("Sine Wave");
    gluOrtho2D(-sWidth / 2, sWidth / 2, - sHeight / 2, sHeight / 2);
    
    glutDisplayFunc(renderScene);
    glutTimerFunc(1, timer, 0);
    
    glutMainLoop();
}
