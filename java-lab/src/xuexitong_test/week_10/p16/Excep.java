package xuexitong_test.week_10.p16;


/*TODO:求得字符串为数值的和。
输出：

index should be an Double.
index should be an Double.
Index out of  bounds.
sum=168.0
*/
class Excep{
    public static void main(String[] args)

    {
        String[] str = { "45", "1th", "123", "123er45" };
        // 补充完整
        double sum = 0.0;
        for (int i = 0; i <= str.length; i++) {     //改成=故意测试数组异常的测试
            try {
                double num = Double.parseDouble(str[i]);
                sum += num;
            } catch (NumberFormatException e) {
                System.out.println("index should be an Double.");
            } catch (ArrayIndexOutOfBoundsException e){
                System.out.println("Index out of  bounds.");
            }
        }
        System.out.println("sum=" + sum);
    }
}
