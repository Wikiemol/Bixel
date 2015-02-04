#include <stdio.h>
#include "logger.hpp"

//namespace oliLog {
    void olilog::log(std::string 
                #ifdef LOG 
                log 
                #endif
                ) {

        #ifdef LOG
            fprintf(stderr, "%s\n", log.c_str());
        #endif
    }
//};
