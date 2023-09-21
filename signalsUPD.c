#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>
#include <math.h>

// Signal handler function
void handle_signal(int signum) {
    // Handle different types of signals
    switch(signum) {

        case SIGFPE:
            printf("Signal received: Division by zero or overflow exception occurred\n");
            break;
        default:
            printf("Signal %d occurred\n", signum);
    }
    // Exit the program with the signal number as the exit code
    exit(EXIT_FAILURE);
}


int main() {

    pid_t pid;

    float fl1, fl2, result;
    int int1, int2, div_result, intproduct, billionProduct;

    // Prompt the user for two floating-point numbers
    printf("Enter two floating-point numbers: ");
    scanf("%f%f", &fl1, &fl2);

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        printf("Error: fork failed\n");
        exit(EXIT_FAILURE);
    }

    // Child process
    if (pid == 0) { 

        // Set up signal handlers
        signal(SIGFPE, handle_signal);
        

        // Perform division of two floating-point numbers
        result = fl1 / fl2;

        // Check for floating-point exceptions
        if (isinf(result)) {
            raise(SIGFPE);
        }
        else {
            printf("Result of division: %f\n", result);
        }

        // Floating-point multiplication

        float test = FLT_MAX;

        float product = fl1 * fl2;


        if (product > test || product < -test || isinf(product)) {
            raise(SIGFPE);
        }

        printf("Result of product two float values : %f\n", product);

        product *= 1000000000;

        if (product > test || product < -test) {
            raise(SIGFPE);
        }
 
        printf("Result of product after multiplication by 1 billion: %f\n", product);

        // Prompt the user for two integer numbers
        printf("Enter two integer numbers: ");
        scanf("%d%d", &int1, &int2);

        if (int2 == 0) {
            raise(SIGFPE);
        } else {
            div_result = int1 / int2;
            printf("Integer division result: %d\n", div_result);
        }

        // Perform multiplication of two integers and check for overflow

        intproduct = int1 * int2;

         if ((int2 != 0 && intproduct / int2 != int1) || (int1 == INT_MIN && int2 == -1)) {
        
        raise(SIGFPE);

    } else {

        billionProduct = intproduct * 1000000000;
        
         if ((intproduct != 0 && billionProduct / intproduct != 1000000000) || (intproduct == INT_MIN && 1000000000 == -1)) {

        raise(SIGFPE);

    } else {

        printf("Result of integer multiplication: %d\n", billionProduct);
        }
        
    }
        
    } else { // Parent process
        wait(NULL);
    }

    return 0;
}

