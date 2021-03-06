/**
 * Responsibilities:
 *   - Boots up sample.scene into a Renderer and Scene instance
 *   - Creates a GLUT window with an orthographic projection to render the
 *     image into
 */
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <ctime>
#include <string>

#include "Renderer.h"
#include "Scene.h"
#include "SceneFile.h"


Scene scene;
Renderer renderer(scene);


void handleDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    renderer.gl();
    glFlush();
}


void handleReshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Center the statically-sized canvas within the window. Essentially we're
    // computing the correct margin between the sides of the window and when
    // (0,0) to (canvasWidth, canvasHeight) is centered.
    float centeringMarginX = (float) (w - renderer.mWidth) / 2.0f;
    float centeringMarginY = (float) (h - renderer.mHeight) / 2.0f;
    gluOrtho2D(
        -centeringMarginX,
        w - centeringMarginX,
        -centeringMarginY,
        h - centeringMarginY
    );

    glMatrixMode(GL_MODELVIEW);
}


void handleKeyboard(unsigned char key, int _x, int _y) {
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
}


int main(int argc, char **argv) {
    srand(time(NULL));
    std::string file = "./sample.scene";
    if (argc == 2) {
        file = std::string(argv[1]);
    }
    loadSceneFile(renderer, scene, file);
    renderer.printIntro(file);
    renderer.render();

    glutInit(&argc, argv);
    glutInitWindowSize(renderer.mWidth, renderer.mHeight);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Raytracer Output");

    glutDisplayFunc(handleDisplay);
    glutKeyboardFunc(handleKeyboard);
    glutReshapeFunc(handleReshape);

    glutMainLoop();

    return 0;
}
