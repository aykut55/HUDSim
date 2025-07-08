#ifndef MYHUDSIM_H
#define MYHUDSIM_H

#include "HudSimExt.h"
#include <iostream>

class MyHudSim : public CHudSimExt
{
public:
    MyHudSim(int argc, char** argv);

protected:
    void OnInitialize() override;
    void Draw() override;
    void OnKeyboard(unsigned char key, int x, int y) override;
    void OnSpecial(int key, int x, int y) override;
    void OnTimer(int value) override;
    void OnUpdate(float deltaTime) override;

    double rollDeg;
    double pitchDeg;
    double yawDeg;

private:
    void DrawDemo(int choice);

    void DrawPlus(float centerX, float centerY, float size);

    // ortadaki “w” şeklindeki marker
    void DrawCentralWMarker(float centerX = 0.0f, float centerY = 0.0f, float size = 0.2f);   

    void DrawPitchLadder(float centerX, float centerY, float size, double rollDeg, double pitchDeg);
};

#endif // MYHUDSIM_H
