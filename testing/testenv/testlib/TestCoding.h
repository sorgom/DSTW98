#ifndef TEST_CODING_H
#define TEST_CODING_H

#include <codebase/nocopy.h>

//  enable usage of "and", "or", "not" in place of "&&", "||", "!"
#include <ciso646>

//  unified instance declaration
#define TEST_INSTANCE_DEC(NAME) \
    static NAME& instance();

//  unified instance definition
#define TEST_INSTANCE_DEF(NAME) \
    NAME& NAME::instance() \
    { \
        static NAME instance; \
        return instance; \
    }
#endif // _H
