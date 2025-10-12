package e316;

/**
 * 定义抽象类Income
 */
public abstract class Income {
	protected double income;
	// TODO
	public Income(double in){
		this.income = in;
	}

	abstract double getTax();

}
