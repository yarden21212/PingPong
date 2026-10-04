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
#include "Sound.h"


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

/* Sound */
std::string path = "Sounds/racket_hit.wav";
Sound sound;


/*Temporary*/
int applied = 0;

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
    //if (ball.getBallLocation().y <= yWindowMin + 5) {
	if (ball.getBallLocation().y <= yWindowMin) {
        user1Points++;
        ball.setBallLocation(xWindowMax / 2.0f, yWindowMax/2.0f);

        ball.changeXDirection(1.0f);
        ball.changeYDirection(1.0f);
    }
    else if (ball.getBallLocation().y >= xWindowMax) {
        user2Points++;
        ball.setBallLocation(xWindowMax/2.0f, yWindowMax/2.0f);

        ball.changeXDirection(-1.0f);
        ball.changeYDirection(-1.0f);
    }

}
/* Text */
void playersText() {
    std::string text = "~~~~~~~~~~~~";
    std::string user1 = "User1 points: " + std::to_string(user1Points) + " | ";
    user1 += " Physics type: " + std::to_string(racket1.getPhysics());
    std::string user2 = "User2 points: " + std::to_string(user2Points) + " | ";
    user2 += " Physics type: " + std::to_string(racket2.getPhysics());


    glRasterPos2f(xWindowMin + 2.0f, yWindowMax -10.0f);
    for(int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glRasterPos2f(xWindowMin + 4.0f, yWindowMax -25.0f);
    for (int i = 0; i < user1.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, user1[i]);
    }
    glRasterPos2f(xWindowMin + 4.0f, yWindowMax -40.0f);
    for (int i = 0; i < user2.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, user2[i]);
    }
    glRasterPos2f(xWindowMin + 2.0f, yWindowMax -55.0f);
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
	bool player1OutOfBounds = ball.getBallLocation().y <= racket1.getTopLeftYLocation() - racket1.getHeight(); // Checks if the ball is below the racket (out of bounds)
    if (!(player1OutOfBounds) && ball.getBallLocation().x > racket1.getTopLeftXLocation() && ball.getBallLocation().x < racket1.getTopLeftXLocation() + racket1.getWidth() && (ball.getBallLocation().y - 2) < yWindowMin + (2 * racket1.getHeight()))
    {
        std::cout << "I'm player 1\n";
        /* Racket's hit sound */
        sound.playSound(path);

        if (racket1.getPhysics() == 0) {
            /* Physics 1 -> Most accurate */
            /* Guide for physics(The first reply\answer): https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl */
            float racketCenter = racket1.getTopLeftXLocation() + racket1.getWidth() / 2.0f; // GetTopLeftXLocation = the left edge, and then we add half the width and we reach the center
            float intersectX = ball.getBallLocation().x - racketCenter; // The intersect of the ball with the racket's x location
            float relativeIntersectX = (racket1.getTopLeftXLocation() + (racket1.getWidth() / 2.0f)) - intersectX;
            float normalizedRelativeIntersectionX = (relativeIntersectX / (racket1.getWidth() / 2.0f)); // Expresses that distance relative to the racket’s size:
            float bounceAngle = normalizedRelativeIntersectionX * ((5.0f * 3.141f) / 12.0f); // Turns that position into an angle. The expression in parentheses is approximately 75° in radians.


            /* calculate new ball velocities, using simple trigonometry. */
            float ballVx = -ball.getSpeed() * (float)cos(bounceAngle);
            float ballVy = ball.getSpeed() * (bounceAngle);
			std::cout << "ballVy = " << ballVy << std::endl;

			// The ball got hit on the racket's side, so it needs the first line prevents the ball from going through the racket, and the second line changes the ball's direction to the opposite one, 
			// but with a wider angle, so it moves more to the side, and not just straight up, which is more realistic
            if (ball.getBallLocation().y < racket1.getTopLeftYLocation())
            {
                ball.setBallLocation(ball.getBallLocation().x, racket1.getTopLeftYLocation());
                ball.changeXDirection(ballVx * -10.0f);
                ball.changeYDirection(ballVy);
            }
            // The ball hit the racket it self and not its edges (sides)
            else {
                ball.changeXDirection(ballVx);
                ball.changeYDirection(ballVy);
            }

        }
        else {
            /*Physics 2 -> Mine*/
            //(ballPos.y - racketPos.y) / racketHeight
            float collisionFraction = ball.getBallLocation().x - racket1.getTopLeftXLocation();
            const float racketProportions = racket1.getWidth() / 2.0f;
            if (collisionFraction < racketProportions) { collisionFraction = racketProportions - collisionFraction; }
            const float racketCollisionRatio = collisionFraction / 15.0f == 0 ? 1.0f : collisionFraction / 15.0f;

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
	bool player2OutOfBounds = ball.getBallLocation().y >= racket2.getTopLeftYLocation(); // Checks if the ball is above the racket (out of bounds)
    if (!(player2OutOfBounds) && ball.getBallLocation().x > racket2.getTopLeftXLocation() && ball.getBallLocation().x < racket2.getTopLeftXLocation() + racket2.getWidth() && (ball.getBallLocation().y + 2) > (racket2.getTopLeftYLocation() - racket2.getHeight()))
    {
        /* Racket's hit sound */
        sound.playSound(path);
        

        if (racket2.getPhysics() == 0) {
            float racketCenter = racket2.getTopLeftXLocation() + racket2.getWidth() / 2.0f;
            float intersectX = ball.getBallLocation().x - racketCenter;
            float relativeIntersectX = (racket2.getTopLeftXLocation() + (racket2.getWidth() / 2.0f)) - intersectX;
            float normalizedRelativeIntersectionX = relativeIntersectX / (racket2.getWidth() / 2.0f);
            float bounceAngle = normalizedRelativeIntersectionX * ((5.0f * 3.141f) / 12.0f);

            float ballVx = -ball.getSpeed() * sin(bounceAngle);
            float ballVy = -ball.getSpeed() * (bounceAngle);

            std::cout << "bounceAngle: " << bounceAngle
                << " | ballVx: " << ballVx
                << " | ballVy: " << ballVy << '\n';

            if (ball.getBallLocation().y > racket2.getTopLeftYLocation() - racket2.getHeight())
            {
                ball.setBallLocation(ball.getBallLocation().x, racket2.getTopLeftYLocation() - racket2.getHeight());
                ball.changeXDirection(ballVx * 10.0f);
                ball.changeYDirection(ballVy);
            }
            else {
                ball.changeXDirection(ballVx);
                ball.changeYDirection(ballVy);
            }
        }
        
        else {
            /* Physics 2 */
            float collisionFraction = ball.getBallLocation().x - racket2.getTopLeftXLocation();
            const float racketProportions = racket2.getWidth() / 2.0f;
            if (collisionFraction < racketProportions) { collisionFraction = racketProportions - collisionFraction; }
            const float racketCollisionRatio = collisionFraction / 15.0f == 0.0f ? 1.1f : collisionFraction / 15.0f;

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
        glVertex2f( ball.getBallLocation().x,  ball.getBallLocation().y);
        timer.wait(10);
        ball.moveBall();
    glEnd();

    /* Rackets creation */
    racket1.setColor(255, 0, 0);
    racket2.setColor(0, 255, 0);
    if (ball.getBallLocation().x > racket1.getTopLeftXLocation() && ball.getBallLocation().x < racket1.getTopLeftXLocation() + racket1.getWidth() && (ball.getBallLocation().y - 2.0f) < yWindowMin + (2.0f * racket1.getHeight()))
        racket1.setColor(255, 255, 0);
    if (ball.getBallLocation().x > racket2.getTopLeftXLocation() && ball.getBallLocation().x < racket2.getTopLeftXLocation() + racket2.getWidth() && (ball.getBallLocation().y + 2.0f) > (racket2.getTopLeftYLocation() - racket2.getHeight()))
        racket2.setColor(0, 255, 255);

    /* Draw the first racket */
    std::vector<float> racket1Color = racket1.getColor();
    /*Outlines*/
    glColor4f(255.0f,255.0f,255.0f, 0.85f);
    glBegin(GL_POLYGON);
        glVertex2f((racket1.getTopLeftXLocation()) -1.0f, racket1.getTopLeftYLocation()*1.0f +2.0f);
        glVertex2f((racket1.getTopLeftXLocation() + racket1.getWidth() + 1.0f), (racket1.getTopLeftYLocation() + 2.0f));
        glVertex2f((racket1.getTopLeftXLocation() + racket1.getWidth() + 1.0f), (racket1.getTopLeftYLocation() - racket1.getHeight() - 2.0f));
        glVertex2f((racket1.getTopLeftXLocation()-1.0f), (racket1.getTopLeftYLocation() - racket1.getHeight()-2.0f));
    glEnd();
    /*Racket*/
    glColor3f(racket1Color[0], racket1Color[1], racket1Color[2]);
    glBegin(GL_POLYGON);
        glVertex2f( racket1.getTopLeftXLocation(),  racket1.getTopLeftYLocation());
        glVertex2f( (racket1.getTopLeftXLocation() + racket1.getWidth()),  racket1.getTopLeftYLocation());
        glVertex2f( (racket1.getTopLeftXLocation() + racket1.getWidth()),  racket1.getTopLeftYLocation() -  racket1.getHeight());
        glVertex2f( racket1.getTopLeftXLocation(),  racket1.getTopLeftYLocation() -  racket1.getHeight());
    glEnd();

    /* Draw the second racket */
    std::vector<float> racket2Color = racket2.getColor();

    /*Outlines*/
    glColor4f(255.0f, 255.0f, 255.0f, 0.85f);
    glBegin(GL_POLYGON);
        glVertex2f( (racket2.getTopLeftXLocation() - 1.0f),  (racket2.getTopLeftYLocation() + 2.0f));
        glVertex2f( (racket2.getTopLeftXLocation() + racket2.getWidth() + 1.0f),  (racket2.getTopLeftYLocation() + 2.0f));
        glVertex2f( (racket2.getTopLeftXLocation() + racket2.getWidth() + 1.0f),  (racket2.getTopLeftYLocation() - racket2.getHeight() - 2.0f));
        glVertex2f( (racket2.getTopLeftXLocation() - 1.0f),  (racket2.getTopLeftYLocation() - racket2.getHeight() - 2.0f));
    glEnd();

    glColor3f(racket2Color[0], racket2Color[1], racket2Color[2]);
    //glColor3f(red2, green2, blue2);
    glBegin(GL_POLYGON);
        glVertex2f( racket2.getTopLeftXLocation(),  racket2.getTopLeftYLocation());
        glVertex2f( (racket2.getTopLeftXLocation() + racket2.getWidth()),  racket2.getTopLeftYLocation());
        glVertex2f( (racket2.getTopLeftXLocation() + racket2.getWidth()),  racket2.getTopLeftYLocation() -  racket2.getHeight());
        glVertex2f( racket2.getTopLeftXLocation(),  racket2.getTopLeftYLocation() -  racket2.getHeight());
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






























