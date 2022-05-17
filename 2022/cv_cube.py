import cv2
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

# Loading Camera and Nose image and Creating mask
cap = None
def opencv_init():
    global cap
    cap = cv2.VideoCapture(0)

def opencv_loop():
    global cap
    _, frame = cap.read()
    cv2.imshow("Frame", frame)
    return cv2.waitKey(1)

def main2():
    opencv_init()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH)
    glutInitWindowSize(300, 300)     # window size
    glutInitWindowPosition(100, 100) # window position
    glutCreateWindow(b"teapot")      # show window
    glutDisplayFunc(display)         # draw callback function
    glutReshapeFunc(reshape)         # resize callback function
    glutKeyboardFunc(keyboard)       # Keyboard event callback
    glutIdleFunc(opencv_loop)        # call opencv_loop when idle time
    init(300, 300)
    i = 0;
    glutMainLoop()

def main():
    opencv_init()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH)
    glutInitWindowSize(300, 300)     # window size
    glutInitWindowPosition(100, 100) # window position
    glutCreateWindow(b"teapot")      # show window
    glutDisplayFunc(display)         # draw callback function
    glutReshapeFunc(reshape)         # resize callback function
    glutKeyboardFunc(keyboard)       # Keyboard event callback
    init(300, 300)
    i = 0;
    while True:
        print("running within while loop {}".format(i))
        glutMainLoopEvent()
        ret = opencv_loop()
        if ret == 27:
            break

def keyboard(key, x, y):
    if key == chr(27):
        print("exitting")
        sys.exit()

def init(width, height):
    """ initialize """
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glEnable(GL_DEPTH_TEST) # enable shading

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    ##set perspective
    gluPerspective(45.0, float(width)/float(height), 0.1, 100.0)

def display():
    """ display """
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    ##set camera
    gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    ##draw a teapot
    glColor3f(1.0, 0.0, 0.0)
    glutWireTeapot(1.0)   # wireframe
    glFlush()  # enforce OpenGL command

def reshape(width, height):
    """callback function resize window"""
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(width)/float(height), 0.1, 100.0)

if __name__ == "__main__":
    main()
    # main2() try with glutIdelFunc() version


#################################################################333

