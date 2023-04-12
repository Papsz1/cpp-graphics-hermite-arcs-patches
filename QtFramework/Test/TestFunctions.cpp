#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return hyperboloid::d00(u, sin(u));
    // return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    return hyperboloid::d01(u, sin(u));

    // GLdouble c = cos(u), s = sin(u);
    // return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    return hyperboloid::d10(u, sin(u));

    // GLdouble c = cos(u), s = sin(u);
    // return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}


GLdouble spiral_on_torus::u_min = 0;
GLdouble spiral_on_torus::u_max = +2 * TWO_PI;
GLdouble spiral_on_torus::r = 1.0;
GLdouble spiral_on_torus::R = 2.0;



DCoordinate3 spiral_on_torus::d0(GLdouble u)
{
    GLdouble cu = cos(u), su = sin(u), cv = cos(u * 2), sv = sin(u * 2);
    return DCoordinate3((R + r * cu) * sv, (R + r * cu) * cv, r * su);
}


DCoordinate3 spiral_on_torus::d1(GLdouble u)
{
    GLdouble cu = cos(u), su = sin(u), cv = cos(u * 2), sv = sin(u * 2);
    return DCoordinate3(2 * (r * cu + R) * cv - r * su * sv, -2.0 * (r * cu + R) * sv -r * su * cv, r * cu);
}

DCoordinate3 spiral_on_torus::d2(GLdouble u)
{
    GLdouble cu = cos(u), su = sin(u), cv = cos(u * 2), sv = sin(u * 2);
    return DCoordinate3((5.0 * r * cu + 4.0 * R) * -sv - 4.0 * r * su * cv, 4.0 * r * su * sv + (-5.0 * r * cu - 4.0 * R) * cv, -r * su);
}


GLdouble spiral_on_circle::u_min = 0.0;
GLdouble spiral_on_circle::u_max = TWO_PI;

DCoordinate3 spiral_on_circle::d0(GLdouble u)
{
    return surface_sphere::d00(u, 0.75 * u);
//    return DCoordinate3(cos(u), sin(u), u);
}

DCoordinate3 spiral_on_circle::d1(GLdouble u)
{
    return surface_sphere::d01(u, 0.75 * u);
//    return DCoordinate3(-sin(u), cos(u), 1.0);
}

DCoordinate3 spiral_on_circle::d2(GLdouble u)
{
    return surface_sphere::d10(u, 0.75 * u);
//    return DCoordinate3(-cos(u), -sin(u), 0.0);
}

GLdouble spiral_on_cylinder::u_min = 0.0;
GLdouble spiral_on_cylinder::u_max = TWO_PI;

DCoordinate3 spiral_on_cylinder::d0(GLdouble u)
{
    return surface_sphere::d00(u, u);
}

DCoordinate3 spiral_on_cylinder::d1(GLdouble u)
{
    return surface_sphere::d01(u, u);
}

DCoordinate3 spiral_on_cylinder::d2(GLdouble u)
{
    return surface_sphere::d10(u, u);
}


GLdouble spiral_on_lissajous::u_min = 0.0;
GLdouble spiral_on_lissajous::u_max = TWO_PI;
GLdouble spiral_on_lissajous::a = 2.0;
GLdouble spiral_on_lissajous::b = 2.0;
GLdouble spiral_on_lissajous::kx = 3.0;
GLdouble spiral_on_lissajous::ky = 2.0;

DCoordinate3 spiral_on_lissajous::d0(GLdouble u)
{
    return DCoordinate3(a*cos(u*kx), b*sin(u*ky), u);
}

DCoordinate3 spiral_on_lissajous::d1(GLdouble u)
{
    return DCoordinate3(-a*kx*sin(u*kx), b*ky*cos(u*ky), 1.0);
}

DCoordinate3 spiral_on_lissajous::d2(GLdouble u)
{
    return DCoordinate3(-a*kx*kx*cos(u*kx), -b*ky*ky*sin(u*ky), 0.0);
}


GLdouble spiral_on_hypotrochoid::u_min = 0.0;
GLdouble spiral_on_hypotrochoid::u_max = 3.0*TWO_PI;
GLdouble spiral_on_hypotrochoid::r = 3.0;
GLdouble spiral_on_hypotrochoid::R = 5.0;
GLdouble spiral_on_hypotrochoid::d = 5.0;


