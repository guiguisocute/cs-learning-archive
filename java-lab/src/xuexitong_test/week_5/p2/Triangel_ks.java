package p2;

/*
设计一个三角形类：

  1.三角形有三条边；

  2.实现三种构造方法（有参，无参，拷贝）；

  3.三角形提供五项服务：

       计算周长、计算面积、 修改三条边的值、判断两个三角形是否相等、实现toString()方法获得三条边的信息，输出信息方法（通过调用toString()实现）。

    注：面积计算的海伦公式为：

      Math.sqrt(p*(p-a)*(p-b)*(p-c))，

       其中p是半周长，a/b/c是边,Math.sqrt()是开平方函数。
       输出结果：

三角形的边为：x=2.0,y=3.0,z=4.0
三角形的边为：x=2.0,y=2.0,z=3.0
三角形的边为：x=2.0,y=2.0,z=3.0
三角形的面积为：1.984313483298443
三角形的周长为：9.0
三角形的边为：x=4.0,y=5.0,z=6.0
false
 */

class Triangel_ks{

    public static void main(String[] args){

        Triangle t1=new Triangle(2,3,4);

        Triangle t2=new Triangle( );

        Triangle t3=new Triangle(t2);

        t1.disp();

        t2.disp();

        t3.disp();

        System.out.println("三角形的面积为："+t3.area());

        System.out.println("三角形的周长为："+t1.per());

        t2.setEdge(4,5,6);

        t2.disp();

        System.out.println(t2.equals(t3));

    }



}

class Triangle {//补充完整
  double a;
  double b;
  double c;
  
  Triangle(){
    a = 2.0;
    b = 2.0;
    c = 3.0;
  }

  Triangle(double x, double y, double z){
    a = x;
    b = y;
    c = z;
  }

  Triangle(Triangle t){
    a = t.a;
    b = t.b;
    c = t.c;
  }

  @Override
  public String toString(){
    return "三角形的边为：x=" + a + ",y=" + b + ",z=" + c;
  }

  boolean equals(Triangle t){
    if (a == t.a && b == t.b && c == t.c) {
      return true;
    } else {
      return false;
    }
  }

  void disp(){
    System.out.println(this);
  }

  double area(){
    double p = (a + b + c) / 2;
    return Math.sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double per(){
    return Math.round((a + b + c) * 10) / 10.0;
  }
  void setEdge(double x, double y, double z){
    a = x;
    b = y;
    c = z;
  }
}
