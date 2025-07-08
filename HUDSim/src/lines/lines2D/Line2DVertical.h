#ifndef Line2DVerticalH
#define Line2DVerticalH

#include "Line3DVertical.h"

class CLine2DVertical : public CLine3DVertical
{
public:
    virtual ~CLine2DVertical() { z1 = 0.f; z2 = 0.f; }
             CLine2DVertical() {}
             CLine2DVertical(float x1 = 0.f, float y1 = 0.f,
                 float x2 = 0.f, float y2 = 1.f,
                 const Color& color = Color(0.f, 1.f, 0.f, 1.f),
                 float width = 1.f,
                 bool solid = true,
                 bool visible = true,
                 float scale = 1.f)
             {
                 this->x1 = x1; this->y1 = y1; this->z1 = 0.f;
                 this->x2 = x2; this->y2 = y2; this->z2 = 0.f;
                 this->color = color;
                 this->width = width;
                 this->solid = solid;
                 this->visible = visible;
                 this->scale = scale;
             }

    void SetZ1(float val) override { z1 = 0.f; }
    void SetZ2(float val) override { z2 = 0.f; }
    float GetZ1() const override { return 0.f; }
    float GetZ2() const override { return 0.f; }

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
