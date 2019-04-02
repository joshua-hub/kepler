//  phys3071 as07 melsom 42593249

/*
This program will solve the root for the Kepler equation over a range of values
of M. It solves the root using either the bisection method, or the 
Newton-Raphson method.

Input: The user is required to enter the value of eccentricity, 'epsi', and and 
the accuracy parameter, 'delta'. The value of eccentricity is verified before 
the program will progress. The user is also required to choose the numerical 
method used to solve.

Calculations: The program calculates for what value of E, 'root', is a root of 
the Kepler equation for a given M. M is then modified and the program 
calculates the specific E, and with each iteration the relative distance, the x
and y coordinates and time since last apogee passage. For each iteration of M, 
all the results are printed to file.

For the bisection method, if 30 iterations have occured and the solution has 
not converged, the program will exit.

Outputs: an output file is produced with the column headers
time, M, root, x, y, distance, count

compiled as gcc as07-melsom-42593249.c -o as07 -Wall -lm
*/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

// Global Variables ***********************************************************
int count; // Used for counting how many iterations for convergence.
double dE= 1e-5; // Used for the numerical derivative for the Newton method.

// Function prototypes ********************************************************
double bisection(double M, double delta, double epsi); // Bisection method
double fun(double E, double M, double epsi); // Function
double fundash(double E, double M, double epsi, double dE);//FunctionDerivative
double newton(double M, double delta, double epsi); // Newton-Raphson method

// Begin main function ********************************************************
int main () {
  int loop_count; //loop counter to count for 500 steps of M
  double epsi, delta; // eccentricity and accuracy parameter.
  double M, time, root; 
  const double T_orb= 1.0; // T_orb set to one, as per instructions.
  double r1, r2, x, y, distance; // position variables.

  int method_choice; // User input to choose numerical method to solve root.
  FILE *fp; // for pointing at file.
  
  fp= fopen("adv.d", "w");
  
  
  printf("This program will solve Kepler's equation: "
         "'0 = E - epsilon*(sin(E)) - M', using the bisection method for"
         " multiple values of M between 0 and 4*pi.\n");
  
  printf("The eccenticity needs to be 0 <= e < 1\n");
  printf("Please provide the eccentiricity of the orbit: ");
  scanf("%lf", &epsi);
  
  // Checks if the user enters the correct value of eccentricity.
  if ( (epsi< 0.0) || (epsi>= 1.0) ) {
    printf("ERROR: The entered value of epsilon is incorrect.");
    return EXIT_FAILURE;
  }
  
  printf("Please provide the precision variable, delta: ");
  scanf("%lf", &delta);
  printf("Please enter 1 for Bisection method, or 2 for Newton-Raphson "
         "method: ");
  scanf("%i", &method_choice);

  if (method_choice== 1) { // Execute bisection method
  
    // This loop will run for M= 0:4pi over 500 steps.
    // inside of the loop, root is calculated such that E(root) \approx 0.
    // time is calculated, as a funtion of M
    M= 0.0; // initialise M, is incremented inside the loop
    r1= 1.0; // set to 1 as per instructions.
    r2= sqrt(1.0- pow(epsi,2.0));
    
    for (loop_count= 0; loop_count< 500; loop_count++) {
    
      // Calls bisection method to solve for each value of M
      root= bisection(M, delta, epsi);
      // T_orb is set to 1.0 as per instructions.
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
  } 
  
  else if (method_choice== 2) { // Execute Newton-Raphson method
    
    // This loop will run for M= 0:4pi over 500 steps.
    // inside of the loop, root is calculated such that E(root) \approx 0.
    // time is calculated, as a funtion of M
    M= 0.0; // initialise M, is incrememnted inside the loop.
    r1=1.0; // Set to 1 as per instructions.
    r2= sqrt(1.0- pow(epsi,2.0));
    
    for (loop_count = 0; loop_count< 500; loop_count++) {
    
      // Calls Newton-Raphson method to solve for each value of M
      root= newton(M, delta, epsi);
      // T_orb is set to 1.0 as per instructions.
      time= M* T_orb/ (2.0* M_PI);
      
      // calculated x and y position of orbiting body.
      // calculate relative distance between bodies.
      x= r1* cos(root);
      y= r2* sin(root);
      distance= sqrt(pow(x- epsi, 2.0)+ pow(y, 2.0));
      
      // Print command.
      fprintf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%i\n"
                , time, M, root, x, y, distance, count);
      
      // Increment M.
      M+= 4.0* M_PI/ 500.0;  
    }
    
    // the root should occur at x_new if the program reaches this point.
   printf("The program has solved Newtons method.");
    
  } 
  
  else { // User entered an invalid option
    printf("ERROR: you have entered an incorrect option.");
    return EXIT_FAILURE;
  }
  
  fclose(fp); //close the open file and exit.
  return EXIT_SUCCESS;
}

// Functions ******************************************************************

// Bisection method function
double bisection(double M, double delta, double epsi) {
  double FofA, FofC; // Function evaluated at lower_bound, and mid_point.
  double lower_bound= 0.0, mid_point, upper_bound= 4.0* M_PI; // a, b, c
  // Have chosen Bounds as general as possible, convergence still in under 30 
  // iterations per M

  count= 0.0; // Global variable so I need to reset it before each calculation.
  while (fabs(upper_bound- lower_bound)/ 2.0> delta) {
    mid_point= (upper_bound+ lower_bound)/ 2.0;
    FofA= fun(lower_bound,M,epsi); // solving function at lower bound
    FofC= fun(mid_point, M, epsi); // solving function at mid point
    
    // either the upper or lower bound is moved to the mid point.
    // keeping the upper and lower bounds at opposite signs.
    if (FofA* FofC< 0.0) (upper_bound= mid_point);
    else (lower_bound= mid_point);
    
    count++; // number of iterative steps
  }
  return ((fabs(upper_bound+ lower_bound))/ 2.0);
}

// Solves the function 
double fun(double E, double M, double epsi) {
  return E- epsi* sin(E)- M;
}

// solves the numerical derivative of the function using center point method.
double fundash(double E, double M, double epsi, double dE) {
  return ((fun( E+ dE, M, epsi)- fun(E- dE, M, epsi))/2);
}

// Newton-Raphson method function.
double newton(double M, double delta, double epsi) {
  double x_old, x_new; // x_{n+1} and x_{n} values.
  x_old= M+ epsi* sin(M); // Initial guess value.
  
  // This do while loop stops iterations if steps converge.
  // There is a check inside the loop that breaks if solution doesnt return
  // have used a do while loop so I don't have to initialise my x_new value
  count= 0;
  do {
    // single step for Newton-Raphson method.
    x_new= x_old- (fun(x_old, M, epsi))/ (fundash(x_old, M, epsi, dE)); 

    // If no convergence after 30 iterations, display error and exit.
    if (count== 29) { 
      printf("ERROR: The program has not converged to a root after 30 "
             "iterations\n");
      exit(EXIT_FAILURE);
    
    count++; // Number of iterative steps.
    }
  } while (fabs(x_new- x_old)> delta); //checks for convergrnce.
  
  return x_new; // x_new is the last calculation.
}
