#include "MyHudSim.h"

MyHudSim::MyHudSim(int argc, char** argv)
    : CHudSimExt(argc, argv)
{
}

void MyHudSim::OnInitialize()
{
    std::cout << "OpenGL HUD Başlatıldı." << std::endl;
    // Başlangıç ayarları burada yapılabilir
}

void MyHudSim::DrawDemo(int choice)
{
    // Yeşil çizgi çizimi
    glColor3f(0.f, 1.f, 0.f);

    // Pencere orta noktası (örnek)
    float centerX = 400.f;
    float centerY = 300.f;

    if (choice == 0)
    {
        // 1) Yatay çizgi: Centered versiyon (merkez + uzunluk + rotasyon)
        auto pLine2DHorizontalCentered = std::make_unique<CLine2DHorizontalCentered>(
            centerX,          // centerX
            centerY,          // centerY
            300.f,            // length (300 px genişlik)
            0.f,              // rotationAngle (0 derece, yatay)
            Color(0.f, 1.f, 0.f, 1.f), // yeşil
            2.f,              // line width
            true,             // solid
            true,             // visible
            1.f               // scale
        );
        pLine2DHorizontalCentered->Draw();

        // 2) Dikey çizgi: Centered versiyon (merkez + uzunluk + rotasyon)
        auto pLine2DVerticalCentered = std::make_unique<CLine2DVerticalCentered>(
            centerX,          // centerX
            centerY,          // centerY
            200.f,            // length (200 px yükseklik)
            0.f,              // rotationAngle (dikey için 0, çünkü sabit dikey)
            Color(1.f, 0.f, 0.f, 1.f), // kırmızı
            2.f,              // line width
            true,             // solid
            true,             // visible
            1.f               // scale
        );
        pLine2DVerticalCentered->Draw();
    }
    else if (choice == 1)
    {
        // 3) Yatay çizgi: StartLength (Başlangıç + uzunluk + rotasyon)
        auto pLine2DHorizontalStartLength = std::make_unique<CLine2DHorizontalStartLength>(
            centerX,       // startX
            centerY,       // startY
            300.f,         // length
            0.f,           // rotationAngle (0 derece yatay)
            Color(0.f, 1.f, 0.f, 1.f), // yeşil
            2.f,           // kalınlık
            true,          // solid
            true,          // görünür
            1.f            // scale
        );
        pLine2DHorizontalStartLength->Draw();

        // 4) Dikey çizgi: StartLength (Başlangıç + uzunluk + rotasyon)
        auto pLine2DVerticalStartLength = std::make_unique<CLine2DVerticalStartLength>(
            centerX,       // startX
            centerY,       // startY
            200.f,         // length
            0.f,           // rotationAngle (dikeyde genelde 0 kullanılır)
            Color(1.f, 0.f, 0.f, 1.f), // kırmızı
            2.f,           // kalınlık
            true,          // solid
            true,          // görünür
            1.f            // scale
        );
        pLine2DVerticalStartLength->Draw();
    }
    else if (choice == 2)
    {
        // 5) Yatay çizgi: sol ve sağ uç noktalar
        auto pLine2DHorizontal = std::make_unique<CLine2DHorizontal>(
            centerX - 150.f, centerY,    // x1, y1 (sol uç)
            centerX + 150.f, centerY,    // x2, y2 (sağ uç)
            Color(0.f, 1.f, 0.f, 1.f),   // yeşil
            2.f,                        // kalınlık
            true,                       // solid
            true,                       // görünür
            1.f                         // scale
        );
        pLine2DHorizontal->Draw();

        // 6) Dikey çizgi: alt ve üst uç noktalar
        auto pLine2DVertical = std::make_unique<CLine2DVertical>(
            centerX, centerY - 100.f,    // x1, y1 (alt uç)
            centerX, centerY + 100.f,    // x2, y2 (üst uç)
            Color(1.f, 0.f, 0.f, 1.f),   // kırmızı
            2.f,                        // kalınlık
            true,                       // solid
            true,                       // görünür
            1.f                         // scale
        );
        pLine2DVertical->Draw();
    }

    /*
    auto pLine2DHorizontal = std::make_unique<CLine2DHorizontal>();
    auto pLine2DHorizontalCentered = std::make_unique<CLine2DHorizontalCentered>();
    auto pLine2DHorizontalStartLength = std::make_unique<CLine2DHorizontalStartLength>();

    auto pLine2DVertical = std::make_unique<CLine2DVertical>();
    auto pLine2DVerticalCentered = std::make_unique<CLine2DVerticalCentered>();
    auto pLine2DVerticalStartLength = std::make_unique<CLine2DVerticalStartLength>();
    */
}

