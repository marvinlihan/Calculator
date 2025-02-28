#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function prototype
double evaluate(const char* expression); 
int is_valid_expression(const char *input);
const char* skip_whitespace(const char* expr);

int main() {
    char input[256];    // Size of INput for user
    
    printf("Welcome to the interactive calculator!\n");
    printf("Enter a mathematical expression (max 256 char) or type 'exit' to quit.\n");
    
    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin); // Store the input(bytes) in input array
        
        if (strncmp(input, "exit", 4) == 0) {   // Exit if user types "exit"
            break;
        }
        
        if (!is_valid_expression(input)) {      // checks if user types valid input
            continue;
        }
        
        double result = evaluate(input); 
        if(isinf(result)){                          // Checks if the result is infinity, which should only appear if the user divides by 0
            printf("Dividing by zero is not permitted\n");
        }
        else{
            printf("result: %.2f\n", result);       // result has now 2 decimal places
        }
    }
    
    return 0;
}

// Function to convert substring into an double
double parse_term(const char** expr) {
    double value = 0;
    const char* e = *expr;

    int sign = 1;               // positive sign
    // check sign before the first number
    while (*e == '+' || *e == '-') {
        if (*e == '-') {
            sign = -sign;       // switch sign if '-' detected     
        }
        e++;
    }


    if(*e == '*' || *e == '/'){
        printf("Error: one '%c' operation too much. Your result is not correct!\n", *e);
    }
    
    if (isdigit(*e)) {
        value = strtod(e, (char**)&e);  // Convert string into double and store in value
        value *= sign;                  // add sign to the value
    }
    
    // Process multiplication and division
    while (1) {
        e = skip_whitespace(e);  // Skip whitespace after number
        if (*e == '*' || *e == '/') {
            char op = *e++;
            e = skip_whitespace(e);  // Skip whitespace after operator

            const char* check = e;

            // checks if two '*' or '/' character are between two numbers
            while (!isdigit(*check) && *check != '\0') {  
                if (*check == '*' || *check == '/') {  
                    printf("Error: one '%c' operation too much. Your result is not correct!\n", *check);
                    break;
                }
            check++;  
            }

            int nextSign = 1;           // check sign from nextvalue
            while (*e == '+' || *e == '-') {  
                if (*e == '-'){
                     nextSign = -nextSign;
                }
                e++;
            }


            double nextValue = strtod(e, (char**)&e);  // Convert next number to double
            nextValue *= nextSign;                     // add sign to "next"value 

            if (op == '*') {
                value *= nextValue;
            } else if (op == '/') {
                value /= nextValue;
            }
        } else {
            break;  // Exit loop if no "*"" or "/" operator is found
        }
    }
    *expr = e;  // Update the expression pointer to point to the next character
    return value;
}

// Function to evaluate a mathematical expression
double evaluate(const char* expression) {
    const char* expr = skip_whitespace(expression); // skipp whitespace before the first number
    double result = parse_term(&expr);  // Evaluate first character
    
    // Operation of addition and substraction
    while (*expr != '\0' && *expr != '\n') {
        expr = skip_whitespace(expr);   // skipp whitespace before opeation
        char op = *expr++; 
        
        expr = skip_whitespace(expr);   // skipp whitespace after operation

        int sign = 1;                   // check sign           
        while (*expr == '+' || *expr == '-') {  
            if (*expr == '-'){
                sign = -sign;
            }
            expr++;
        }


        double nextValue = parse_term(&expr);  // Evaluation next character
        nextValue *= sign;                     // add sign 


        if (op == '+') {
            result += nextValue;
        } else if (op == '-') {
            result -= nextValue;
        }
    }
    return result;
}



// Function to skip unnecessary whitespaces
const char* skip_whitespace(const char* expr) {
    while (*expr == ' ') {
        expr++;
    }
    return expr;
}

// Function to check if expression is valid
int is_valid_expression(const char *input) {
    while (*input) {
        if (!(isdigit(*input) || *input == '+' || *input == '-' || *input == '*' || *input == '/' || *input == ' ' || *input == '\n')) {    // all valid characters
            printf("Error: '%c' is not valid character!\n", *input);
            return 0; 
        }
        input++;
    }
    return 1;
}