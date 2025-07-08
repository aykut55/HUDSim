#ifndef Line3DCenteredH
#define Line3DCenteredH

#include "Line3D.h"

class CLine3DCentered : public CLine3D
{
public:
    virtual ~CLine3DCentered() {}
             CLine3DCentered() {}

    // Getters/Setters for center and rotation
    float GetCenterX() const { return centerX; }
    float GetCenterY() const { return centerY; }
    float GetCenterZ() const { return centerZ; }
    float GetLengthParam() const { return length; }
    float GetRotationAngle() const { return rotationAngle; }

    void SetCenterX(float val) { centerX = val; }
    void SetCenterY(float val) { centerY = val; }
    void SetCenterZ(float val) { centerZ = val; }
    void SetLength(float val) { length = val; }
    void SetRotationAngle(float angle) { rotationAngle = angle; }

    void IncreaseRotation(float deltaAngle) {
        rotationAngle += deltaAngle;
        if (rotationAngle >= 360.f) rotationAngle -= 360.f;
        else if (rotationAngle < 0.f) rotationAngle += 360.f;
    }

    void DecreaseRotation(float deltaAngle) {
        IncreaseRotation(-deltaAngle);
    }

    float GetRotationRadians() const {
        return rotationAngle * 3.14159265f / 180.f;
    }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        float rad = GetRotationRadians();

        x1 = centerX - halfLen * std::cos(rad);
        y1 = centerY - halfLen * std::sin(rad);
        z1 = centerZ;

        x2 = centerX + halfLen * std::cos(rad);
        y2 = centerY + halfLen * std::sin(rad);
        z2 = centerZ;
    }

    // Override getters
    float GetX1() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return x1; }
    float GetY1() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return y1; }
    float GetZ1() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return z1; }
    float GetX2() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return x2; }
    float GetY2() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return y2; }
    float GetZ2() const override { const_cast<CLine3DCentered*>(this)->CalculateEndpoints(); return z2; }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine3DCentered*>(this)->CalculateEndpoints();

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
    float rotationAngle = 0.0f; // degrees (around Z-axis)

private:

};

#endif
