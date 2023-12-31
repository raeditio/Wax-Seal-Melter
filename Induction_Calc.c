#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <C:\Users\Ryan\OneDrive - UBC\Documents\VSCode\projects\Wax Seal Melter\Wax-Seal-Melter\modpar.h>

int main (void){
    /* this execution intends to calculate the induction heating of a load with OD = 2" and ID = 1.8" at 60 Hz frequency
    using a 1/4" diameter copper tube
    the load is 0.7" long
    the coil is 1.5" long
    the coil is 1/4" diameter
    the coil is 1/8" from the load
    */

    double Tc = 150; // Tc is the required tempeture to be reached by the wax in °C.
    double Ta = 22; // Ta is the ambient tempeture in °C.
    double kc = 400; // kc is the thermal conductivity of copper in W/m-K.
    double OD = 1.7 * 2.54e-2; // OD is the outer diameter of the load in m.
    double ID = 1.5 * 2.54e-2; // ID is the inner diameter of the load in m.
    double d = 0.2 *2.54e-2; // d is the distance from the surface of the wax bead to its core in m.
    double f = 20e3; // f is the frequency of the induction heater in Hz.
    double t = 13; // t is the time required to reach the required tempeture in seconds.
    double p = 	1.68e-8; // p is the resistivity of copper at 20 °C in Ω/m.
    double x = 2.0e-3; // x is the thickness of the load in m.
    double mw = 5; // mw is the mass of the wax in g.
    double cw = 2.14; // specific heat of wax is 2.14 J/g-K
    double Lw = 210; // latent heat of wax is 210 J/g
    double ms = 20; // ms is the mass of the copper spoon in g.
    double cs = 0.385; // cs is the specific heat of copper in J/g-K.
    double e = 0.7; // e is the efficiency of the induction heating on impure copper spoon.

    double A = M_PI * pow(OD,2) / 4; // A is the cross-sectional area of the load.
    double R = p * x / A; // R is the resistance of the load.

    /* Q = mcΔT and Q = Pt. Therefore, t = mcΔT / P
    In order to calculate Q, the specific heat & latent heat of wax and the conduction
    between the copper spoon and the wax bead must be considered. */

    // Find the integration ∫ Q dt = ∫ mc*dT to account for the entire heat over the time period
    double Q1 = mw * cw * (Tc - Ta) * 10 + mw * Lw; // Solving the integral gives a constant multiplier of 10.
    // Find the effective area of contact surface between the spoon and the wax. In this case, it is a generous surface area of the interior of the spoon. 
    double A1 = 2.0 * pow((ID / 2.0), 2.0) * M_PI;

    // Calculate the temperature of the spoon
    double Ts = (Q1 / (kc * A1 / x)) + Tc; // kw is the thermal conductivity of the wax in W/m-K. A is the effective area of contact surface. Ts is the temperature of the spoon. t is the time required to reach the required tempeture.
    // Find Q = mc*delta T required for the copper spoon
    double Q2 = ms * cs * (Ts - Ta);
    
    // Find the current required to heat the load
    double i = sqrt(Q2 / t / R); // i0 is the current required to heat the load.
    // Find the skin depth of the load
    double delta = 1 / (sqrt(M_PI * f) * sqrt(p));
    // Find the effective current of the load at OD accounting for depth loss
    double i0 = i / exp(-(OD - ID) / delta);

    // Find the power required to heat the load
    double P = i0 * i0 * R; // P is the power required for the load to reach the required tempeture in the given time.
    // Account for efficiency
    double P0 = P / e;
    /* Find the Resistance Limits */
    double V0 = 24; // V0 is the voltage supplied to the induction coil.
    double R0 = V0 * V0 / P0; // R0 is the resistance of the induction coil.
    double l0 = .5; // l0 is the length of the induction coil in m.
    double d0 = 2 * sqrt(p * l0 / R0 / M_PI); // d0 is the diameter of the induction coil in m.

    // Print the results
    printf("The required tempeture for wax is %lf C\n", Tc);
    printf("The required heat for wax is %lf J\n", Q1);
    printf("The required tempeture for copper spoon is %lf C\n", Ts);
    printf("The required heat for copper spoon is %lf J\n", Q2);
    printf("The resistance of the load is %lf ohms\n", R);
    // printf("The required current is %lf A\n", i0);
    printf("The required power is %lf W\n", P0);
    // printf("The required voltage is %lf V\n", V0);
    printf("The required diameter of the induction coil is %lf mm\n", d0 * 1e3);

    // printf("%lf\n", Q1);
    // printf("%lf\n", kc);
    // printf("%lf\n", A1);
    // printf("%lf\n", Ts);

    return 0;
}