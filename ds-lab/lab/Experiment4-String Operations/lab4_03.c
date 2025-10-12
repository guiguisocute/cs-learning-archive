/*
3．利用字符顺序栈，设计并实现算术表达式求值的程序，请将相关函数补充完整。（实验代码
详见 lab4_03.c）
*/
#include <stdio.h>
#include <string.h>
#include "stack.h"  
/*引入自定义的字符栈结构*/
/**********************/
/* 判断是否为运算符   */ 
/*********************/
int is_op(char op)
 {
   switch(op)
  { case '+':
    case '-':
    case '*':
    case '/':return 1;
    default:return 0;
    }
 }
/****************************/
/*   判断运算符的优先级     */
/****************************/
int priority(char op)
   {
     switch(op)
       {
          case '(':return 0;
          case '+':
          case '-':return 1;
          case '*':
          case '/':return 2;
	    default: return -1;
        }
  }

/****************************************
 * 将中缀表达式转换为后缀表达式
 * 参数说明：
 *   infix[] - 输入的中缀表达式字符数组
 *   postfix[] - 输出的后缀表达式字符数组
 ****************************************/
void postfix(char infix[], char postfix[])
{
    seqstack operatorStack;  // 运算符栈
    int inputIndex = 0;      // 输入表达式索引
    int outputIndex = 0;     // 输出表达式索引
    
    // 初始化栈并压入空字符作为哨兵
    initstack(&operatorStack);
    push(&operatorStack, '\0');

    while (infix[inputIndex] != '\0') 
    {
        // 处理数字和小数点：直接输出到后缀表达式
        if ((infix[inputIndex] >= '0' && infix[inputIndex] <= '9') || infix[inputIndex] == '.') {
            postfix[outputIndex++] = infix[inputIndex];
        }
        // 处理左括号：直接入栈
        else if (infix[inputIndex] == '(') {
            push(&operatorStack, infix[inputIndex]);
        }
        // 处理右括号：弹出栈元素直到遇到左括号
        else if (infix[inputIndex] == ')') {
            while (stacktop(&operatorStack) != '(') {
                postfix[outputIndex++] = pop(&operatorStack);
            }
            pop(&operatorStack); // 弹出左括号但不输出
        }
        // 处理运算符（+ - * /）
        else if (is_op(infix[inputIndex])) {
            // 添加空格分隔操作数(就是数字啦)
            postfix[outputIndex++] = ' ';
            
            // 弹出优先级更高或相等的运算符
            while (priority(stacktop(&operatorStack)) >= priority(infix[inputIndex])) {
                postfix[outputIndex++] = pop(&operatorStack);
            }
            
            // 当前运算符入栈
            push(&operatorStack, infix[inputIndex]);
        }
        
        inputIndex++; // 处理下一个字符
    }

    // 弹出栈中剩余的所有运算符
    while (!stackempty(&operatorStack)) {
        postfix[outputIndex++] = pop(&operatorStack);
    }
    
    postfix[outputIndex] = '\0'; // 添加字符串结束符
}
/****************************************
 * 将字符串形式的数字转换为浮点数
 * 参数说明：
 *   str[] - 输入字符串
 *   index - 当前读取位置的指针（会被修改）
 * 返回值：转换后的浮点数值
 ****************************************/
float readnumber(char str[], int *index)      //这个index是可以直接定位一个后缀表达式，读完一个数以后指针会自动推进到非数字字符的部分
{
    float number = 0.0;
    int decimalPlaces = 0; // 记录小数位数
    
    // 处理整数部分
    while (str[*index] >= '0' && str[*index] <= '9') {
        number = number * 10 + (str[*index] - '0');
        (*index)++;
    }
    
    // 遇到小数点时处理小数部分
    if (str[*index] == '.') {
        (*index)++; // 跳过小数点
        
        while (str[*index] >= '0' && str[*index] <= '9') {
            // 继续累加数值，同时记录小数位数
            number = number * 10 + (str[*index] - '0');
            (*index)++;
            decimalPlaces++;
        }
    }
    
    // 根据小数位数调整最终数值
    while (decimalPlaces > 0) {
        number /= 10.0;
        decimalPlaces--;
    }
    printf("\n*%f*",number);
    return number;
}

/****************************************/
/*         后缀表达式求值程序           */
/****************************************/
float  evalpost(char f[])
{
    float   obst[50]; 
    int top = -1;    /*这两行是定义操作数栈*/
    int pos = 0;
     /*请将本函数补充完整
     个人感觉这个计算的函数反而在算法里面是最简单的……，

     核心思路就是把中置表达式转化成后缀表达式后，然后把该数组元素从左到右逐一入新栈`obst`，如果遇到了操作符，那就执行对应操作(我这里用switch case)，把结果再入栈，然后重复读取后缀字符串数组直到指向为空，

     实现的麻烦程度可能比前置那些函数还要小些,如果重新写起我可能还好一点，但做完形填空就得阅读一下揭老师给的函数类型和主函数里到底想表达什么含义……，这个double绝对是写错了吧……主函数是%f前面也一直都用浮点类型

     因为datatype与头文件里的不符合，所以这里的出栈进栈操作应该得自己写，揭老师应该是这也意思吧*/
     while(f[pos] != '\0'){
      while(f[pos] == ' '){       //如果遇到空格就跳过
        pos++;
      }
      if(f[pos] >= '0' && f[pos] <= '9'){   //如果空格后面的数是数字的话
          obst[++top] = readnumber(f,&pos);     //直接进栈
      }else{
        float b,a;
        switch(f[pos]){
          case '+' : //是操作数的话就先出栈取两个进行相应操作然后把结果入栈
          b = obst[top--];
          a = obst[top--];
          obst[++top] = a + b;
          break;
          case '-' : 
          b = obst[top--];
          a = obst[top--];
          obst[++top] = a - b;
          break;
          case '*' : 
          b = obst[top--];
          a = obst[top--];
          obst[++top] = a * b;
          break;
          case '/' : 
          b = obst[top--];
          a = obst[top--];
          obst[++top] = a / b;
          break;
        }
        pos++;      //别忘记手动移一下
      }      
     }
    return obst[top];
}

/*
主程序：输入中缀表达式，经转换后输出后缀表达式
*/
int main()
 {
        char e[50],f[50];
        int i;
        printf("\n\n请输入中缀表达式:\n");
        // gets(e);    //从标准输入设备读字符串函数，其可以无限读取，不会判断上限，以回车结束读取（gcc认为这个函数不安全，我自己手动换成fgets了）
        fgets(e,sizeof(e),stdin);
        e[strcspn(e,"\n")] = '\0';
        postfix(e,f);     //转后缀表达式的函数
        i=0;
        printf("\n\n对应的后缀表达式为: [");
        while (f[i]!='\0')
                printf("%c",f[i++]);
        printf("]");
        printf("\n\n计算结果为 :");
        printf("\n\n%f",evalpost(f));
        return 0;
 }
