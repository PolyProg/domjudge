/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "takeawayLib3.h"

int main() {
	if (!strcmp(ready_for_contest(), "We hereby digitally sign the hc2 terms and conditions")) {
		printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
		return 0;
	}
	if (!strcmp(ready_for_contest(), "Hiermit unterzeichnen wir digital die hc2 Bedingungen und Konditionen")) {
		printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
		return 0;
	}
	if (!strcmp(ready_for_contest(), "Par la presente, nous signons numeriquement les conditions de participation au concours hc2")) {
		printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
		return 0;
	}
	printf("Incorrect\n");
	return 0;
}
