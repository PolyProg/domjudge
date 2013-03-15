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


public class ArtLib2 {
	private static final int CODE_SIZE_MISMATCH = -1;
	private static final int CODE_NO_TOUR = -2;
	private static final int CODE_FIRST_COLOR_NOT_ONE = -3;
	private static final int CODE_NO_CONNECTION = -4;
	private static final int CODE_TOO_LONG_DIST = -5;
	private static final int CODE_TOUR_EXCESS = -6;
	
	private static int checkSolution(int n, int m, Connexion[] scheme, int[] teamColors, int[] teamTour) {
		// create set out of list of connections
		HashSet <Pair <Integer, Integer> > s = new HashSet<Pair <Integer, Integer> >();
		int a, b;
		for (int i = 0; i < m; i++) {
			a = scheme[i].a-1;
			b = scheme[i].b-1;
			s.add(new Pair(a,b));
			s.add(new Pair(b,a));
		}
		
		if (teamColors.length != n)
			return CODE_SIZE_MISMATCH;
		
		if (teamTour.length < 1)
			return CODE_NO_TOUR;
		
		for (int i = 1; i < teamTour.length; i++)
			if (s.contains(new Pair(teamTour[i-1], teamTour[i])))
				return CODE_NO_CONNECTION;
		
		if (teamColors[teamTour[0]] != 1)
			return CODE_FIRST_COLOR_NOT_ONE;
		
		int cur = 0;
		for (int i = 2; i <= n+1; i++) {
			// searching for color i
			int col = i;
			if (col == n+1)
				col = 1;
			int prev = cur;
			while ((cur < teamTour.length) && (teamColors[teamTour[cur]] != col)) {
				cur++;
			}
			if (cur == teamTour.length)
				return i;
			if (cur - prev > 3)
				return CODE_TOO_LONG_DIST;
		}
		if (cur != teamTour.length - 1)
			return CODE_TOUR_EXCESS;
		return 0;
	}

	public static void main(String args[]) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		
		int numOfCases;
		int n, m;
		numOfCases = in.nextInt();
		for (int tt = 0; tt < numOfCases; tt++) {
			n = in.nextInt();
			m = in.nextInt();
			Connexion[] scheme = new Connexion[m];
			for (int i = 0; i < m; i++) {
				int a, b;
				a = in.nextInt();
				b = in.nextInt();
				scheme[i] = new Connexion(a, b);
			}
			
			Pair<int[], int[]> teamAnswer = Art2.draw_literate_painting(n, m, scheme);
			int checkResult = checkSolution(n, m, scheme, teamAnswer.f, teamAnswer.s);
			
			if (checkResult != 0) {
				out.printf ("INCORRECT - Test case %d: ", tt+1);
				if (checkResult == CODE_SIZE_MISMATCH)
					out.printf("size mismatch, received %d, expected %d", teamAnswer.f.length, n);
				else if (checkResult == CODE_NO_TOUR)
					out.printf("received empty tour");
				else if (checkResult == CODE_FIRST_COLOR_NOT_ONE)
					out.printf("color of the first vertex in tour is not 1");
				else if (checkResult == CODE_NO_CONNECTION)
					out.printf("tour includes nonexistent connection");
				else if (checkResult == CODE_TOO_LONG_DIST)
					out.printf("distance between some pair of colors is bigger than 3 (tour is illiteral)");
				else if (checkResult == CODE_TOUR_EXCESS)
					out.printf("tour is too long, should be shorter");
				else if (checkResult > 0)
					out.printf("didn't find color %d", checkResult % n);
				else
					out.printf("unknown code error");
				out.printf("\n");
				out.close();
				System.exit(0);
			}
		}
		out.printf("CORRECT 1ZVLsWpdrdt1UGg3s4qnpuS9cJpTBHqZ\n");
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