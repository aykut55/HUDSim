#ifndef Line2DStartLengthH
#define Line2DStartLengthH

#include "Line3DStartLength.h"

class CLine2DStartLength : public CLine3DStartLength
{
public:
    virtual ~CLine2DStartLength() {}
             CLine2DStartLength() { startZ = 0.f; }

    void SetStartZ(float val) { startZ = 0.f; }
    float GetStartZ() const { return 0.f; }

    void CalculateEndpoint() {
        float rad = GetRotationRadians();

        x1 = startX;
        y1 = startY;
        z1 = 0.f;

        x2 = startX + length * std::cos(rad);
        y2 = startY + length * std::sin(rad);
        z2 = 0.f;
    }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine2DStartLength*>(this)->CalculateEndpoint();

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
