#ifndef ColorH
#define ColorH

class Color
{
public:
    virtual ~Color() {}
    Color(float rr = 0.0f, float gg = 1.0f, float bb = 0.0f, float aa = 1.0f)
        : r(rr), g(gg), b(bb), a(aa) { }

    float r, g, b, a;

protected:

private:

};

#endif
