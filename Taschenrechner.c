#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototype
int evaluate(const char* expression);   

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
        
        int result = evaluate(input);  
        printf("result: %d\n", result);
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
int parse_term(const char** expr) {
    int value = 0;
    //const char* e = skip_whitespace(*expr);
    const char* e = *expr;
    
    if (isdigit(*e)) {
        value = strtol(e, (char**)&e, 10);  // Convert string into integer and store in value
    }
    
    // Process multiplication and division
    while (1) {
        e = skip_whitespace(e);  // Skip whitespace after number
        if (*e == '*' || *e == '/') {
            char op = *e++;
            e = skip_whitespace(e);  // Skip whitespace after operator
            int nextValue = strtol(e, (char**)&e, 10);  // Convert next number to integer
            
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
int evaluate(const char* expression) {
    const char* expr = skip_whitespace(expression); // skipp whitespace before the first number
    int result = parse_term(&expr);  // Evaluate first character
    
    // Operation of addition and substraction
    while (*expr != '\0' && *expr != '\n') {
        expr = skip_whitespace(expr);   // skipp whitespace before opeation
        char op = *expr++;  
        
        expr = skip_whitespace(expr);   // skipp whitespace after operation
        int nextValue = parse_term(&expr);  // Evaluation next character

        if (op == '+') {
            result += nextValue;
        } else if (op == '-') {
            result -= nextValue;
        }
    }
    return result;
}
