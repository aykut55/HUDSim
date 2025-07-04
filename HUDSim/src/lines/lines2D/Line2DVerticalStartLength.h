#ifndef Line2DVerticalStartLengthH
#define Line2DVerticalStartLengthH

#include "Line3DVerticalStartLength.h"

class CLine2DVerticalStartLength : public CLine3DVerticalStartLength
{
public:
    virtual ~CLine2DVerticalStartLength() {}
             CLine2DVerticalStartLength() { startZ = 0.f; }

    void SetStartZ(float val) { startZ = 0.f; }
    float GetStartZ() const { return 0.f; }

    void CalculateEndpoint() {
        x1 = startX;
        y1 = startY;
        z1 = 0.f;

        x2 = startX;
        y2 = startY + length;
        z2 = 0.f;
    }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine2DVerticalStartLength*>(this)->CalculateEndpoint();

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
