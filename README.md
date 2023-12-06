# Wax-Seal-Melter

This project intends to create a wax seal melter, a device that outputs heat to a spoon that can be placed on top of it, enough to melt a wax seal.

The amount of heat will be controlled using a knob, but it will have a preset value of 150.

See Nichrome_Calc.c for electrical value calculation.

12/05/2023
- This project was originally intended to be carried out using a nichrome wire coil conducting heat to a metal plate surface where a spoon can be laid. Considering calculations given through the Nichrome_Calc.c, the original plan has been dropped as the required power was extraordinarily high and lifted safety concerns to be used in households.
- The use of induction heating is under consideration due to its high efficiency and lack of heat remnants

Using the induction heating calculator in the link below, the necessary power at 100 kHz frequency was calculated as 0.9 kW.
https://ultraflexpower.com/learn-about-induction-heating/induction-heating-calculation-tool/
![Screenshot (172)](https://github.com/raeditio/Wax-Seal-Melter/assets/93297311/e2e7fe65-07a5-4315-bbd4-3b8003f7d145)
