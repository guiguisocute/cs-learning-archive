package Quickverify.checkversion;

public class CheckJavaVersion {
    public static void main(String[] args) {
        // 通用方式：System.getProperty()
        System.out.println("Java 运行时版本 (java.version): " + System.getProperty("java.version"));
        System.out.println("Java 运行时规范版本 (java.specification.version): " + System.getProperty("java.specification.version"));
        System.out.println("Java 运行时供应商 (java.vendor): " + System.getProperty("java.vendor"));
        System.out.println("Java 运行时安装路径 (java.home): " + System.getProperty("java.home"));

        // 检查当前主版本号
        String version = System.getProperty("java.version");
        int major;
        if (version.startsWith("1.")) {
            // JDK 8 及以前版本号形如 "1.8.0_421"
            major = Integer.parseInt(version.substring(2, 3));
        } else {
            // JDK 9+ 版本号形如 "25"、"21.0.1"、"17"
            int dot = version.indexOf(".");
            major = (dot != -1) ? Integer.parseInt(version.substring(0, dot))
                    : Integer.parseInt(version);
        }

        System.out.println("\n检测到主版本号: " + major);
        if (major <= 8) {
            System.out.println("当前运行在 JDK " + major + " (旧版格式 1." + major + ")");
        } else {
            System.out.println("当前运行在 JDK " + major + " 或更高版本");
        }

        // 可选提示
        if (major == 8 || major == 11 || major == 17 || major == 21) {
            System.out.println("这是一个长期支持版 (LTS)");
        } else if (major > 21) {
            System.out.println("这是未来或预览版本");
        }
    }
}

