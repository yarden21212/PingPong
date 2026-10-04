/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <math.h>
#include <string> 

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

/* Keyboard detection variables*/
enum key_state { NOTPUSHED = 0, PUSHED = 1 };
int keyArr[127];

/* TODO: player results */
int user1Points = 0;
int user2Points = 0;



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

// will reset terminal (NoAngel reply (42 likes) -> https://stackoverflow.com/questions/6486289/how-to-clear-the-console-in-c  
void clearConsole() {
    printf("\033c"); 
}

/* Handles the pressed buttons for movement of the racket\paddle*/
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
}

/* Detects the pressed buttons, for movement it stores them into an array (to avoid delay between pressed), 
    for physics, it just changes the racket's physics status and prints to the console */
void key(unsigned char key, int x, int y) {
    if (key == 'd')
        keyArr[int('d')] = PUSHED;
    if (key == 'a')
        keyArr[int('a')] = PUSHED;
    if (key == 'l')
        keyArr[int('l')] = PUSHED;
    if (key == 'j')
        keyArr[int('j')] = PUSHED;

    handleKeypress();

    if (key == 'i' || key == 'w') {

        if (key == 'w')
            racket1.setPhysics();
        if (key == 'i')
            racket2.setPhysics();

        clearConsole();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        std::cout << "[User1 physics: " << racket1.getPhysics() << std::endl;
        std::cout << "[User2 physics: " << racket2.getPhysics() << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    //glutPostRedisplay();
}

/* Once the button is up (stopped being pressed, "it pops it off the array" */
void keyUp(unsigned char key, int x, int y) {
    if (key == 'd')
        keyArr['d'] = NOTPUSHED;
    if (key == 'a')
        keyArr['a'] = NOTPUSHED;
    if (key == 'l')
        keyArr['l'] = NOTPUSHED;
    if (key == 'j')
        keyArr['j'] = NOTPUSHED;
}

/* Not sure if it's really helpful, needs to be checked */
void idle() {
    glutPostRedisplay();
}


void detectPoint() {
    if (ball.getBallLocation().y <= yWindowMin + 5) {
        user1Points++;
        ball.setBallLocation(xWindowMax / 2, yWindowMax/2);

        ball.changeXDirection(1);
        ball.changeYDirection(1);
    }
    else if (ball.getBallLocation().y >= xWindowMax) {
        user2Points++;
        ball.setBallLocation(xWindowMax/2, yWindowMax/2);

        ball.changeXDirection(-1);
        ball.changeYDirection(-1);
    }

}
/* Text */
void playersText() {
    std::string text = "~~~~~~~~~~~~";
    std::string user1 = "User1 points: " + std::to_string(user1Points) + " | ";
    user1 += " Physics type: " + std::to_string(racket1.getPhysics());
    std::string user2 = "User2 points: " + std::to_string(user2Points) + " | ";
    user2 += " Physics type: " + std::to_string(racket2.getPhysics());


    glRasterPos2f(xWindowMin + 2, yWindowMax -10);
    for(int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glRasterPos2f(xWindowMin + 4, yWindowMax -25);
    for (int i = 0; i < user1.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, user1[i]);
    }
    glRasterPos2f(xWindowMin + 4, yWindowMax -40);
    for (int i = 0; i < user2.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, user2[i]);
    }
    glRasterPos2f(xWindowMin + 2, yWindowMax -55);
    for (int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

}

/* 
    The physics it self.
    Created 2 different physics methods:
    1. The most recommended from a guide I found
    2. Mine, that wasn't perfect, but it works very well
    The can be switched by pressing 'W' for player 1 (bottom racket) or 'I' for player 2 (upper racket)
*/
void checkPointPosition() {
    /* Window collisions */
    if (ball.getBallLocation().x <= xWindowMin || ball.getBallLocation().x >= xWindowMax)
    {
        ball.changeDefaultXDirection();
        detectPoint();
    }
    if (ball.getBallLocation().y <= yWindowMin || ball.getBallLocation().y >= yWindowMax)
    {
        ball.changeDefaultYDirection();
        detectPoint();
    }
    /* Player 1 collisions */
    if (ball.getBallLocation().x > racket1.getTopLeftXLocation() && ball.getBallLocation().x < racket1.getTopLeftXLocation() + racket1.getWidth() && (ball.getBallLocation().y - 2) < yWindowMin + (2 * racket1.getHeight()))
    {
        if (racket1.getPhysics() == 0) {
            /* Physics 1 -> Most accurate */
            /* Guide for physics(The first reply\answer): https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl */
            double racketCenter = (racket1.getTopLeftXLocation() + racket1.getWidth()) / 2.0;
            double intersectX = ball.getBallLocation().x - racketCenter; // The intersect of the ball with the racket's x location
            double relativeIntersectX = (racket1.getTopLeftXLocation() + (racket1.getWidth() / 2.0)) - intersectX;
            double normalizedRelativeIntersectionX = (relativeIntersectX / (racket1.getWidth() / 2.0));
            double bounceAngle = normalizedRelativeIntersectionX * ((5.0 * 3.141) / 12.0);


            /* calculate new ball velocities, using simple trigonometry. */
            //double ballVx = 4 * cos(bounceAngle);
            //double ballVy = 4 * -sin(bounceAngle);
            double ballVx = ball.getSpeed() * cos(bounceAngle);
            double ballVy = -(bounceAngle);

            ball.changeXDirection(ballVx);
            ball.changeYDirection(ballVy);
        }
        else {
            /*Physics 2 -> Mine*/
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
        }
    }
    /* Player 2 collisions */
    if (ball.getBallLocation().x > racket2.getTopLeftXLocation() && ball.getBallLocation().x < racket2.getTopLeftXLocation() + racket2.getWidth() && (ball.getBallLocation().y + 2) > (racket2.getTopLeftYLocation() - racket2.getHeight()))
    {

        if (racket2.getPhysics() == 0) {
            /* Physics 1 */
            double racketXCenter = (racket2.getTopLeftXLocation() + racket2.getWidth()) / 2.0;
            double intersectX = ball.getBallLocation().x - racketXCenter; // The intersect of the ball with the racket's x location
            double relativeIntersectX = (racket2.getTopLeftXLocation() + (racket2.getWidth() / 2.0)) - intersectX;
            double normalizedRelativeIntersectionX = (relativeIntersectX / (racket2.getWidth() / 2.0));
            double bounceAngle = normalizedRelativeIntersectionX * ((5.0 * 3.141) / 12.0);


            /* calculate new ball velocities, using simple trigonometry. */
            //double ballVx = 4 * cos(bounceAngle);
            //double ballVy = 4 * -sin(bounceAngle);
            double ballVx = ball.getSpeed() * cos(bounceAngle);
            double ballVy = (bounceAngle);

            ball.changeXDirection(ballVx);
            ball.changeYDirection(ballVy);
        }
        
        else {
            /* Physics 2 */
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
        }




    }
}

/* Generating the scene, 2 rackets\paddles and a ball*/
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Display user points and physics type of the screen (white colored) */
    glColor3f(255, 255, 255);
    playersText();

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
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "[User1 physics: " << racket1.getPhysics() << std::endl;
    std::cout << "[User2 physics: " << racket2.getPhysics() << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
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