#ifndef Line3DH
#define Line3DH

#include <string>
#include <cmath>
#include <GL/glut.h>
#include "Color.h"

class CLine3D
{
public:
    virtual ~CLine3D() {}
             CLine3D() {}

    // Getters
    virtual float GetX1() const { return x1; }
    virtual float GetY1() const { return y1; }
    virtual float GetZ1() const { return z1; }
    virtual float GetX2() const { return x2; }
    virtual float GetY2() const { return y2; }
    virtual float GetZ2() const { return z2; }

    Color GetColor() const { return color; }
    float GetWidth() const { return width; }
    bool IsSolid() const { return solid; }
    bool IsVisible() const { return visible; }

    float GetScale() const { return scale; }

    // Setters
    virtual void SetX1(float val) { x1 = val; }
    virtual void SetY1(float val) { y1 = val; }
    virtual void SetZ1(float val) { z1 = val; }
    virtual void SetX2(float val) { x2 = val; }
    virtual void SetY2(float val) { y2 = val; }
    virtual void SetZ2(float val) { z2 = val; }

    void SetColor(const Color& c) { color = c; }
    void SetColor(float r, float g, float b, float a = 1.0f) { color = Color(r, g, b, a); }
    void SetWidth(float w) { width = w; }
    void SetSolid(bool s) { solid = s; }
    void SetVisible(bool v) { visible = v; }

    void SetScale(float s) { scale = s; }

    // Length calculation (3D distance)
    float GetLength() const {
        float dx = x2 - x1;
        float dy = y2 - y1;
        float dz = z2 - z1;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Angle in degrees XY-plane from start to end
    float CalculateAngleXY() const {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::atan2(dy, dx) * 180.0f / 3.14159265f;
    }

    // Angle in degrees XZ-plane from start to end
    float CalculateAngleXZ() const {
        float dx = x2 - x1;
        float dz = z2 - z1;
        return std::atan2(dz, dx) * 180.0f / 3.14159265f;
    }

    // Angle in degrees YZ-plane from start to end
    float CalculateAngleYZ() const {
        float dy = y2 - y1;
        float dz = z2 - z1;
        return std::atan2(dz, dy) * 180.0f / 3.14159265f;
    }

    virtual void Draw() const = 0;

protected:
    float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;
    float x2 = 1.0f, y2 = 0.0f, z2 = 0.0f;

    Color color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    float width = 1.0f;
    bool solid = true;
    bool visible = true;

    float scale = 1.0f;   // Ölçek

private:

};

#endif
