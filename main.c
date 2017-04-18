#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
#define EPS1 0.001
#define EPS2 0.0001

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

static int steps = 0;
static int intersection_print = 0;
static int steps_print = 0;
static int help_print = 0;
static char *help_text = "Options:\n"
						 "-h / --help	\tshow this help\n"
						 "-i / --intersect	print abscisses of intersections\n"
						 "-s / --steps	\tprint amount of steps of equation solver algorithm\n"
						 "-r / --root	\tfind intersection of 2 functions on given interval\n"
						 "-a / --integral	\tcalculate integral of 2 functions on given interval\n";
static char *root_checker;
static char *integral_checker;
static struct option long_options[] =
		{
			{"help", no_argument, &help_print, 1},
			{"intersections", no_argument,   &intersection_print, 1},
			{"steps",  no_argument, &steps_print, 1},
			{"root",  required_argument, 0, 'r'},
			{"integral",  required_argument, 0, 'a'},
			{0, 0, 0, 0}
		};

double inline fabs(double x){
	return x > 0 ? x : -x;
}

//binary search
double bin(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	int mod = f(a) > g(a) ? 1 : -1;
	double middle = (a+b)/2;
	while ((b-a)>eps1){
		steps++;
		if (mod * f(middle) > mod * g(middle)){
			a = middle;
		} else {
			b = middle;
		}
		middle = (a+b)/2;
	}
	return middle;
}

//sec
double sec(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	while (fabs(f(b) - g(b)) > eps1){
		steps++;
		b -= (b-a) * (f(b)-g(b)) / (f(b)-g(b)-f(a)+g(a));
	}
	return b;
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
	double (*root)(double (*f)(double x), double (*g)(double x), double a, double b, double eps1);
	#if METHOD == 1
	printf("Compiled with Binary Search\n");
	root = bin;
	#else
	printf("Compiled with Chords Method\n");
	root = sec;
	#endif
	int option_index = 0;
	int c = 0;
	while((c = getopt_long_only(argc, argv, "hisr:a:", long_options, &option_index)) != -1){
		option_index = 0;
		switch (c)
			{
			case 0:
				break;

			case 'h':
				help_print = 1;
				break;

			case 'i':
				intersection_print = 1;
				break;

			case 's':
				steps_print = 1;
				break;

			case 'r':
				strcpy(root_checker, optarg);
				break;
			case 'a':
				strcpy(integral_checker, optarg);
				break;

			default:
				abort();
			}
		}
	if (help_print){
		printf(help_text);
		return 0;
	}
		
	double x1, x2, x3;
	//double (*root)(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) = sec;
	x1 = root(f1, f2, 5.5, 6.5, EPS1); //
	x2 = root(f2, f3, 3.5, 4.5, EPS1); // all limits are precalculated
	x3 = root(f3, f1, 2.01, 2.5, EPS1);//
	double answ = 0;
	answ += integral(f3, x3, x2, EPS2);
	answ += integral(f2, x2, x1, EPS2);
	answ -= integral(f1, x3, x1, EPS2);
	if (intersection_print){
		printf("F1 intersects with F2: %lf\n", x1);
		printf("F2 intersects with F3: %lf\n", x2);
		printf("F3 intersects with F1: %lf\n", x3);
		printf("---\n");
	}
	if (steps_print){
		printf("Total iterations for all equations: %d\n", steps);
		printf("---\n");
	}
	printf("Area between thesex curves: %lf\n", answ);
	return 0;
}


