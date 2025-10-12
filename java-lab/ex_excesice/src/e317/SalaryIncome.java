package e317;

public class SalaryIncome implements Income{

	// TODO
	double income;

	public SalaryIncome(double in) {
		income = in;
	}

	@Override
	public double getTax() {
		return income * 0.1;
	}
}
