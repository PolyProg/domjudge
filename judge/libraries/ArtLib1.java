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
import java.util.HashSet;

public class ArtLib1 {
	private static int checkSolution(int N, int[] teamAnswer) {
		HashSet<Integer> colors = new HashSet<Integer>();
		if (N != teamAnswer.length)
			return -1;
		for (int i = 0; i < teamAnswer.length; i++) {
			if (teamAnswer[i] < 1)
				return -2;
			else if (teamAnswer[i] > 2*N-1)
				return teamAnswer[i];
			else if (colors.contains(teamAnswer[i]))
				return teamAnswer[i];
			else {
				colors.add(teamAnswer[i]);
			}
		}
	
		for (int i = 1; i < N; i++) {
			int l1 = teamAnswer[i-1];
			int l2 = teamAnswer[i];
			if (colors.contains(Math.abs(l1-l2)))
				return Math.abs(l1-l2);
			else {
				colors.add(Math.abs(l1-l2));
			}
		}
		return 0;
	}
	
	public static void main(String args[]) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		
		int numOfCases = in.nextInt();
		int N;
		for (int tt = 0; tt < numOfCases; tt++) {
			N = in.nextInt();
			int[] teamAnswer = Art1.draw_charming_painting(N);
			int checkResult = checkSolution(N, teamAnswer);
			if (checkResult != 0) {
				if (checkResult == -1)
					out.printf("INCORRECT - Test case %d: size mismatch, received %d, expected %d\n",
								tt+1, (int) teamAnswer.length, N);
				else if (checkResult > 2*N-1)
					out.printf("INCORRECT - Test case %d: colors are too high, received %d\n",
								tt+1, checkResult);
				else if (checkResult == -2)
					out.printf("INCORRECT - Test case %d: received color less than 1\n",
								tt+1);
				else
					out.printf("INCORRECT - Test case %d has duplicate in the coloring %d\n",
								tt+1, checkResult);
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