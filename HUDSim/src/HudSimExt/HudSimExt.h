#ifndef HudSimExtH
#define HudSimExtH

#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <vector>
#include <memory>

#include <GL/freeglut.h>

#include "Line2D.h"
#include "Line2DCentered.h"
#include "Line2DStartLength.h"

#include "Line2DHorizontal.h"
#include "Line2DHorizontalCentered.h"
#include "Line2DHorizontalStartLength.h"

#include "Line2DVertical.h"
#include "Line2DVerticalCentered.h"
#include "Line2DVerticalStartLength.h"

#include "Line3D.h"
#include "Line3DCentered.h"
#include "Line3DStartLength.h"

#include "Line3DHorizontal.h"
#include "Line3DHorizontalCentered.h"
#include "Line3DHorizontalStartLength.h"

#include "Line3DVertical.h"
#include "Line3DVerticalCentered.h"
#include "Line3DVerticalStartLength.h"

class CHudSimExt
{
public:
    virtual ~CHudSimExt();
             CHudSimExt(int argc, char** argv);

    void InitWindow(int width, int height, const std::string& title);
    void Run();

protected:
    virtual void Draw();                                        // Tüm çizimler burada olacak
    virtual void OnInitialize();                   // Başlangıçta 1 kere çağrılır
    virtual void OnDisplay();                      // glutDisplayFunc
    virtual void OnReshape(int w, int h);          // glutReshapeFunc
    virtual void OnKeyboard(unsigned char key, int x, int y);      // glutKeyboardFunc
    virtual void OnSpecial(int key, int x, int y);                 // glutSpecialFunc
    virtual void OnTimer(int value);                // glutTimerFunc
    virtual void OnMouse(int button, int state, int x, int y);    // glutMouseFunc
    virtual void OnMouseMotion(int x, int y);       // glutMotionFunc
    virtual void OnMousePassiveMotion(int x, int y); // glutPassiveMotionFunc
    virtual void OnIdle();                           // glutIdleFunc
    virtual void OnClose();                          // glutCloseFunc
    virtual void OnUpdate(float deltaTime);             // sss
    int m_width = 800;   // Varsayılan genişlik
    int m_height = 600;  // Varsayılan yükseklik

private:
    static void DisplayCallback();
    static void ReshapeCallback(int w, int h);
    static void KeyboardCallback(unsigned char key, int x, int y);
    static void SpecialCallback(int key, int x, int y);
    static void TimerCallback(int value);
    static void MouseCallback(int button, int state, int x, int y);
    static void MouseMotionCallback(int x, int y);
    static void MousePassiveMotionCallback(int x, int y);
    static void IdleCallback();
    static void CloseCallback();

    static CHudSimExt* s_instance;
};

#endif
