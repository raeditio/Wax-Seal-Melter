#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

int main (void){
    /* this execution intends to calculate the induction heating of a load with OD = 2" and ID = 1.8" at 100 kHz frequency
    using a 1/4" diameter copper tube
    the load is 0.7" long
    the coil is 1.5" long
    the coil is 1/4" diameter
    the coil is 1/8" from the load
    */

    double Tc = 150; // Tc is the required tempeture to be reached by the wax in °C.
    double Ta = 22; // Ta is the ambient tempeture in °C.
    double kw = 0.25; // k1 is the thermal conductivity of wax in W/m-K.
    double OD = 2.0 * 2.54e-2; // OD is the outer diameter of the load in m.
    double ID = 1.8 * 2.54e-2; // ID is the inner diameter of the load in m.
    double f = 100000; // f is the frequency of the induction heater in Hz.
    double t = 10; // t is the time required to reach the required tempeture in seconds.
    double p = 	6.9e-7; // p is the resistivity of stainless steel at 20 °C Ω/m.
    double l = 0.7 * 2.54e-2; // l is the length of the load in m.
    double mw = 30; // mw is the mass of the wax in g.
    double cw = 2.14; // specific heat of wax is 2.14 J/g-K
    double Lw = 210; // latent heat of wax is 210 J/g
    double ms = 300; // ms is the mass of the stainless steel spoon in g.
    double cs = 0.385; // c1 is the specific heat of stainless steel in J/g-K.

    double A = M_PI * (pow(OD, 2) - pow(ID, 2)) / 4; // A is the cross-sectional area of the load.
    double R = p * l / A; // R is the resistance of the load.

    /* Q = mcΔT and Q = Pt. Therefore, t = mcΔT / P 
    In order to calculate Q, the specific heat & latent heat of wax and the conduction
    between the stainless steel spoon and the wax bead must be considered. */

    // Find Q = mc*delta T required for the wax
    double Q1 = mw * cw * (Tc - Ta) + mw * Lw; // 30 is the approximate weight of the wax in g. 2.14 is the specific heat of the wax in J/g-K. 210 is the latent heat of the wax in J/g.
    // Find the effective area of contact surface between the spoon and the wax
    double A1 = 2.0 * pow((ID / 2.0), 2.0) * M_PI;

    // Calculate the temperature of the spoon
    double Ts = (Q1 / (kw * A1 * t)) + Tc; // kw is the thermal conductivity of the wax in W/m-K. A is the effective area of contact surface. Ts is the temperature of the spoon. t is the time required to reach the required tempeture.
    // Find Q = mc*delta T required for the stainless steel spoon
    double Q2 = ms * cs * (Ts - Ta);
    
    // Find the current required to heat the load
    double i = sqrt(Q2 * t / R); // i0 is the current required to heat the load.
    // Find the skin depth of the load
    double delta = 1 / (sqrt(M_PI * f) * sqrt(p));
    // Find the effective current of the load at OD accounting for depth loss
    double i0 = i / exp(-(OD - ID) / delta);

    // Find the power required to heat the load
    double P = i0 * i0 * R; // P is the power required for the load to reach the required tempeture in the given time.
    // Find the voltage required to heat the load
    double V = sqrt(P * R); // V is the voltage required to reach the required tempeture.

    // Print the results
    printf("The required tempeture for wax is %lf C\n", Tc);
    printf("The required heat for wax is %lf J\n", Q1);
    printf("The required tempeture for stainless steel spoon is %lf C\n", Ts);
    printf("The required heat for stainless steel spoon is %lf J\n", Q2);
    printf("The resistance of the load is %lf ohms\n", R);
    printf("The required current is %lf A\n", i0);
    printf("The required power is %lf W\n", P);
    printf("The required voltage is %lf V\n", V);
}