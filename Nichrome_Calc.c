#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <C:\Users\Ryan\OneDrive - UBC\Documents\VSCode\projects\Wax Seal Melter\Wax-Seal-Melter\modpar.h>

void modifyvar(double *var, char varname[]) {
	char userInput[100];
	bool ModBool = false;
	printf("%s = %lf. Enter a value to modify: \n", varname, *var);
	ModBool = getUserInput(&userInput);
	if(ModBool) sscanf(userInput, "%lf", var);
	printf("%lf\n", *var);
}

int main(void) {
	double Tc = 150; // Tc is the required tempeture to be reached.
	double kc = 400; // k1 is the thermal conductivity of copper in W/m-K.
	double d = 1.5 * 2.54e-2; // d is the diameter of the spoon.
	double t = 30; // t is the time required to reach the required tempeture.
	double p = 1.5e-6; // p is the resistivity of the nichrome wire.
	double l = 1.0; // l is the length of the nichrome wire.
	double r = 1.5e-3; // r is the radius of the nichrome wire.
	double x = 2.0e-3; // x is the thickness of the spoon.

	bool ModBool = false;
	char userInput[100];

	/* gives the option to modify values */
	printf("Tc = %lf\n", Tc);
	printf("kw = %lf\n", kc);
	printf("d = %lf\n", d);
	printf("t = %lf\n", t);
	printf("p = %lf\n", p);
	printf("l = %lf\n", l);
	printf("r = %lf\n", r);
	printf("x = %lf\n", x);
	printf("Enter Y to modify: \n");

	char userchoice = getUserChoice();

	if (userchoice == 'Y' || userchoice == 'y') {
		modifyvar(&Tc, "Tc");
		modifyvar(&kc, "kc");
		modifyvar(&d, "d");
		modifyvar(&t, "t");
		modifyvar(&p, "p");
		modifyvar(&l, "l");
		modifyvar(&r, "r");
		modifyvar(&x, "x");
		
		printf("Tc = %lf\n", Tc);
		printf("kc = %lf\n", kc);
		printf("d = %lf\n", d);
		printf("t = %lf\n", t);
		printf("p = %lf\n", p);
		printf("l = %lf\n", l);
		printf("r = %lf\n", r);
		printf("x = %lf\n", x);
	}

	/* Find Q = mc*delta T */
	double Td1 = Tc - 22; // Td1 is the difference between the required tempeture and the room tempeture.
	
	/* Find required heat for wax over 10s */
	double Q1 = 5 * 2.14 * Td1 * 10 + 30 * 210; // 5 is the approximate weight of the wax in g. 2.14 is the specific heat of the wax in J/g-K. 210 is the latent heat of the wax in J/g. Through integration, the constant multiplier is 10.
	
	double A1 = 2.0 * pow((d / 2.0), 2.0) * M_PI; // A is the effective area of contact surface between the spoon and the wax.
	
	/* Td2 is the difference in temperature between the wax and the spoon in nominal conditions */
	double Td2 = (Q1 / (kc * A1 / x)); // kw is the thermal conductivity of the wax in W/m-K. A is the effective area of contact surface. Td2 is the difference in temperature between the wax and the spoon. t is the time required to reach the required tempeture.
	
	/* Find required heat for the copper spoon */
	double Q2 = 20 * 0.385 * (Tc + Td2 - 22); // 20 is the approximate weight of the spoon in g. 0.385 is the specific heat of the copper spoon in J/g-K.

	/* Find required temperature for nichrome wire */
	double A2 = M_PI * r * l; // A is the effective area of contact surface between the spoon and the nichrome wire.
	double Td3 = (Q2 / (kc * A2)); /* kn is the thermal conductivity of the nichrome wire in W/m-K. A is the effective area of contact surface.
	Td2 is the difference in temperature between the copper spoon and the nichrome wire. t is the time required to reach the required tempeture.
	x is the thickness of the spoon in m. */
	
	/* Find required heat for nichrome wire */
	double Q3 = 10 * 0.48 * (Td1 + Td2 + Td3 - 22); // 10 is the approximate weight of the nichrome wire in g. 0.48 is the specific heat of the nichrome wire in J/g-K.
	
	/* Find the power required to reach the required tempeture */
	double P = Q3 / t; // P is the power required for the nichrome wire to reach the required tempeture in the given time.
	
	/* Find the resistance of the nichrome wire */
	double A3 = M_PI * r * r; // A is the cross-sectional area of the nichrome wire.
	double R = p * l / A3; // R is the resistance of the nichrome wire.
	
	/* Find the voltage required to reach the required tempeture */
	double V = sqrt(P * R); // V is the voltage required to reach the required tempeture.

	/* Print the results */
	printf("The required tempeture for wax is %lf C\n", Td1 + 22);
	printf("The required heat for wax is %lf J\n", Q1);
	printf("The required tempeture for copper spoon is %lf C\n", (Td1 + Td2 + 22));
	printf("The required heat for copper spoon is %lf J\n", Q2);
	printf("The required tempeture for nichrome wire is %lf C\n", (Td1 + Td2 + Td3 + 22));
	printf("The required heat for nichrome wire is %lf J\n", Q3);
	printf("The resistance of the nichrome wire is %lf ohms\n", R);
	printf("The required power is %lf W\n", P);
	printf("The required voltage is %lf V\n", V);

	// printf("%lf\n", Q1);
    // printf("%lf\n", kc);
    // printf("%lf\n", A1);
	// printf("%lf\n", Td1 + Td2 + 22);
    // // printf("%lf\n", Td1);
	// // printf("%lf\n", Td2);
	// // printf("%lf\n", Tc);

	return 0;
}
