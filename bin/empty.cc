#include <cstdlib>

#include <iostream>

#include "glog/logging.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "log 1";
    LOG(INFO) << "log 2";

    return EXIT_SUCCESS;
}
