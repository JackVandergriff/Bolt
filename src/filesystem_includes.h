//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_FILESYSTEM_INCLUDES_H
#define BOLT_FILESYSTEM_INCLUDES_H

#if  defined(__GNUC__) && !defined(__clang__) && (__GNUC__ <= 7)
#include <experimental/filesystem> // Using old gcc, need to use technical specification
namespace fs = std::experimental::filesystem;
#else
#include <filesystem> // Using clang or modern gcc, even clang 7 has std::filesystem
namespace fs = std::filesystem;
#endif

#endif //BOLT_FILESYSTEM_INCLUDES_H
