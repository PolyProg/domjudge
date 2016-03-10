#include "testlib.h"
#include <iostream>
using namespace std;

int main (int argc, char ** argv)
{
	setName("checker for collective mindsets hard");
	registerTestlibCmd(argc, argv);
	int T = inf.readInt();
	int answers[6 * 6 * 6 * 6 * 6 * 6];
	int N;
	
	for (int i = 0; i < T; ++i)
	{
		N = inf.readInt();
		int index = 0;
		for (int j = 0; j < N; ++j)
		{
			index = index * N + inf.readInt() - 1;
		}
		answers[index] = ouf.readInt() - 1;
	}
	
	int P = pow(N, N);
	for (int i = 0; i < P; ++i)
	{
		int j = N;
		int k = 1;
		int index;
		int correctAnswer;
		do
		{
			--j;
			index = j * P / N + i / (k*N) * k + i%k;
			correctAnswer = (i / k) % N;
			k *= N;
		} while (j > 0 && answers[index] != correctAnswer);
		if (answers[index] != correctAnswer)
		{
			quitf(_wa, "wrong answer");
		}
	}
	
	quitf(_ok, "correct");
}