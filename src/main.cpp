#include "config.h"
#include <iostream>
#include <tendril.h>
int main(int argc, char *argv[]) {
    try {
        tendril::version();
        tendril::start(argc, argv);
    }
    catch(std::string exception) {
        std::cerr << exception << "\n";
        tendril::stop();
        exit(1);
    }
    catch(...) {
        std::cerr << "Unknown exception" << "\n";
        tendril::stop();
        exit(1);
    }
    return 0;
}