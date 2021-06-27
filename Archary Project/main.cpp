#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
#include <dos.h>
#include <string.h>
double angle;
bool fire=true;
double incx=0, incy=0;
double incx1=0, incy1=0;
double incx2=0, incy2=0;
double incx3=0, incy3=0;
double cloudOne=90,cloudSecond=50,cloudThree=20,cloudFour=-30;
double cloudFive=-60,cloudSix=-10,cloudSeven=-90;
double bowPostionY=-40;
bool arrowhandle=true;
double scoreCheck=true;
double circleX;
double circleY;
double archeryPositonX,archeryPositonY;
double arrowPositonX=-80,arrowPositonY=-20;
bool arrowfire=false,start=true;
int state;
bool screenOne=true,screenSecond=true,screenThree=false,ScreenFour=false;
int screen=0;
double anglerot=0;
double FinalScore=0;
double Life=5;
char miss[5];
int printRandoms(int lower, int upper,int count){

    return (rand() %(upper - lower + 1)) + lower;
}


//circleoneX= printRandoms(10, 65, 1);
struct point
{
	double x,y,z;
};



void arrow(){
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(0.64, 0.16, 0.16);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(30.0f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.64, 0.16, 0.16);
        glVertex2f(25, 2.5);
        glVertex2f(25, -2.5);
        glVertex2f(31, 0);
    glEnd();

}

void draw_tri()
{
    glBegin(GL_POLYGON);
        glVertex2f(10, 10);
        glVertex2f(10, 0);
        glVertex2f(-10, 0);
    glEnd();
}
void push_pop(void)
{
    glPushMatrix();
        //glRotatef(45, 0, 0, 1);

        glPushMatrix(); // Furthest Triangle, Draw first
            //glRotatef(45, 0, 0, 1);
            glTranslatef(-20, 0, 0);
            //glScaled(2, 1, 0);
            glColor3f(0.0, 0.0, 1.0);
            draw_tri();

        glPopMatrix();

        glPushMatrix(); // Middle Triangle, Draw 2nd
            glTranslatef(0, 20, 0);
            glColor3f(0.0, 1.0, 0.0);
            draw_tri();
        glPopMatrix();

        glPushMatrix(); // Nearest Triangle, Draw last
            glTranslatef(20, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            draw_tri();
        glPopMatrix();


    glPopMatrix();

}


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);

        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}
void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

void rec_animation()
{
    glColor3f(0,1,0);
    //glRotatef(5*angle,0,0,1);

    glTranslatef(incx,incy,0);

    glRotatef(50*angle,0,0,1);
    drawSquare(1);

}
void draw_rec()
{

    drawSquare(5);

}
void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);
    //glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);
    //glPopMatrix();

    glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,0,1);
    drawSquare(10);

}

void background1()
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.298f, 0.321f, 0.137f);glVertex2d(-105,-80.0);
        glColor3f(0.521f, 0.513f, 0.20f);glVertex2d(-105.0,-110.0);
        glColor3f(0.282f, 0.392f, 0.18f);glVertex2d(105.0,-110.0);
        glColor3f(0.478f, 0.568f, 0.227f);glVertex2d(105.0,-50.0);
    glEnd();
}

void background2()
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.745f, 0.870f, 0.960f);glVertex2d(-105,110.0);
        glColor3f(0.854f, 0.874f, 0.925f);glVertex2d(-105.0,-110.0);
        glColor3f(0.827f, 0.843f, 0.898f);glVertex2d(105.0,-110.0);
        glColor3f(0.756f, 0.878f, 0.964f);glVertex2d(105.0,110.0);

    glEnd();

}

void tree()
{
    glBegin(GL_TRIANGLES); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,-20.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(10.0,-50.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-10.0,-50.0);

        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,-10.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(10.0,-40.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-10.0,-40.0);

        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,0.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(10.0,-30.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-10.0,-30.0);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.568f, 0.294f, 0.129f);
        glVertex2d(-2,-45.0);
        glVertex2d(-2.5,-80.0);
        glVertex2d(2.5,-80.0);
        glVertex2d(2,-45.0);

    glEnd();
}

