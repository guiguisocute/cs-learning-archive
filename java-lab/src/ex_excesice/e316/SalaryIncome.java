package e316;

public class SalaryIncome extends Income{

	// TODO
	public SalaryIncome(double in){
		super(in);
	}
	
	@Override
	public double getTax(){
		return income * 0.1;
	}
}
