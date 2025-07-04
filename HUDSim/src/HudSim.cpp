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

    // horizon ana çizgisi
    //DrawHorizonLine(0.0f, 0.0f, 1.1f);

    // Pitch ladder güncel pitchDeg ile çizilir
    DrawPitchLadder(0.0f, 0.0f, 1.0f, rollDeg, pitchDeg);
    DrawRollText(-0.8f, 0.8f, rollDeg);
    DrawPitchText(-0.8f, 0.6f, pitchDeg);
    DrawYawText(-0.8f, 0.4f, yawDeg);


    DrawSideVerticalLines(0.0f, 0.0f, 1.6f, 0.6f);

    DrawRightSideIndicators(0.0f, 0.0f, 1.6f, 0.6f);
    DrawRightSideCaretIndicator(0.0f, 0.0f, 1.1f, 0.60f, -0.65f, 0.0f);

    DrawSpeedIndicator(-0.8f, 0.2f, 0.1f, 0.05f);
    DrawSpeedText(-0.8f, 0.2f, 50.f);

    // Sağ tarafa kutu ve yazı çizmek için örnek koordinatlar
    float x = 0.8f;   // sağ kenar civarı
    float y = 0.2f;
    float width = 0.1f;
    float height = 0.05f;
    int altValue = 150;

    DrawAltIndicatorBox(x, y, width, height);
    DrawAltText(x, y, altValue);

    DrawTargetBox(0.5f, 0.0f, 0.1f, 142);

    DrawCompass(0.0f, 0.7f, 0.6f, yawDeg);

    // merkez metni
    //DrawCenteredText(0.0f, 0.0f, "CENTER");
/*
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
    centered2DLine->Draw();

    auto startLength2DLine = std::make_unique<CLine2DStartLength>();    
    startLength2DLine->SetStartX(-0.5f);
    startLength2DLine->SetStartY(-0.5f);
    startLength2DLine->SetLength(1.2f);
    startLength2DLine->SetRotationAngle(30.0f);
    startLength2DLine->SetColor(1.0f, 1.0f, 0.0f); // sarı
    startLength2DLine->Draw();
*/
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

    // soldaki küçük ok (sağa bakan okun tersi)
    glBegin(GL_LINES);
    glVertex2f(x, y - height / 2.0f);
    glVertex2f(x - 0.02f, y - height / 2.0f + 0.01f);

    glVertex2f(x, y - height / 2.0f);
    glVertex2f(x - 0.02f, y - height / 2.0f - 0.01f);
    glEnd();
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
/*
    float textOffset = 0.015f;
    glRasterPos2f(x - 0.01f, centerY + lineHeight + textOffset);
    for (const char* c = txt; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
*/
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
    std::string label = "Pitch";
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
    std::string label = "Roll";
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
    std::string label = "Yaw";
    for (char c : label)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    // değer (sayısal)
    char txt[8];
    sprintf(txt, "%d", yawValue);
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

}

void CHudSim::DecreaseThrottle(double step)
{

}