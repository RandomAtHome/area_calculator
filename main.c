#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#define EPS1 0.001
#define EPS2 0.0001

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

static struct option long_options[] =
        {
          {"help", no_argument, 0, 'h'},
          {"intersections", no_argument,   0, 'i'},
          {"steps",  no_argument, 0, 's'},
          {"test_root",  required_argument, 0, 'r'},
          {"test_integral",  required_argument, 0, 'a'},
	  {"solver", required_argument, 0, 'D'},
          {0, 0, 0, 0}
        };

//binary search
double root(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	int mod = f(a) > g(a) ? 1 : -1;
	double middle = (a+b)/2;
	while ((b-a)>eps1){
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

int main(int argc, char **argv){
	double x1, x2, x3;
	x1 = root(f1, f2, 5.5, 6.5, EPS1); //
	x2 = root(f2, f3, 3.5, 4.5, EPS1); // all limits are precalculated
	x3 = root(f3, f1, 2.01, 2.5, EPS1);//
	double answ = 0;
	answ += integral(f3, x3, x2, EPS2);
	answ += integral(f2, x2, x1, EPS2);
	answ -= integral(f1, x3, x1, EPS2);
	printf("Area between thesex curves: %lf\n", answ);
	return 0;
}


