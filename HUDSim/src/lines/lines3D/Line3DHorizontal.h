#ifndef Line3DHorizontalH
#define Line3DHorizontalH

#include "Line3D.h"

class CLine3DHorizontal : public CLine3D
{
public:
    virtual ~CLine3DHorizontal() {}
             CLine3DHorizontal() {}
             CLine3DHorizontal(float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
             {
                 this->x1 = x1; this->y1 = y1; this->z1 = z1;
                 this->x2 = x2; this->y2 = y2; this->z2 = z2;
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

    void Draw() const override {
        if (!visible) return;

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

private:
};

#endif
