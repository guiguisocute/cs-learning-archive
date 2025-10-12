package class_week4;

import java.math.BigDecimal;
import java.util.Scanner;

public class Bank_main {
    public static void main(String[] args) {
        bank a = new bank("A","100");
        bank b = new bank("B", "250");
        System.out.println(a);
        System.out.println(b);
        System.out.println("请输入要转账的的金额：");
        Scanner sc = new Scanner(System.in);
        String in1 = sc.nextLine();
        a.transfer(b, in1);
        sc.close();
        
    }
}

class bank{
    private String name;
    private BigDecimal value;       //金额相关实在不想用double，太灾难了
    bank(String InName, String InValue){
        name = InName;
        value = new BigDecimal(InValue);
    }

    @Override
    public String toString() {
        return name + "账户的余额为：" + value.toString();
    }

    void transfer(bank B, String InValue){
        BigDecimal in = new BigDecimal(InValue);
        if(value.compareTo(in) < 0){
            System.out.println("您的余额不足！");
        }else{
            value = value.subtract(in);
            B.value = B.value.add(in);
            System.out.println(name + "向" + B.name + "转账" + InValue + "元后:");
            System.out.println(this);
            System.out.println(B);
        }
    }

}
