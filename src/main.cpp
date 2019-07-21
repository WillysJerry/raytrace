#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glut.h>

#include <math3d.h>
#include <transform.h>
#include <color.h>
#include <light.h>
#include <material.h>
#include <entity.h>

#include "camera/camera.h"
#include "light_model/light_model.h"

using namespace raytracer;

int activeCamera = 0;

std::vector<Entity*> scene;
std::vector<Light*> lights;
std::vector<Camera> cameras;

//Camera camera( 320, 320, 0.02 );
LightModel* lightModel;

void update(void) {
    glutPostRedisplay();
}
void keyPressed(unsigned char key, int x, int y) {
    vec3f d;
    float rot = 0.52359;

    Camera& cam = cameras[activeCamera];
    std::cout << "Camera position: " << cam.transform.getPosition() <<
        ". Camera forward: " << cam.transform.getForwardVector() <<
        ". Camera up: " << cam.transform.getUpVector() << std::endl;

    switch(key) {
        case 'q':
            cam.transform.axisRotate(-rot, Axis::Y);
            break;
        case 'e':
            cam.transform.axisRotate(rot, Axis::Y);
            break;
        case 'w':
            cam.transform.translate(cam.transform.getForwardVector());
            break;
        case 'a':
            cam.transform.translate(-cam.transform.getRightVector());
            break;
        case 's':
            cam.transform.translate(-cam.transform.getForwardVector());
            break;
        case 'd':
            cam.transform.translate(cam.transform.getRightVector());
            break;
        case 'z':
            cam.transform.translate(cam.transform.getUpVector());
            break;
        case 'x':
            cam.transform.translate(-cam.transform.getUpVector());
            break;
        case 'c':
            activeCamera = (activeCamera + 1) % cameras.size();
            break;
    }

    glutPostRedisplay();
}

void renderScene(void) {
    static int a = 0;

    PixBuf* pixBuf;
    cameras[activeCamera].render(*lightModel, scene, lights, pixBuf);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, 320, 0, 320, -1, 1);

    glBegin(GL_POINTS);

    for(int i = 0; i < pixBuf->getWidth(); i++) {
        for(int j = 0; j < pixBuf->getHeight(); j++) {

            Color c = (*pixBuf)(i, j);
            glColor3f(c.r, c.g, c.b);
            glVertex2i(i, j);
        }
    }
    glEnd();

    glutSwapBuffers();

    delete pixBuf;
}

void toPPM() {
    PixBuf* pixBuf;
    cameras[activeCamera].render(*lightModel, scene, lights, pixBuf);

    std::ofstream out("out.ppm");
    out << "P3\n" << pixBuf->getWidth() << ' ' << pixBuf->getHeight() << ' ' << "255\n";

    Color c;
    for(int i = 0; i < pixBuf->getHeight(); i++) {
        for(int j = 0; j < pixBuf->getWidth(); j++) {
            c = (*pixBuf)(j, i);
            out << (int)(c.r * (float)255) << ' '
                << (int)(c.g * (float)255) << ' '
                << (int)(c.b * (float)255) << '\n';
        }
    }
}

int main(int argc, char *argv[]) {

    //Camera camera( 320, 320, 0.02 );
    cameras.push_back(Camera(320, 320, 0.001, vec3f(0,1,-4.0)));
    cameras[0].transform.axisRotate(3.14, Axis::Y);
    cameras.push_back(Camera(320, 320, 0.001, vec3f(-7,0,-5)));
    cameras[1].transform.axisRotate(1.571, Axis::Y);
    cameras.push_back(Camera(320, 320, 0.001, vec3f(0,10,-8)));
    cameras[2].transform.axisRotate(1.571, Axis::X);

    Material red(Color(1, 0, 0),
                 Color(1, 1, 1),
                 20.0);
    Material green(Color(0, 1, 0),
                   Color(1, 1, 1),
                   10.0);
    Material blue(Color(0, 0, 1),
                  Color(1, 1, 1),
                  50.0);
    Material white(Color(1, 1, 1),
                   Color(1, 1, 1),
                   100);

    Material gray(Color(0.4, 0.4, 0.4),
                  Color(1, 1, 1),
                  200);

    Material orange(Color(0.7, 0.4, 0.0),
                    Color(1, 1, 1),
                    500);

    scene.push_back(new Sphere(vec3f(-4.0, 0.0, -8.0),
                               1.0f,
                               red));

    scene.push_back(new Sphere(vec3f(-0.0, 3.0, -8.0),
                               1.0f,
                               green));

    scene.push_back(new Sphere(vec3f(4.0, 0.0, -8.0),
                               1.0f,
                               blue));

    scene.push_back(new Sphere(vec3f(0.0, -3.0, -8.0),
                               1.0f,
                               white));

    scene.push_back(new Plane(vec3f(0.0, -9.0, 0.0), gray));

    scene.push_back(new Sphere(vec3f(-2.0, 0.0, -30.0), 10.0, orange));

    lights.push_back(new Light(vec3f(-1.0, 10.0, -8.0), Color(1.0, 1.0, 1.0), 1));
    //lights.push_back(new Light(vec3f(2.0, 3.0, -5.0), Color(1.0, 0.2, 0.3)));
    //

    lightModel = new PhongModel();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Raytracer");

    glutDisplayFunc(renderScene);
    glutIdleFunc(update);
    glutKeyboardFunc(keyPressed);

    glutMainLoop();

    return 1;
}
