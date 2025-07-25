﻿#ifndef Line3DHorizontalH
#define Line3DHorizontalH

#include "Line3D.h"

class CLine3DHorizontal : public CLine3D
{
public:
    virtual ~CLine3DHorizontal() {}
             CLine3DHorizontal() {}

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
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0f);
        glPopMatrix();
    }
protected:

private:
};

#endif
