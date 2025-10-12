package e317;

/**
 * 稿费收入税率是20%
 */
public class RoyaltyIncome implements Income{
	// TODO
	double income;
	public RoyaltyIncome(double in) {
		income = in;
	}

	@Override
	public double getTax() {
		return income * 0.2;
	}
}
