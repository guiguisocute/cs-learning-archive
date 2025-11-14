package Quickverify.exc;


import java.util.Scanner;

public class App {
    public static void main(String[] args) {
        while (true) {
            Scanner sc = new Scanner(System.in);
            int x = sc.nextInt();
            int y = sc.nextInt();
            String op = sc.next();
            char operator = op.charAt(0);
            int result = 0;
            if(operator == '+') {
                result = x + y;
            } else if(operator == '-') {
                result = x - y;
            } else if(operator == '*') {
                result = x * y;
            } else if(operator == '/') {
                result = x / y;
            }
            System.out.println("Result: " + result);
        }
        
    }
}

class opCharException extends Exception {
    public opCharException() {
        super("Invalid operator");
    }
}

static long compute(int x, int y, char operator) throws opCharException {
    long result = 0;
    switch (operator) {
        case '+':
            result = x + y;
            break;
        case '-':
            result = x - y;
            break;
        case '*':
            result = x * y;
            break;
        case '/':
            result = x / y;
            break;
        default:
            throw new opCharException();
    }
    if(result < Integer.MIN_VALUE || result > Integer.MAX_VALUE) {
        throw new ArithmeticException("Overflow/Underflow occurred");
    }
    return result;
}