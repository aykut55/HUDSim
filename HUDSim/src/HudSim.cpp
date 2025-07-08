#include "HudSim.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/freeglut.h>

#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")

CHudSim::~CHudSim()
{

}

CHudSim::CHudSim()
{

}

void CHudSim::Draw()
{
    DrawPlus(0.0f, 0.05f, 0.04f);

    // ortadaki w marker
    DrawCentralWMarker(0.02f, 0.0f, 0.2f);
/*
    // horizon ana çizgisi
    //DrawHorizonLine(0.0f, 0.0f, 1.1f);

    // Pitch ladder güncel pitchDeg ile çizilir
    //DrawPitchLadder(0.0f, 0.0f, 1.0f, rollDeg, pitchDeg);
*/
    float posX = -0.80f;
    float posY =  0.05f;
    float incrementY = 0.15f;
    DrawHeadingText(posX, posY - incrementY * 0.f, headingDeg);
    DrawRollText(posX, posY - incrementY * 1.f, rollDeg);
    DrawPitchText(posX, posY - incrementY * 2.f, pitchDeg);
    DrawYawText(posX, posY - incrementY * 3.f, yawDeg);
    DrawThrottleText(posX, posY - incrementY * 4.f, throttle);

    posX = 0.65f;
    posY = - 0.10f;
    DrawAngleOfAttackText(posX, posY - incrementY * 0.f, angleOfAttackDeg);
    DrawAngleOfSideSlipText(posX, posY - incrementY * 1.f, angleOfSideSlipDeg);
    DrawFlightPathAngleText(posX, posY - incrementY * 2.f, flightPathAngleDeg);
    DrawanGFactorText(posX, posY - incrementY * 3.f, gFactor);

#if 0
    calisiyor
    float color1[3] = { 1.0f, 1.0f, 1.0f };
    DrawEmptyBox(0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.1f, color1);

    float color2[3] = { 1.0f, 0.0f, 0.0f };
    DrawEmptyTriangle(0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.1f, color2);

    float color3[3] = { 1.0f, 0.0f, 0.0f };
    DrawEmptyCircle(0.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.1f, color2);
#endif
    DrawPitchLadderDeepSeek(0.0f, 0.0f, 0.4f, rollDeg, pitchDeg, 0.25f, 0.25f);

    //DrawYawCompassDeepSeek(0.0f, 0.7f, 0.1f, yawDeg, 0.0f, 0.0f);
    DrawHorizontalCompassDeepSeek(0.0f, 0.7f, 0.1f, headingDeg + yawDeg, 0.0f, 0.0f);

    DrawRollCompassDeepSeek(0.0f, -0.7f, 0.1f, rollDeg, 0.0f, 0.0f);

    DrawVerticaLinesDeepSeek(0.0f, 0.0f, 1.2f, 0.0f, 0.0f);
    //DrawHorizonLinesDeepSeek(0.0f, 0.0f, 1.2f, 0.0f, 0.0f);

    //DrawThrottleCompassDeepSeek(0.85f, -0.75f, 0.1f, throttle, 0.0f, 0.0f);       // Bu kullanilacak
    ////DrawThrottleCompassDeepSeek1(0.85f, -0.75f, 0.1f, throttle, 0.0f, 0.0f);
    ////DrawThrottleCompassDeepSeek2(0.85f, -0.75f, 0.1f, throttle, 0.0f, 0.0f);



    //DrawSideVerticalLines(0.0f, 0.0f, 1.6f, 0.6f);

    DrawRightSideIndicators(0.0f, 0.0f, 0.9f, 0.6f);
    DrawRightSideCaretIndicator(0.0f, 0.0f, 0.9f, 0.58f, -0.65f, 0.1f);

    int speedValue = 500;
    DrawSpeedIndicator(-0.8f, 0.5f, 0.1f, 0.05f);
    DrawSpeedText(-0.8f, 0.5f, speedValue);

    // Sağ tarafa kutu ve yazı çizmek için örnek koordinatlar
    float x = 0.80f;   // sağ kenar civarı
    float y = 0.5f;
    float width = 0.1f;
    float height = 0.05f;

    int altValue = 150;
    DrawAltIndicatorBox(x, y, width, height);
    DrawAltText(x-0.02f, y, altValue);

    DrawTargetBox(0.5f, 0.0f, 0.1f, 142);

    //DrawCompass(0.0f, 0.7f, 0.6f, yawDeg);
    /**/
    // merkez metni
    //DrawCenteredText(0.0f, 0.0f, "CENTER");


    auto p2DLine = std::make_unique<CLine2D>();
    auto pLine2DCentered = std::make_unique<CLine2DCentered>();
    auto pLine2DStartLength = std::make_unique<CLine2DStartLength>();

    auto pLine2DHorizontal = std::make_unique<CLine2DHorizontal>();
    auto pLine2DHorizontalCentered = std::make_unique<CLine2DHorizontalCentered>();
    auto pLine2DHorizontalStartLength = std::make_unique<CLine2DHorizontalStartLength>();
         
    auto pLine2DVertical = std::make_unique<CLine2DVertical>();
    auto pLine2DVerticalCentered = std::make_unique<CLine2DVerticalCentered>();
    auto pLine2DVerticalStartLength = std::make_unique<CLine2DVerticalStartLength>();

    auto centered2DLine = std::make_unique<CLine2DCentered>();
    centered2DLine->SetCenterX(0.0f);
    centered2DLine->SetCenterY(0.0f);
    centered2DLine->SetLength(0.8f);
    centered2DLine->SetRotationAngle(0.0f);
    centered2DLine->SetColor(0.0f, 0.0f, 1.0f); // mavi
    //centered2DLine->Draw();

    auto startLength2DLine = std::make_unique<CLine2DStartLength>();    
    startLength2DLine->SetStartX(-0.5f);
    startLength2DLine->SetStartY(-0.5f);
    startLength2DLine->SetLength(1.2f);
    startLength2DLine->SetRotationAngle(30.0f);
    startLength2DLine->SetColor(1.0f, 1.0f, 0.0f); // sarı
    //startLength2DLine->Draw();
}

void CHudSim::Update(float deltaTime)
{
/*
    // Pitch değerini otomatik artırıp 20'ye kadar çıkart, sonra tersine döndür
    static bool increasing = true;

    if (increasing)
    {
        pitchDeg += 10.0f * deltaTime;  // 10 derece/saniye hızla artış
        if (pitchDeg >= 20.0f)
        {
            pitchDeg = 20.0f;
            increasing = false;
        }
    }
    else
    {
        pitchDeg -= 10.0f * deltaTime;  // azalış
        if (pitchDeg <= -20.0f)
        {
            pitchDeg = -20.0f;
            increasing = true;
        }
    }

    glutPostRedisplay();
*/

    glutPostRedisplay();
}


void CHudSim::DrawHorizonLine(float centerX, float centerY, float lineLength)
{
    float halfLength = lineLength / 2.0f;

    glColor3f(0.0f, 1.0f, 0.0f); // yeşil
    glBegin(GL_LINES);
    glVertex2f(centerX - halfLength, centerY);
    glVertex2f(centerX + halfLength, centerY);
    glEnd();
}

// pitchDeg: mevcut pitch değeri (derece cinsinden)
// centerX, centerY: orijin noktası (örnek 0,0)
// size: ladder boyutu (örneğin 1.6f)

