#ifndef Line2DVerticalCenteredH
#define Line2DVerticalCenteredH

#include "Line3DVerticalCentered.h"

class CLine2DVerticalCentered : public CLine3DVerticalCentered
{
public:
    virtual ~CLine2DVerticalCentered() {}
             CLine2DVerticalCentered() { centerZ = 0.f; }
             CLine2DVerticalCentered(float centerX = 0.f, float centerY = 0.f,
                 float length = 1.f,
                 float rotationAngle = 0.f,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
             {
                 this->centerX = centerX;
                 this->centerY = centerY;
                 this->centerZ = 0.f;
                 this->length = length;
                 this->rotationAngle = rotationAngle;
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

    void SetCenterZ(float val) { centerZ = 0.f; }
    float GetCenterZ() const { return 0.f; }

    void CalculateEndpoints() {
        float halfLen = length / 2.f;
        // Rotation ignored for vertical, Y axis direction
        x1 = centerX;
        y1 = centerY - halfLen;
        z1 = 0.f;

        x2 = centerX;
        y2 = centerY + halfLen;
        z2 = 0.f;
    }

    void Draw() const override {
        if (!visible) return;
        const_cast<CLine2DVerticalCentered*>(this)->CalculateEndpoints();

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
