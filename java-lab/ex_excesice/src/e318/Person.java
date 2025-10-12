package e318;

public class Person {

	// TODO

	String name;
	static int COUNT = 0;

	public Person(String name) {
		this.name = name;
	}

	static int getCount(){
		return ++COUNT;
	}

}