void small_tree()
{
    glBegin(GL_TRIANGLES); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,-35.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(5.0,-50.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-5.0,-50.0);

        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,-30.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(5.0,-45.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-5.0,-45.0);

        glColor3f(0.65f, 0.69f, 0.225f); glVertex2d(0.0,-25.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(5.0,-40.0);
        glColor3f(0.01f, 0.36f, 0.176f); glVertex2d(-5.0,-40.0);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.568f, 0.294f, 0.129f);
        glVertex2d(-1,-45.0);
        glVertex2d(-1.5,-60.0);
        glVertex2d(1.5,-60.0);
        glVertex2d(1,-45.0);

    glEnd();
}


void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);{
		for(i = 0; i < 100; i++){
			angle = 2 * 3.1416 * i / 100;
			//glColor3f(1,1,1);
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

    }
	glEnd();

}


void half_circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);{
		for(i = 0; i < 100; i++){
			angle = (3.1416/2) * i / 100;
			//glColor3f(1,1,1);
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

    }
	glEnd();

}
void grass()
{
    glColor3f(.40,.52,.23);
    glPushMatrix();
    glTranslatef(30, -80, 0);
    circle(150,60);
    glPopMatrix();
}

void road()
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2d(-105,-80.0);
        glVertex2d(105.0,-50.0);
        glVertex2d(105.0,-45.0);
        glVertex2d(-105.0,-60.0);
    glEnd();

}

void road_divider()
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(1, 1, 1);
        glVertex2d(-105,-69.0);
        glVertex2d(-74.0,-68.0);
        glVertex2d(-77.0,-66.0);
        glVertex2d(-105,-71);
    glEnd();
}



void cloud1()

{
    glColor3f(1,1,1);

    glPushMatrix();
    glTranslatef(4, 5.5, 0);
    circle(6,6);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-8, 5.5, 0);
    circle(3.5,3.5);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-3.5, 5.9, 0);
    circle(3.5,3.5);
    glPopMatrix();

//top right

    glPushMatrix();
    glTranslatef(1, 9, 0);
    circle(3,3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 5.5, 0);
    circle(4,4);
    glPopMatrix();
}

void cloud2()
{
    glColor3f(1,1,1);

    glPushMatrix();
    glTranslatef(4, 5.5, 0);
    circle(6,6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8, 5.5, 0);
    circle(5.5,5.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5, 5.9, 0);
    circle(5.5,5.5);
    glPopMatrix();

    //top right
    glPushMatrix();
    glTranslatef(1, 9, 0);
    circle(5,5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 5.5, 0);
    circle(6,6);
    glPopMatrix();


}

void archery()
{
    //circleoneX= (double)printRandoms(10, 65, 1);
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslated(circleX,circleY,0);
        circle(3,9);
    glPopMatrix();

    glPushMatrix();
        glColor3f(01,.0,0);
        glTranslated(circleX+0.5,circleY,0);
        circle(4.5,14);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.51,0.8,.21);
        glTranslated(circleX+1,circleY,0);
        circle(6.5,19);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0,.5,.78);
        glTranslated(circleX+1.5,circleY,0);
        circle(9,24);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0,0,0);
        glTranslated(circleX+2.5,circleY,0);
        circle(11,28);
    glPopMatrix();

    glPushMatrix();
        glColor3f(.69,.69,.69);
        glTranslated(circleX+3,circleY,0);
        circle(12,30);
    glPopMatrix();


}


void c1()
{
    glBegin(GL_POINTS);
    float angle = 0.0;
    for(int i=0;i<1000;++i)
    {
        angle = (3.1416/2) * i / 1000;
        glVertex3f(cos(angle)*10,sin(angle)*10,0);
    }
    glBegin(GL_LINES);

 glEnd();

}

void c2()
{
    glBegin(GL_POINTS);
    float angle = 0.0;
    for(int i=1000;i<2000;++i)
    {
        angle = (3.1416/2) * i / 1000;
        glVertex3f(cos(angle)*10,sin(angle)*10,0);
    }
 glEnd();
}

