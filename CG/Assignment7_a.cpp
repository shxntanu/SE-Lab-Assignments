#include <iostream>
#include <GLUT/GLUT.h>

int boxHeight = 40;
int boxWidth = 100;
int bottom = -200;

class Stack {
public:
    char arr[10];
    int top;
    
    Stack() {
        this->top = 0;
    }
    
    void pop() {
        if (top) {
            top--;
        }
    }
    
    void push(char a) {
        if (top < 9) {
            arr[top++] = a;
        }
    }
} stack;

void renderScene();

void keyboardFunc(unsigned char c, int x, int y) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        stack.push(c);
    } else if (c == 127) {
        stack.pop();
    }
    renderScene();
}

inline void drawBox(int x, int y) {
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(x, y, 0);
    glVertex3f(x + boxWidth, y, 0);
    glVertex3f(x + boxWidth, y + boxHeight, 0);
    glVertex3f(x, y + boxHeight, 0);
    
    glEnd();
}

inline void drawStack() {
    for (int i = 0; i < stack.top; i++) {
        drawBox(-boxWidth / 2, bottom + i * boxHeight);
        glRasterPos3f(-9, bottom + i * boxHeight + 12, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stack.arr[i]);
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStack();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    stack.push('A');
    stack.push('A');
    stack.push('A');
    stack.push('A');
    glutInit(&argc, argv);
    
    glutInitWindowSize(800, 600); // Optional
    glutCreateWindow("Stack");
    gluOrtho2D(-400, 400, -300, 300);
    glutKeyboardFunc(keyboardFunc);
    
    glutDisplayFunc(renderScene);
    
    glutMainLoop();
}
