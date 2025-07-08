#include <iostream>
#include "HudSim.h"
CHudSim hud;

using Clock = std::chrono::high_resolution_clock;
auto lastTime = Clock::now();
std::chrono::duration<float> delta;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); // her karede matrisi resetle

    hud.Draw();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // basit 2D koordinat
    glMatrixMode(GL_MODELVIEW);
}

void reshape_(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // pencere merkezli orantılı ortho
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // CHudSim örneğin varsa pencere boyutunu bildir
    hud.SetWindowSize(w, h);
}

void timer(int value)
{
    auto now = Clock::now();
    delta = now - lastTime;
    lastTime = now;

    //hud.Update(delta.count());

    glutPostRedisplay();           // display fonksiyonunu tetikle
    glutTimerFunc(8, timer, 0); // 16 = ~60 FPS
}

void keyboard(unsigned char key, int x, int y)
{
    const double yawStep = 1.0; // her tuş basışında 1 derece değişim
    const double headingStep = 1.0; // her tuş basışında 1 derece değişim

    switch (key)
    {
    case 27:  // ESC
        exit(0);
        break;

    case ' ': // Space tuşu
        hud.SetPitchDeg(0.0);
        hud.SetRollDeg(0.0);
        hud.SetYawDeg(0.0);
        hud.SetHeadingDeg(0.0);
        hud.SetThrottle(0.0);
        hud.Update(delta.count());
        printf("Resetlendi\n");
        break;
    case 'a':
        hud.IncreaseYaw(yawStep);  // a ile yaw artır
        break;
    case 'd':
        hud.DecreaseYaw(yawStep);  // d ile yaw azalt
        break;
    case 'q':
        hud.IncreaseHeading(headingStep);  // q ile heading artır
        break;
    case 'e':
        hud.DecreaseHeading(headingStep);  // e ile heading azalt
        break;
    case 'w':
        // W tuşu basıldı
        printf("W basıldı\n");
        break;
    case 's':
        printf("S basıldı\n");
        break;
        // diğer tuşlar...
    default:
        printf("Basılan tuş: %c\n", key);
        break;
    }
}

void special(int key, int x, int y)
{
    const double pitchStep = 1.0; // her tuş basışında 1 derece değişim
    const double rollStep = 1.0; // her tuş basışında 1 derece değişim
    const double yawStep = 1.0; // her tuş basışında 1 derece değişim
    const double throttleStep = 1.0; // her tuş basışında 1 derece değişim

    switch (key)
    {
    case GLUT_KEY_UP:
        hud.IncreasePitch(pitchStep); // aşağı ok pitch artırır (burun yukarı)
        break;
    case GLUT_KEY_DOWN:
        hud.DecreasePitch(pitchStep); // yukarı ok pitch azaltır (burun aşağı)
        break;
    case GLUT_KEY_LEFT:
        hud.DecreaseRoll(rollStep);  // Sol ok: roll sola
        break;
    case GLUT_KEY_RIGHT:
        hud.IncreaseRoll(rollStep);  // Sağ ok: roll sağa
        break;
    case GLUT_KEY_PAGE_UP:
        hud.IncreaseThrottle(throttleStep);  // Page Up ile Throttle artır
        break;
    case GLUT_KEY_PAGE_DOWN:
        hud.DecreaseThrottle(throttleStep);  // Page Down ile Throttle azalt
        break;
    default:
        printf("Özel tuş basıldı: %d\n", key);
        break;
    }

    hud.Update(delta.count());
}

void initializeGL(int argc, char** argv) 
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    glutCreateWindow("HUDSim");

    glutDisplayFunc(display);       // çizim fonksiyonu
    glutReshapeFunc(reshape);       // pencere yeniden boyutlanınca   

    glutKeyboardFunc(keyboard);     // normal tuşlar
    glutSpecialFunc(special);       // ok tuşları ve özel tuşlar

    glutTimerFunc(0, timer, 0);     // sürekli timer başlat

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // arka plan siyah
}

int main(int argc, char** argv)
{
    initializeGL(argc, argv);

    glutMainLoop();                 // olay döngüsüne gir

    return 0;
}