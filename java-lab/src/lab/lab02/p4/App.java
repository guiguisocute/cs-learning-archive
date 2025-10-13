package p4;

/*
假设给定输入：1.2+3.4*（5.6-7.8/（9.0-10））。请借助正则表达式实现：（1）提取出
所有的操作数，并输出； （2）提取出所有的运算符（注意左右括号也视为运算符）；
 */

import java.util.regex.Matcher;

public class App {
    public static void main(String[] args) {
        String str = "1.2+3.4*(5.6-7.8/(9.0-10))";
        String regex1 = "\\d+(\\.\\d+)?"; //匹配操作数,java好恶心啊，所有转义字符还要多打一个反斜杠，不是纯纯恶心人
        String regex2 = "[+\\-*/()]"; //匹配运算符

        System.out.println("操作数有：");
        Matcher m1 = java.util.regex.Pattern.compile(regex1).matcher(str);      //前一个参数是说把regex1编译成一个待匹配文本的对象（不可变，变成类似游标的作用，用于传递给Matcher的构造方法），.matcher(str)就是把str给输进去，传给matcher构造对象的另一个参数
        /*  这里的对象初始化并没有用new，这是为什么？：
                因为matcher的构造方法并非用户可见，这个创建链实际上是先构造了一个Pattern p，然后再把p给传到Matcher构造方法的另一个参数，其实就是已经new了，只不过用户不可见
                Pattern p = regex.Pattern.compile(regex1)
                Matcher m1 = new matcher(p,matcher)
                maybe这样
        */

        while (m1.find()) {     //m1.find()就是从*当前位置*继续搜索下一个匹配，如果找到了，就把“这次匹配的开始和结束位置”记录下来（用于.group，自己的下一次匹配开始，或者其他方法），然后再返回true，如果没找到当然就是直接返回 false了

            System.out.print(m1.group() + " ");     // 取出*最近一次*成功匹配的内容，也就是说，只有.find为true时，这个方法才能具有意义

        }
        System.out.println("\n运算符有：");
        Matcher m2 = java.util.regex.Pattern.compile(regex2).matcher(str);
        while (m2.find()) {
            System.out.print(m2.group() + " ");
        }
    }
}

