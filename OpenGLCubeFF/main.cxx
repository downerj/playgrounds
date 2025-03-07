// Code adapted from https://gist.github.com/hkulekci/2300262

#include <cstdlib>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif // __APPLE__

#define KEY_ESC 27

int window = -1;

void initialize() {
  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0f);
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
  switch (key) {
    case KEY_ESC: {
      glutDestroyWindow(window);
      std::exit(0);
    }
  }
  glutPostRedisplay();
}

void resize(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  const float growShrink{70.0f};
  const float resizeF{1.0f};
  gluPerspective(growShrink, resizeF*w/h, resizeF, 100*resizeF);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawBox() {
  glBegin(GL_QUADS); {
    glColor3f(1.0f, 0.0f, 0.0f);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, -0.5f, 0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
  } glEnd();  
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(
	  0.0f, 0.0f, 3.0f,
	  0.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f
  );

  drawBox();

  glFlush();
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  window = glutCreateWindow("GLTest");
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);

  initialize();

  glutMainLoop();
}
