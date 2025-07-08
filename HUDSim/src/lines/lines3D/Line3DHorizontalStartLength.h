#ifndef Line3DHorizontalStartLengthH
#define Line3DHorizontalStartLengthH

#include "Line3DHorizontal.h"

class CLine3DHorizontalStartLength : public CLine3DHorizontal
{
public:
    virtual ~CLine3DHorizontalStartLength() {}
             CLine3DHorizontalStartLength() : startX(0), startY(0), startZ(0), length(1.f), rotationAngle(0.f) {}
             CLine3DHorizontalStartLength(float startX, float startY, float startZ,
                 float length,
                 float rotationAngle,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
                 : startX(startX), startY(startY), startZ(startZ),
                 length(length), rotationAngle(rotationAngle)
             {
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

    void SetStartX(float val) { startX = val; }
    void SetStartY(float val) { startY = val; }
    void SetStartZ(float val) { startZ = val; }
    void SetLength(float val) { length = val; }
    void SetRotationAngle(float angle) { rotationAngle = angle; }

    float GetStartX() const { return startX; }
    float GetStartY() const { return startY; }
    float GetStartZ() const { return startZ; }
    float GetLengthParam() const { return length; }
    float GetRotationAngle() const { return rotationAngle; }

    float GetRotationRadians() const {
        return rotationAngle * 3.14159265f / 180.0f;
    }

    void CalculateEndpoint() {
        float rad = GetRotationRadians();

        x1 = startX;
        y1 = startY;
        z1 = startZ;

        x2 = startX + length * std::cos(rad);
        y2 = startY;
        z2 = startZ;
    }

    float GetX1() const override { const_cast<CLine3DHorizontalStartLength*>(this)->CalculateEndpoint(); return x1; }
    float GetY1() const override { return y1; }
    float GetZ1() const override { return z1; }
    float GetX2() const override { const_cast<CLine3DHorizontalStartLength*>(this)->CalculateEndpoint(); return x2; }
    float GetY2() const override { return y2; }
    float GetZ2() const override { return z2; }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine3DHorizontalStartLength*>(this)->CalculateEndpoint();

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
    float rotationAngle = 0.0f;

private:

};

#endif
