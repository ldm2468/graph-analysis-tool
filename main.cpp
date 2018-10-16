#include "snugal.h"
#include <stdio.h>

int main(int argc, char **argv) {

	// TODO: 이 함수에서 만든 라이브러리를 실험한다
	snu::DSGraph *graph = new snu::DSGraph();
	struct snu::DSResult result;

	if(snu::basic_stat(graph, &result))
		printf("error\n");

	return 0;
}
