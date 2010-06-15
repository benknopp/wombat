#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "logging_suite.h"

void testLogggerInstanciation() {
	ASSERTM("start writing tests", false);
}

void testLoggerMessaging() {
    ASSERTM("start writing tests", false);
}

void testLoggerFileBackend() {
    ASSERTM("start writing tests", false);
}


cute::suite make_suite_logging_suite(){
	cute::suite s;
	s.push_back(CUTE(testLogggerInstanciation));
    s.push_back(CUTE(testLoggerMessaging));
    s.push_back(CUTE(testLoggerFileBackend));

    cute::ide_listener lis;
    cute::makeRunner(lis)(s, "Logging and Messaging Suite");

    return s;
}

int main(){
    make_suite_logging_suite();

    return 0;
}