void CHudSim::DrawPitchLadder__(float centerX, float centerY, float size, double pitchDeg)
{
    // pitchDeg değerine göre centerY'yi kaydırmak için bir çarpan belirleyelim
    // Örneğin, pitchDeg maksimum ±20 derece aralığında, bunu size'ye orantılayalım
    const double maxPitch = 20.0;
    float yOffset = static_cast<float>((pitchDeg / maxPitch) * size);

    // Yeni centerY, pitchDeg'e göre kaydırılmış
    float shiftedCenterY = centerY + yOffset;

    float centerGap = size * 0.2f;
    float lineHalfLen = centerGap + size * 0.15f;
    float lArm = size * 0.03f;
    float textOffset = size * 0.05f;

    for (int pitch = -10; pitch <= 10; pitch += 5)
    {
        // pitch değerine göre y pozisyonu (kaydırılmış centerY baz alınarak)
        float y = shiftedCenterY + (pitch / 20.0f) * size;

        glColor3f(0.0f, 1.0f, 0.0f);

        if (pitch == 0)
        {
            glDisable(GL_LINE_STIPPLE);
        }
        else
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        // yatay çizgiler
        glBegin(GL_LINES);
        glVertex2f(centerX - centerGap, y);
        glVertex2f(centerX - lineHalfLen, y);

        glVertex2f(centerX + centerGap, y);
        glVertex2f(centerX + lineHalfLen, y);
        glEnd();

        glDisable(GL_LINE_STIPPLE);

        // L bacakları
        glBegin(GL_LINES);
        if (pitch >= 0)
        {
            glVertex2f(centerX - lineHalfLen, y);
            glVertex2f(centerX - lineHalfLen, y - lArm);

            glVertex2f(centerX + lineHalfLen, y);
            glVertex2f(centerX + lineHalfLen, y - lArm);
        }
        else
        {
            glVertex2f(centerX - lineHalfLen, y);
            glVertex2f(centerX - lineHalfLen, y + lArm);

            glVertex2f(centerX + lineHalfLen, y);
            glVertex2f(centerX + lineHalfLen, y + lArm);
        }
        glEnd();

        // text
        char txt[8];
        sprintf(txt, "%d", pitch);
        glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        glRasterPos2f(centerX + lineHalfLen + textOffset - 0.02f, y - 0.01f);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}


float CHudSim::CalculateYOffset(double pitchDeg, double maxPitch, float size)
{
    // pitchDeg, maxPitch aralığında normalize edilir ve size ile çarpılır
    return static_cast<float>((pitchDeg / maxPitch) * size);
}

void CHudSim::DrawPitchLadder_ZeroLine(float centerX, float centerY, float size, double pitchDeg)
{
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset;

    float centerGap = size * 0.2f;
    float lineHalfLen = centerGap + size * 0.15f;
    float lArm = size * 0.03f;
    float textOffset = size * 0.05f;

    glColor3f(0.0f, 1.0f, 0.0f);
    glDisable(GL_LINE_STIPPLE); // solid çizgi

    glBegin(GL_LINES);
    glVertex2f(centerX - centerGap, y);
    glVertex2f(centerX - lineHalfLen, y);

    glVertex2f(centerX + centerGap, y);
    glVertex2f(centerX + lineHalfLen, y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(centerX - lineHalfLen, y);
    glVertex2f(centerX - lineHalfLen, y - lArm);

    glVertex2f(centerX + lineHalfLen, y);
    glVertex2f(centerX + lineHalfLen, y - lArm);
    glEnd();

    char txt[8];
    sprintf(txt, "0");
    glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

    glRasterPos2f(centerX + lineHalfLen + textOffset - 0.02f, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}

void CHudSim::DrawPitchLadder_Line(float centerX, float centerY, float size, double pitchDeg, int pitchValue)
{
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset + (static_cast<float>(pitchValue) / 20.0f) * size;

    float centerGap = size * 0.2f;
    float lineHalfLen = centerGap + size * 0.15f;
    float lArm = size * 0.03f;
    float textOffset = size * 0.05f;

    glColor3f(0.0f, 1.0f, 0.0f);

    // 0 dışındaki çizgiler kesikli, 0 ise solid olabilir
    if (pitchValue != 0)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    // Yatay çizgiler
    glBegin(GL_LINES);
    glVertex2f(centerX - centerGap, y);
    glVertex2f(centerX - lineHalfLen, y);

    glVertex2f(centerX + centerGap, y);
    glVertex2f(centerX + lineHalfLen, y);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    // L bacakları
    glBegin(GL_LINES);
    if (pitchValue >= 0)
    {
        glVertex2f(centerX - lineHalfLen, y);
        glVertex2f(centerX - lineHalfLen, y - lArm);

        glVertex2f(centerX + lineHalfLen, y);
        glVertex2f(centerX + lineHalfLen, y - lArm);
    }
    else
    {
        glVertex2f(centerX - lineHalfLen, y);
        glVertex2f(centerX - lineHalfLen, y + lArm);

        glVertex2f(centerX + lineHalfLen, y);
        glVertex2f(centerX + lineHalfLen, y + lArm);
    }
    glEnd();

    // Metin yazısı
    char txt[8];
    if (pitchValue > 0)
        sprintf(txt, "+%d", pitchValue);
    else
        sprintf(txt, "%d", pitchValue);

    glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

    glRasterPos2f(centerX + lineHalfLen + textOffset - 0.02f, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}


void CHudSim::DrawPitchLadder_PlusUp1Line(float centerX, float centerY, float size, double pitchDeg)
{
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset + (5.0f / 20.0f) * size;

    float centerGap = size * 0.2f;
    float lineHalfLen = centerGap + size * 0.15f;
    float lArm = size * 0.03f;
    float textOffset = size * 0.05f;

    glColor3f(0.0f, 1.0f, 0.0f);

    // Kesikli çizgi
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);

    glBegin(GL_LINES);
    glVertex2f(centerX - centerGap, y);
    glVertex2f(centerX - lineHalfLen, y);

    glVertex2f(centerX + centerGap, y);
    glVertex2f(centerX + lineHalfLen, y);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    // L bacakları (pozitif pitch, aşağı doğru)
    glBegin(GL_LINES);
    glVertex2f(centerX - lineHalfLen, y);
    glVertex2f(centerX - lineHalfLen, y - lArm);

    glVertex2f(centerX + lineHalfLen, y);
    glVertex2f(centerX + lineHalfLen, y - lArm);
    glEnd();

    // Metin +5 yazısı
    char txt[8];
    sprintf(txt, "+5");
    glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

    glRasterPos2f(centerX + lineHalfLen + textOffset - 0.02f, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}

/*

void CHudSim::DrawPitchLadder_PlusUp2Line(float centerX, float centerY, float size, double pitchDeg)
{
    // +10 çizgisi
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset + (10.0f / 20.0f) * size;

    // Kesikli çizgi, metin yaz
    // ...
}

void CHudSim::DrawPitchLadder_PlusDown1Line(float centerX, float centerY, float size, double pitchDeg)
{
    // -5 çizgisi
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset - (5.0f / 20.0f) * size;

    // Kesikli çizgi, metin yaz
    // ...
}

void CHudSim::DrawPitchLadder_PlusDown2Line(float centerX, float centerY, float size, double pitchDeg)
{
    // -10 çizgisi
    float yOffset = CalculateYOffset(pitchDeg, 20.0, size);
    float y = centerY + yOffset - (10.0f / 20.0f) * size;

    // Kesikli çizgi, metin yaz
    // ...
}
*/
void CHudSim::DrawPitchLadder(float centerX, float centerY, float size, double rollDeg, double pitchDeg)
{
    glPushMatrix();

    // center etrafında rollDeg kadar döndür
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(static_cast<float>(-rollDeg), 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerX, -centerY, 0.0f);

    // Çizgiler
    DrawPitchLadder_Line(centerX, centerY, size, pitchDeg, -10);
    DrawPitchLadder_Line(centerX, centerY, size, pitchDeg, -5);
    DrawPitchLadder_ZeroLine(centerX, centerY, size, pitchDeg);
    DrawPitchLadder_Line(centerX, centerY, size, pitchDeg, 5);
    DrawPitchLadder_Line(centerX, centerY, size, pitchDeg, 10);

    glPopMatrix();
}

void CHudSim::DrawPitchLadder_(float centerX, float centerY, float size)
{
    float centerGap = size * 0.2f;
    float lineHalfLen = centerGap + size * 0.15f;    // normal çizgiler
    float lineHalfLen0 = centerGap + size * 0.1f;     // 0° için biraz kısa
    float lArm = size * 0.03f;
    float textOffset = size * 0.05f;
    float lAttach = lineHalfLen - size * 0.005f; // L bacağı pozisyonu

    for (int pitch = -10; pitch <= 10; pitch += 5)
    {
        float y = centerY + (pitch / 20.0f) * size;
        float currentLineHalfLen = lineHalfLen;

        glColor3f(0.0f, 1.0f, 0.0f);

        if (pitch == 0)
        {
            glDisable(GL_LINE_STIPPLE);
            //currentLineHalfLen = lineHalfLen0;  // 0° daha kısa
        }
        else
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        // yatay ana çizgiler
        glBegin(GL_LINES);
        glVertex2f(centerX - centerGap, y);
        glVertex2f(centerX - currentLineHalfLen, y);

        glVertex2f(centerX + centerGap, y);
        glVertex2f(centerX + currentLineHalfLen, y);
        glEnd();

        glDisable(GL_LINE_STIPPLE);  // L bacakları solid

        // L bacaklarını
        glBegin(GL_LINES);
        if (pitch >= 0)
        {
            glVertex2f(centerX - currentLineHalfLen, y);
            glVertex2f(centerX - currentLineHalfLen, y - lArm);

            glVertex2f(centerX + currentLineHalfLen, y);
            glVertex2f(centerX + currentLineHalfLen, y - lArm);
        }
        else
        {
            glVertex2f(centerX - currentLineHalfLen, y);
            glVertex2f(centerX - currentLineHalfLen, y + lArm);

            glVertex2f(centerX + currentLineHalfLen, y);
            glVertex2f(centerX + currentLineHalfLen, y + lArm);
        }
        glEnd();

#if 0
        // text
        char txt[8];
        sprintf(txt, "%d", pitch);
        if (pitch >= 0)
        {
            glRasterPos2f(centerX - currentLineHalfLen - textOffset, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        else if (pitch >= -5)
        {
            glRasterPos2f(centerX - currentLineHalfLen - textOffset - 0.02f, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        else
        {
            glRasterPos2f(centerX - currentLineHalfLen - textOffset - 0.04f, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        if (pitch > 0)
        {
            glRasterPos2f(centerX + currentLineHalfLen + textOffset - 0.02f, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        else if (pitch >= -5)
        {
            glRasterPos2f(centerX + currentLineHalfLen + textOffset - 0.02f, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
        else
        {
            glRasterPos2f(centerX + currentLineHalfLen + textOffset - 0.02f, y - 0.01f);
            for (const char* c = txt; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
#else
        // text
        char txt[8];
        sprintf(txt, "%d", pitch);
        glRasterPos2f(centerX - currentLineHalfLen - textOffset, y - 0.01f);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        glRasterPos2f(centerX + currentLineHalfLen + textOffset - 0.02f, y - 0.01f);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
#endif
    }
}

void CHudSim::DrawCentralWMarker(float centerX, float centerY, float size)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_STRIP);
    glVertex2f(centerX - 0.12f, centerY + 0.0f);    // sol yatay baş
    glVertex2f(centerX - 0.04f, centerY + 0.0f);    // sol yatay bitiş
    glVertex2f(centerX - 0.03f, centerY - 0.02f);   // ilk V iniş
    glVertex2f(centerX - 0.02f, centerY + 0.0f);    // ilk V çıkış
    glVertex2f(centerX - 0.01f, centerY - 0.02f);   // ikinci V iniş
    glVertex2f(centerX + 0.0f, centerY + 0.0f);    // ikinci V çıkış (tam merkez)
    glVertex2f(centerX + 0.08f, centerY + 0.0f);    // sağ yatay
    glEnd();
}

void CHudSim::DrawCenteredText(float x, float y, const char* text)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x - 0.05f, y);
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void CHudSim::DrawPlus(float centerX, float centerY, float size)
{
    glColor3f(1.0f, 1.0f, 1.0f);  // beyaz

    float halfSize = size / 2.0f;

    glBegin(GL_LINES);
    // yatay çizgi
    glVertex2f(centerX - halfSize, centerY);
    glVertex2f(centerX + halfSize, centerY);

    // dikey çizgi
    glVertex2f(centerX, centerY - halfSize);
    glVertex2f(centerX, centerY + halfSize);
    glEnd();
}

void CHudSim::DrawSideVerticalLines(float centerX, float centerY, float size, float xOffset)
{
    glColor3f(0.0f, 1.0f, 0.0f);  // yeşil

    float halfSize = size / 2.0f;

    glBegin(GL_LINES);
    // sol dikey
    glVertex2f(centerX - xOffset, centerY - halfSize);
    glVertex2f(centerX - xOffset, centerY + halfSize);

    // sağ dikey
    glVertex2f(centerX + xOffset, centerY - halfSize);
    glVertex2f(centerX + xOffset, centerY + halfSize);
    glEnd();
}

void CHudSim::DrawRightSideIndicators(float centerX, float centerY, float size, float xOffset)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    float halfSize = size / 2.0f;
    float smallLine = size * 0.02f;               // daha kısa
    float verticalOffset = size * 0.05f;

    glBegin(GL_LINES);
    // üst küçük yatay
    glVertex2f(centerX + xOffset, centerY + halfSize - verticalOffset);
    glVertex2f(centerX + xOffset - smallLine, centerY + halfSize - verticalOffset);

    // alt küçük yatay
    glVertex2f(centerX + xOffset, centerY - halfSize + verticalOffset);
    glVertex2f(centerX + xOffset - smallLine, centerY - halfSize + verticalOffset);
    glEnd();
}


void CHudSim::DrawRightSideCaretIndicator(float centerX, float centerY, float size, float xOffset, float caretY, float yOffset)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    float caretSize = size * 0.02f;  // küçük caret boyu
    float posY = caretY + yOffset;

    glBegin(GL_LINE_STRIP);
    glVertex2f(centerX + xOffset - caretSize, posY + caretSize);    // sol üst
    glVertex2f(centerX + xOffset, posY);                            // sağ uç
    glVertex2f(centerX + xOffset - caretSize, posY - caretSize);    // sol alt
    glEnd();
}

void CHudSim::DrawSpeedIndicator(float x, float y, float width, float height)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // kutu
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();

    // sağdaki küçük ok
    glBegin(GL_LINES);
    glVertex2f(x + width, y - height / 2.0f);
    glVertex2f(x + width + 0.02f, y - height / 2.0f + 0.01f);

    glVertex2f(x + width, y - height / 2.0f);
    glVertex2f(x + width + 0.02f, y - height / 2.0f - 0.01f);
    glEnd();
}


void CHudSim::DrawSpeedText(float x, float y, int speedValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "SPEED";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", speedValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::SetWindowSize(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}

void CHudSim::SetSpeedValue(int speed)
{
    speedValue = speed;
}

void CHudSim::DrawAltIndicatorBox(float x, float y, float width, float height)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // kutu (ters yönlü, sağdan sola)
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x - width, y);
    glVertex2f(x - width, y - height);
    glVertex2f(x, y - height);
    glEnd();
/*
    // soldaki küçük ok (sağa bakan okun tersi)
    glBegin(GL_LINES);
    glVertex2f(x, y - height / 2.0f);
    glVertex2f(x - 0.02f, y - height / 2.0f + 0.01f);

    glVertex2f(x, y - height / 2.0f);
    glVertex2f(x - 0.02f, y - height / 2.0f - 0.01f);
    glEnd();
*/
}

void CHudSim::DrawAltText(float x, float y, int altValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // ALT yazısı
    glRasterPos2f(x - 0.05f, y + 0.02f);
    std::string label = "ALT";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", altValue);
    glRasterPos2f(x - 0.04f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawTargetBox(float centerX, float centerY, float size, int value)
{
    glColor3f(1.0f, 1.0f, 1.0f); // beyaz kesikli kutu

    // Kesikli çizgi için line stipple aktif et
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);

    // Beyaz kesikli kare (dış kutu)
    float halfSize = size / 2.0f;
    glBegin(GL_LINE_LOOP);
    glVertex2f(centerX - halfSize, centerY - halfSize);
    glVertex2f(centerX + halfSize, centerY - halfSize);
    glVertex2f(centerX + halfSize, centerY + halfSize);
    glVertex2f(centerX - halfSize, centerY + halfSize);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    // Kırmızı diyagonal kare (iç kutu, çapraz)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(centerX, centerY - halfSize);            // alt orta
    glVertex2f(centerX + halfSize, centerY);            // sağ orta
    glVertex2f(centerX, centerY + halfSize);            // üst orta
    glVertex2f(centerX - halfSize, centerY);            // sol orta
    glEnd();

    // Kırmızı sayısal değer (sağda)
    glRasterPos2f(centerX + halfSize + 0.02f, centerY - 0.01f);
    char txt[8];
    sprintf(txt, "%d", value);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawCompass_(float centerX, float centerY, float width)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    float halfWidth = width / 2.0f;
    float lineHeight = 0.05f;
    float smallLineHeight = 0.02f;
    float textOffset = 0.015f; // Yazılardan önce çizgi duracak mesafe

    struct CompassMark
    {
        float offsetX;
        std::string label;
        bool isMajor;
    };

    CompassMark marks[] = {
        {-halfWidth, "SE", true},
        {0.0f, "S", true},
        {halfWidth, "SW", true},
    };

    // Çizgiler
    for (auto& mark : marks)
    {
        float x = centerX + mark.offsetX;

        // Dikey çizgiyi yazıya değmeyecek kadar kısa çiz
        glBegin(GL_LINES);
        glVertex2f(x, centerY);
        glVertex2f(x, centerY + lineHeight - textOffset);
        glEnd();

        // Yazı
        if (!mark.label.empty())
        {
            if (mark.label == "S")
            {
                // S harfi
                glRasterPos2f(x - 0.01f, centerY + lineHeight + 0.005f);
                for (char c : mark.label)
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

                // 180 sayısı, biraz daha yukarı
                std::string number = "180";
                glRasterPos2f(x - 0.03f, centerY + lineHeight + 0.05f);
                for (char c : number)
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            else
            {
                glRasterPos2f(x - 0.02f, centerY + lineHeight + 0.005f);
                for (char c : mark.label)
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }

    // Aradaki küçük çizgiler 5 tane (-2, -1, 0, 1, 2 konumları)
    float interval = halfWidth / 3.0f;  // 3 aralık, 5 çizgi

    for (int i = -2; i <= 2; i++)
    {
        if (i == 0) continue; // ortada S var, çizgi yok

        float x = centerX + i * interval;

        glBegin(GL_LINES);
        glVertex2f(x, centerY);
        glVertex2f(x, centerY + smallLineHeight);
        glEnd();
    }
}

void CHudSim::DrawCompass1(float centerX, float centerY, float width, double yawDeg)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    float halfWidth = width / 2.0f;
    float lineHeight = 0.05f;
    float textHeight = 0.03f;
    float baseY = centerY + lineHeight;

    // Yaw’a göre kaydırma (pozitif sağa)
    float shiftX = static_cast<float>((yawDeg / 360.0) * width);

    struct Mark
    {
        float baseX;
        std::string label;
    };

    Mark marks[] = {
        {0.0f, "N"},
        {-halfWidth, "NW"},
        {halfWidth, "NE"},
    };

    // Yazıları çiz (kaydırılmış x pozisyonları)
    for (auto& mark : marks)
    {
        float x = centerX + mark.baseX - shiftX;

        // Görünürlük kontrolü (örneğin -halfWidth..halfWidth arası çiz)
        if (x < centerX - halfWidth - 0.1f || x > centerX + halfWidth + 0.1f)
            continue;

        // Dikey çizgi
        glBegin(GL_LINES);
        glVertex2f(x, centerY);
        glVertex2f(x, baseY);
        glEnd();

        // Yazı
        glRasterPos2f(x - 0.00f, baseY + textHeight);
        for (char c : mark.label)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Ortadaki N'nin üstüne yawDeg yazısı
    char yawText[16];
    sprintf(yawText, "%.0f", yawDeg);
    glRasterPos2f(centerX - 0.00f, baseY + textHeight * 4);
    for (char* c = yawText; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}



void CHudSim::DrawCompass(float centerX, float centerY, float width, double yawDeg)
{
    float halfWidth = width / 2.0f;
    float shiftX = static_cast<float>((yawDeg / 360.0) * width);

    glPushMatrix();
    glTranslatef(-shiftX, 0.0f, 0.0f);

    DrawCompass_Line(centerX, centerY, width, yawDeg, -4, true);  // Kalın ve uzun
    DrawCompass_Line(centerX, centerY, width, yawDeg, -3, false); // İnce ve kısa
    DrawCompass_Line(centerX, centerY, width, yawDeg, -2, false);
    DrawCompass_Line(centerX, centerY, width, yawDeg, -1, false);

    DrawCompass_ZeroLine(centerX, centerY, width, yawDeg);        // Kalın ve uzun

    DrawCompass_Line(centerX, centerY, width, yawDeg, 1, false);
    DrawCompass_Line(centerX, centerY, width, yawDeg, 2, false);
    DrawCompass_Line(centerX, centerY, width, yawDeg, 3, false);
    DrawCompass_Line(centerX, centerY, width, yawDeg, 4, true);

    glPopMatrix();

    // yawDeg yazısı
    float lineHeight = 0.06f;
    float textOffset = 0.015f;

    char yawText[16];
    sprintf(yawText, "%.0f", yawDeg);

    glRasterPos2f(centerX - 0.015f, centerY + lineHeight + textOffset + 0.04f);
    for (char* c = yawText; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}





void CHudSim::DrawCompass_Line(float centerX, float centerY, float width, double yawDeg, int positionIndex, bool isMajorLine)
{
    float halfWidth = width / 2.0f;

    // Kaydırma miktarı (yawDeg'nin width içindeki orantılı kaydırması)
    float shiftX = static_cast<float>((yawDeg / 360.0) * width);

    float spacing = halfWidth / 4.0f;
    float x = centerX + positionIndex * spacing - shiftX;

    // Görünürlük kontrolü
    if (x < centerX - halfWidth - 0.1f || x > centerX + halfWidth + 0.1f)
        return;

    float lineHeight = isMajorLine ? 0.05f : 0.04f;
    float lineWidth = isMajorLine ? 2.0f : 1.0f;

    glLineWidth(lineWidth);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(x, centerY);
    glVertex2f(x, centerY + lineHeight);
    glEnd();

    glLineWidth(1.0f); // Reset çizgi kalınlığı

    // Yazı
    char txt[8];
    sprintf(txt, "%d", positionIndex * 30);

    if (isMajorLine)
    {
        float textOffset = 0.015f;
        glRasterPos2f(x - 0.01f, centerY + lineHeight + textOffset);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}



void CHudSim::DrawCompass_ZeroLine(float centerX, float centerY, float width, double yawDeg)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    float halfWidth = width / 2.0f;
    float lineHeight = 0.05f;
    float lineWidth = 2.0f;
    float textOffset = 0.015f;

    // Kaydırma miktarı (yawDeg'nin width içinde kaydırması)
    float shiftX = static_cast<float>((yawDeg / 360.0) * width);

    float x = centerX - shiftX;

    glLineWidth(lineWidth);
    // Dikey çizgi
    glBegin(GL_LINES);
    glVertex2f(x, centerY);
    glVertex2f(x, centerY + lineHeight);
    glEnd();
    glLineWidth(1.0f); // Reset çizgi kalınlığı

    // "N" yazısı
    glRasterPos2f(x - 0.01f, centerY + lineHeight + textOffset);
    for (const char* c = "N"; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}








void CHudSim::DrawPitchText(float x, float y, int pitchValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "PITCH";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", pitchValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawRollText(float x, float y, int rollValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "ROLL";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", rollValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawYawText(float x, float y, int yawValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "YAW";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", yawValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawThrottleText(float x, float y, int throttleValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "THROTTLE";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", throttleValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawAngleOfAttackText(float x, float y, int angleOfAttackDegValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "AngleOfAttack"; label = "ALPHA";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", angleOfAttackDegValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawAngleOfSideSlipText(float x, float y, int angleOfSideSlipDeg)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "AngleOfSideSlip"; label = "BETA";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", angleOfSideSlipDeg);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawFlightPathAngleText(float x, float y, int flightPathAngleDeg)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "FlightPathAngle"; label = "GAMMA";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", flightPathAngleDeg);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawanGFactorText(float x, float y, int gFactor)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "G-FORCE";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", gFactor);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

void CHudSim::DrawHeadingText(float x, float y, int headingValue)
{
    glColor3f(0.0f, 1.0f, 0.0f);

    // SPEED yazısı biraz daha küçük
    glRasterPos2f(x, y + 0.02f);
    std::string label = "HEADING";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", headingValue);
    glRasterPos2f(x + 0.01f, y - 0.035f);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}

// Roll Cmd
void CHudSim::SetRollCmd(double val)  
{ 
    rollCmd = val;
}

double CHudSim::GetRollCmd(void) const 
{ 
    return rollCmd;
}

// Pitch Cmd
void CHudSim::SetPitchCmd(double val) 
{ 
    pitchCmd = val;
}

double CHudSim::GetPitchCmd(void) const
{ 
    return pitchCmd;
}

// Yaw Cmd
void CHudSim::SetYawCmd(double val)
{ 
    yawCmd = val;
}

double CHudSim::GetYawCmd(void) const
{ 
    return yawCmd;
}

// Throttle Cmd
void CHudSim::SetThrottleCmd(double val) 
{ 
    throttleCmd = val;
}

double CHudSim::GetThrottleCmd(void) const
{ 
    return throttleCmd;
}

// Heading
double CHudSim::GetHeadingDeg(void) const
{ 
    return headingDeg; 
}

void CHudSim::SetHeadingDeg(double val) 
{ 
    headingDeg = val; 
}

// Roll
double CHudSim::GetRollDeg(void) const
{ 
    return rollDeg; 
}

void CHudSim::SetRollDeg(double val) 
{ 
    rollDeg = val; 
}

// Pitch
double CHudSim::GetPitchDeg(void) const
{ 
    return pitchDeg; 
}

void CHudSim::SetPitchDeg(double val) 
{ 
    pitchDeg = val; 
}

// Yaw
double CHudSim::GetYawDeg(void) const
{ 
    return yawDeg; 
}

void CHudSim::SetYawDeg(double val) 
{ 
    yawDeg = val; 
}

// Throttle
double CHudSim::GetThrottle(void) const
{ 
    return throttle; 
}

void CHudSim::SetThrottle(double val) 
{ 
    throttle = val; 
}

// Latitude
void CHudSim::SetLatDeg(double val) 
{ 
    latDeg = val; 
}

double CHudSim::GetLatDeg(void) const 
{
    return latDeg; 
}

// Longitude
void CHudSim::SetLonDeg(double val) 
{ 
    lonDeg = val; 
}

double CHudSim::GetLonDeg(void) const 
{ 
    return lonDeg; 
}

// Altitude (Meter)
void CHudSim::SetAltMeter(double val) 
{ 
    altMeter = val; 
}

double CHudSim::GetAltMeter(void) const 
{ 
    return altMeter; 
}

// Speed (MPS)
void CHudSim::SetSpeedMPS(double val) 
{ 
    speedMPS = val; 
}

double CHudSim::GetSpeedMPS(void) const 
{ 
    return speedMPS; 
}

// Altitude (Feet)
void CHudSim::SetAltFeet(double val)
{
    altFeet = val;
}

double CHudSim::GetAltFeet(void) const
{
    return altFeet;
}

// Speed (Mach)
void CHudSim::SetSpeedMach(double val)
{
    speedMach = val;
}

double CHudSim::GetSpeedMach(void) const
{
    return speedMach;
}

// Angle Of Attack 
void CHudSim::SetAngleOfAttackDeg(double val)
{
    angleOfAttackDeg = val;
}

double CHudSim::GetAngleOfAttackDeg(void) const
{
    return angleOfAttackDeg;
}

// Angle Of SideSlip 
void CHudSim::SetAngleOfSideSlipDeg(double val)
{
    angleOfSideSlipDeg = val;
}

double CHudSim::GetAngleOfSideSlipDeg(void) const
{
    return angleOfSideSlipDeg;
}

// Fligh Path Angle
void CHudSim::SetFlightPathAngleDeg(double val)
{
    flightPathAngleDeg = val;
}

double CHudSim::GetFlightPathAngleDeg(void) const
{
    return flightPathAngleDeg;
}

// gFactor
void CHudSim::SetGFactor(double val)
{
    gFactor = val;
}

double CHudSim::GetGFactor(void) const
{
    return gFactor;
}

void CHudSim::IncreaseRollCmd(double step)
{
    rollCmd += step;
    if (rollCmd > 1.0) rollCmd = 1.0; // limit
}

void CHudSim::DecreaseRollCmd(double step)
{
    rollCmd -= step;
    if (rollCmd < -1.0) rollCmd = -1.0; // limit
}

void CHudSim::IncreasePitchCmd(double step)
{
    pitchCmd += step;
    if (pitchCmd > 1.0) pitchCmd = 1.0; // limit
}

void CHudSim::DecreasePitchCmd(double step)
{
    pitchCmd -= step;
    if (pitchCmd < -1.0) pitchCmd = -1.0; // limit
}

void CHudSim::IncreaseYawCmd(double step)
{
    yawCmd += step;
    if (yawCmd > 1.0) yawCmd = 1.0; // limit
}

void CHudSim::DecreaseYawCmd(double step)
{
    yawCmd -= step;
    if (yawCmd < -1.0) yawCmd = -1.0; // limit
}

void CHudSim::IncreaseThrottleCmd(double step)
{
    throttleCmd += step;
    if (throttleCmd > 1.0) throttleCmd = 1.0; // limit
}

void CHudSim::DecreaseThrottleCmd(double step)
{
    throttleCmd -= step;
    if (throttleCmd < 0.0) throttleCmd = 0.0; // limit
}

void CHudSim::IncreaseRoll(double step)
{
    rollDeg += step;
    if (rollDeg > 180.0) rollDeg -= 360.0;  // Roll açısını -180..180 arası tutar
}

void CHudSim::DecreaseRoll(double step)
{
    rollDeg -= step;
    if (rollDeg < -180.0) rollDeg += 360.0;
}

void CHudSim::IncreasePitch(double step)
{
    pitchDeg += step;
    if (pitchDeg > 90.0) pitchDeg = 90.0; // limit
}

void CHudSim::DecreasePitch(double step)
{
    pitchDeg -= step;
    if (pitchDeg < -90.0) pitchDeg = -90.0; // limit
}

void CHudSim::IncreaseYaw(double step) 
{
    yawDeg += step;
    if (yawDeg >= 360.0) yawDeg -= 360.0;
    if (yawDeg < 0.0) yawDeg += 360.0;
}

void CHudSim::DecreaseYaw(double step) 
{
    yawDeg -= step;
    if (yawDeg < 0.0) yawDeg += 360.0;
    if (yawDeg >= 360.0) yawDeg -= 360.0;
}

void CHudSim::IncreaseThrottle(double step)
{
    throttle += step;
    if (throttle > 100.0) throttle = 100.0; // limit
}

void CHudSim::DecreaseThrottle(double step)
{
    throttle -= step;
    if (throttle < 0.0) throttle = 0.0; // limit
}

void CHudSim::IncreaseHeading(double step)
{
    headingDeg += step;
    if (headingDeg >= 360.0) headingDeg -= 360.0;
    if (headingDeg < 0.0) headingDeg += 360.0;
}

void CHudSim::DecreaseHeading(double step)
{
    headingDeg -= step;
    if (headingDeg < 0.0) headingDeg += 360.0;
    if (headingDeg >= 360.0) headingDeg -= 360.0;
}

void CHudSim::DrawPitchLabelDeepSeek(float x, float y, int pitch) 
{
    // Sayıyı formatla
    std::string textStr = "0";

    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = textStr.length() * 1.0f; // Yaklaşık genişlik

    char txt[8];

    if (pitch > 0)
    {
        textStr = "+" + std::to_string(pitch);
        sprintf(txt, "%3s", textStr.c_str());
    }
    else if (pitch < 0)
    {
        textStr = std::to_string(pitch);
        sprintf(txt, "%-3s", textStr.c_str());
    }
    else
    {
        textStr = std::to_string(pitch);
        sprintf(txt, "%3s", textStr.c_str());
    }

    glRasterPos2f(x, y);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);

#if 0
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);

    // Sayıyı formatla
    std::string text;
    if (pitch > 0) 
        text = "+" + std::to_string(pitch);
    else if (pitch < 0) 
        text = "-" + std::to_string(pitch);
    else 
        text = "0";

    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = text.length() * 1.0f; // Yaklaşık genişlik

    glColor3f(1.0f, 1.0f, 1.0f); // Yesil renk

    // OpenGL text rendering (GLUT kullanarak)
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

/*
    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = text.length() * 1.0f; // Yaklaşık genişlik

    // OpenGL text rendering (GLUT kullanarak)
    glRasterPos2f(x - textWidth / 2, y - 0.4);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
*/
/*
    char txt[8];
    sprintf(txt, "0");
    glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
*/

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

void CHudSim::DrawPitchLadderDeepSeek(float centerX, float centerY, float size, double rollDeg, double pitchDeg, float centerXGap, float centerYGap)
{
    const float ladderHeight = size * 2.0f;
    const float degreesToPixels = size / 10.0f;
    const float topBound = centerY - ladderHeight / 2.0f;
    const float bottomBound = centerY + ladderHeight / 2.0f;

    float pitchOffset = 0.f;
    double clampedPitch = std::max(-90.0, std::min(90.0, pitchDeg));
    pitchOffset = -clampedPitch * degreesToPixels;

    const float smallLineLength = size * 1.0f;
    const float largeLineLength = size * 1.0f;

    int minPitch = -90;
    int maxPitch = 90;

    // Goronur aralik
    int visibleMinPitch = static_cast<int>(clampedPitch) - static_cast<int>(ladderHeight / degreesToPixels) / 2 - 10;
    int visibleMaxPitch = static_cast<int>(clampedPitch) + static_cast<int>(ladderHeight / degreesToPixels) / 2 + 10;

    minPitch = std::max(minPitch, (visibleMinPitch / 5) * 5 - 5);
    maxPitch = std::min(maxPitch, (visibleMaxPitch / 5) * 5 + 5);

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);
    glRotatef(-rollDeg, 0, 0, 1);

    // Çizgi stilleri
    const float solidLineWidth = 3.0f;
    const float dashedLineWidth = 1.5f;

    // Dash pattern
    GLfloat dashPattern[] = { 5.0f, 5.0f };
    GLfloat solidPattern[] = { 1.0f, 0.0f };

    for (int pitch = minPitch; pitch <= maxPitch; pitch += 5) 
    {
        if (pitch < -90 || pitch >90) continue;

        float yPos = pitchOffset + pitch * degreesToPixels;

        if (yPos < topBound || yPos > bottomBound) continue;

        float length = (pitch % 10 == 0) ? largeLineLength : smallLineLength;
        float halfXGap = centerXGap / 2.0f;
        float halfYGap = centerYGap / 2.0f;

        if (pitch == 0) {
            // Özel 0 çizgisi - kalın ve solid
            glLineWidth(solidLineWidth);
            glLineStipple(1, 0xFFFF);
            glColor3f(0.0f, 1.0f, 0.0f); // Beyaz
            glBegin(GL_LINES);
                glVertex2f(-length * 0.75f, yPos);
                glVertex2f(-halfXGap, yPos);
                glVertex2f(halfXGap, yPos);
                glVertex2f(length * 0.75f, yPos);
            glEnd();
        }
        else {
            // Diğer çizgiler - ince ve dash
            glLineWidth(dashedLineWidth);
            glLineStipple(1, 0x00FF);
            glColor3f(0.0f, 1.0f, 0.0f);
            glEnable(GL_LINE_STIPPLE);
            glBegin(GL_LINES);
                glVertex2f(-length * 0.75f, yPos);
                glVertex2f(-halfXGap, yPos);
                glVertex2f(halfXGap, yPos);
                glVertex2f(length * 0.75f, yPos);
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }

        // Çizgi etiketlerini çiz (sol ve sağ uçlara)
        if (pitch % 10 == 0 || pitch == 0) {
            float rightLabelX = length - 0.07f;
            float leftLabelX = -rightLabelX - 0.05f;
            DrawPitchLabelDeepSeek(leftLabelX, yPos - 0.020f, pitch);   // Sol etiket
            DrawPitchLabelDeepSeek(rightLabelX, yPos - 0.020f, pitch);  // Sağ etiket
        }
    }

    glPopMatrix();
}

void CHudSim::DrawVerticaLinesDeepSeek(float centerX, float centerY, float size, float centerXGap, float centerYGap) 
{
    // Çizgi özellikleri
    const float lineWidth = 1.0f;
    const float halfSize = size * 0.5f;

    // Merkez boşluklarını boyuta oranla (0.25f = %25 boşluk anlamında)
    float xGap = size * centerXGap;
    float yGap = size * centerYGap;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // Çizgi rengi (beyaz)
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(lineWidth);

    // Sol dikey çizgi
    glBegin(GL_LINES);
    glVertex2f(-halfSize, halfSize - yGap);   // Üst nokta
    glVertex2f(-halfSize, -halfSize + yGap);  // Alt nokta
    glEnd();

    // Sağ dikey çizgi
    glBegin(GL_LINES);
    glVertex2f(halfSize, halfSize - yGap);    // Üst nokta
    glVertex2f(halfSize, -halfSize + yGap);   // Alt nokta
    glEnd();

#if 0
    // Yatay bağlantı çizgileri (isteğe bağlı)
    glBegin(GL_LINES);
    // Üst yatay çizgi
    glVertex2f(-halfSize + xGap, halfSize);
    glVertex2f(halfSize - xGap, halfSize);

    // Alt yatay çizgi
    glVertex2f(-halfSize + xGap, -halfSize);
    glVertex2f(halfSize - xGap, -halfSize);
    glEnd();
#endif

    glPopMatrix();
}

void CHudSim::DrawHorizonLinesDeepSeek(float centerX, float centerY, float size, float centerXGap, float centerYGap) 
{
    // Çizgi özellikleri
    const float lineWidth = 1.0f;
    const float halfSize = size * 0.5f;

    // Merkez boşluklarını boyuta oranla
    float xGap = size * centerXGap;
    float yGap = size * centerYGap;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // Çizgi rengi (beyaz)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(lineWidth);

    // Üst yatay çizgi
    glBegin(GL_LINES);
    glVertex2f(-halfSize + xGap, halfSize);   // Sol nokta
    glVertex2f(halfSize - xGap, halfSize);    // Sağ nokta
    glEnd();

    // Alt yatay çizgi
    glBegin(GL_LINES);
    glVertex2f(-halfSize + xGap, -halfSize);  // Sol nokta
    glVertex2f(halfSize - xGap, -halfSize);   // Sağ nokta
    glEnd();

#if 0
    // Dikey bağlantı çizgileri (isteğe bağlı)
    glBegin(GL_LINES);
    // Sol dikey çizgi
    glVertex2f(-halfSize, halfSize - yGap);
    glVertex2f(-halfSize, -halfSize + yGap);

    // Sağ dikey çizgi
    glVertex2f(halfSize, halfSize - yGap);
    glVertex2f(halfSize, -halfSize + yGap);
    glEnd();
#endif
    glPopMatrix();
}

void _DrawYawCompassDeepSeek(float centerX, float centerY, float size, double yawDeg, float centerXGap, float centerYGap)
{
    const float compassWidth = size * 10.0f;
    const float degreesToPixels = size / 15.0f; // 15° başına boyut
    const float leftBound = centerX - compassWidth / 2.0f;
    const float rightBound = centerX + compassWidth / 2.0f;

    // Yaw değerini normalize et [0-360)
    yawDeg = fmod(yawDeg, 360.0);
    if (yawDeg < 0) yawDeg += 360.0;

    float yawOffset = -yawDeg * degreesToPixels;

    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.3f;
    const float textOffset = size * 0.35f;

    // Dinamik yaw aralığı
    int visibleYawRange = static_cast<int>(compassWidth / degreesToPixels) + 30;
    int minYaw = static_cast<int>(floor(yawDeg)) - visibleYawRange;
    int maxYaw = static_cast<int>(ceil(yawDeg)) + visibleYawRange;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // Çizgi stilleri
    const float lineWidth = 2.0f;
    glLineWidth(lineWidth);
    glColor3f(1.0f, 1.0f, 1.0f); // Beyaz

    for (int yaw = minYaw; yaw <= maxYaw; yaw += 15) 
    {
        // Normalize yaw değeri
        int normalizedYaw = (yaw % 360 + 360) % 360;
        float xPos = yawOffset + yaw * degreesToPixels;

        if (xPos < leftBound || xPos > rightBound) continue;

        // Çizgi uzunluğunu belirle (45°'nin katlarında uzun)
        bool isMajorTick = (normalizedYaw % 45 == 0);
        float length = isMajorTick ? largeLineLength : shortLineLength;

        glBegin(GL_LINES);
        glVertex2f(xPos, -length);
        glVertex2f(xPos, length);
        glEnd();

        // Başlık etiketleri (45°'nin katlarında)
        if (isMajorTick) 
        {
            std::string label;
            switch (normalizedYaw) {
            case 0: label = "N"; break;
            case 45: label = "NE"; break;
            case 90: label = "E"; break;
            case 135: label = "SE"; break;
            case 180: label = "S"; break;
            case 225: label = "SW"; break;
            case 270: label = "W"; break;
            case 315: label = "NW"; break;
            default: label = std::to_string(normalizedYaw);
            }

            // Etiketi çiz
            glRasterPos2f(xPos - (label.length() * 4.0f), textOffset);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }
/*
    // Merkez çizgisi (daha kalın)
    glLineWidth(lineWidth * 1.5f);
    glBegin(GL_LINES);
    glVertex2f(0, -largeLineLength * 1.5f);
    glVertex2f(0, largeLineLength * 1.5f);
    glEnd();

    // Mevcut yaw değerini göster
    std::string yawText = std::to_string(static_cast<int>(yawDeg)) + "°";
    glRasterPos2f(-(yawText.length() * 1.0f), textOffset * 1.5f);
    for (char c : yawText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
*/
    glPopMatrix();
}
/*
void DrawYawCompassDeepSeek2(float centerX, float centerY, float size, double yawDeg, float centerXGap, float centerYGap) {
    const float compassWidth = size * 10.0f;
    const float degreesToPixels = size / 15.0f;
    const float leftBound = -compassWidth / 2.0f;
    const float rightBound = compassWidth / 2.0f;

    // Normalize yaw [0-360)
    yawDeg = fmod(yawDeg, 360.0);
    if (yawDeg < 0) yawDeg += 360.0;

    // Line properties
    const float shortLineLength = size * 0.2f;
    const float largeLineLength = size * 0.3f;
    const float textOffset = size * 0.35f;

    // Calculate visible range
    int visibleRangeDegrees = static_cast<int>(compassWidth / degreesToPixels) / 2;
    int minYaw = static_cast<int>(yawDeg) - visibleRangeDegrees - 90; // Extended range
    int maxYaw = static_cast<int>(yawDeg) + visibleRangeDegrees + 90;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // Draw ticks
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    for (int yaw = minYaw; yaw <= maxYaw; yaw += 15) {
        float xPos = (yaw - yawDeg) * degreesToPixels;

        if (xPos < leftBound || xPos > rightBound) continue;

        // Always draw the line
        bool isMajorTick = (yaw % 45 == 0);
        float length = isMajorTick ? largeLineLength : shortLineLength;

        glLineWidth(isMajorTick ? 2.5f : 0.5f);
        glBegin(GL_LINES);
        glVertex2f(xPos, -length);
        glVertex2f(xPos, length);
        glEnd();

        // Draw labels for major ticks and current position
        if (isMajorTick || yaw == static_cast<int>(yawDeg)) {
            std::string label;
            int displayYaw = (yaw % 360 + 360) % 360; // Normalized [0-360)

            if (displayYaw % 45 == 0) {
                switch (displayYaw) {
                case 0: label = "N"; break;
                case 45: label = "NE"; break;
                case 90: label = "E"; break;
                case 135: label = "SE"; break;
                case 180: label = "S"; break;
                case 225: label = "SW"; break;
                case 270: label = "W"; break;
                case 315: label = "NW"; break;
                }
            }
            else if (yaw == static_cast<int>(yawDeg)) {
                label = std::to_string(displayYaw) + "°";
            }

            if (!label.empty()) {
                DrawCompassLabelDeepSeek(xPos - (label.length() * 3.5f),
                    textOffset,
                    label);
            }
        }
    }

    // Draw center indicator (thicker line)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0, -largeLineLength * 1.5f);
    glVertex2f(0, largeLineLength * 1.5f);
    glEnd();

    // Draw center indicator (thick line) - slightly raised
    const float centerLineRaise = size * 1.0f;

    // 1. Merkezdeki yaw değeri (üstte)
    std::string yawText = std::to_string(static_cast<int>(yawDeg)) + "°";
    float textWidth = yawText.length() * 3.5f;
    DrawCompassLabelDeepSeek(-0.01f, largeLineLength * 0.75f + centerLineRaise, yawText);

    glPopMatrix();
}
*/

void CHudSim::DrawYawCompassDeepSeek(float centerX, float centerY, float size, double yawDeg, float centerXGap, float centerYGap) {
    const float compassWidth = size * 10.0f;
    const float degreesToPixels = size / 15.0f;
    const float leftBound = -compassWidth / 2.0f;
    const float rightBound = compassWidth / 2.0f;

    // Normalize yaw [0-360)
    yawDeg = fmod(yawDeg, 360.0);
    if (yawDeg < 0) yawDeg += 360.0;

    // Line properties
    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.4f;
    const float textOffset = size * 0.35f;

    // Calculate visible range
    int visibleRangeDegrees = static_cast<int>(compassWidth / degreesToPixels) / 2;
    int minYaw = static_cast<int>(yawDeg) - visibleRangeDegrees - 90; // Extended range
    int maxYaw = static_cast<int>(yawDeg) + visibleRangeDegrees + 90;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // Draw ticks
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    for (int yaw = minYaw; yaw <= maxYaw; yaw += 15) 
    {
        float xPos = (yaw - yawDeg) * degreesToPixels;

        if (xPos < leftBound || xPos > rightBound) continue;

        // Always draw the line
        bool isMajorTick = (yaw % 45 == 0);
        float length = isMajorTick ? largeLineLength : shortLineLength;

        glLineWidth(isMajorTick ? 2.5f : 0.5f);
        glBegin(GL_LINES);
        glVertex2f(xPos, -length);
        glVertex2f(xPos, length);
        glEnd();

        // Draw labels for major ticks and current position
        if (isMajorTick || yaw == static_cast<int>(yawDeg)) {
            std::string label;
            int displayYaw = (yaw % 360 + 360) % 360; // Normalized [0-360)

            if (displayYaw % 45 == 0) {
                switch (displayYaw) {
                case 0: label = "N"; break;
                case 45: label = "NE"; break;
                case 90: label = "E"; break;
                case 135: label = "SE"; break;
                case 180: label = "S"; break;
                case 225: label = "SW"; break;
                case 270: label = "W"; break;
                case 315: label = "NW"; break;
                }
            }
            else if (yaw == static_cast<int>(yawDeg)) {
                label = std::to_string(displayYaw) + "°";
            }

            if (!label.empty()) {
                DrawCompassLabelDeepSeek(xPos - (label.length() * 3.5f),
                    textOffset,
                    label);
            }
        }
    }

#if 0
    // Draw center indicator (thicker line)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0, -largeLineLength * 1.5f);
    glVertex2f(0, largeLineLength * 1.5f);
    glEnd();
#endif
    // Draw center indicator (thick line) - slightly raised
    const float centerLineRaise = size * 1.0f;

    // 1. Merkezdeki yaw değeri (üstte)
    std::string yawText = std::to_string(static_cast<int>(yawDeg)) + "°";
    float textWidth = yawText.length() * 3.5f;
    DrawCompassLabelDeepSeek(-0.01f, largeLineLength * 0.75f + centerLineRaise, yawDeg);

    glPopMatrix();
}

void CHudSim::DrawCompassLabelDeepSeek(float x, float y, const std::string& text) 
{
    // Sayıyı formatla
    std::string textStr = "0";

    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = textStr.length() * 1.0f; // Yaklaşık genişlik

    // Helvetica 18 için karakter genişlik faktörü (~10 piksel/karakter)
    const float charWidth = 10.0f;
    textWidth = text.length() * charWidth;

    char txt[8];
    sprintf(txt, "%3s", text.c_str());

    glRasterPos2f(x, y);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
}

void CHudSim::DrawCompassLabelDeepSeek(float x, float y, int heading)
{
    // Sayıyı formatla
    std::string textStr = "0";

    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = textStr.length() * 1.0f; // Yaklaşık genişlik

    char txt[8];

    if (heading > 0)
    {
        textStr = std::to_string(heading);
        sprintf(txt, "%3s", textStr.c_str());
    }
    else if (heading < 0)
    {
        textStr = std::to_string(heading);
        sprintf(txt, "%-3s", textStr.c_str());
    }
    else
    {
        textStr = std::to_string(heading);
        sprintf(txt, "%3s", textStr.c_str());
    }

    glRasterPos2f(x, y);
    for (char* p = txt; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);

#if 0
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);

    // Sayıyı formatla
    std::string text;
    if (pitch > 0)
        text = "+" + std::to_string(pitch);
    else if (pitch < 0)
        text = "-" + std::to_string(pitch);
    else
        text = "0";

    // Sayıyı ortalamak için genişlik hesapla
    float textWidth = text.length() * 1.0f; // Yaklaşık genişlik

    glColor3f(1.0f, 1.0f, 1.0f); // Yesil renk

    // OpenGL text rendering (GLUT kullanarak)
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    /*
        // Sayıyı ortalamak için genişlik hesapla
        float textWidth = text.length() * 1.0f; // Yaklaşık genişlik

        // OpenGL text rendering (GLUT kullanarak)
        glRasterPos2f(x - textWidth / 2, y - 0.4);
        for (char c : text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    */
    /*
        char txt[8];
        sprintf(txt, "0");
        glRasterPos2f(centerX - lineHalfLen - textOffset, y - 0.01f);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    */

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}




void CHudSim::DrawHorizontalCompassDeepSeek(float centerX, float centerY, float size, double headingDeg, float centerXGap, float centerYGap) 
{
        bool drawCenterLine = true;
        const float compassWidth = size * 10.0f;
        const float degreesToPixels = size / 30.0f;  // 15° = size/15 pixels
        const float leftBound = -compassWidth / 2.0f;  // Local coordinates
        const float rightBound = compassWidth / 2.0f;

        // Normalize heading [0-360)
        headingDeg = fmod(headingDeg, 360.0);
        if (headingDeg < 0) headingDeg += 360.0;

        // Line properties
        const float shortLineLength = size * 0.1f;
        const float largeLineLength = size * 0.3f;
        const float textOffset = size * 0.4f;

        glPushMatrix();
        glTranslatef(centerX, centerY, 0);

        if (drawCenterLine)
        {
            // 1. Draw CENTER LINE (fixed, always at 0)
            glLineWidth(3.0f);
            glColor3f(0.0f, 1.0f, 0.0f); // Green center line
            glBegin(GL_LINES);
            glVertex2f(0, -largeLineLength - 0.075f);
            glVertex2f(0, largeLineLength - 0.075f);
            glEnd();
        }

        // 2. Draw MOVING TICKS
        glColor3f(0.0f, 1.0f, 0.0f); // White ticks
        for (int hdg = -180; hdg <= 540; hdg += 5) { // Extended range for smooth movement
            float xPos = (hdg - headingDeg) * degreesToPixels;

            if (xPos < leftBound || xPos > rightBound) continue;

            bool isMajorTick = (hdg % 30 == 0);
            float length = isMajorTick ? largeLineLength : shortLineLength;

            glLineWidth(isMajorTick ? 2.0f : 1.0f);
            glBegin(GL_LINES);
            glVertex2f(xPos, -length);
            glVertex2f(xPos, length);
            glEnd();

            // Draw labels for major ticks
            if (isMajorTick) 
            {
                int normalizedHdg = (hdg % 360 + 360) % 360;
                std::string label;
                switch (normalizedHdg) {
                case 0: label = "N"; break;
                //case 30: label = "30"; break;
                case 45: label = "NE"; break;
                //case 60: label = "60"; break;
                //case 75: label = "75"; break;
                case 90: label = "E"; break;
                //case 120: label = "120"; break;
                case 135: label = "SE"; break;
                //case 150: label = "150"; break;
                case 180: label = "S"; break;
                //case 210: label = "210"; break;
                case 225: label = "SW"; break;
                //case 240: label = "240"; break;
                case 270: label = "W"; break;
                //case 300: label = "300"; break;
                //case 330: label = "330"; break;
                }

                if (normalizedHdg >= 0 && normalizedHdg < 10)
                {
                    //DrawCompassLabelDeepSeek(xPos - 0.01f, textOffset + 0.01f, label);
                }
                else if (normalizedHdg >= 10 && normalizedHdg < 100)
                {
                    //DrawCompassLabelDeepSeek(xPos - 0.00f, textOffset + 0.01f, label);
                }
                else if (normalizedHdg >= 100)
                {
                    //DrawCompassLabelDeepSeek(xPos + 0.01f, textOffset + 0.01f, label);
                }

                DrawCompassLabelDeepSeek(xPos - 0.035f, textOffset + 0.01f, label);
            }
        }
        // Draw center indicator (thick line) - slightly raised
        const float centerLineRaise = size * 1.0f;

        // 1. Merkezdeki yaw değeri (üstte)
        std::string headingDegText = std::to_string(static_cast<int>(headingDeg)) + "°";

        float green[3] = { 0.0f, 1.0f, 0.0f };
        DrawEmptyBox(
            -0.015f,                                    // centerX   
            largeLineLength * 0.75f + centerLineRaise,  // centerY
            0.020f,                                     // offsetX 
            0.018f,                                     // offsetY
            0.2f, 0.06f,                                // width, height
            1.0f,                                       // border thickness
            green);                                     // color

        // 3. Metni kutunun içine ortalayarak yaz
        DrawCompassLabelDeepSeek(-0.015f, largeLineLength * 0.75f + centerLineRaise, headingDegText);

        glPopMatrix();
}

void CHudSim::DrawEmptyBox(float centerX, float centerY,
    float offsetX, float offsetY,
    float width, float height,
    float borderThickness,
    const float color[3],
    float rotationDeg) // Varsayılan: döndürme yok
{
    // 1. Çizim ayarları
    glLineWidth(borderThickness);
    glColor3fv(color);

    // 2. Offset uygulanmış merkez noktası
    float finalX = centerX + offsetX;
    float finalY = centerY + offsetY;

    // 3. Döndürme için transformasyon matrisi
    glPushMatrix();
    glTranslatef(finalX, finalY, 0);
    glRotatef(rotationDeg, 0, 0, 1); // Z ekseninde döndür

    // 4. İçi boş kutu çiz (orijin merkezli)
    glBegin(GL_LINE_LOOP);
    glVertex2f(-width / 2, -height / 2);  // Sol alt
    glVertex2f(width / 2, -height / 2);   // Sağ alt
    glVertex2f(width / 2, height / 2);    // Sağ üst
    glVertex2f(-width / 2, height / 2);   // Sol üst
    glEnd();

    // 5. Transformasyon matrisini geri yükle
    glPopMatrix();

    // 6. OpenGL ayarlarını sıfırla
    glLineWidth(1.0f);
}



void CHudSim::DrawEmptyTriangle(float centerX, float centerY,
    float offsetX, float offsetY,
    float size,
    float borderThickness,
    const float color[3],
    float rotationDeg) // Varsayılan: düz üçgen
{
    // 1. Çizim ayarları
    glLineWidth(borderThickness);
    glColor3fv(color);

    // 2. Offset uygulanmış merkez
    float finalX = centerX + offsetX;
    float finalY = centerY + offsetY;

    // 3. Üçgen noktaları (eşkenar üçgen)
    float height = size * 0.866f; // sqrt(3)/2

    glPushMatrix();
    glTranslatef(finalX, finalY, 0);
    glRotatef(rotationDeg, 0, 0, 1); // Döndürme

    // 4. İçi boş üçgen çiz
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, height / 2);         // Tepe
    glVertex2f(-size / 2, -height / 2);  // Sol alt
    glVertex2f(size / 2, -height / 2);   // Sağ alt
    glEnd();

    glPopMatrix();

    // 5. OpenGL ayarlarını sıfırla
    glLineWidth(1.0f);
}

void CHudSim::DrawEmptyCircle(float centerX, float centerY,
    float offsetX, float offsetY,
    float radius,
    float borderThickness,
    const float color[3],
    int segments) // Daire çözünürlüğü
{
    // 1. Çizim ayarları
    glLineWidth(borderThickness);
    glColor3fv(color);

    // 2. Offset uygulanmış merkez
    float finalX = centerX + offsetX;
    float finalY = centerY + offsetY;

    // 3. Daire çiz
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(finalX + x, finalY + y);
    }
    glEnd();

    // 4. OpenGL ayarlarını sıfırla
    glLineWidth(1.0f);
}




void CHudSim::DrawRollCompassDeepSeek(float centerX, float centerY, float size, double rollDeg, float centerXGap, float centerYGap)
{
    const float compassWidth = size * 10.0f;
    const float degreesToPixels = size / 5.0f;
    const float leftBound = -compassWidth / 2.0f;
    const float rightBound = compassWidth / 2.0f;

    // Roll değerini normalize et (-90 ile +90 arası)
    //rollDeg = fmod(rollDeg, 180.0);
    //if (rollDeg > 90.0) rollDeg -= -90.0;
    //if (rollDeg < -90.0) rollDeg += 180.0;

    // Roll değerini normalize et (-180 ile +180 arası)
    rollDeg = fmod(rollDeg, 360.0);
    if (rollDeg > 180.0) rollDeg -= 360.0;
    if (rollDeg < -180.0) rollDeg += 360.0;

    // Normalize heading [0-360)
    //rollDeg = fmod(rollDeg, 360.0);
    //if (rollDeg < 0) rollDeg += 360.0;

    // Çizgi özellikleri
    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.3f;
    const float textOffset = size * 0.4f;
    const float centerLineRaise = size * 1.0f;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // 1. Hareketli çizgiler
    glColor3f(0.0f, 1.0f, 0.0f); // Yeşil çizgiler
    //for (int roll = -180; roll <= 540; roll += 5) { // Extended range for smooth movement
    for (int roll = -360; roll <= 540; roll += 5) { // Extended range for smooth movement
        float xPos = (roll - rollDeg) * degreesToPixels;

        if (xPos < leftBound || xPos > rightBound) continue;

        bool isMajorTick = (abs(roll) % 15 == 0); // Her 15°'de bir ana çizgi
        float length = isMajorTick ? largeLineLength : shortLineLength;

        glLineWidth(isMajorTick ? 2.0f : 1.0f);
        glBegin(GL_LINES);
        glVertex2f(xPos, -length);
        glVertex2f(xPos, length);
        glEnd();

        // Ana çizgi etiketleri
        if (isMajorTick) {
            std::string label = std::to_string(abs(roll));
            if (roll == 0) label = "0";
            else if (roll > 0) label = std::to_string(abs(roll));
            else label = std::to_string(roll);

            // Etiket pozisyonunu ayarla
            float labelX = xPos - (label.length() * 0.015f);
            DrawCompassLabelDeepSeek(labelX, textOffset + 0.01f, roll);
        }
    }

    // 2. Merkez çizgisi (daha kalın)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0, -largeLineLength * 1.5f);
    glVertex2f(0, largeLineLength * 1.5f);
    glEnd();

    // 3. Roll değeri kutusu
    std::string rollText = std::to_string(static_cast<int>(rollDeg)) + "°";
    float green[3] = { 0.0f, 1.0f, 0.0f };
    DrawEmptyBox(
        -0.025f,                                       // centerX   
        -largeLineLength * 0.75f - centerLineRaise,  // centerY (alt kısım)
        0.02f,                                       // offsetX 
        0.02f,                                       // offsetY
        0.24f, 0.075f,                                // width, height
        1.0f,                                       // border thickness
        green);                                     // color

    // 4. Roll değerini yaz
    DrawCompassLabelDeepSeek(-0.025f, -largeLineLength * 0.75f - centerLineRaise, rollText);

    glPopMatrix();
}

void CHudSim::DrawCompassLabelDeepSeek2(float x, float y, const std::string& text) {
    // 1. Geçerli OpenGL durumunu kaydet
    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // 2. 2D çizim moduna geç
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 3. Metin özelliklerini ayarla
    glColor3f(1.0f, 1.0f, 1.0f); // Beyaz renk
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // 4. Koordinat dönüşümü (pencerenin merkezine göre)
    float screenX = windowWidth / 2 + x;
    float screenY = windowHeight / 2 + y;

    // 5. Metin genişliğini hesapla (Helvetica 12 için yaklaşık)
    float textWidth = text.length() * 9.0f;

    // 6. Metni ortalamak için pozisyon ayarla
    glRasterPos2f(screenX - textWidth / 2, screenY);

    // 7. Karakterleri render et
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // 8. OpenGL durumunu geri yükle
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

void CHudSim::DrawThrottleCompassDeepSeek1(float centerX, float centerY, float size, double throttle, float centerXGap, float centerYGap)
{
    const float compassHeight = size * 10.0f;
    const float valueToPixels = size / 25.0f; // Her 25 birimde 1 size
    const float bottomBound = -compassHeight / 2.0f;
    const float topBound = compassHeight / 2.0f;

    // Throttle değerini normalize et (0-1 arası)
    throttle = std::max(0.0, std::min(1.0, throttle));
    float throttleOffset = (1.0 - throttle) * 100 * valueToPixels; // Ters yönde kaydırma

    // Çizgi özellikleri
    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.5f;
    const float textOffsetX = -size * 0.6f; // Sol tarafa yaz
    const float lineOffsetX = -size * 0.4f; // Çizgiler sola kaymış

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // 1. Sabit yatay çizgiler ve etiketler
    glColor3f(0.0f, 1.0f, 0.0f); // Yeşil çizgiler
    for (int value = 0; value <= 100; value += 25) {
        float yPos = value * valueToPixels - throttleOffset;

        if (yPos < bottomBound || yPos > topBound) continue;

        
        // Ana çizgi (kalın)
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(lineOffsetX - largeLineLength, yPos);
        glVertex2f(lineOffsetX, yPos);
        glEnd();
        

        // Etiket (sol tarafa)
        std::string label = std::to_string(value);
        DrawCompassLabelDeepSeek(textOffsetX + 0.09f, yPos, label);

        // Ara çizgiler (5'li adımlarla)
        if (value < 100) {
            glLineWidth(1.0f);
            for (int sub = 5; sub < 25; sub += 5) {
                float subYPos = (value + sub) * valueToPixels - throttleOffset;
                if (subYPos < bottomBound || subYPos > topBound) continue;

                glBegin(GL_LINES);
                glVertex2f(lineOffsetX - shortLineLength, subYPos);
                glVertex2f(lineOffsetX, subYPos);
                glEnd();
            }
        }
    }

    
    // 2. Mevcut throttle göstergesi (dikey çizgi)
    /*glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // Beyaz
    glBegin(GL_LINES);
    glVertex2f(lineOffsetX, bottomBound);
    glVertex2f(lineOffsetX, topBound);
    glEnd();*/

    // 3. Mevcut değer göstergesi (kutu)
    std::string throttleText = std::to_string(static_cast<int>(throttle * 100)) + "%";
    float boxColor[3] = { 0.0f, 1.0f, 0.0f };
    /*DrawEmptyBox(
        lineOffsetX - largeLineLength / 2,
        0.0f,
        0.0f,
        0.0f,
        0.25f,
        0.07f,
        1.5f,
        boxColor
    );*/
    DrawCompassLabelDeepSeek(lineOffsetX - largeLineLength / 2, 0.0f, throttleText);

    glPopMatrix();
}

void CHudSim::DrawThrottleCompassDeepSeek2(float centerX, float centerY, float size, double throttle, float centerXGap, float centerYGap)
{
    const float compassHeight = size * 10.0f;
    const float valueToPixels = size / 25.0f; // Her 25 birimde 1 size
    const float bottomBound = -compassHeight / 2.0f;
    const float topBound = compassHeight / 2.0f;

    // Throttle değerini normalize et (0-1 arası)
    throttle = std::max(0.0, std::min(1.0, throttle));
    float throttleOffset = throttle * 100 * valueToPixels; // DÜZELTME: Artık pozitif yönde kaydırma

    // Çizgi özellikleri
    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.5f;
    const float textOffsetX = -size * 0.6f; // Sol tarafa yaz
    const float lineOffsetX = -size * 0.4f; // Çizgiler sola kaymış

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // 1. Sabit yatay çizgiler ve etiketler
    for (int value = 0; value <= 100; value += 25) {
        float yPos = value * valueToPixels - throttleOffset; // DÜZELTME: Doğru yönde kaydırma

        if (yPos < bottomBound || yPos > topBound) continue;

        // Eğer bu çizgi throttle değerine karşılık geliyorsa kırmızı yap
        bool isCurrentThrottleLine = (value == static_cast<int>(throttle * 100));

        if (isCurrentThrottleLine) {
            glColor3f(1.0f, 0.0f, 0.0f); // Kırmızı
            glLineWidth(3.0f); // Daha kalın çizgi
        }
        else {
            glColor3f(0.0f, 1.0f, 0.0f); // Yeşil
            glLineWidth(2.0f);
        }

        // Ana çizgi
        glBegin(GL_LINES);
        glVertex2f(lineOffsetX - largeLineLength, yPos);
        glVertex2f(lineOffsetX, yPos);
        glEnd();

        // Etiket (sol tarafa)
        std::string label = std::to_string(value);
        DrawCompassLabelDeepSeek(textOffsetX + 0.09f, yPos, label);

        // Ara çizgiler (5'li adımlarla)
        if (value < 100) {
            glLineWidth(1.0f);
            glColor3f(0.0f, 1.0f, 0.0f); // Yeşil
            for (int sub = 5; sub < 25; sub += 5) {
                float subYPos = (value + sub) * valueToPixels - throttleOffset;
                if (subYPos < bottomBound || subYPos > topBound) continue;

                // Ara çizgilerde de throttle çizgisini kontrol et
                if (value + sub == static_cast<int>(throttle * 100)) {
                    glColor3f(1.0f, 0.0f, 0.0f); // Kırmızı
                    glLineWidth(2.0f);
                }

                glBegin(GL_LINES);
                glVertex2f(lineOffsetX - shortLineLength, subYPos);
                glVertex2f(lineOffsetX, subYPos);
                glEnd();

                // Renk ve çizgi kalınlığını resetle
                if (value + sub == static_cast<int>(throttle * 100)) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glLineWidth(1.0f);
                }
            }
        }
    }

    // 3. Mevcut değer göstergesi (kutu)
    std::string throttleText = std::to_string(static_cast<int>(throttle * 100)) + "%";
    float boxColor[3] = { 1.0f, 0.0f, 0.0f }; // Kırmızı yap
    DrawCompassLabelDeepSeek(lineOffsetX - largeLineLength / 2, 0.0f, throttleText);

    glPopMatrix();
}

void CHudSim::DrawThrottleCompassDeepSeek(float centerX, float centerY, float size, double throttle, float centerXGap, float centerYGap)
{
    bool useDirectThrottleValue = true;

    static float arrowPosY = 0.f;

    const float compassHeight = size * 25.0f;
    const float valueToPixels = size / 25.0f;
    const float bottomBound = -compassHeight / 2.0f;
    const float topBound = compassHeight / 2.0f;
    const float lineSpacing = size * 0.05f;
    const float lineLength = size * 0.3f;

    // Throttle değerini normalize et (0-1 arası)
    throttle = std::max(0.0, std::min(1.0, throttle));

    // Kırmızı yapılacak değeri belirle
    int highlightValue;
    if (useDirectThrottleValue) {
        // Doğrudan throttle değerini kullan (0-100 arasında)
        highlightValue = static_cast<int>(throttle * 100 + 0.5f); // Daha doğru yuvarlama
    }
    else {
        // En yakın 5'in katını bul
        highlightValue = static_cast<int>(round(throttle * 20) * 5); // 0-20 arasına ölçeklendir
    }
    highlightValue = std::max(0, std::min(100, highlightValue));

    // Çizgi özellikleri
    const float shortLineLength = size * 0.1f;
    const float largeLineLength = size * 0.5f;
    const float textOffsetX = -size * 0.6f;
    const float lineOffsetX = -size * 0.4f;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);

    // 1. Sabit yatay çizgiler ve etiketler
    for (int value = 0; value <= 100; value += 25) {
        float yPos = value * valueToPixels;

        // Ana çizgi ve etiket
        bool isMainLineHighlighted = (value == highlightValue);        
        DrawCompassLine_(lineOffsetX, yPos, largeLineLength, isMainLineHighlighted, value);
        if (isMainLineHighlighted)
            arrowPosY = yPos;

        // Ara çizgiler (5'li adımlarla)
        if (value < 100) {
            for (int sub = 5; sub < 25; sub += 5) {
                float subYPos = (value + sub) * valueToPixels;
                if (subYPos < bottomBound || subYPos > topBound) continue;

                bool isSubLineHighlighted = ((value + sub) == highlightValue);
                DrawCompassLine_(lineOffsetX, subYPos, shortLineLength, isSubLineHighlighted);
            }
        }
    }

    // Mevcut değer göstergesi
    std::string throttleText = std::to_string(highlightValue) + "%";
    //DrawCompassLabelDeepSeek(lineOffsetX - largeLineLength / 2, 0.0f, throttleText);

    // Kırmızı işaretçi çizgisi (yatay)
    //DrawHorizontalIndicator_(lineOffsetX, largeLineLength);    
    // 
    // Hareketli ok işareti
    //DrawArrowIndicator(lineOffsetX, 0, size, throttle, bottomBound, topBound);
    // Ok çiz (merkez X, merkez Y, boyut, throttle, minY, maxY)
    DrawArrowIndicator(lineOffsetX, arrowPosY, size * 0.8f, throttle, bottomBound, topBound);

    glPopMatrix();
}

// Yardımcı fonksiyon: Çizgi çizme
void CHudSim::DrawCompassLine_(float lineOffsetX, float yPos, float length, bool isHighlighted, int value)
{
    if (isHighlighted) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(isHighlighted ? 3.0f : 2.0f);
    }
    else {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(2.0f);
    }

    glBegin(GL_LINES);
    glVertex2f(lineOffsetX - length, yPos);
    glVertex2f(lineOffsetX, yPos);
    glEnd();

    // Etiket (sadece ana çizgiler için)
    if (value >= 0) {
        std::string label = std::to_string(value);
        //DrawCompassLabelDeepSeek(textOffsetX + 0.09f, yPos, label);
    }
}

// Yardımcı fonksiyon: Yatay işaretçi çizgisi
void CHudSim::DrawHorizontalIndicator_(float lineOffsetX, float length)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(lineOffsetX - length, 0);
    glVertex2f(lineOffsetX, 0);
    glEnd();
}

// Yeni yardımcı fonksiyon: "<" şeklinde ok çizer
void CHudSim::DrawArrowIndicator(float x, float y, float size, double throttle, float minY, float maxY, float thickness)
{
    // Throttle değerini [0,1] aralığına kesinlikle sınırla
    throttle = std::max(0.0, std::min(1.0, throttle));

    // Y pozisyonunu doğru şekilde hesapla (throttle=0 en altta, throttle=1 en üstte)
    float yPos = y + minY + (maxY - minY) * (1.0f - static_cast<float>(throttle));
    yPos = -yPos;

    // Hata ayıklama için koordinat kontrolü
    //assert(yPos >= (baseY + minY) && yPos <= (baseY + maxY));

    const float arrowSize = size * 0.15f;
    const float lineLength = size * 0.3f;

    // Renk ayarı (kırmızı -> turuncu gradiyan)
    glColor3f(1.0f, 1.0f - static_cast<float>(throttle), 0.0f);
    glLineWidth(thickness);

    glBegin(GL_LINES);
    bool pointingRight = (throttle > 0.5);

    if (pointingRight) {
        // Sağa bakan ok
        glVertex2f(x, yPos);
        glVertex2f(x + lineLength, yPos);
        glVertex2f(x + lineLength - arrowSize, yPos - arrowSize);
        glVertex2f(x + lineLength, yPos);
        glVertex2f(x + lineLength - arrowSize, yPos + arrowSize);
        glVertex2f(x + lineLength, yPos);
    }
    else {
        // Sola bakan ok
        glVertex2f(x, yPos);
        glVertex2f(x - lineLength, yPos);
        glVertex2f(x - lineLength + arrowSize, yPos - arrowSize);
        glVertex2f(x - lineLength, yPos);
        glVertex2f(x - lineLength + arrowSize, yPos + arrowSize);
        glVertex2f(x - lineLength, yPos);
    }
    glEnd();
}
