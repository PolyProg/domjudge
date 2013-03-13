/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class PortalLib1 {
	public static final int NSPEEDS = 1000;
	
	public static int nLeftTeam;
	public static int nTopTeam;
	public static int nLeftJudge;
	public static int nTopJudge;
	
	public static void answer(int T, int L){
		nLeftTeam = L;
		nTopTeam = T;
	}
	
	public static void main(String args[]){
		int ntc, nsp;
		Cube c = new Cube(0,0);
		double speeds[];
		java.util.Scanner sc = new java.util.Scanner(System.in);
		
		ntc = sc.nextInt();
		for (int i=0; i<ntc; i++){
			speeds = new double[NSPEEDS];
			c.x = sc.nextInt(); c.y = sc.nextInt(); nsp = sc.nextInt();
			for (int j=0; j<nsp; j++){
				speeds[j] = sc.nextDouble();
			}
			nLeftJudge = sc.nextInt(); nTopJudge = sc.nextInt();
			Portal1.speed_assessment(c,nsp,speeds);
			if (nLeftTeam != nLeftJudge || nTopTeam != nTopJudge){
				System.out.printf("INCORRECT - Test case %d received (Left,top) (%d,%d) / expected (%d,%d)\n",
					i+1, nLeftTeam, nTopTeam, nLeftJudge, nTopJudge);
				System.exit(0);
			}
		}
		System.out.printf("CORRECT\n");
	}
}
