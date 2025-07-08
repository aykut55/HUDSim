#ifndef Line2DStartLengthH
#define Line2DStartLengthH

#include "Line3DStartLength.h"

class CLine2DStartLength : public CLine3DStartLength
{
public:
    virtual ~CLine2DStartLength() {}
             CLine2DStartLength() { startZ = 0.f; }
             CLine2DStartLength(float startX = 0.f, float startY = 0.f,
                 float length = 1.f,
                 float rotationAngle = 0.f,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
             {
                 this->startX = startX;
                 this->startY = startY;
                 this->startZ = 0.f;
                 this->length = length;
                 this->rotationAngle = rotationAngle;
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

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
