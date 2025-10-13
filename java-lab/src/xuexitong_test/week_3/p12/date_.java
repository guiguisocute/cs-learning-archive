package p12;

// import java.util.Scanner;

/*
实现一个日期类，包含成员变量year,month,day分别表示年、月和日。

要求：

  1。有两个构造方法：一个无参，默认为1971年9月1日；一个有参，根据参数初始化。

  2。重新设置年、月和日的方法。

  3。有toString()方法【作用：打印对象，默认好像是打印哈希值，得用一些重写父类的写法】，display()方法，输出结果形如：日期为：2025年8月30日

  4。有方法plusDays(int days)用于求几天后的新的日期，为减少复杂度，大家只要考虑30天内的情况。

  5。测试内中要求生成两个实例，分别用无参和有参的初始化；重新设置日期，调用两次plusDays(int days)生成两个新的日期，days的值分别为13和15

最后的输出结果为：

日期为：1971年9月1日
重新设置后的日期为：2000年9月1日
日期为：2025年8月17日
13天后的日期为：2025年8月30日
15天后的日期为：2025年9月1日

 */
public class date_ {
    public  static void main(String args[]){
      date x = new date();
      x.display();
      x.setYear(2000);
      x.setMonth(9);
      x.setDay(1);
      System.out.println("重新设置后的日期为：" + x);
      // Scanner in = new Scanner(System.in);
      // int y = in.nextInt();
      // int m = in.nextInt();
      // int d = in.nextInt();
      int y = 2025;
      int m = 8;
      int d = 17;
      date z = new date(y, m, d);
      z.display();

      date z1 = z.plusDays(13);
      date z2 = z.plusDays(15);
      
      System.out.println("13天后的日期为："+ z1);
      System.out.println("15天后的日期为：" + z2);

      // in.close();
    }
}


class date{
    private int year;
    private int month;
    private int day;

    date(){
      this.year = 1971;
      this.month = 9;
      this.day = 1;
    }
    
    date(int y, int m, int d){
      this.year = y;
      this.month = m;
      this.day = d;
    }
    @Override
    public String toString(){        //打印类名的方法，默认是类名@哈希，想要自定义就要重载父类，就是这个写法，不能省略可见性，而且只能相同或者更宽
      return year + "年" + month + "月" + day + "日";
    }

    void display(){
      System.out.println("日期为：" + this);
      
    }

    void setYear(int year){
      this.year = year;
    }

    void setMonth(int month) {
      this.month = month;
    }

    void setDay(int day) {
      this.day = day;
    }

    date plusDays(int days) {
      int y = this.year, m = this.month, d = this.day + days;
      int dim = dayInmonth(y, m);
      if (d > dim) {
        d -= dim;
        m += 1;
        if (m > 12) {
          m = 1;
          y += 1;
        }
      }
      return new date(y, m, d);
    }

    private int dayInmonth(int y, int m) {
      switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
          return 31;
        case 4:
        case 6:
        case 9:
        case 11:
          return 30;
        case 2:
          return isLeap(y) ? 29 : 28;
        default:
          return 30;
      }           //学习通OJ不支持新特性吗，很难受
    }

    private boolean isLeap(int y) {
      return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
}
