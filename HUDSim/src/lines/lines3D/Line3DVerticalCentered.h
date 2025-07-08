#ifndef Line3DVerticalCenteredH
#define Line3DVerticalCenteredH

#include "Line3DVertical.h"

class CLine3DVerticalCentered : public CLine3DVertical
{
public:
    virtual ~CLine3DVerticalCentered() {}
             CLine3DVerticalCentered() {}

    void SetCenterX(float val) { centerX = val; }
    void SetCenterY(float val) { centerY = val; }
    void SetCenterZ(float val) { centerZ = val; }
    void SetLength(float val) { length = val; }
    void SetRotationAngle(float angle) { rotationAngle = angle; }

    float GetCenterX() const { return centerX; }
    float GetCenterY() const { return centerY; }
    float GetCenterZ() const { return centerZ; }
    float GetLengthParam() const { return length; }
    float GetRotationAngle() const { return rotationAngle; }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        // Rotation ignored for vertical, Y axis direction
        x1 = centerX;
        y1 = centerY - halfLen;
        z1 = centerZ;

        x2 = centerX;
        y2 = centerY + halfLen;
        z2 = centerZ;
    }

    float GetX1() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return x1; }
    float GetY1() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return y1; }
    float GetZ1() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return z1; }
    float GetX2() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return x2; }
    float GetY2() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return y2; }
    float GetZ2() const override { const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints(); return z2; }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine3DVerticalCentered*>(this)->CalculateEndpoints();

        glPushMatrix();
        glLineWidth(width);
        glColor4f(color.r, color.g, color.b, color.a);

        if (solid) glDisable(GL_LINE_STIPPLE);
        else {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }

        glBegin(GL_LINES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0f);
        glPopMatrix();
    }

protected:
    float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
    float length = 1.0f;
    float rotationAngle = 0.0f; // can be used if needed

private:

};

#endif
