### 3.4.3 示例:模拟主板集成各类板卡



【例 3.8】 模拟实现如下情形:PC 包括主板,主板上有 5 个 PCI 插槽,可插装显卡、声卡、网卡等 PCI 设备。主板启动、关机时,依次启动、关闭主板上的各设备。

**目的:** ①厚度接口与实现类之间的关系,以及类如何实现接口;②怎样何时需要用类口数组,如何定义和使用接口数组。

**设计:** PCI 接口有启动、运行、关闭三个方法,显卡、声卡、网卡等是实现 PCI 接口。主板上有能容纳 5 个元素的 PCI 数组(代表 5 个 PCI 插槽),另有计算机类。代码详见 Ch_3_7.java。


```java
interface PCI {
	void start();

	void run();

	void stop();
}// PCI 接口

class DisplayCard implements PCI {
	public void start() {
		System.out.print("显卡启动");
	}

	public void run() {
		System.out.print("显卡运行");
	}

	public void stop() {
		System.out.print("显卡停止");
	}
}//显卡

class NetCard implements PCI{...} // 网卡设计与显卡类似,略

class SoundCard implements PCI{...} // 声卡设计与显卡类似,略

class Mainboard {
	PCI[] pci = new PCI[5]; // 主板提供5个PCI插槽

	void addPCI(PCI p) { // 向主板插入 PCI 设备 p
		for (int i = 0; i < pci.length; i++)
			if (pci[i] == null) {
				pci[i] = p;
				return;
			}
	}

	void run() { // 运行主板上的所有设备
		for (int i = 0; i < pci.length; i++)
			if (pci[i] != null) {
				pci[i].start();
				pci[i].run();
			}
	}

	void stop() { // 停止主板上的所有设备
		for (int i = 0; i < pci.length; i++)
			if (pci[i] != null)
				pci[i].stop();
	}
}

class Computer {
	private Mainboard mb = new Mainboard();

	Computer() { // 创建时要插入各板卡
		mb.add(new DisplayCard());
		mb.add(new SoundCard());
		mb.add(new NetCard());
	}

	void start() {
		System.out.print("【开机】");
		mb.run();
	}

	void stop() {
		System.out.print("\n【关机】");
		mb.stop();
	}
}

public class App {
	public static void main(String[] args) {
		Computer c = new Computer();
		c.start();
		c.stop();
	}
}
```

**【输出结果】**

【开机】 显卡启动-显卡运行 声卡启动-声卡运行 网卡启动-网卡运行

【关机】 显卡停止 声卡停止 网卡停止

**【示例分析】**

(1) 显卡、声卡、网卡等属于不同类型体系,故共性 PCI 只能是接口,显卡等类实现该接口。

(2) 实现接口,就是对接口中定义的所有抽象方法提供方法体。由于接口中的方法均为 public, 故接口实现类对应方法前必须加上 public。

(3) `new PCI[5]` 创建的是数组对象,不是接口对象。该数组能容纳所有实现 PCI 接口类的对象,即显卡对象。从效果上看,接口相当于实现类的超类。

(4) 接口不是类,不能自己造对象。但可以使用类实现的对象。“当然,只能“使用”接口中定义的成员,如 `pci[i].start()`。

(5) 本例的 MainBoard 类是按框架来序, 基于接口 PCI 来编程,可插装 PCI 实现类的对象。