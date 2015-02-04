#ifndef VEC2_HPP
#define VEC2_HPP
class vec2 {
    public:
        double x;
        double y;
        vec2(double x = 0, double y = 0);
        void set(double x, double y);

        vec2 operator+(const vec2 &b) const;
        vec2 operator-(const vec2 &b) const;
        bool operator==(const vec2 &b) const;
        
};
#endif
