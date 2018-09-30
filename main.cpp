#include "snugal.h"

int main(int argc, char **argv) {

	// TODO: 이 함수에서 만든 라이브러리를 실험한다
	snu::Graph *graph = new snu::Graph();
	struct snu::basic_result result;

	snu::basicstat(graph, result);

	return 0;
}
