// originally written by ban-masa https://gist.github.com/ban-masa/0ce4b750a5dffd72e6a653cb12696cc7

#include <stdlib.h>
#include <GL/glut.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

cv::VideoCapture capture;
cv::Mat origin_img[6];
cv::Mat src_img[6];
//IplImage* origin_img[6] = {0};
//IplImage* src_img[6] = {0};
int r[3] = {0};
int states[3] = {0};

GLdouble vertex[][3] = {
  {0.0, 0.0, 0.0},
  {1.0, 0.0, 0.0},
  {1.0, 1.0, 0.0},
  {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0},
  {1.0, 0.0, 1.0},
  {1.0, 1.0, 1.0},
  {0.0, 1.0, 1.0}
};

int edge[][2] = {
  {0, 1},
  {1, 2},
  {2, 3},
  {3, 0},
  {4, 5},
  {5, 6},
  {6, 7},
  {7, 4},
  {0, 4},
  {1, 5},
  {2, 6},
  {3, 7}
};

int face[][4] = {
  {0, 1, 2, 3},
  {1, 5, 6, 2},
  {5, 4, 7, 6},
  {4, 0, 3, 7},
  {4, 5, 1, 0},
  {7, 3, 2, 6}
};

GLdouble normal[][3] = {
  {0.0, 0.0, -1.0},
  {1.0, 0.0, 0.0},
  {0.0, 0.0, 1.0},
  {-1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0},
  {0.0, 1.0, 0.0}
};

GLdouble color[][3] = {
  {1.0, 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0},
  {1.0, 1.0, 0.0},
  {1.0, 0.0, 1.0},
  {0.0, 1.0, 1.0}
};

GLdouble texture[][2] = {
  {1.0, 1.0},
  {0.0, 1.0},
  {0.0, 0.0},
  {1.0, 0.0}
};

GLuint textures[6];
void idle2(void);
void convert_size(cv::Mat from, cv::Mat to);
void idle(void)
{
  int i;
  static int pr[3] = {0};
  for (i = 0; i < 3; i++) {
    if (states[i] != 0) {
      r[i] += states[i]*2;
      //            pr[i] += 2;
    }
    if (r[i] >= 360 || r[i] <= -360) r[i] = 0;
    if (pr[i] >= 90) {
      pr[i] = 0;
      glutIdleFunc(idle2);
    }
  }
  idle2();
  glutPostRedisplay();
}

void idle2(void)
{
  capture.read(origin_img[5]);
  convert_size(origin_img[5], src_img[5]);
  glEnable(GL_TEXTURE_2D);
  {
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, src_img[5].cols, src_img[5].rows, GL_RGB, GL_UNSIGNED_BYTE, src_img[5].data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
  glDisable(GL_TEXTURE_2D);
}

void init(void)
{
  int i;
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glEnable(GL_TEXTURE_2D);
  glGenTextures(6, textures);
  for (i = 0; i < 6; i++) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, src_img[i].cols, src_img[i].rows, GL_RGB, GL_UNSIGNED_BYTE, src_img[i].data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
  glDisable(GL_TEXTURE_2D);
  glClearColor (0.2, 0.2, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  //    glEnable(GL_LIGHTING);
  //    glEnable(GL_LIGHT0);
}

void display(void)
{
  int i;
  int j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glScaled(1.5, 1.5, 1.5);
  glRotated((double)r[0], 1.0, 0.0, 0.0);
  glRotated((double)r[1], 0.0, 1.0, 0.0);
  glRotated((double)r[2], 0.0, 0.0, 1.0);
  glTranslated(-0.5, -0.5, -0.5);
  glColor3d(1.0, 1.0, 1.0);
  for (j = 0; j < 6; j++) {
    glBindTexture(GL_TEXTURE_2D, textures[j]);
    glBegin(GL_QUADS);
    //        glNormal3dv(normal[j]);
    for (i = 0; i < 4; i++) {
      glTexCoord2dv(texture[i]);
      glVertex3dv(vertex[face[j][i]]);
    }
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
  glFlush();
  /*    if (glutLayerGet(GLUT_NORMAL_DAMAGED) == 0) {
        r += 2;
        if (r >= 360) {
        r = 0;
        glutIdleFunc(0);
        }
        }*/
}

void resize (int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w/(double)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  int i;
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP) {
        if (states[0] == 0) states[0] = 1;
        else states[0] = 0;
        glutIdleFunc(idle);
      }
      break;
    case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_UP) {
        if (states[1] == 0) states[1] = 1;
        else states[1] = 0;
        glutIdleFunc(idle);
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_UP) {
        if (states[2] == 0) states[2] = 1;
        else states[2] = 0;
        glutIdleFunc(idle);
      }
      break;
    default:
      break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 'r':
      r[0] = 0;
      r[1] = 0;
      r[2] = 0;
      break;
    case 'q':
      states[0] = 0;
      states[1] = 0;
      states[2] = 0;
      break;
    case '\033':
      exit(0);
    default:
      break;
  }
}

void specialkeydown(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_UP:
      states[0] = 1;
      glutIdleFunc(idle);
      break;
    case GLUT_KEY_DOWN:
      states[0] = -1;
      glutIdleFunc(idle);
      break;
    case GLUT_KEY_LEFT:
      states[1] = -1;
      glutIdleFunc(idle);
      break;
    case GLUT_KEY_RIGHT:
      states[1] = 1;
      glutIdleFunc(idle);
      break;
  }
}

void convert_size(cv::Mat from, cv::Mat to)
{
  cv::resize(from, to, to.size());
  cv::cvtColor(to, to, cv::COLOR_BGR2RGB);
  cv::transpose(to, to);
  cv::flip(to, to, 0);
}

int main(int argc, char **argv)
{
  int i;
  printf("start program\n");
  capture = cv::VideoCapture(0);
  printf("create capture object\n");
  for (i = 0; i < 5; i++) {
    src_img[i] = cv::Mat(640, 640, CV_8UC3);
    if (i < argc - 1) {
      origin_img[i] = cv::imread(argv[1 + i], CV_LOAD_IMAGE_COLOR);
      convert_size(origin_img[i], src_img[i]);
    }
  }
  printf("setup src_img[0-4]\n");
  src_img[5] = cv::Mat(640, 640, CV_8UC3);
  printf("setup src_img[5]\n");
  capture.read(origin_img[5]);
  printf("capture_read\n");
  convert_size(origin_img[5], src_img[5]);
  printf("convert size\n");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeydown);
  init();
  glutPostRedisplay();
  printf("start glut main loop\n");
  glutMainLoop();
  return 0;
}
