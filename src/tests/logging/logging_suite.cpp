#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "logging_suite.h"

void thisIsATest() {
	ASSERTM("start writing tests", false);
}

cute::suite make_suite_logging_suite(){
	cute::suite s;
	s.push_back(CUTE(thisIsATest));
	return s;
}

int main(){
    make_suite_logging_suite();
}

