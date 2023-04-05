//#include <string>
//#include <sstream>
////#include <windows.h>
////#include <GL/glut.h>
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>
//#include <iostream>
//using namespace std;
//
//class Node
//{
//private:
//    int data;
//    Node *next;
//
//public:
//    explicit Node(int data = 0, Node *next = NULL) : data(data), next(next) {};
//
//    friend class Stack;
//};
//
//class Stack
//{
//private:
//    Node *top;
//
//public:
//    static int size;
//    Stack() : top(NULL) {};
//
//    void push(int data)
//    {
//        Node *temp = new Node(data);
//        temp->next = top;
//        top = temp;
//        size++;
//    }
//
//    int pop()
//    {
//        if (top == NULL)
//        {
//            return INT_MAX;
//        }
//        else
//        {
//            Node *temp = top;
//            top = top->next;
//            temp->next = NULL;
//            int x = temp->data;
//            delete temp;
//            size--;
//            return x;
//        }
//
//    }
//
//    bool isEmpty()
//    {
//        return top == NULL ? true : false;
//    }
//
//    int getTop()
//    {
//        return top->data;
//    }
//    int *getAllData()
//    {
//        int* data = new int[Stack::size];
//        Node *temp = top;
//        int j = 0;
//        while (temp != NULL)
//        {
//            data[j] = temp->data;
//            temp = temp->next;
//            j++;
//        }
//        return data;
//    }
//};
//int Stack::size = 0;
//Stack s1;
//
//void display()
//{
//    int y = 20;                   // initial y_position
//    glClearColor(1, 1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT); //clear buffers to preset values
//    glPointSize(10.0);
//    glColor3f(0.0, 0.0, 0.0); // color of polygon
//    int *data = s1.getAllData();
//    for (int j = Stack::size-1 ; j >= 0; j--)
//    {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        glBegin(GL_POLYGON);
//        glVertex2f(100, y);
//        glVertex2f(150, y);
//        glVertex2f(150, y + 50);
//        glVertex2f(100, y + 50);
//        glEnd();
//        glRasterPos2f(115, y + 20);
//        int val = data[j];
//        ostringstream stream;
//        stream << val;
//        string s = stream.str();
//        for (int i = 0; i < 2; i++)
//        {
//            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
//        }
//        y += 50;
//        glEnd();
//    }
//    delete[] data;
//    glFlush();
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'p' | 'P':
//        cout << "Enter the element you want to push" << endl;
//        int data;
//        cin >> data;
//        s1.push(data);
//        display();
//        break;
//    case 'q' | 'Q':
//    {
//        int dat = s1.pop();
//        if (dat == INT_MAX)
//        {
//            cout << "STACK UNDERFLOW" << endl;
//        }
//        else
//        {
//            cout << "Element popped is " << dat << endl;
//        }
//        display();
//        break;
//    }
//    case 's' | 'S':
//        cout << "Total element/s in Stack is/are: " << Stack::size << endl;
//        ;
//        display();
//        break;
//    case 'f' | 'F':
//        cout << "The front element is: " << s1.getTop() << endl;
//        display();
//        break;
//    case 'x' | 'X':
//        exit(0);
//    }
//}
//
//void init()
//{
//    glClearColor(1, 1, 1, 1);
//}
//void reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0, 500, 0, 500);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char *argv[])
//{
//    int option = 1;
//    while (option != 7)
//    {
//        cout << "\n\n<---------- MENU ---------->" << endl;
//        cout << "Enter operation to be performed on Stacks: " << endl;
//        cout << "1. Push" << endl;
//        cout << "2. Pop" << endl;
//        cout << "3. Peek" << endl;
//        cout << "4. Total Elements" << endl;
//        cout << "5. Display" << endl;
//        cout << "-1. Exit" << endl;
//        cout << "Enter option (0 to exit): ";
//        cin >> option;
//        switch (option)
//        {
//        case 1:
//            cout << "Enter the element you want to push" << endl;
//            int data;
//            cin >> data;
//            s1.push(data);
//            break;
//        case 2:{
//            int dat = s1.pop();
//            if (dat == INT_MAX)
//            {
//                cout << "STACK UNDERFLOW" << endl;
//            }
//            else
//            {
//                cout << "Element popped is " << dat << endl;
//            }
//            break;
//        }
//        case 3:
//            cout << s1.getTop() << endl;
//            break;
//        case 4:
//            cout << "Total element/s in stack is/are: " << Stack::size;
//            break;
//        case 5:
//            glutInit(&argc, argv);
//            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//            glutInitWindowPosition(0, 0);
//            glutInitWindowSize(500, 500);
//            glutCreateWindow("Stacks Visualisation");
//            glutDisplayFunc(display);
//            glutKeyboardFunc(keyboard);
//            glutReshapeFunc(reshape);
//            init();
//            glutMainLoop();
//            break;
//        case -1:
//            cout << "Program ended successfully!" << endl;
//            break;
//        default:
//            cout << "Program ended successfully!" << endl;
//            break;
//        }
//    }
//    return 0;
//}
