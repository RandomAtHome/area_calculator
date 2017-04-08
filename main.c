#include<stdio.h>
#include<stdlib.h>

double f1(double x){
	return x + 1;
}

double f2(double x){
	return x * x;
}

//binary search
double root(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	int mod = f(a) > g(a) ? 1 : -1;
	double middle = (a+b)/2;
	while ((a-b)>eps1){
		if (mod * f(middle) > mod * g(middle)){
			a = middle;
		} else {
			b = middle;
		}
		middle = (a+b)/2;
	}
	return middle;
}

//trapezium method
double integral(double (*f)(double x), double a, double b, double eps2){
	double answ = (f(a) + f(b))/2;
	a += eps2;
	while (a < b){
		answ += f(a);
		a += eps2;
	}
	answ *= eps2;
	return answ;
}

int main(void){
	double intersection = root(f1, f2, -0.5, 0.5, 0.001);
	double answ = integral(f2, 0, 1, 0.001);
	printf("%f", answ);
	return 0;
}

