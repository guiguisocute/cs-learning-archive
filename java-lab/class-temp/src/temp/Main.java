package temp;
// 这是 Java 25 的新语法

public class Main {
    void main() {
        // java.base 模块导出的所有包（如 java.util、java.io、java.time …）
        // 里的类现在都能直接用，不需要单独 import
        List<String> list = List.of("Java", "25", "Module");
        System.out.println(list);

        Path path = Path.of(System.getProperty("user.home"));
        System.out.println("Home directory: " + path);

        LocalDate today = LocalDate.now();
        System.out.println("Today is " + today);
    }
}