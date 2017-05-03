#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
#define EPS1 0.001
#define EPS2 0.0001
#ifndef START_SEG
#define START_SEG 2.1
#endif
#ifndef END_SEG
#define END_SEG 6.5
#endif

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
						 "-a / --integral	\tcalculate integral of 2 functions on given interval\n"
						 "If -r and/or -a are specified -i and -s are ignored\n";
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
#if METHOD == 1
//binary search
double root(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	if (a > b){
		double tmp = a;
		a = b;
		b = tmp;
	}
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
#else
//sec
double root(double (*f)(double x), double (*g)(double x),  double a, double b, double eps1){
	if (a > b){
		double tmp = a;
		a = b;
		b = tmp;
	}
	while (fabs(f(b) - g(b)) > eps1){
		steps++;
		b -= (b-a) * (f(b)-g(b)) / (f(b)-g(b)-f(a)+g(a));
	}
	return b;
}
#endif
//trapezium method
double integral(double (*f)(double x), double a, double b, double eps2){
	if (a > b){
		double tmp = a;
		a = b;
		b = tmp;
	}
	double answ = (f(a) + f(b))/2;
	a += eps2;
	while (a < b){
		answ += f(a);
		a += eps2;
	}
	answ *= eps2;
	return answ;
}

int process_root(char * input_line){
	if (!input_line){
		return -1;
	}
	double a, b;
	double (*f)(double x), (*g)(double x);
	int num1, num2;
	sscanf(input_line, "%d%d%lf%lf", &num1, &num2, &a, &b);
	// this is terrible. fix this please
	switch (num1){
		case 1:
			f = f1;
			break;
		case 2:
			f = f2;
			break;
		case 3:
			f = f3;
			break;
		default:
			return 1;
	}
	switch (num2){
		case 1:
			g = f1;
			break;
		case 2:
			g = f2;
			break;
		case 3:
			g = f3;
			break;
		default:
			return 1;
	}
	double x = root(f, g, a, b, EPS1);
	printf("-r execution:\n");
	printf("F%d intersects with F%d: %lf\n", num1, num2, x);
	printf("---\n");
	return 0;
}

int process_integral(char * input_line){
	if (!input_line){
		return -1;
	}
	double a, b;
	double (*f)(double x);
	int num1;
	sscanf(input_line, "%d%lf%lf", &num1, &a, &b);
	// this is terrible. fix this please
	switch (num1){
		case 1:
			f = f1;
			break;
		case 2:
			f = f2;
			break;
		case 3:
			f = f3;
			break;
		default:
			return 1;
	}
	double x = integral(f, a, b, EPS2);
	printf("-a execution:\n");
	printf("F%d area: %lf\n", num1, x);
	printf("---\n");
	return 0;
}

int main(int argc, char **argv){
	#if METHOD == 1
	printf("Compiled with Binary Search\n");
	#else
	printf("Compiled with Chords Method\n");
	#endif
	int option_index = 0;
	int c = 0, count;
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
				if (root_checker){
					free(root_checker);
				}
				root_checker = malloc(sizeof(char) * (strlen(optarg) + 1));
				strcpy(root_checker, optarg);
				for (count = 1; optind < argc && count < 4; optind++, count++){
					strcat(root_checker, " "); // this is terrible
					strcat(root_checker, argv[optind]);
				}
				if (count < 4){
					printf("Not enough arguments for -r!\n");
					abort();
				}
				
				break;
			case 'a':
				if (integral_checker){
					free(integral_checker);
				}
				integral_checker = malloc(sizeof(char) * (strlen(optarg) + 1));
				strcpy(integral_checker, optarg);
				for (count = 1; optind < argc && count < 3; optind++, count++){
					strcat(integral_checker, " "); // this is terrible
					strcat(integral_checker, argv[optind]);
				}
				if (count < 3){
					printf("Not enough arguments for -a!\n");
					abort();
				}
				break;

			default:
				abort();
			}
		}
	if (help_print){
		printf(help_text);
		return 0;
	}
	if (root_checker || integral_checker){
        if (process_root(root_checker) == 1){
            printf("Functions numbers are invalid for -r\n");
        }
        if (process_integral(integral_checker) == 1){
            printf("Function number is invalid for -a\n");
        }
		return 0;
	}
	double x1, x2, x3;
	x1 = root(f1, f2, START_SEG, END_SEG, EPS1); //
	x2 = root(f2, f3, START_SEG, END_SEG, EPS1); // all limits are precalculated
	x3 = root(f3, f1, START_SEG, END_SEG, EPS1);//
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


