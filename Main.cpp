/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

#include "Equipment.h"

char title[10] = "2D Scene!";

Racket racket1;

int movement = 5;

int leftPos = 40;
int rightPos = 120;
int topPos = 80;
int bottomPos = 40;

int ballLocation[2] = { 250, 480 };

int user1Points = 0;
int user2Points = 0;


enum key_state { NOTPUSHED = 0, PUSHED = 1};
int keyArr[127];

void init()
{
    glViewport(0, 0, 1000, 1000);

    glPointSize(10);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void handleKeypress() {
    if (keyArr['a']) {
        if (leftPos < 0)
            return;
        leftPos -= movement;
        rightPos -= movement;
    }
    if (keyArr['d']) {
        if (rightPos > 500)
            return;
        leftPos += movement;
        rightPos += movement;
    }
    if (keyArr['j']) {
        ballLocation[0] -= movement;
    }
    if (keyArr['l']) {
        ballLocation[0] += movement;
    }
    if (keyArr['k']) {
        ballLocation[1] -= movement;
    }
}

void key(unsigned char key, int x, int y) {
    if (key == 'd')
        keyArr[int('d')] = PUSHED;
    if (key == 'a')
        keyArr[int('a')] = PUSHED;
    if (key == 'i')
        keyArr[int('i')] =  PUSHED;
    if (key == 'k')
        keyArr[int('k')]  = PUSHED;
    if (key == 'l')
        keyArr[int('l')] = PUSHED;
    if (key == 'j')
        keyArr[int('j')] = PUSHED;

    handleKeypress();
    //glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    if (key == 'd')
        keyArr['d'] = NOTPUSHED;
    if (key == 'a')
        keyArr['a'] = NOTPUSHED;
    if (key == 'i')
        keyArr['i'] = NOTPUSHED;
    if (key == 'k')
        keyArr['k'] = NOTPUSHED;
    if (key == 'l')
        keyArr['l'] = NOTPUSHED;
    if (key == 'j')
        keyArr['j'] = NOTPUSHED;
}

void idle() {
    glutPostRedisplay();
}

//void handleKeypress(unsigned char key, int x, int y) {
//    if (key == 'a') {
//        if (leftPos < 0)
//            return;
//        leftPos -= movement;
//        rightPos -= movement;
//    }
//    if (key == 'd') {
//        if (rightPos > 500)
//            return;
//        leftPos += movement;
//        rightPos += movement;
//    }
//    if (key == 'j') {
//        ballLocation[0] -= 4;
//    }
//    if (key == 'l') {
//        ballLocation[0] += 4;
//    }
//    if (key == 'k') {
//        ballLocation[1] -= 4;
//    }
//    
//    glutPostRedisplay();
//}



void checkPointPosition() {
    if (ballLocation[1] < topPos) {
        if (ballLocation[0] > rightPos || ballLocation[0] < leftPos) {
            user1Points++;
        }
        else {
            user2Points++;
        }
        printf("\033c"); // will reset terminal.
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        std::cout << "User1 points: " << user1Points << std::endl;
        std::cout << "User2 points: " << user2Points << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        ballLocation[0] = 250;
        ballLocation[1] = 480;
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //std::cout << "leftPos: " << leftPos << "rightPos: " << rightPos << "\n";

    glColor3f(0, 255, 0);
    glBegin(GL_POINTS);
        glVertex2f(ballLocation[0], ballLocation[1]);
    glEnd();

    glColor3f(255, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(leftPos, bottomPos);
        glVertex2f(leftPos, topPos);
        glVertex2f(rightPos, topPos);
        glVertex2f(rightPos, bottomPos);
    glEnd();
    glFlush();
    
    checkPointPosition();
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Window");

    // here are the new entries
    //glutKeyboardFunc(handleKeypress);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);

    init();

    glutDisplayFunc(display);

    glutMainLoop();
}