void c3()
{
    glBegin(GL_POINTS);
    float angle = 0.0;
    for(int i=2000;i<3000;++i)
    {
        angle = (3.1416/2) * i / 1000;
        glVertex3f(cos(angle)*10,sin(angle)*10,0);
    }
 glEnd();
}
void c4()
{
    glPointSize(10);
    glBegin(GL_POINTS);

    float angle = 0.0;
    for(int i=3000;i<4000;++i)
    {
        angle = (3.1416/2) * i / 1000;
        glVertex3f(cos(angle)*10,sin(angle)*10,0);
    }
 glEnd();
}
void s1(){
glLineWidth(3);

glBegin(GL_LINES);
glVertex2f(0.0f, 40.0f);
glVertex2f(0.0f, 0.0f);
glEnd();


}

void bow(){
        glColor3f(0.64, 0.16, 0.16);

        glPushMatrix();
            glTranslatef(0, 30, 0);
            c1();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(20, 10, 0);
            c2();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(20, 30, 0);
            c3();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 10, 0);
            c4();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2, 0, 0);
            s1();
        glPopMatrix();
}

void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
    length = strlen(stringToDisplay);
	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}
void Score(int x,int y){

    char temp[40];

	glColor3f(0 ,0 ,1);
	sprintf(temp,"SCORE = %d",x);
	displayRasterText(62 ,85 ,1 ,temp);
	sprintf(temp,"LIFE = %d",y);
	displayRasterText(-90 ,85 ,1 ,temp);

}
void MissStr(char mtep [5]){

    char mtemp[5];
	glColor3f(0 ,0 ,1);
	sprintf(mtemp,"%s",mtep);
	displayRasterText(-5 ,15 ,1 ,mtemp);
}
void simple_trans()
{
    glPushMatrix();

        glColor3f(1,1,1);
        glTranslated(arrowPositonX,arrowPositonY,0);
        glRotated(anglerot,0,0,1);
        arrow();
    glPopMatrix();

    //dhanuk
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslated(-80,bowPostionY,0);
        glRotated(anglerot,0,0,1);
        bow();
    glPopMatrix();


    //Archaic
    glPushMatrix();
        archery();
    glPopMatrix();



    //Tree
    glPushMatrix();
        glTranslatef(90, 0, 0);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(60, 15, 0);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(80, 25, 0);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(40, 10, 0);
        tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-40, 30, 0);
        small_tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20, 35, 0);
        small_tree();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 38, 0);
        small_tree();
    glPopMatrix();


    //cloud
    glPushMatrix();
        glTranslatef(cloudOne, 50, 0);
        cloud1();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cloudSecond, 75, 0);
        cloud2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cloudThree, 50, 0);
        cloud2();
    glPopMatrix();

        glPushMatrix();
        glTranslatef(cloudFour, 40, 0);
        cloud1();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cloudFive, 70, 0);
        cloud2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cloudSix, 80, 0);
        cloud1();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cloudSeven, 30, 0);
        cloud2();
    glPopMatrix();

    //Road divider
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslated(50,5,0);
        road_divider();
    glPopMatrix();

        glPushMatrix();
        glColor3f(1,1,1);
        glTranslated(100,11,0);
        road_divider();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1,1,1);
        glTranslated(150,17,0);
        road_divider();
    glPopMatrix();



}
double curve_by_points()
{
    ///
}
double func(double x)
{
    return x*x;
}
void curve()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    for(double i =-180; i<180;i+=.5)
    {
        glVertex2d(i,10*func(i));
        glVertex2d(i+.5, 10*func(i+.5));
    }
     // It can be any type Gl_POINT,_LINE
    glEnd();

}


void start_screen()
{



    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.0f, 0.6f, 0.6f);
        glVertex2d(-15.0,20.0);

        glVertex2d(15.0,20.0);

        glVertex2d(15.0,5.0);

        glVertex2d(-15.0,5.0);

    glEnd();

    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.0f, 0.6f, 0.6f);
        glVertex2d(-15.0,-5.0);

        glVertex2d(15.0,-5.0);

        glVertex2d(15.0,-20.0);

        glVertex2d(-15.0,-20.0);

    glEnd();

    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(0.745f, 0.870f, 0.960f);
        glVertex2d(-96.0,96.0);

        glVertex2d(96.0,96.0);

        glVertex2d(96.0,-96.0);

        glVertex2d(-96.0,-96.0);

    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-5 ,10 ,1 ,"Start");

	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-10 ,-15 ,1 ,"Instruction");

	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-15 ,-70 ,1 ,"Press `S` to Start");

	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-21 ,-80 ,1 ,"Press `I` for Instruction");


}