void MyHudSim::Draw()
{
    // Yeşil çizgi çizimi
    glColor3f(0.f, 1.f, 0.f);

    // Pencere orta noktası (örnek)
    float centerX = static_cast<float>(m_width) / 2.0f;     // Ekran genişliğinin yarısı (örnek)
    float centerY = static_cast<float>(m_height) / 2.0f;    // Ekran yüksekliğinin yarısı (örnek)
    float size = 5.0f;                                      // Ölçek

    //DrawPlus(centerX, centerY, 200);

    // ortadaki w marker
    this->DrawCentralWMarker(centerX, centerY, size = 5.0f);

    rollDeg = 0;
    pitchDeg = 0;
    this->DrawPitchLadder(centerX, centerY, size = 105.0f, rollDeg, pitchDeg);

    //glutSwapBuffers();
}

void MyHudSim::OnKeyboard(unsigned char key, int x, int y)
{
    if (key == 27) // ESC tuşu
    {
        std::cout << "ESC ile çıkılıyor." << std::endl;
        exit(0);
    }
}

void MyHudSim::OnSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        std::cout << "Yukarı ok tuşuna basıldı." << std::endl;
        break;

    case GLUT_KEY_DOWN:
        std::cout << "Aşağı ok tuşuna basıldı." << std::endl;
        break;

    case GLUT_KEY_LEFT:
        std::cout << "Sol ok tuşuna basıldı." << std::endl;
        break;

    case GLUT_KEY_RIGHT:
        std::cout << "Sağ ok tuşuna basıldı." << std::endl;
        break;

    case GLUT_KEY_F1:
        std::cout << "F1 tuşuna basıldı." << std::endl;
        break;

    default:
        std::cout << "Başka özel tuşa basıldı: " << key << std::endl;
        break;
    }
}

void MyHudSim::OnTimer(int value)
{
    glutPostRedisplay(); // Sürekli yenile
}

void MyHudSim::OnUpdate(float deltaTime)
{
    // Oyun veya simülasyon mantığı burada güncellenir
}

void MyHudSim::DrawPlus(float centerX, float centerY, float size)
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

void MyHudSim::DrawCentralWMarker(float centerX, float centerY, float size)
{
    // 56
    float shiftX = -2.f;  // Sağa kaydırma miktarı
    float shiftY = -2.f;   // Aşağı kaydırma miktarı

    glPushMatrix();

    // Önce center noktasına taşı, sonra ek kaydırma yap, sonra scale uygula
    glTranslatef(centerX + shiftX, centerY + shiftY, 0);
    glScalef(size, size, 1.0);
    glTranslatef(-(centerX + shiftX), -(centerY + shiftY), 0);

    glColor4f(0.f, 1.f, 0.f, 1.f);
    glLineWidth(2.f);

    auto pLine2DHorizontalStartLength1 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 8, centerY - 1.85f, 4.f);
    pLine2DHorizontalStartLength1->Draw();

    auto pLine2DHorizontalStartLength2 = std::make_unique<CLine2DHorizontalStartLength>(centerX, centerY - 1.85f, 4.f);
    pLine2DHorizontalStartLength2->Draw();
    float l = pLine2DHorizontalStartLength2->GetLength();

    glBegin(GL_LINE_STRIP);
    //glVertex2f(centerX - 12.f, centerY - 1.85f);

    glVertex2f(centerX - 4.f, centerY - 1.85f);    
    glVertex2f(centerX - 3.f, centerY);
    glVertex2f(centerX - 2.f, centerY - 1.85f);
    glVertex2f(centerX - 1.f, centerY);

    glVertex2f(centerX - 0.f, centerY - 1.85f);

    //glVertex2f(centerX + 8.f, centerY - 1.85f);

    glEnd();

    glPopMatrix();
}

