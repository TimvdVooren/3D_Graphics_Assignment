#include "GL/freeglut.h"
#include "World.h"

static World* world;

int main(int argc, char * argv[])
{
	glEnable(GL_DEPTH_TEST);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	glutInitWindowSize(desktop.right, desktop.bottom);

	glutCreateWindow("Tim van der Vooren");

	world = new World(desktop.right, desktop.bottom);

	glutIdleFunc([](){ World::getWorld()->idle(); });
	glutDisplayFunc([]() { World::getWorld()->display(); });
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	glutPassiveMotionFunc([](int mouseX, int mouseY) {World::getWorld()->mousePassiveMotion(mouseX, mouseY); });
	glutMouseFunc([](int button, int state, int x, int y) {World::getWorld()->mouseClick(button, state, x, y); });

	glutMainLoop();
}