void instruction_screen(){







    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        //glColor3f(1.9f, 0.7f, 1.0f);
       glColor3f(0.745f, 0.870f, 0.960f);
        glVertex2d(-96.0,96.0);

        glVertex2d(96.0,96.0);

        glVertex2d(96.0,-96.0);

        glVertex2d(-96.0,-96.0);

    glEnd();




	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-19 ,60 ,1 ,"*** Instruction ***");


	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-28 ,30 ,1 ,"1. Press `Up key` to Move Up");
	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-28 ,15 ,1 ,"2. Press `Down key` to Move Down");
    glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-28 ,0 ,1 ,"3. Press `F` for Fire");
	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-28 ,-15 ,1 ,"4. Press `M` for Main Menu");


}

void your_score_screen(int x){
    char tempp[40];


    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        //glColor3f(1.9f, 0.7f, 1.0f);
       glColor3f(0.745f, 0.870f, 0.960f);
        glVertex2d(-96.0,96.0);

        glVertex2d(96.0,96.0);

        glVertex2d(96.0,-96.0);

        glVertex2d(-96.0,-96.0);

    glEnd();


	glColor3f(0.0f, 0.0f, 0.0f);
	displayRasterText(-19 ,60 ,1 ,"*** Your Score ***");

	glColor3f(0.0f, 0.0f, 0.0f);
    sprintf(tempp,"%d",x);
	displayRasterText(-3 ,30 ,1 ,tempp);



}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();


	gluLookAt(0,0,80,	0,0,0,	0,1,0);



	glMatrixMode(GL_MODELVIEW);
    if (screen==0){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);	//color black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            start_screen();
    }

	//drawGrid();
	//drawCircle(50, 50);
    if (screen==1){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);	//color black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        MissStr(miss);
        Score(FinalScore,Life);
        simple_trans();

        //drawGrid();
        drawAxes();
        //cloud();
        //push_pop();
        //rec_animation();
        //tree();
        road_divider();
        road();
        background1();
        grass();
        background2();
    }
    if (screen==2){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);	//color black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        instruction_screen();
    }
    if (Life==0){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);	//color black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        your_score_screen(FinalScore);
    }
    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){


    cloudOne=cloudOne+0.01;
    cloudSecond=cloudSecond+0.01;
    cloudThree=cloudThree+0.01;
    cloudFour=cloudFour+0.01;
    cloudFive=cloudFive+0.01;
    cloudSix=cloudSix+0.01;
    cloudSeven=cloudSeven+0.01;
    if(cloudOne>=105){
        cloudOne=-105;
    }
    if(cloudSecond>=105){
        cloudSecond=-105;
    }
    if(cloudThree>=105){
        cloudThree=-105;
    }
    if(cloudFour>=105){
        cloudFour=-105;
    }
    if(cloudFive>=105){
        cloudFive=-105;
    }
    if(cloudSix>=105){
        cloudSix=-105;
    }
    if(cloudSeven>=105){
        cloudSeven=-105;
    }
    if (start==true){
        circleX = (double)printRandoms(10, 65, 1);
        circleY = (double)printRandoms(-30, 65, 1);
        //printf("%f \n",circleX);
        //printf("%f \n",circleY);
        //printf("\n");
        start=false;
    }

    if (arrowfire==true){
        arrowPositonX+=0.1;
       // printf("%f\n",arrowPositonX);
    }
    if (arrowPositonX>-80){
        arrowhandle=false;
    }
    if(arrowPositonX>=105){
        //printf("Miss\n");
        strcpy(miss,"MISS");
        //puts(miss);
        Life=Life-1;
        arrowPositonX=-80;
        arrowfire=false;
        arrowhandle=true;
        arrowPositonY=bowPostionY+20;
        fire=true;
        circleX = (double)printRandoms(10, 65, 1);
        circleY = (double)printRandoms(-30, 65, 1);
        strcpy(miss,"");
    }
    if(scoreCheck==true){
        if (arrowPositonY<=circleY+9 && arrowPositonY>=circleY-9 && arrowPositonX+30>=circleX ){
            //printf("%f \n",arrowPositonX);
            //printf("50 point\n");
            Life=Life-1;
            FinalScore=FinalScore+50;
            arrowfire=false;
            scoreCheck=false;
            arrowPositonX=-80;
            arrowPositonY=bowPostionY+20;
            arrowhandle=true;
            fire=true;
            circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
        }
        else if ((arrowPositonY<=circleY+14 && arrowPositonY>circleY+9) || (arrowPositonY>=circleY-14 && arrowPositonY<circleY-9) && arrowPositonX+30.5>=circleX ){
            //printf("%f>=%f \n",arrowPositonX+30.5,circleX);
            //printf("40 point\n");
            Life=Life-1;
            FinalScore=FinalScore+40;
            arrowfire=false;
            scoreCheck=false;
            arrowPositonX=-80;
            arrowPositonY=bowPostionY+20;
            arrowhandle=true;
            fire=true;
            circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
        }
        else if ((arrowPositonY<=circleY+19 && arrowPositonY>circleY+14)  || (arrowPositonY>=circleY-19 && arrowPositonY<circleY-14) && arrowPositonX+31>=circleX){
            //printf("%f >=%f\n",arrowPositonX+31,circleX);
            //printf("30 point\n");
            Life=Life-1;
            FinalScore=FinalScore+30;
            arrowfire=false;
            scoreCheck=false;
            arrowPositonX=-80;
            arrowPositonY=bowPostionY+20;
            arrowhandle=true;
            fire=true;
            circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
        }
        else if((arrowPositonY<=circleY+24 && arrowPositonY>circleY+19) || (arrowPositonY>=circleY-24 && arrowPositonY<circleY-19) && arrowPositonX+31.5>=circleX){
            //printf("%f>=%f \n",arrowPositonX+31.5,circleX);
            //printf("20 point\n");
            Life=Life-1;
            FinalScore=FinalScore+40;
            arrowfire=false;
            scoreCheck=false;
            arrowPositonX=-80;
            arrowPositonY=bowPostionY+20;
            arrowhandle=true;
            fire=true;
            circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
        }
        else if ((arrowPositonY<=circleY+28 && arrowPositonY>circleY+24) || (arrowPositonY>=circleY-28 && arrowPositonY<circleY-24) && arrowPositonX+32.5>=circleX){
            //printf("%f >=%f\n",arrowPositonX+32.5,circleX);
            //printf("10 point\n");
            Life=Life-1;
            FinalScore=FinalScore+10;
            arrowfire=false;
            scoreCheck=false;
            arrowPositonX=-80;
            arrowPositonY=bowPostionY+20;
            arrowhandle=true;
            fire=true;
            circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
        }

    }


	glutPostRedisplay();
}

