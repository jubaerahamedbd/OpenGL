#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
double angle;
double incx, ani_angle;
struct point
{
	double x,y,z;
};

struct point pos,l,u,r;
double X=0,Z=0;
int Y=-1;
struct point arra[100];
void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
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


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void draw_cylinder(double radius1,double radius2,double height,int segments)
{
    int i;
    double shade;
     struct point points[2][100];
     for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius2*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius2*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;

        points[1][i].x=radius1*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius1*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height;
    }

    for (i=0;i<segments;i++)
    {
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);

    //    glColor3f(shade,shade,1);
        glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f((i)%2,(i)%2,(i+1)%2);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);

				glColor3f((i)%2,(i)%2,(i+1)%2);
				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}glEnd();


    }
}
void draw_c(double radius1,double radius2,double height,int segments)
{
    int i;
     struct point points[2][100];
     for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius2*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius2*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;

        points[1][i].x=radius1*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius1*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height;
    }

    for (i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(1,1,1);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);

				glColor3f(1,1,1);
				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}glEnd();


    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        glColor3f((i+1)%2,(i)%2,(i+2)%2);
       /* if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);

        glColor3f(shade,shade,1);*/

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void GombuzCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        glColor3f((i)%2,(i+2)%2,(i+1)%2);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void dimond(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);

        glColor3f(shade,shade,1);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,15);
			glVertex3f(points[i+1].x,points[i+1].y,15);
        }
        glEnd();
    }
}

void Gombuz(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(1,.50,0.32);
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glColor3f(0,0,1);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}
}

void SphereCircle(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			     glColor3f(1,.50,0.32);
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glColor3f(0,0,1);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere

                glColor3f(1,.50,0.32);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glColor3f(0,0,1);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}
void ground(){
    glBegin(GL_QUADS);

            glColor3f(0.3f,1.0f,0.5f);

            glVertex3f(-50.0f,50.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(50.0f,50.0f,0.0f);					    // Top back Of The Quad (right)
            glVertex3f(50.0f,-50.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(-50.0f,-50.0f,0.0f);					// Bottom front Of The Quad (right)
             glEnd();

}
void quad()
{
  // Draw A Quad
        glBegin(GL_QUADS);

            glColor3f(1.0f,1.0f,0.0f);

            glVertex3f(5.0f,5.0f,0.0f);
            glVertex3f(5.0f,-5.0f,0.0f);
            glVertex3f(5.0f,-5.0f,6.0f);
            glVertex3f(5.0f,5.0f,6.0f);


            glColor3f(0.0f,1.0f,1.0f);

            glVertex3f(5.0f,5.0f,0.0f);
            glVertex3f(-5.0f,5.0f,0.0f);
            glVertex3f(-5.0f,5.0f,6.0f);
            glVertex3f(5.0f,5.0f,6.0f);

            glColor3f(0.0f,1.0f,0.0f);

            glVertex3f(-5.0f,5.0f,0.0f);
            glVertex3f(-5.0f,-5.0f,0.0f);
            glVertex3f(-5.0f,-5.0f,6.0f);
            glVertex3f(-5.0f,5.0f,6.0f);


            glColor3f(1.0f,0.10f,0.60f);

            glVertex3f(-5.0f,-5.0f,0.0f);
            glVertex3f(5.0f,-5.0f,0.0f);
            glVertex3f(5.0f,-5.0f,6.0f);
            glVertex3f(-5.0f,-5.0f,6.0f);


            glColor3f(0.0f,0.0f,1.0f);

            glVertex3f(-5.0f,5.0f,6.0f);
            glVertex3f(5.0f,5.0f,6.0f);
            glVertex3f(5.0f,-5.0f,6.0f);
            glVertex3f(-5.0f,-5.0f,6.0f);

        glEnd();
}
void pyramid()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,0);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glColor3f(1,0,1);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(0,0,5);

    glColor3f(1,0,0);

    glVertex3d(0,5,0);
    glVertex3d(0,0,5);
    glVertex3d(-5,-3,0);

    glColor3f(0,1,0);

    glVertex3d(0,0,5);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glEnd();
}

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int xx,int yy){
    double x,y,z;
    double rate = 0.01;
	switch(key){

		case '1':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+1*r.x*sin(rate);
			l.y = l.y*cos(rate)+r.y*sin(rate);
			l.z = l.z*cos(rate)+r.z*sin(rate);

			r.x = r.x*cos(rate)-x*sin(rate);
			r.y = r.y*cos(rate)-y*sin(rate);
			r.z = r.z*cos(rate)-z*sin(rate);}
			break;
        case '2':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+r.x*sin(-rate);
			l.y = l.y*cos(-rate)+r.y*sin(-rate);
			l.z = l.z*cos(-rate)+r.z*sin(-rate);

			r.x = r.x*cos(-rate)-x*sin(-rate);
			r.y = r.y*cos(-rate)-y*sin(-rate);
			r.z = r.z*cos(-rate)-z*sin(-rate);
			}
			break;
        case '3':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+u.x*sin(rate);
			l.y = l.y*cos(rate)+u.y*sin(rate);
			l.z = l.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '4':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
			l.y = l.y*cos(-rate)+u.y*sin(-rate);
			l.z = l.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case '6':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(rate)+u.x*sin(rate);
			r.y = r.y*cos(rate)+u.y*sin(rate);
			r.z = r.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '5':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(-rate)+u.x*sin(-rate);
			r.y = r.y*cos(-rate)+u.y*sin(-rate);
			r.z = r.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
		default:
			break;
	}

}


