#include<stdio.h>

/*
*  This is a test function for the second derivative test
*
*
*/
float RightInput = 0, LeftInput = 0, CentralInput = 0;
float secondDerivative(float tempInterval);
float actual_derivative(float input);
float simulation(float input);

int main() {
    float in = 0;
    float error = 0;
    for(int i = 0; i < 500; i ++) {
        in = i * 0.005;
        LeftInput = CentralInput;
        CentralInput = RightInput;
        RightInput = simulation(in);
        error = (actual_derivative(in) - secondDerivative(0.005))/actual_derivative(in);
        printf("%s%lf%s\n","Error: ", error*100, "%");
        // printf("%s%lf\n","sim: ", simulation(in));
        // printf("%s%lf\n","actual: ", actual_derivative(in));
        // printf("%s%lf\n","calculated: ", secondDerivative(0.005));
    }

    return 0;
}

/*
*   @para: Time interval of time difference
*   Global parameters: LeftInput, RightInput, CentralInput
*   Estimation function of second derivative using Taylor Expansion
*   Error EstimatedL O(dt^3)
*   April 21th by Kaiser Sun
*/
float secondDerivative(float tempInterval) {
    return (LeftInput - 2*CentralInput + RightInput) / (tempInterval*tempInterval);
  }


/*
*    @para: input of simulation time
*    return the value of simulation
*    This function simulate t^3+3*t+13.4
*/
float simulation(float input) {
    return input * input * input + 3 * input + 13.4;
}

/*
*    @para: input of simulation time
*    return the value of real second derivative
*/
float actual_derivative(float input) {
    return 6 * input;
}