DCoordinate3 spiral_on_hypotrochoid::d0(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*cos(u) + d*c, Rmr*sin(u) - d*s, u);
}

DCoordinate3 spiral_on_hypotrochoid::d1(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*(-sin(u)) - d*(Rmr/r)*s, Rmr*cos(u) - d*(Rmr/r)*c, 1.0);
}

DCoordinate3 spiral_on_hypotrochoid::d2(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*(-cos(u)) - d*((Rmr*Rmr)/(r*r))*c, Rmr*(-sin(u)) + d*((Rmr*Rmr)/(r*r))*s, 0.0);
}


GLdouble spiral_on_torus_knot::u_min = 0.0;
GLdouble spiral_on_torus_knot::u_max = 6 * PI;

DCoordinate3 spiral_on_torus_knot::d0(GLdouble u)
{
    GLdouble c = cos(2.0*u/3.0), s = sin(2.0*u/3.0);
    return DCoordinate3((2.0+c)*cos(u), (2.0+c)*sin(u), s);
}

DCoordinate3 spiral_on_torus_knot::d1(GLdouble u)
{
    GLdouble c2 = cos(2.0*u/3.0), s2 = sin(2.0*u/3.0), c = cos(u), s = sin(u);
    return DCoordinate3((2.0+c2)*(-s) - ((2.0/3.0)*s2)*c, (2.0+c2)*c - (2.0/3.0*s2)*s, (2.0/3.0)*c2);
}

DCoordinate3 spiral_on_torus_knot::d2(GLdouble u)
{
    GLdouble c2 = cos(2.0*u/3.0), s2 = sin(2.0*u/3.0), c = cos(u), s = sin(u);
    return DCoordinate3((2.0/3.0*s2)*s - (2.0+c2)*c - (((4.0/9.0)*c2)*c - ((2.0/3.0)*s2)*s),
                        ((2.0/3.0*s2)*(-c) - (2.0+c2)*s) - ((4.0/9.0*c2)*s + (2.0/3.0*s2)*c),
                        -(4.0/9.0)*s2);
}


GLdouble spiral_on_rose::u_min = 0.0;
GLdouble spiral_on_rose::u_max = TWO_PI;
GLdouble spiral_on_rose::k = 2.0;

DCoordinate3 spiral_on_rose::d0(GLdouble u)
{
    GLdouble ck = cos(k * u);
    return DCoordinate3(ck * cos(u), ck*sin(u), u);
}

DCoordinate3 spiral_on_rose::d1(GLdouble u)
{
    GLdouble ck = cos(k * u);
    GLdouble sk = sin(k * u);
    return DCoordinate3(-k *sk * cos(u) - ck * sin(u), -k*sk*sin(u) + ck * cos(u), 1.0);
}

DCoordinate3 spiral_on_rose::d2(GLdouble u)
{
    GLdouble ck = cos(k * u);
    GLdouble sk = sin(k * u);
    return DCoordinate3(-k * k * ck * cos(u) - k * sk * sin(u)- (-k*sk * sin(u) + ck * cos(u)),
                        -k * k * ck * sin(u) - k * sk * cos(u) - k * sk * cos(u) - ck * sin(u),
                        0.0);
}

GLdouble surface_torus::u_min = 0;
GLdouble surface_torus::u_max = TWO_PI;
GLdouble surface_torus::v_min = 0;
GLdouble surface_torus::v_max = TWO_PI;
GLdouble surface_torus::r = 1;
GLdouble surface_torus::R = 2;

DCoordinate3 surface_torus::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((R + r * sin(u)) * cos(v), (R + r * sin(u)) * sin(v), r*cos(u));
}

DCoordinate3 surface_torus::d01(GLdouble u, GLdouble v)
{
     return DCoordinate3(-(R + r * sin(u)) * sin(v), (R + r * sin(u)) * cos(v), 0.0);
}

DCoordinate3 surface_torus::d10(GLdouble u, GLdouble v)
{
     return DCoordinate3((0 + r * cos(u)) * cos(v), (0 + r * cos(u)) * sin(v), -r*sin(u));
}

GLdouble surface_sphere::v_min = 0;
GLdouble surface_sphere::v_max = TWO_PI;
GLdouble surface_sphere::u_min = EPS;
GLdouble surface_sphere::u_max = PI-EPS;


