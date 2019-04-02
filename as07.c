//  phys3071 as07 melsom 42593249

/*
This program will solve the root for the Kepler equation over a range of values
of M. It solves the root using the bisection method.

Input: The user is required to enter the value of eccentricity, 'epsi', and and 
the accuracy parameter, 'delta'. The value of eccentricity is verified before the 
program will progress.

Calculations: The program calculates for what value of E, 'root', is a root of 
the Kepler equation for a given M. M is then modified and the program 
calculates the specific E, and with each iteration the relative distance, the x
and y coordinates and time since last apogee passage. For each iteration of M, 
all the results are printed to file.

Outputs: an output file is produced with the column headers
time, M, root, x, y, distance, count

compiled as gcc as07-melsom-42593249.c -o as07 -lm -Wall
*/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

// Global Variables ***********************************************************
int count; // Used for counting how many iterations for convergence.

// Function prototypes ********************************************************
double bisection(double M, double delta, double epsi);
double fun(double E, double M, double epsi);

// Begin main function ********************************************************
int main () {
  int loop_count;
  double epsi, delta; // eccentricity and accuracy parameter.
  double M, time, root; 
  const double T_orb= 1.0; // T_orb set to one, as per instructions.
  double r1, r2, x, y, distance; // position variables.
  FILE *fp; // for pointing at file.
  
  fp= fopen("data.dat", "w");
  
  
  printf("This program will solve Kepler's equation: "
         "'0 = E - epsilon*(sin(E)) - M', using the bisection method for"
         " multiple values of M between 0 and 4*pi.\n");
  
  printf("The eccenticity needs to be 0 <= e < 1");
  printf("Please provide the eccentiricity of the orbit: ");
  scanf("%lf", &epsi);
  // Checks if the user enters the correct value of eccentricity.
  if (epsi< 0.0 || epsi>= 1.0) {
    printf("ERROR: The entered value of epsilon is incorrect.");
    return EXIT_FAILURE;
  }
  printf("Please provide the value delta: ");
  scanf("%lf", &delta);

  // This loop will run for M= 0:4pi over 500 steps.
  // inside of the loop, root is calculated such that E(root) \approx 0.
  // time is calculated, as a funtion of M, r2, which is a function of 
  M = 0.0; // initialise M value.
  r1= 1.0; // set to 1 as per instructions.
  r2= sqrt(1.0- pow(epsi,2.0));
  for (loop_count = 0; loop_count< 500; loop_count++) {
    root = bisection(M, delta, epsi);
    // T_orb is permamently set to 1.0 as per instructions.
    time= M* T_orb/ (2.0* M_PI);
    
    // calculated x and y position of orbiting body.
    // calculate relative distance between bodies.
    x= r1* cos(root);
    y= r2* sin(root);
    distance= sqrt(pow(x- epsi, 2.0)+ pow(y, 2.0));
    
    // print command.
    fprintf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%i\n"
              , time, M, root, x, y, distance, count);
    
    // Increment M.
    M+= 4.0* M_PI/ 500.0;
  }
  
  fclose(fp);
  return EXIT_SUCCESS;
}

// Functions ******************************************************************
double bisection(double M, double delta, double epsi) {
  double FofA, FofC; // Function evaluated at lower_bound, and mid_point.
  double lower_bound= 0.0, mid_point, upper_bound= 4.0* M_PI; // a, b, c

  count= 0.0; // Global variable so I need to reset it before each calculation.
  while (fabs(upper_bound- lower_bound)/2.0 > delta) {
    mid_point= (upper_bound+ lower_bound)/ 2.0;
    FofA= fun(lower_bound, M, epsi);
    FofC= fun(mid_point, M, epsi);
    
    // either the upper or lower bound is movedto the mid point.
    if (FofA* FofC< 0.0) (upper_bound= mid_point);
    else (lower_bound= mid_point);
    count++ ;
  }
  return ((fabs(upper_bound+ lower_bound))/ 2.0);
}

double fun(double E, double M, double epsi) {
  return E- epsi* sin(E)- M;
}
