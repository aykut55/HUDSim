#ifndef Line2DHorizontalH
#define Line2DHorizontalH

#include "Line3DHorizontal.h"

class CLine2DHorizontal : public CLine3DHorizontal
{
public:
    virtual ~CLine2DHorizontal() {}
             CLine2DHorizontal() { z1 = 0.f; z2 = 0.f; }

    void SetZ1(float val) override { z1 = 0.f; }
    void SetZ2(float val) override { z2 = 0.f; }
    float GetZ1() const override { return 0.f; }
    float GetZ2() const override { return 0.f; }

    void Draw() const override {
        if (!visible) return;

        glPushMatrix();
        glLineWidth(width);
        glColor4f(color.r, color.g, color.b, color.a);

        if (solid) glDisable(GL_LINE_STIPPLE);
        else {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0f);
        glPopMatrix();
    }

protected:

private:
};

#endif
