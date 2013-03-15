/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

class Cube{
	public int x;
	public int y;
	public Cube(int setx, int sety){
		x = setx;
		y = sety;
	}
}

public class PortalLib2 {
	public static final int MAX_OBS = 200000;

	public static void main(String args[]){
		java.util.TreeSet<Integer> speedsJudge;
		int ntc;
		int nsp,nob,nsol,sol,teamAnswer;
		double speed;
		Cube gate;
		Cube obstacles[] = new Cube[MAX_OBS];
		java.util.Scanner sc = new java.util.Scanner(System.in);
		
		ntc = sc.nextInt();
		for (int i=0; i<ntc; i++){
			speedsJudge = new java.util.TreeSet<Integer>();
			gate = new Cube(0,0);
			
			gate.x = sc.nextInt(); gate.y = sc.nextInt(); nob = sc.nextInt();
			nsp = sc.nextInt(); nsol = sc.nextInt();
			for (int j=0; j<nob; j++){
				obstacles[j] = new Cube(0,0);
				obstacles[j].x = sc.nextInt(); obstacles[j].y = sc.nextInt(); 
			}
			// team initialize
			Portal2.initialize(gate, nob, obstacles);
			while (nsol-->0){
				sol = sc.nextInt();
				speedsJudge.add(sol);
			}
			for (int j=0; j<nsp; j++){
				speed = sc.nextDouble();
				// team queries
				teamAnswer = Portal2.check_speed(speed);
				if (teamAnswer!=0 && !speedsJudge.contains(j)){
					System.out.printf("INCORRECT - Test case %d speed %f is bad.\n",i+1,speed);
					System.exit(0);
				}
				if (teamAnswer==0 && speedsJudge.contains(j)){
					System.out.printf("INCORRECT - Test case %d speed %f would be good.\n",i+1,speed);
					System.exit(0);
				}
			}
		}
		System.out.printf("OK - 6673454bb0eb6491f54407deed2b7a23\n");
	}
}