DCoordinate3 surface_sphere::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(sin(u) * cos(v), sin(u) * sin(v), cos(u));
}
DCoordinate3 surface_sphere::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u) * cos(v), cos(u) * sin(v), -sin(u));
}
DCoordinate3 surface_sphere::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(u) * sin(v), sin(u) * cos(v), 0.0);
}

GLdouble surface_cylinder::u_min = 0;
GLdouble surface_cylinder::u_max = TWO_PI;
GLdouble surface_cylinder::v_min = 0;
GLdouble surface_cylinder::v_max = TWO_PI;

DCoordinate3 surface_cylinder::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u), sin(u), v);
}
DCoordinate3 surface_cylinder::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(u), cos(u), 0);
}
DCoordinate3 surface_cylinder::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(0, 0, 1);
    // return DCoordinate3(cos(u), sin(u), 1);
}

GLdouble surface_revolution::u_min = 0;
GLdouble surface_revolution::u_max = PI;
GLdouble surface_revolution::v_min = 0;
GLdouble surface_revolution::v_max = TWO_PI;

DCoordinate3 surface_revolution::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * cos(v), u * sin(v), 2*sin(u)*cos(u));
}
DCoordinate3 surface_revolution::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v), sin(v), 2*cos(u)*cos(u) - 2*sin(u)*sin(u));
}
DCoordinate3 surface_revolution::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * sin(v), -u * cos(v), 0);
}


GLdouble surface_saddle::u_min = -1;
GLdouble surface_saddle::u_max = 1;
GLdouble surface_saddle::v_min = -1;
GLdouble surface_saddle::v_max = 1;
GLdouble surface_saddle::a = 0.1;

DCoordinate3 surface_saddle::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u, v, u * u - v * v);
}
DCoordinate3 surface_saddle::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(1, 0, 2 * u);
}
DCoordinate3 surface_saddle::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(0, 1, -2 * v);
}

GLdouble surface_helicoid::u_min = 0;
GLdouble surface_helicoid::u_max = TWO_PI;
GLdouble surface_helicoid::v_min = 0;
GLdouble surface_helicoid::v_max = TWO_PI;

DCoordinate3 surface_helicoid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * cos(v), u * sin(v), u * u);
}
DCoordinate3 surface_helicoid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v), sin(v), 2 * u);
}
DCoordinate3 surface_helicoid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-u * sin(v), u * cos(v), 0);
}


GLdouble mobius_strip::u_min = 0.;
GLdouble mobius_strip::u_max = TWO_PI;
GLdouble mobius_strip::v_min = -1.;
GLdouble mobius_strip::v_max = 1.;

DCoordinate3 mobius_strip::d00(GLdouble u, GLdouble v) {
    return DCoordinate3((1 + v/2. * cos(u/2.)) * cos(u),
                        (1 + v/2. * cos(u/2.)) * sin(u),
                        v/2. * sin(u/2.));
}

DCoordinate3 mobius_strip::d10(GLdouble u, GLdouble v) {
    return DCoordinate3(sin(u) * (-.5 * v * cos(.5 * u) - 1) - .25 * v * sin(.5 * u),
                        -.25 * v * sin(.5 * u) * sin(u) + .5 * v * cos(.5 * u) * cos(u) + cos(u),
                        .25 * v * cos(.5 * u));
}

DCoordinate3 mobius_strip::d01(GLdouble u, GLdouble v) {
    return DCoordinate3(.5 * cos(0.5 * u) * cos(u),
                        .5 * sin(u) * cos(.5 * u),
                        .5 * sin(.5 * u));
}

GLdouble hyperboloid::u_min = 0;
GLdouble hyperboloid::u_max = 3;
GLdouble hyperboloid::v_min = 0;
GLdouble hyperboloid::v_max = TWO_PI;

DCoordinate3 hyperboloid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((1 + cosh(u-3.0/2))*sin(v),
                        (1 + cosh(u-3.0/2))*cos(v),
                        sinh(u-3.0/2));
}
DCoordinate3 hyperboloid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(sinh(3.0/2-u)*(-sin(v)),
                        sinh(3.0/2-u)*(-cos(v)),
                        cosh(3.0/2-u));
}
DCoordinate3 hyperboloid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3((cosh(3.0/2-u)+1)*cos(v),
                        -(cosh(3.0/2-u)+1)*sin(v),
                        0);
}
