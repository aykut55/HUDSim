#ifndef Line2DHorizontalCenteredH
#define Line2DHorizontalCenteredH

#include "Line3DHorizontalCentered.h"

class CLine2DHorizontalCentered : public CLine3DHorizontalCentered
{
public:
    virtual ~CLine2DHorizontalCentered() {}
             CLine2DHorizontalCentered() { centerZ = 0.f; }

    void SetCenterZ(float val) { centerZ = 0.f; }
    float GetCenterZ() const { return 0.f; }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        float rad = GetRotationRadians();

        x1 = centerX - halfLen * std::cos(rad);
        y1 = centerY;
        z1 = 0.f;

        x2 = centerX + halfLen * std::cos(rad);
        y2 = centerY;
        z2 = 0.f;
    }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine2DHorizontalCentered*>(this)->CalculateEndpoints();

        glPushMatrix();
        glLineWidth(width);
        glColor4f(color.r, color.g, color.b, color.a);

        if (solid) glDisable(GL_LINE_STIPPLE);
        else {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        glBegin(GL_LINES);
        glVertex2f(x1 * scale, y1 * scale);
        glVertex2f(x2 * scale, y2 * scale);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0f);
        glPopMatrix();
    }
protected:

private:
};

#endif