void MyHudSim::DrawPitchLadder(float centerX, float centerY, float size, double rollDeg, double pitchDeg)
{
    glPushMatrix();

    // center etrafında rollDeg kadar döndür
    glTranslatef(centerX, centerY, 0.0f);
    //glRotatef(static_cast<float>(-rollDeg), 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerX, -centerY, 0.0f);

    glColor4f(0.f, 1.f, 0.f, 1.f);
    glLineWidth(2.f);

    // Metin yazısı
    char txt[8];
    if (pitchDeg > 0)
        sprintf(txt, "+%d", (int)pitchDeg);
    else
        sprintf(txt, "%d", (int)pitchDeg);

    {
        // ZeroLine
        auto pLine2DHorizontalStartLength1 = std::make_unique<CLine2DHorizontalStartLength>(centerX + 60.f, centerY - 1.f, size);
        pLine2DHorizontalStartLength1->Draw();

        auto pLine2DVerticalStartLength11 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength1->GetX2(), pLine2DHorizontalStartLength1->GetY2(), 10.f);
        pLine2DVerticalStartLength11->Draw();

        sprintf(txt, "%d", (int)pitchDeg);

        glRasterPos2f(pLine2DHorizontalStartLength1->GetX2() + 15, pLine2DHorizontalStartLength1->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // +5
        auto pLine2DHorizontalStartLength2 = std::make_unique<CLine2DHorizontalStartLength>(centerX + 60.f, centerY - 75.f, size);
        pLine2DHorizontalStartLength2->SetSolid(false);
        pLine2DHorizontalStartLength2->Draw();

        auto pLine2DVerticalStartLength21 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength2->GetX2(), pLine2DHorizontalStartLength2->GetY2(), 10.f);
        pLine2DVerticalStartLength21->Draw();

        sprintf(txt, "%d", (int)pitchDeg + 5);
        
        glRasterPos2f(pLine2DHorizontalStartLength2->GetX2() + 15, pLine2DHorizontalStartLength2->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // +10
        auto pLine2DHorizontalStartLength3 = std::make_unique<CLine2DHorizontalStartLength>(centerX + 60.f, centerY - 150.f, size);
        pLine2DHorizontalStartLength3->SetSolid(false);
        pLine2DHorizontalStartLength3->Draw();

        auto pLine2DVerticalStartLength31 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength3->GetX2(), pLine2DHorizontalStartLength3->GetY2(), 10.f);
        pLine2DVerticalStartLength31->Draw();

        sprintf(txt, "%d", (int)pitchDeg + 10);

        glRasterPos2f(pLine2DHorizontalStartLength3->GetX2() + 15, pLine2DHorizontalStartLength3->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // -5
        auto pLine2DHorizontalStartLength4 = std::make_unique<CLine2DHorizontalStartLength>(centerX + 60.f, centerY + 75.f, size);
        pLine2DHorizontalStartLength4->SetSolid(false);
        pLine2DHorizontalStartLength4->Draw();

        auto pLine2DVerticalStartLength41 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength4->GetX2(), pLine2DHorizontalStartLength4->GetY2(), -10.f);
        pLine2DVerticalStartLength41->Draw();

        sprintf(txt, "%d", (int)pitchDeg - 5);

        glRasterPos2f(pLine2DHorizontalStartLength4->GetX2() + 10, pLine2DHorizontalStartLength4->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // -10
        auto pLine2DHorizontalStartLength5 = std::make_unique<CLine2DHorizontalStartLength>(centerX + 60.f, centerY + 150.f, size);
        pLine2DHorizontalStartLength5->SetSolid(false);
        pLine2DHorizontalStartLength5->Draw();

        auto pLine2DVerticalStartLength51 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength5->GetX2(), pLine2DHorizontalStartLength5->GetY2(), -10.f);
        pLine2DVerticalStartLength51->Draw();

        sprintf(txt, "%d", (int)pitchDeg - 10);

        glRasterPos2f(pLine2DHorizontalStartLength5->GetX2() + 10, pLine2DHorizontalStartLength5->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    {
        // ZeroLine
        auto pLine2DHorizontalStartLength1 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 163.f, centerY - 1.f, size);
        pLine2DHorizontalStartLength1->Draw();

        auto pLine2DVerticalStartLength11 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength1->GetX2() - pLine2DHorizontalStartLength1->GetLength(), pLine2DHorizontalStartLength1->GetY2(), 10.f);
        pLine2DVerticalStartLength11->Draw();

        sprintf(txt, "%d", (int)pitchDeg);

        glRasterPos2f(pLine2DHorizontalStartLength1->GetX2() - pLine2DHorizontalStartLength1->GetLength() - 20, pLine2DHorizontalStartLength1->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // +5
        auto pLine2DHorizontalStartLength2 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 163.f, centerY - 75.f, size);
        pLine2DHorizontalStartLength2->SetSolid(false);
        pLine2DHorizontalStartLength2->Draw();

        auto pLine2DVerticalStartLength21 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength2->GetX2() - pLine2DHorizontalStartLength2->GetLength(), pLine2DHorizontalStartLength2->GetY2(), 10.f);
        pLine2DVerticalStartLength21->Draw();

        sprintf(txt, "%d", (int)pitchDeg + 5);

        glRasterPos2f(pLine2DHorizontalStartLength2->GetX2() - pLine2DHorizontalStartLength2->GetLength() - 20, pLine2DHorizontalStartLength2->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // +10
        auto pLine2DHorizontalStartLength3 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 163.f, centerY - 150.f, size);
        pLine2DHorizontalStartLength3->SetSolid(false);
        pLine2DHorizontalStartLength3->Draw();

        auto pLine2DVerticalStartLength31 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength3->GetX2() - pLine2DHorizontalStartLength3->GetLength(), pLine2DHorizontalStartLength3->GetY2(), 10.f);
        pLine2DVerticalStartLength31->Draw();

        sprintf(txt, "%d", (int)pitchDeg + 10);

        glRasterPos2f(pLine2DHorizontalStartLength3->GetX2() - pLine2DHorizontalStartLength3->GetLength() - 20, pLine2DHorizontalStartLength3->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // -5
        auto pLine2DHorizontalStartLength4 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 163.f, centerY + 75.f, size);
        pLine2DHorizontalStartLength4->SetSolid(false);
        pLine2DHorizontalStartLength4->Draw();

        auto pLine2DVerticalStartLength41 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength4->GetX2() - pLine2DHorizontalStartLength4->GetLength(), pLine2DHorizontalStartLength4->GetY2(), -10.f);
        pLine2DVerticalStartLength41->Draw();

        sprintf(txt, "%d", (int)pitchDeg - 5);

        glRasterPos2f(pLine2DHorizontalStartLength4->GetX2() - pLine2DHorizontalStartLength4->GetLength() - 30, pLine2DHorizontalStartLength4->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

        // -10
        auto pLine2DHorizontalStartLength5 = std::make_unique<CLine2DHorizontalStartLength>(centerX - 163.f, centerY + 150.f, size);
        pLine2DHorizontalStartLength5->SetSolid(false);
        pLine2DHorizontalStartLength5->Draw();

        auto pLine2DVerticalStartLength51 = std::make_unique<CLine2DVerticalStartLength>(pLine2DHorizontalStartLength5->GetX2() - pLine2DHorizontalStartLength5->GetLength(), pLine2DHorizontalStartLength5->GetY2(), -10.f);
        pLine2DVerticalStartLength51->Draw();

        sprintf(txt, "%d", (int)pitchDeg - 10);

        glRasterPos2f(pLine2DHorizontalStartLength5->GetX2() - pLine2DHorizontalStartLength5->GetLength() - 30, pLine2DHorizontalStartLength5->GetY2() + 10);
        for (const char* c = txt; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }

    glPopMatrix();
}