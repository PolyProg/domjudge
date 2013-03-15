/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.InputStream;

public class ArtLib3 {
	private static final int CODE_SIZE_MISMATCH = -1;
	private static final int CODE_FIRST_CREATURE_NOT_HEIDI = -2;
	private static final int CODE_NEGATIVE_MARMOT = -3;
	private static final int CODE_NO_FRIENDSHIP = -4;

	private static int checkSolution(int n, Connexion[] scheme, int[] teamAnswer) {
		int[][] table = new int[n][n];
		boolean[] visited = new boolean[n];
		for (int i = 0; i < scheme.length; i++) {
			table[scheme[i].a-1][scheme[i].b-1] = 1;
			table[scheme[i].b-1][scheme[i].a-1] = 1;
		}
		if (teamAnswer.length != n+1)
			return CODE_SIZE_MISMATCH;
		if (teamAnswer[0] != 1)
			return CODE_FIRST_CREATURE_NOT_HEIDI;
		
		for (int i = 1; i < teamAnswer.length; i++) {
			if (teamAnswer[i] < 1)
				return CODE_NEGATIVE_MARMOT;
			else if (teamAnswer[i] > n)
				return teamAnswer[i];
			int a = teamAnswer[i-1]-1;
			int b = teamAnswer[i]-1;
			if (visited[b])
				return b+1;
			if (table[a][b] == 0) {
				return CODE_NO_FRIENDSHIP;
			}
			visited[b] = true;
		}
		// probably, because the size matches and there were no duplicate visits - 
		// then the last creature is automatically Heidi
		return 0;
	}

	public static void main(String args[]) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		
		int numOfCases = in.nextInt();
		for (int tt = 0; tt < numOfCases; tt++) {
			int n = in.nextInt();
			int m = in.nextInt();
			Connexion[] scheme = new Connexion[m];
			for (int i = 0; i < m; i++) {
				int a = in.nextInt();
				int b = in.nextInt();
				scheme[i] = new Connexion(a,b);
			}
			int[] teamAnswer = Art3.arrange_marmots(n, scheme);
			int checkResult = checkSolution(n, scheme, teamAnswer);
			if (checkResult != 0) {
				out.printf("INCORRECT - Test case %d: ", tt+1);
				if (checkResult == CODE_SIZE_MISMATCH)
					out.printf("tour size mismatch, received %d, expected %d", teamAnswer.length, n+1);
				else if (checkResult == CODE_FIRST_CREATURE_NOT_HEIDI)
					out.printf("first creature is not Heidi");
				else if (checkResult == CODE_NO_FRIENDSHIP)
					out.printf("tour includes nonexistent friendship");
				else if (checkResult == CODE_NEGATIVE_MARMOT)
					out.printf("tour includes negative marmot numbers; not our Cyberspace");
				else if (checkResult > 0)
					out.printf("creature %d is duplicated or doesn't exist at all", checkResult);
				else
					out.printf("unknown code error");
				out.printf("\n");
				out.close();
				System.exit(0);
			}
		}
		out.printf("CORRECT fHPWZsCJy6Sn7BUF0kzOxEm2CnQE83p1\n");
		out.close();
	}
}

class InputReader {
	public BufferedReader reader;
	public StringTokenizer tokenizer;

	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public int nextInt() {
		return Integer.parseInt(next());
	}

}

class Connexion {
	public int a;
	public int b;
	
	Connexion(int a_value, int b_value) {
		a = a_value; 
		b = b_value; 
	}
}
