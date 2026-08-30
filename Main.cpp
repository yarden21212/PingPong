/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

#include "Equipment.h"
#include "GlobalVariableDefinitions.h"
#include "Timer.h"

int red1 = 255, blue1 = 0, green1 = 0;
int red2 = 0, blue2 = 255, green2 = 0;

char title[10] = "2D Scene!";

/* Rackets */
Racket racket1("first");
Racket racket2("second");

/* Ball */
Ball ball;

/* Timer */
Timer timer;

//int movement = 5;

int leftPos = 40;
int rightPos = 120;
int topPos = 80;
int bottomPos = 40;

int ballLocation[2] = { xWindowMax/2, yWindowMax - 40};

int user1Points = 0;
int user2Points = 0;


enum key_state { NOTPUSHED = 0, PUSHED = 1};
int keyArr[127];

void init()
{
    glViewport(0, 0, xWindowMax, yWindowMax);

    glPointSize(10);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xWindowMin, xWindowMax, yWindowMin, yWindowMax, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void handleKeypress() {
    if (keyArr['a']) {
        racket1.setLocation(racket1.getTopLeftXLocation() - racket1.getSpeed(), racket1.getTopLeftYLocation());
    }
    if (keyArr['d']) {
        racket1.setLocation(racket1.getTopLeftXLocation() + racket1.getSpeed(), racket1.getTopLeftYLocation());
    }
    if (keyArr['j']) {
        //ballLocation[0] -= racket1.getSpeed();
        racket2.setLocation(racket2.getTopLeftXLocation() - racket2.getSpeed(), racket2.getTopLeftYLocation());
    }
    if (keyArr['l']) {
        //ballLocation[0] += racket1.getSpeed();
        racket2.setLocation(racket2.getTopLeftXLocation() + racket2.getSpeed(), racket2.getTopLeftYLocation());
    }
    //if (keyArr['k']) {
    //    //ballLocation[1] -= racket1.getSpeed();
    //}
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
    //if (ball.getBallLocation().y < yWindowMin + racket1.getHeight()*2 + 4) {
    //    if (ball.getBallLocation().x > racket1.getTopLeftXLocation() + racket1.getWidth() || ball.getBallLocation().x < racket1.getTopLeftXLocation()) {
    //        user1Points++;
    //    }
    //    else {
    //        user2Points++;
    //    }
    //    printf("\033c"); // will reset terminal.
    //    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    //    std::cout << "User1 points: " << user1Points << std::endl;
    //    std::cout << "User2 points: " << user2Points << std::endl;
    //    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    //    ballLocation[0] = 250;
    //    ballLocation[1] = 480;
    //    ball.setBallLocation(250, 480);
    //}


    /* Window collisions */
    if (ball.getBallLocation().x <= xWindowMin || ball.getBallLocation().x >= xWindowMax)
        ball.changeDefaultXDirection();
    if (ball.getBallLocation().y <= yWindowMin || ball.getBallLocation().y >= yWindowMax)
        ball.changeDefaultYDirection();
    /* Player 1 collisions */
    if (ball.getBallLocation().x > racket1.getTopLeftXLocation() && ball.getBallLocation().x < racket1.getTopLeftXLocation() + racket1.getWidth() && (ball.getBallLocation().y - 2) < yWindowMin + (2 * racket1.getHeight()))
    {
        //(ballPos.y - racketPos.y) / racketHeight
        int collisionFraction = ball.getBallLocation().x - racket1.getTopLeftXLocation();
        const int racketProportions = racket1.getWidth() / 2;
        if (collisionFraction < racketProportions) { collisionFraction = racketProportions - collisionFraction; }
        const double racketCollisionRatio = collisionFraction / 15 == 0 ? 1 : collisionFraction / 15;

        std::cout << "collisionFraction: " << collisionFraction << std::endl;
        std::cout << "racketCollisionRatio: " << racketCollisionRatio << std::endl;
        std::cout << "pushBackRatio: " << racketCollisionRatio << std::endl;
        if (racketCollisionRatio == 1)
        {
            ball.changeDefaultYDirection();
        }
        else {
            ball.changeDefaultYDirection();
            ball.changeXDirection(racketCollisionRatio);
        }
        //ball.changeDefaultXDirection();
        //ball.changeDefaultYDirection();
    }
    /* Player 2 collisions */
    if (ball.getBallLocation().x > racket2.getTopLeftXLocation() && ball.getBallLocation().x < racket2.getTopLeftXLocation() + racket2.getWidth() && (ball.getBallLocation().y + 2) > (racket2.getTopLeftYLocation() - racket2.getHeight()))
    {
        int collisionFraction = ball.getBallLocation().x - racket2.getTopLeftXLocation();
        const int racketProportions = racket2.getWidth() / 2;
        if (collisionFraction < racketProportions) { collisionFraction = racketProportions - collisionFraction; }
        const double racketCollisionRatio = collisionFraction / 15 == 0 ? 1 : collisionFraction / 15;

        std::cout << "collisionFraction: " << collisionFraction << std::endl;
        std::cout << "racketCollisionRatio: " << racketCollisionRatio << std::endl;
        std::cout << "pushBackRatio: " << racketCollisionRatio << std::endl;
        if (racketCollisionRatio == 1)
        {
            ball.changeDefaultYDirection();
        }
        else {
            ball.changeDefaultYDirection();
            ball.changeXDirection(racketCollisionRatio);
        }
        //ball.changeDefaultXDirection();
        //ball.changeDefaultYDirection();
        //ball.changeDefaultXDirection();
        //ball.changeDefaultYDirection();
    }
}






void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //std::cout << "leftPos: " << leftPos << "rightPos: " << rightPos << "\n";

    // How to make the point round (circle): https://community.khronos.org/t/rounded-and-square-points/77249
    // How to use timer? https://cplusplus.com/forum/beginner/280938/
    glColor3f(0, 255, 0);
    glPointSize(12.0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);
        glVertex2f(ball.getBallLocation().x, ball.getBallLocation().y);
        timer.wait(10);
        ball.moveBall();
    glEnd();

    /* Rackets creation */
    racket1.setColor(255, 0, 0);
    racket2.setColor(0, 255, 0);
    if (ball.getBallLocation().x > racket1.getTopLeftXLocation() && ball.getBallLocation().x < racket1.getTopLeftXLocation() + racket1.getWidth() && (ball.getBallLocation().y - 2) < yWindowMin + (2 * racket1.getHeight()))
        racket1.setColor(255, 255, 0);
    if (ball.getBallLocation().x > racket2.getTopLeftXLocation() && ball.getBallLocation().x < racket2.getTopLeftXLocation() + racket2.getWidth() && (ball.getBallLocation().y + 2) >(racket2.getTopLeftYLocation() - racket2.getHeight()))
        racket2.setColor(0, 255, 255);

    /* Draw the first racket */
    std::vector<int> racket1Color = racket1.getColor();
    glColor3f(racket1Color[0], racket1Color[1], racket1Color[2]);
    glBegin(GL_POLYGON);
        glVertex2f(racket1.getTopLeftXLocation(), racket1.getTopLeftYLocation());
        glVertex2f(racket1.getTopLeftXLocation() + racket1.getWidth(), racket1.getTopLeftYLocation());
        glVertex2f(racket1.getTopLeftXLocation() + racket1.getWidth(), racket1.getTopLeftYLocation() - racket1.getHeight());
        glVertex2f(racket1.getTopLeftXLocation(), racket1.getTopLeftYLocation() - racket1.getHeight());
    glEnd();

    /* Draw the second racket */
    std::vector<int> racket2Color = racket2.getColor();
    glColor3f(racket2Color[0], racket2Color[1], racket2Color[2]);
    //glColor3f(red2, green2, blue2);
    glBegin(GL_POLYGON);
        glVertex2f(racket2.getTopLeftXLocation(), racket2.getTopLeftYLocation());
        glVertex2f(racket2.getTopLeftXLocation() + racket2.getWidth(), racket2.getTopLeftYLocation());
        glVertex2f(racket2.getTopLeftXLocation() + racket2.getWidth(), racket2.getTopLeftYLocation() - racket2.getHeight());
        glVertex2f(racket2.getTopLeftXLocation(), racket2.getTopLeftYLocation() - racket2.getHeight());
    glEnd();
    glFlush();
    
    checkPointPosition();
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("PingPong");

    // here are the new entries
    //glutKeyboardFunc(handleKeypress);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);

    init();

    glutDisplayFunc(display);

    glutMainLoop();
}