void init(){
	//codes for initialization
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);


	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(100,	1,	1,	1000.0);

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

        case 'w':
            //archeryPositonX = printRandoms(10, 65, 1);
            //archeryPositonY = printRandoms(-20, 75, 1);
            /*circleX = (double)printRandoms(10, 65, 1);
            circleY = (double)printRandoms(-30, 65, 1);
            printf("%f \n",circleX);
            printf("%f \n",circleY);
            printf("\n");*/
			break;
        case '4':
            break;
        case 'f':
            if (Life==0){
                arrowfire==false;
                scoreCheck==false;
                fire=false;
                ScreenFour=true;
            }
            if(fire==true){
                scoreCheck=true;
                arrowfire=true;
                fire=false;
            }


            break;
        case 'm':
            screen=0;
            //anglerot=anglerot+1;
            break;
        case 'i':
            //anglerot=anglerot-1
            screen=2;
            break;
        case 's':
            screen=1;
            break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:
		    bowPostionY=bowPostionY-1;
		    if(arrowhandle==true){
                arrowPositonY=arrowPositonY-1;
		    }

		    if (bowPostionY<=-85){
                bowPostionY=-85;
                arrowPositonY=-65;
		    }
            //bowPostionY=bowPostionY-1;
			break;
		case GLUT_KEY_UP:		// up arrow key
		    bowPostionY=bowPostionY+1;
		    if(arrowhandle==true){
                arrowPositonY=arrowPositonY+1;
		    }
		    if (bowPostionY>=40){
                bowPostionY=40;
                arrowPositonY=60;
		    }
			break;

		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_LEFT:
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
		    //code
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}
int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(150, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");
	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	//glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}


