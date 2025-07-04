#ifndef HudSimH
#define HudSimH

#include <stdio.h>
#include <string>
#include <chrono>
#include <vector>
#include <memory>

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

#include <GL/freeglut.h>

class CHudSim
{
public:
    virtual ~CHudSim();
             CHudSim();
             void Draw();
             void Update(float dt); // simülasyon update

             // ana ufuk çizgisi
             void DrawHorizonLine(float centerX, float centerY, float lineLength);

             // pitch ladder (0, ±5, ±10 çizgileri ve L kolları)
             void DrawPitchLadder_(float centerX, float centerY, float size);
             void DrawPitchLadder__(float centerX, float centerY, float size, double pitchDeg);

             float CalculateYOffset(double pitchDeg, double maxPitch, float size);
             void DrawPitchLadder_ZeroLine(float centerX, float centerY, float size, double pitchDeg);
             void DrawPitchLadder_PlusUp1Line(float centerX, float centerY, float size, double pitchDeg);
             void DrawPitchLadder_Line(float centerX, float centerY, float size, double pitchDeg, int pitchValue);
             void DrawPitchLadder(float centerX, float centerY, float size, double rollDeg, double pitchDeg);

             void DrawPitchText(float x, float y, int pitchValue);
             void DrawRollText(float x, float y, int rollValue);
             void DrawYawText(float x, float y, int yawValue);

             // ortadaki “w” şeklindeki marker
             void DrawCentralWMarker(float centerX = 0.0f, float centerY = 0.0f, float size = 0.2f);

             void DrawSideVerticalLines(float centerX, float centerY, float size, float xOffset);

             void DrawRightSideIndicators(float centerX, float centerY, float size, float xOffset);

             void DrawRightSideCaretIndicator(float centerX, float centerY, float size, float xOffset, float caretY, float yOffset); 
             
             void DrawSpeedIndicator(float x, float y, float width, float height);
             void DrawSpeedText(float x, float y, int speedValue);

             void DrawAltIndicatorBox(float x, float y, float width, float height);
             void DrawAltText(float x, float y, int altValue);

             void DrawTargetBox(float centerX, float centerY, float size, int value);

             void DrawCompass_(float centerX, float centerY, float width);
             void DrawCompass1(float centerX, float centerY, float width, double yawDeg);

             void DrawCompass(float centerX, float centerY, float width, double yawDeg);
             void DrawCompass_Line(float centerX, float centerY, float width, double yawDeg, int positionIndex, bool isMajorLine);
             void DrawCompass_ZeroLine(float centerX, float centerY, float width, double yawDeg);

             void SetWindowSize(int width, int height);
             void SetSpeedValue(int speed);

             // Getter ve Setterlar
             void   SetRollCmd(double val);
             double GetRollCmd(void) const;

             void   SetPitchCmd(double val);
             double GetPitchCmd(void) const;

             void   SetYawCmd(double val);
             double GetYawCmd(void) const;

             void   SetThrottleCmd(double val);
             double GetThrottleCmd(void) const;

             void   SetHeadingDeg(double val);
             double GetHeadingDeg(void) const;

             void   SetRollDeg(double val);
             double GetRollDeg(void) const;

             void   SetPitchDeg(double val);
             double GetPitchDeg(void) const;

             void   SetYawDeg(double val);
             double GetYawDeg(void) const;

             void   SetThrottle(double val);
             double GetThrottle(void) const;

             void   SetLatDeg(double val);
             double GetLatDeg(void) const;

             void   SetLonDeg(double val);
             double GetLonDeg(void) const;

             void   SetAltMeter(double val);
             double GetAltMeter(void) const;

             void   SetSpeedMPS(double val);
             double GetSpeedMPS(void) const;

             void   SetAltFeet(double val);
             double GetAltFeet(void) const;

             void   SetSpeedMach(double val);
             double GetSpeedMach(void) const;

             void   SetAngleOfAttackDeg(double val);
             double GetAngleOfAttackDeg(void) const;

             void   SetAngleOfSideSlipDeg(double val);
             double GetAngleOfSideSlipDeg(void) const;

             void   SetFlightPathAngleDeg(double val);
             double GetFlightPathAngleDeg(void) const;

             void   SetGFactor(double val);
             double GetGFactor(void) const;

             // Increments ve Decrements
             void IncreaseRollCmd(double step);
             void DecreaseRollCmd(double step);

             void IncreasePitchCmd(double step);
             void DecreasePitchCmd(double step);

             void IncreaseYawCmd(double step);
             void DecreaseYawCmd(double step);

             void IncreaseThrottleCmd(double step);
             void DecreaseThrottleCmd(double step);

             void IncreaseRoll(double step);
             void DecreaseRoll(double step);

             void IncreasePitch(double step);
             void DecreasePitch(double step);

             void IncreaseYaw(double step);
             void DecreaseYaw(double step);

             void IncreaseThrottle(double step);
             void DecreaseThrottle(double step);

protected:

private:
    void DrawPlus(float centerX, float centerY, float size);
    void DrawCenteredText(float x, float y, const char* text);

    double rollCmd = 0.0;               // -1 : ToLeft, +1 : ToRight
    double pitchCmd = 0.0;              // -1 : ToUp,   +1 : ToDown
    double yawCmd = 0.0;                // -1 : ToLeft, +1 : ToRight
    double throttleCmd = 0.0;           //  0 : Min,    +1 : Max
    double headingDeg = 0.0;            // ...
    double rollDeg = 0.0;               // ...
    double pitchDeg = 0.0;              // ...
    double yawDeg = 0.0;                // ...
    double throttle = 0.0;              // ...
    double latDeg = 0.0;                // ...
    double lonDeg = 0.0;                // ...
    double altMeter = 0.0;              // ...
    double altFeet = 0.0;               // ...
    double speedMPS = 0.0;              // ...
    double speedMach = 0.0;             // ...
    double angleOfAttackDeg = 0.0;      // alphaDeg
    double angleOfSideSlipDeg = 0.0;    // betaDeg
    double flightPathAngleDeg = 0.0;    // gamaDeg
    double gFactor = 0.0;               // Vertical Lod Factor (g)

    // HUD dataları
    float speed;
    float altitude;
    float heading;

    int windowWidth = 800;
    int windowHeight = 600;
    int speedValue = 50;
};

#endif
