#ifndef Line2DCenteredH
#define Line2DCenteredH

#include "Line3DCentered.h"

class CLine2DCentered : public CLine3DCentered
{
public:
    virtual ~CLine2DCentered() {}
             CLine2DCentered() { centerZ = 0.f; }

    void SetCenterZ(float val) { centerZ = 0.f; }
    float GetCenterZ() const { return 0.f; }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        float rad = GetRotationRadians();

        x1 = centerX - halfLen * std::cos(rad);
        y1 = centerY - halfLen * std::sin(rad);
        z1 = 0.f;

        x2 = centerX + halfLen * std::cos(rad);
        y2 = centerY + halfLen * std::sin(rad);
        z2 = 0.f;
    }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine2DCentered*>(this)->CalculateEndpoints();

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
