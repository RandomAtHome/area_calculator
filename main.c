#include<stdio.h>
#include<stdlib.h>

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

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
	double x;
	scanf("%lf", &x);
	printf("%lf %lf %lf\n", f1(x), f2(x), f3(x));
	return 0;
}

