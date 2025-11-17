package xuexitong_test.week_11.p2;
/*
TODO:
输入两个int型数据x、y，再输入char型数据op，
实施计算：x op y，如x+y，
要求：无论如何输入，若能计算，则给出计算结果并结束；若不能计算，则给出错误提示。
要求：当传入的x、y、op满足计算要求，则能得到正确的计算结果，并返回结果(System.out.println(x+" "+op+" "+y+" = "+compute(x,y,op));)；
若不能得到正确的计算结果（如产生除零错）
或是不满足计算要求时
请设计自定义异常类（如运算符输入错误）
类内有较为准确的错误提示

import java.util.Scanner;
import  java.util.InputMismatchException;
import java.lang.ArithmeticException;

输入：

请输入两个整数x、y：
1.2 3.4
输出：
输入的数据不是int！

输入：
请输入两个整数x、y：
a 3
输出：
输入的数据不是int！

输入：
请输入两个整数x、y：
1 2
请输入运算符op：
+
输出：
1 + 2 = 3

输入：
请输入两个整数x、y：
3 0
请输入运算符op：
/
输出：
除零错误！

输入：
请输入两个整数x、y：
3 4
请输入运算符op：
a
输出：
输入的操作符只能是+、-、*、/！

输入：
请输入两个整数x、y：
2147483647 10
请输入运算符op：
+
输出：
运算溢出错误！
 */

import java.util.Scanner;
import java.util.InputMismatchException;

public class App {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while(true){
            try{
                System.out.println("请输入两个整数x、y：");
                int x = scanner.nextInt();
                int y = scanner.nextInt();
                System.out.println("请输入运算符op：");
                char op = scanner.next().charAt(0);

                int result = Compute.compute(x, y, op);     //方法throws了异常那么一定要在上层全部都有catch处理
                System.out.println(x + " " + op + " " + y + " = " + result);
                break;

            }
            catch(InputMismatchException e){
                System.out.println("输入的数据不是int！");
                break;
            }
            catch(InvalidOperatorException e){
                System.out.println(e.getMessage());
                break;
            }
            catch(ArithmeticOverflowException e){
                System.out.println(e.getMessage());
                break;
            }
            catch(ArithmeticException e){
                System.out.println(e.getMessage());
                break;
            }
        }
        scanner.close();

    }
    
}

class Compute{
    static int compute(int x, int y, char op)
            throws InvalidOperatorException, ArithmeticOverflowException, ArithmeticException {
                long result;
                switch(op){
                    case '+':
                        result = (long)x + (long)y;
                        break;
                    case '-':
                        result = (long)x - (long)y;
                        break;
                    case '*':
                        result = (long)x * (long)y;
                        break;
                    case '/':
                        if(y == 0){
                            throw new ArithmeticException("除零错误！");
                        }
                        if(x == Integer.MIN_VALUE && y == -1){          //这个CSAPP里有讲过，补码的最大最小值非对称性导致的，无法表示最小负数的相反数
                            throw new ArithmeticOverflowException("运算溢出错误！");
                        }
                        result = (long)x / (long)y;
                        break;
                    default:
                        throw new InvalidOperatorException("输入的操作符只能是+、-、*、/！");

                }   
                if(result > Integer.MAX_VALUE || result < Integer.MIN_VALUE){
                    throw new ArithmeticOverflowException("运算溢出错误！");
                }
                return (int)result;
    }

}


class InvalidOperatorException extends Exception {
    public InvalidOperatorException(String message) {
        super(message);
    }
}

class ArithmeticOverflowException extends Exception {
    public ArithmeticOverflowException(String message) {
        super(message);
    }
}