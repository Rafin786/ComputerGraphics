//#include<windows.h>
#include<GL/glut.h>
using namespace std;

int molePosX;
int molePosY;

void init(){
    glClearColor(0.42,0.69,1.00,1);
}

void reshape(int w, int h){
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW);
}

void holes(double x,double y,double z){
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(x,y,z);
    glutSolidSphere(4.0,50.0,10);
    glPopMatrix();
}

void moles(int){
    glPushMatrix();
    glColor3f(1,0,0);
    int x = (rand() % 4) + 1;
    //currentHole = x;
    switch(x){
        case 1:
            molePosX = -5;
            molePosY = 5;
            break;
        case 2:
            molePosX = 5;
            molePosY = 5;
            break;
        case 3:
            molePosX = -5;
            molePosY = -5;
            break;
        case 4:
            molePosX = 5;
            molePosY = -5;
            break;
    }
    glutTimerFunc(500, moles, 1);
}

void Text(){}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

//Grid
    glPointSize(10.0);
    //glTranslatef(3.5,0,0);
    glBegin(GL_LINES);
    glVertex2f(-10, 0); //-14,0
    glVertex2f(10, 0); //7,0
    glVertex2f(0, 10);
    glVertex2f(0, -10);
    glEnd();

    /*glTranslatef(-7,0,0);
    glBegin(GL_LINES);
    //glVertex2f(0, 5);
    //glVertex2f(0, -5);
    glVertex2f(0, 10);
    glVertex2f(0, -10);
    glEnd();*/

//Score Board
    //glTranslatef(3.5,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-3,1);
    glVertex2f(3,1);
    glVertex2f(3,-1);
    glVertex2f(-3,-1);
    glEnd();

//Holes
    holes(-5,5,0);
    holes(5,5,0);
    //holes(-5,-5,0);
    holes(-5,-5,0);
    holes(5,-5,0);
    //holes(5,-5,0);

//Moles Position///////////////////////////
    glTranslatef(molePosX,molePosY,0);
    glColor3f(0,0,1);
//Head
    glutSolidSphere(2.0,50.0,40);
//Left Eye
    glTranslatef(-0.6,0.5,0);
    glutSolidSphere(0.2,50.0,40);
//Right Eye
    glTranslatef(1.5,0,0);
    glutSolidSphere(0.2,50.0,40);
//Nose
    glTranslatef(-0.5,-1.5,0);
    glutSolidSphere(0.4,50.0,40);

    glPopMatrix();
    glutPostRedisplay();
    glFlush();
}

void mouse(int button, int state, int x, int y){
    int currentClick;
    if (button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            if(x>0 && x<250 && y>0 && y<250){
                currentClick = 1;
            }else if(x>251 && x<500 && y>0 && y<250){
                currentClick = 2;
            }else if(x>0 && x<255 && y>251 && y<500){
                currentClick = 3;
            }else if(x>251 && x<500 && y>251 && y<500){
                currentClick = 4;
            }
            if(life<=0){
                cout<< "Game Over"<< endl;
                gameStatus = "Game Over";
            }

            if(currentClick == currentHole){
                score += 100;
                cout << score << endl;
            }else{
                life--;
                cout << "Missed" << endl;
            }
        }
    }
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(500,200);
    glutInitWindowSize(500,500); //900, 500

    glutCreateWindow("Whac-A-Mole");
    glutTimerFunc(0, moles, 1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(mouse);
    init();
    glutMainLoop();
}
