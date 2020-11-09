#include <math.h>
double f1( register double x) {
	return x;
}
double f2(register double x) {
	return sin(22 * x);
}
double f3(register double x) {
	return pow(x, 4);
}
double f4(register double x) {
	return atan(x);
}

