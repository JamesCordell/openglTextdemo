/*
 * Copyright (c) 1991, 1992, 1993 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the name of
 * Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF
 * ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glut_wrap.h"


char string[] = "";
GLenum rgb, doubleBuffer, windType;
float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
float scaleX = 1.0, scaleY = 1.0, scaleZ = 0.0;
float shiftX = 0.0, shiftY = 0.0, shiftZ = -200.0;

enum {width=400,height=400};

unsigned char img[3 * width * height];

#include "tkmap.c"


static void DrawStrokeString(void *font, const char *string)
{

glPointSize(2.0f);  
//glBegin(GL_POINTS); // Start drawing a point primitive  
glBegin(GL_LINES); // Start drawing a point primitive  
/*glVertex3f(-10.0f, -10.0f, 0.0f); // The bottom left corner  
glVertex3f(-10.0f, 10.0f, 0.0f); // The top left corner  

glVertex3f(-10.0f, 10.0f, 0.0f); // The top left corner  
glVertex3f(10.0f, 10.0f, 0.0f); // The top right corner  

glVertex3f(-10.0f, -10.0f, 0.0f); // The bottom left corner  
glVertex3f(10.0f, -10.0f, 0.0f); // The bottom right corner  

glVertex3f(10.0f, 10.0f, 0.0f); // The top right corner  
glVertex3f(10.0f, -10.0f, 0.0f); // The bottom right corner  

glVertex3f(10.0f, 10.0f, 0.0f); // The top right corner  
glVertex3f(10.0f, -10.0f, 0.0f); // The bottom right corner  
*/
glVertex3f(-10 ,0 ,0);
glVertex3f( 10 ,0 ,0);

glVertex3f(0 ,-10 ,0);
glVertex3f(0 ,10 ,0);


glEnd();  

}

static void Init(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearIndex(0.0);
}

static void Reshape(int width, int height)
{

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-400.0, 400.0, -200.0, 200.0, -400.0, 400.0);
//GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near,GLdouble far)
    glFrustum( -width/2, width/2, -height/2, height/2, 1000, 1);
    glMatrixMode(GL_MODELVIEW);
}

static void Key2(int key, int x, int y)
{

    switch (key) {
      case GLUT_KEY_LEFT:
	shiftX -= 0.1;
	break;
      case GLUT_KEY_RIGHT:
	shiftX += 0.1;
	break;
      case GLUT_KEY_UP:
	shiftY += 0.1;
	break;
      case GLUT_KEY_DOWN:
	shiftY -= 0.1;
	break;
      default:
	return;
    }

    glutPostRedisplay();
}

static void Key(unsigned char key, int x, int y)
{

    switch (key) {
      case 27:
        exit(1);

      case 'n':
	shiftZ += 5.0;
	break;
      case 'm':
	shiftZ -= 5.0;
	break;

      case 'q':
	scaleX -= 0.1;
	if (scaleX < 0.1) {
	    scaleX = 0.1;
	}
	break;
      case 'w':
	scaleX += 0.1;
	break;
      case 'a':
	scaleY -= 0.1;
	if (scaleY < 0.1) {
	    scaleY = 0.1;
	}
	break;
      case 's':
	scaleY += 0.1;
	break;
      case 'z':
	scaleZ -= 0.1;
	if (scaleZ < 0.1) {
	    scaleZ = 0.1;
	}
	break;
      case 'x':
	scaleZ += 0.1;
	break;

      case 'e':
	angleX -= 5.0;
	if (angleX < 0.0) {
	    angleX = 360.0 + angleX;
	}
	break;
      case 'r':
	angleX += 5.0;
	if (angleX > 360.0) {
	    angleX = angleX - 360.0;
	}
	break;
      case 'd':
	angleY -= 5.0;
	if (angleY < 0.0) {
	    angleY = 360.0 + angleY;
	}
	break;
      case 'f':
	angleY += 5.0;
	if (angleY > 360.0) {
	    angleY = angleY - 360.0;
	}
	break;
      case 'p':
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	printf("print\n");
        for (int i=0; i < (width*height*3) ;++i) {
	  if (img[i] != 0 ) {
	  printf("%i %i %i",img[i] ,img[i+1] ,img[i+2]);
	  }
	}
	break;
      case 'c':
	angleZ -= 5.0;
	if (angleZ < 0.0) {
	    angleZ = 360.0 + angleZ;
	}
	break;
      case 'v':
	angleZ += 5.0;
	if (angleZ > 360.0) {
	    angleZ = angleZ - 360.0;
	}
	break;
      default:
	return;
    }

    glutPostRedisplay();
}

static void Draw(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    SetColor(COLOR_WHITE);

    glPushMatrix();

    glTranslatef(shiftX, shiftY, shiftZ);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, scaleZ);

//    glPushMatrix();
//    glTranslatef(0, 0, 0);
    DrawStrokeString(GLUT_STROKE_ROMAN, string);
//    glPopMatrix();

    glPopMatrix();

    glFlush();

    if (doubleBuffer) {
      glutSwapBuffers();
    }
}

static GLenum Args(int argc, char **argv)
{
    GLint i;

    rgb = GL_TRUE;
    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-ci") == 0) {
	    rgb = GL_FALSE;
	} else if (strcmp(argv[i], "-rgb") == 0) {
	    rgb = GL_TRUE;
	} else if (strcmp(argv[i], "-sb") == 0) {
	    doubleBuffer = GL_FALSE;
	} else if (strcmp(argv[i], "-db") == 0) {
	    doubleBuffer = GL_TRUE;
	} else {
	    printf("%s (Bad option).\n", argv[i]);
	    return GL_FALSE;
	}
    }
    return GL_TRUE;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    if (Args(argc, argv) == GL_FALSE) {
	exit(1);
    }

    glutInitWindowPosition(2000, 0); glutInitWindowSize( width, height);

    windType = (rgb) ? GLUT_RGB : GLUT_INDEX;
    windType |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(windType);

    if (glutCreateWindow("Font Test") == GL_FALSE) {
	exit(1);
    }

    InitMap();

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutSpecialFunc(Key2);
    glutDisplayFunc(Draw);
    glutMainLoop();
	return 0;
}
