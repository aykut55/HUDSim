#ifndef Line3DHorizontalCenteredH
#define Line3DHorizontalCenteredH

#include "Line3DHorizontal.h"

class CLine3DHorizontalCentered : public CLine3DHorizontal
{
public:
    virtual ~CLine3DHorizontalCentered() {}
             CLine3DHorizontalCentered() : centerX(0), centerY(0), centerZ(0), length(1.f), rotationAngle(0.f) {}
             CLine3DHorizontalCentered(float centerX, float centerY, float centerZ,
                 float length,
                 float rotationAngle,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
                 : centerX(centerX), centerY(centerY), centerZ(centerZ),
                 length(length), rotationAngle(rotationAngle)
             {
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

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

    float GetRotationRadians() const {
        return rotationAngle * 3.14159265f / 180.0f;
    }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        float rad = GetRotationRadians();

        x1 = centerX - halfLen * std::cos(rad);
        y1 = centerY;
        z1 = centerZ;

        x2 = centerX + halfLen * std::cos(rad);
        y2 = centerY;
        z2 = centerZ;
    }

    float GetX1() const override { const_cast<CLine3DHorizontalCentered*>(this)->CalculateEndpoints(); return x1; }
    float GetY1() const override { return y1; }
    float GetZ1() const override { return z1; }
    float GetX2() const override { const_cast<CLine3DHorizontalCentered*>(this)->CalculateEndpoints(); return x2; }
    float GetY2() const override { return y2; }
    float GetZ2() const override { return z2; }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine3DHorizontalCentered*>(this)->CalculateEndpoints();

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
    float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
    float length = 1.0f;
    float rotationAngle = 0.0f; // degrees (rotation around Z)

private:

};

#endif
