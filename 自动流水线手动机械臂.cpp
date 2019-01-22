//功能描述：按s键流水线启动，当行至第一台机械臂时按下a键机械臂下落，灌注后按下q键机械臂回升，同理当行至第二台机械臂时，按下d键机械臂下落，加盖后按e键机械臂回升。

#include<windows.h>
#include"head.h"

static float shoulder = 0, elbow1 = 0, elbow2 = 0, movex = 0.2, movey = 2, movez = 5, t = 0;


void init(void)
{
	GLfloat mau[] = { 1.0,0.0,0.5,1.0 };
	GLfloat mcu[] = { 50.0 };
	GLfloat light_position[] = { 1.0,1.0,1.0,2.0 };//光照位置
	GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };
	GLfloat msu[] = { 0.1,0.1,0.1,1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mau);
	glMaterialfv(GL_FRONT, GL_SHININESS, mcu);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, msu);
	glEnable(GL_LIGHTING);//启动光照
	glEnable(GL_LIGHT0);//启动第一盏灯的光照
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

}

void display(void)
{
	glClearColor(0.0, 1.0, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 10, 0.0, 0.0, 0.0, 1.0, 0.0);

	//机床
	glPushMatrix();
	glTranslatef(0, 1.75, -5);
	glScalef(3, 3, 4);
	glColor3f(5, 1, 0);
	glutSolidCube(1.0);
	glPopMatrix();

	//地面
	glPushMatrix();
	glColor3f(0.0, 0.2, 0.5);
	glTranslatef(2.0, -2.0, 0.0);
	glScalef(50.0, 1.0, 50.0);
	glutSolidCube(1.0);
	glPopMatrix();
	//天花板
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.3);
	glTranslatef(4.0, 17.0, -20.0);
	glScalef(50.0, 1.0, 100.0);
	glutSolidCube(1.0);
	glPopMatrix();
	//可乐瓶
	glPushMatrix();
	if (t == 1.0)//瓶 
	{
		glColor3f(1.0, 1.0, 0.0);
		GLUquadricObj *pobj;
		pobj = gluNewQuadric();
		gluQuadricNormals(pobj, GLU_SMOOTH);
		glTranslatef(movex, 2, movez);
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		gluCylinder(pobj, 0.5, 0.5, 1.2, 26, 13);
		//gluDisk(pobj,0.0f, 0.5f, 20, 20);
		glPopMatrix();
	}
	if (t == 1.5)//+盖子 
	{
		glColor3f(1.0, 1.0, 0.0);
		GLUquadricObj *pobj;
		pobj = gluNewQuadric();
		gluQuadricNormals(pobj, GLU_SMOOTH);
		glTranslatef(movex, movey, movez);
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		gluCylinder(pobj, 0.5, 0.5, 1.2, 26, 13);
		gluDisk(pobj, 0.0f, 0.5f, 20, 20);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0.45, 0);
		glColor3f(1, 0, 0);
		glRotatef(90, 1, 0, 0);
		gluCylinder(pobj, 0.3, 0.3, 0.4, 26, 13);
		gluDisk(pobj, 0.0f, 0.3f, 20, 20);
		glPopMatrix();
	}
	else if (t == 0)//方块 
	{
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(movex, 1.3, movez);
		glScalef(0.8, 1.2, 0.8);
		glutSolidCube(1.0);
	}
	else if (t == 0.5)//变色方块 
	{
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(movex, 1.3, movez);
		glScalef(0.8, 1.2, 0.8);
		glutSolidCube(1.0);
	}
	glPopMatrix();
	//机械臂1
	glColor3f(0.5, 2, 2);

	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glRotatef((GLfloat)shoulder, 0, 0, 1);
	glTranslatef(0, 1, 0);
	glPushMatrix();
	glScalef(0.4, 4, 1.0);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0, 2, 0);
	glRotatef((GLfloat)elbow1, 0, 0, 1);
	glTranslatef(1, 0, 0);
	glPushMatrix();
	glScalef(2, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	//机械臂2

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef((GLfloat)shoulder, 0, 0, 1);
	glTranslatef(0, 1, 0);
	glPushMatrix();
	glScalef(0.4, 4, 1.0);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0, 2, 0);
	glRotatef((GLfloat)elbow2, 0, 0, 1);
	glTranslatef(1, 0, 0);
	glPushMatrix();
	glScalef(2, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
	//传输带 
	glColor3f(1.0, 1.0, 1.0);
	glScalef(1.2, 1.5, 12);
	glutSolidCube(1.0);

	glPushMatrix();
	glTranslatef(10.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, 0.0, -0.5);
	glScalef(11.0, 1.0, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15.0, 0.0, 0.5);
	glScalef(11, 1.0, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(20, 0.0, 0.5);
	glScalef(2.2, 3.5, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();



	glutSwapBuffers();

	glFlush();

}
//机械臂控制动画 
void down1(void)
{

	if (elbow1> -30)
		elbow1 = elbow1 - 0.02;
	glutPostRedisplay();
}
void up1(void)
{
	if (elbow1<0)
		elbow1 = elbow1 + 0.02;
	glutPostRedisplay();
}
void down2(void)
{

	if (elbow2> -30)
		elbow2 = elbow2 - 0.02;
	glutPostRedisplay();
}
void up2(void)
{
	if (elbow2<0)
		elbow2 = elbow2 + 0.02;
	glutPostRedisplay();
}

//传送带控制动画
void move(int id)
{

	if (movex <= 0.3&&movez >= 0.15)
		movez -= 0.03;
	glutPostRedisplay();
	glutTimerFunc(10, move, 0);//行进至灌注机床
}

void move2(int id)
{

	if (movex <= 0.3&&movez > -6)
	{
		t = 0.5;
		movez -= 0.03;//行进至包装机床
	}
	else if (movex < 12)
	{
		t = 1;
		movex += 0.03;//行进至拐角
	}
	glutPostRedisplay();
	glutTimerFunc(10, move2, 2);
}
//***********************************************
void move3(int id)
{
	if (movez < 0.1)
	{
		t = 1;
		movez += 0.03;
	}
	glutPostRedisplay();
	glutTimerFunc(10, move3, 3);
}

void move4(int id)
{
	if (movez < 5.9)
	{
		t = 1.5;
		movez += 0.03;
	}
	else if (movex < 25)
		movex += 0.03;
	else if (movey>-1)
		movey -= 0.1;
	glutPostRedisplay();
	glutTimerFunc(10, move4, 4);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'q':
		glutIdleFunc(up1);
		break;
	case'a':
		glutIdleFunc(down1);
		break;
	case'e':
		glutIdleFunc(up2);
		break;
	case'd':
		glutIdleFunc(down2);
		break;
	case's':
	{ {
			glutTimerFunc(0, move, 0);
			glutTimerFunc(3500, move2, 2);
			glutTimerFunc(9500, move3, 3);
			glutTimerFunc(13500, move4, 4);
		}
	break;
	}
	default:
		break;
	}
}
void reshape(int width, int height)

{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLfloat)width / (GLfloat)height, 1.0f, 25.0f);//建立一个透视投影视图体，格式为：gluPerspective(视域的角度，宽高比，视点到近裁剪面的距离（总为正），视点到远裁剪面的距离（总为正））
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Cola Factory");
	init();
	glutDisplayFunc(&display);
	glutKeyboardFunc(&keyboard);
	glutReshapeFunc(&reshape);
	glutMainLoop();
	return 0;
}