void specialKeyListener(int key, int x,int y)
{
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			pos.x+=l.x;
			pos.y+=l.y;
			pos.z+=l.z;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			pos.x-=l.x;
			pos.y-=l.y;
			pos.z-=l.z;
			break;

		case GLUT_KEY_LEFT :
			pos.x+=r.x;
			pos.y+=r.y;
			pos.z+=r.z;
			break;
		case GLUT_KEY_RIGHT :
			pos.x-=r.x;
			pos.y-=r.y;
			pos.z-=r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;
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


void mouseListener(int button, int state, int x, int y)
{	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

			}
			break;


		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

				//(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
			}
			break;
			//........

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void mosque()
{
    quad();
    glPushMatrix();
    glTranslated(5,5,0);
    draw_cylinder(1.0,1.0,8,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(5,-5,0);
    draw_cylinder(1.0,1.0,8,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5,5,0);
    draw_cylinder(1.0,1.0,8,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5,-5,0);
    draw_cylinder(1.0,1.0,8,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,6);
    Gombuz(2.5,24,20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,8.5);
    Gombuz(0.5,24,20);
    glPopMatrix();
   //
    glPushMatrix();
    glTranslated(0,0,9);
    GombuzCone(.2,5,6);
    glPopMatrix();


    glPushMatrix();
    glTranslated(5,5,8);
    drawCone(1,2,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(5,-5,8);
    drawCone(1,2,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5,5,8);
    drawCone(1,2,6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5,-5,8);
    drawCone(1,2,6);
    glPopMatrix();
}
void animation3d()
{
    glPushMatrix();
    ground();
    glPopMatrix();
    glPushMatrix();
    glRotated(-1.9*ani_angle+30,0,0,1);
       mosque();
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glRotated(-1.9*ani_angle+30,1,1,1);
    glTranslated(45,0,1);
    SphereCircle(4,40,40);
    glPopMatrix();
}

void display()
{

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	animation3d();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){

    incx+=0.05;
    ani_angle+=0.09;
	glutPostRedisplay();
}

void init(){
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(100,	1,	1,	2000.0);

	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv)
{
    pos.x=0;
    pos.y=-20;
    pos.z=-20;
    l.x=0;u.x=-1;r.x=0;
    l.y=0;u.y=0;r.y=1;
    l.z=1;u.z=0;r.z=0;

	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}


