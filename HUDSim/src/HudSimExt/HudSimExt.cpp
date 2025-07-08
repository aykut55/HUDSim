#include "HudSimExt.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/freeglut.h>

#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")

CHudSimExt* CHudSimExt::s_instance = nullptr;

CHudSimExt::CHudSimExt(int argc, char** argv)
    : m_width(800), m_height(600)
{
    if (!s_instance)
        s_instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
}

CHudSimExt::~CHudSimExt()
{
    if (s_instance == this)
        s_instance = nullptr;
}

void CHudSimExt::InitWindow(int width, int height, const std::string& title)
{
    m_width = width;
    m_height = height;

    glutInitWindowSize(width, height);
    glutCreateWindow(title.c_str());

    OnInitialize();

    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutSpecialFunc(SpecialCallback);
    glutTimerFunc(16, TimerCallback, 0);  // ~60 FPS
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);
    glutPassiveMotionFunc(MousePassiveMotionCallback);
    glutIdleFunc(IdleCallback);
    glutCloseFunc(CloseCallback);
}

void CHudSimExt::Run()
{
    glutMainLoop();
}

void CHudSimExt::DisplayCallback()
{
    if (s_instance)
        s_instance->OnDisplay();
}

void CHudSimExt::ReshapeCallback(int w, int h)
{
    if (s_instance)
        s_instance->OnReshape(w, h);
}

void CHudSimExt::KeyboardCallback(unsigned char key, int x, int y)
{
    if (s_instance)
        s_instance->OnKeyboard(key, x, y);
}

void CHudSimExt::SpecialCallback(int key, int x, int y)
{
    if (s_instance)
        s_instance->OnSpecial(key, x, y);
}

void CHudSimExt::TimerCallback(int value)
{
    if (s_instance)
    {
        float deltaTime = 0.016f; // 16 ms ~ 60 FPS, basit sabit değer
        s_instance->OnUpdate(deltaTime);
        s_instance->OnTimer(value);
        glutTimerFunc(16, TimerCallback, 0);
    }
}

void CHudSimExt::MouseCallback(int button, int state, int x, int y)
{
    if (s_instance)
        s_instance->OnMouse(button, state, x, y);
}

void CHudSimExt::MouseMotionCallback(int x, int y)
{
    if (s_instance)
        s_instance->OnMouseMotion(x, y);
}

void CHudSimExt::MousePassiveMotionCallback(int x, int y)
{
    if (s_instance)
        s_instance->OnMousePassiveMotion(x, y);
}

void CHudSimExt::IdleCallback()
{
    if (s_instance)
        s_instance->OnIdle();
}

void CHudSimExt::CloseCallback()
{
    if (s_instance)
        s_instance->OnClose();
}

void CHudSimExt::Draw()
{
    // Varsayılan boş, override edilir
}

void CHudSimExt::OnInitialize()
{
    // Burada OpenGL ayarları yapılabilir
}

void CHudSimExt::OnDisplay()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    Draw();

    glutSwapBuffers();
}

void CHudSimExt::OnReshape(int w, int h)
{
    bool useCenterAsOrigin = false;

    if (useCenterAsOrigin)
    {
        m_width = w;
        m_height = h;

        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, h, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else
    {
        m_width = w;
        m_height = h;

        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Sol üst köşe orijin, Y ekseni aşağı doğru artar
        gluOrtho2D(0, w, h, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
}

void CHudSimExt::OnKeyboard(unsigned char key, int x, int y)
{
    // Örneğin ESC ile çıkış:
    if (key == 27) // ESC
        exit(0);
}

void CHudSimExt::OnSpecial(int key, int x, int y)
{
    // Özel tuşlar burada işlenebilir
}

void CHudSimExt::OnTimer(int value)
{
    glutPostRedisplay(); // Ekranı sürekli yenile
}

void CHudSimExt::OnMouse(int button, int state, int x, int y)
{
    // Mouse butonları
}

void CHudSimExt::OnMouseMotion(int x, int y)
{
    // Mouse hareketi, buton basılıyken
}

void CHudSimExt::OnMousePassiveMotion(int x, int y)
{
    // Mouse hareketi, butonsuz
}

void CHudSimExt::OnIdle()
{
    // Boşta sürekli yapılacak işler
}

void CHudSimExt::OnClose()
{
    // Pencere kapanırken yapılacaklar
}

void CHudSimExt::OnUpdate(float deltaTime)
{
    // Varsayılan boş
}