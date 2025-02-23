#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototype
double evaluate(const char* expression);   

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
        
        double result = evaluate(input);  
        printf("result: %.2f\n", result);       // result has now 2 decimal places
    }
    
    return 0;
}

// Function to skip unnecessary whitespaces
const char* skip_whitespace(const char* expr) {
    while (*expr == ' ') {
        expr++;
    }
    return expr;
}

// Function to convert substring into an integer
double parse_term(const char** expr) {
    double value = 0;
    const char* e = *expr;
    
    if (isdigit(*e)) {
        value = strtod(e, (char**)&e);  // Convert string into double and store in value
    }
    
    // Process multiplication and division
    while (1) {
        e = skip_whitespace(e);  // Skip whitespace after number
        if (*e == '*' || *e == '/') {
            char op = *e++;
            e = skip_whitespace(e);  // Skip whitespace after operator
            double nextValue = strtod(e, (char**)&e);  // Convert next number to double
            
            if (op == '*') {
                value *= nextValue;
            } else if (op == '/') {
                if(nextValue == 0){
                    printf("Fehler\n"); // Beheben
                }
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

        // Check if after operation comes another operation 
        if (!isdigit(*expr++)){
            *expr--;
            if(*expr++ != '+') {
            printf("Error: one '%c' operation to much.\n", expr[*expr]);    // Rückgabe Zeichen falsch !!!
            return 0;  
            }
        }
        *expr--;    // decrease array position because of "isdigit(*expr++)"

        double nextValue = parse_term(&expr);  // Evaluation next character

        if (op == '+') {
            result += nextValue;
        } else if (op == '-') {
            result -= nextValue;
        }
    }
    return result;
}
