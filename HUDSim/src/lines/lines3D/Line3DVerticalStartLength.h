#ifndef Line3DVerticalStartLengthH
#define Line3DVerticalStartLengthH

#include "Line3DVertical.h"

class CLine3DVerticalStartLength : public CLine3DVertical
{
public:
    virtual ~CLine3DVerticalStartLength() {}
             CLine3DVerticalStartLength() {}

    void SetStartX(float val) { startX = val; }
    void SetStartY(float val) { startY = val; }
    void SetStartZ(float val) { startZ = val; }
    void SetLength(float val) { length = val; }

    float GetStartX() const { return startX; }
    float GetStartY() const { return startY; }
    float GetStartZ() const { return startZ; }
    float GetLengthParam() const { return length; }

    void CalculateEndpoint() {
        x1 = startX;
        y1 = startY;
        z1 = startZ;

        x2 = startX;
        y2 = startY + length;
        z2 = startZ;
    }

    float GetX1() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return x1; }
    float GetY1() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return y1; }
    float GetZ1() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return z1; }
    float GetX2() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return x2; }
    float GetY2() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return y2; }
    float GetZ2() const override { const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint(); return z2; }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine3DVerticalStartLength*>(this)->CalculateEndpoint();

        glPushMatrix();
        glLineWidth(width);
        glColor4f(color.r, color.g, color.b, color.a);

        if (solid) glDisable(GL_LINE_STIPPLE);
        else {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        glBegin(GL_LINES);
        glVertex3f(x1 * scale, y1 * scale, z1 * scale);
        glVertex3f(x2 * scale, y2 * scale, z2 * scale);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0f);
        glPopMatrix();
    }
protected:
    float startX = 0.0f, startY = 0.0f, startZ = 0.0f;
    float length = 1.0f;

private:

};

#endif
