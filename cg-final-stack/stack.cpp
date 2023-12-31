#include<iostream>
#include<cstring>
#include<string>
#include<Windows.h>
#include<GL/glut.h>
#include <cstdlib>
#include<stack>
using namespace std;

struct elem
{
	char c[20];	
};
stack<int> st;
int MAX = 5;
int tos = -1;
int width = 200;
int height = 25;
elem a[20];
int SCREEN_WIDTH = 800; //Width of the screen
int SCREEN_HEIGHT = 500; //Height of the screen

bool init()
{

	glClearColor(0, 0.4 , 0.3 , 1); //Set the background 
	glViewport(0, 0, 500, 500); //Setting the viewport i.e. where the primitive should be displayed
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -100, 100); //Set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //If error is there
	{
		return false; //return error has been detected
	}

	return true; //return everything is fine continue
}
void show();

void drawBitmap(char *string, int x, int y)
{	
	
	glRasterPos2f(x, y);

	for (int i = 0; i < strlen(string); i++)
	{
		
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		

	}
	glFlush();
}

void reverse_polish() {
	if (tos < 0) {
		drawBitmap("STACK IS EMPTY", -70, 200);
		glutSwapBuffers();
		Sleep(1000);
	}
	int temp = tos;
	for (int i = 0; i <= temp; i++) {
		
		if (*a[i].c != '+' && *a[i].c != '-' && *a[i].c != '*' && *a[i].c !='/') {
			st.push(stoi(a[i].c));
			continue;
		}
		else {
			int num1 = st.top();
			st.pop();
			tos--;
			int num2 = st.top();
			st.pop();
			tos--;
			if (*a[i].c == '+') {
				int num = num1 + num2;
				st.push(num);
				string s = to_string(num);
				char const* pchar = s.c_str();
				
				strcpy(a[tos].c,pchar);
			}
			else if (*a[i].c == '-') {
				int num = num1 - num2;
				st.push(num);
				string s = to_string(num);
				char const* pchar = s.c_str();
				strcpy(a[tos].c, pchar);
			}
			else if (*a[i].c == '*') {
				int num = num1 * num2;
				st.push(num);
				string s = to_string(num);
				char const* pchar = s.c_str();
				strcpy(a[tos].c, pchar);
			}
			else {
				if (num2 == 0) {
					drawBitmap("STACK IS FULL", -70, 200);
					glutSwapBuffers();
					Sleep(100);
				}
				else {
				float num = num1 / num2;
				st.push(num);
				string s = to_string(num);
				char const* pchar = s.c_str();
				strcpy(a[tos].c, pchar);
				}
			}

		}
	}
	glutPostRedisplay();
}

void push()
{	
	if (tos >= MAX)
	{
		drawBitmap("STACK IS FULL", -70, 200);
		glutSwapBuffers();
		Sleep(100);
		
	}
	else{
		tos++;
		printf("\nEnter the Element: ");
		cin >> a[tos].c;
		cout << endl;
		show();

	}
}



void pop()
{
	if (tos < 0)
	{
		drawBitmap("STACK IS EMPTY", -70, 200);
		glutSwapBuffers();
		Sleep(1000);
	}
	else
	{
		cout << "\nElement " << a[tos].c << " is removed from stack\n";
		tos--;
		show();
	}
}


void show()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = 0; i <= tos; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		//glColor3f(0, 0, 0);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		for (int j = 0; j < strlen(a[i].c); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i].c[j]);
		}
		k += 50;
	}
	glutSwapBuffers();
	glPopMatrix();
}

void render() //display function 
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	
	if (tos == -1)
	{
		char* c = "4. Enter s or S to solve(Enter valid reverse polish notation)";
		glRasterPos2i(-150, 100);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "3. Enter q or Q to Exit";
		glRasterPos2i(-150, 120);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "2. Enter r or R to Pop";
		glRasterPos2i(-150,140);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "1. Enter i or I to Push";
		glRasterPos2i(-150, 160);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		


		glFlush();
		glutSwapBuffers();
	}
	else{
		glFlush();
		show();
		}
}

void reshape(int w, int h) //function to call when the screen is reshaped
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed
	glOrtho(-250, 250, -250, 250, -100, 100); //set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i' | 'I': push();
		break;

	case 'r' | 'R': pop();
		render();
		break;
	case 's' | 'S': reverse_polish();
		break;
	case 'q' | 'Q': exit(0);
	}
}

int main(int argc, char*argv[])
{
	//Main function
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow("STACK");//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

	return 0;
}