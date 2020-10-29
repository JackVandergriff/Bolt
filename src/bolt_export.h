//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_EXPORT
#   ifdef _MSC_VER
#       ifdef Bolt_EXPORTS
#           define BOLT_EXPORT __declspec(dllexport)
#       else
#           define BOLT_EXPORT __declspec(dllexport)
#       endif
#   else
#       define BOLT_EXPORT __attribute__((visibility("default")))
#   endif
#endif //BOLT_EXPORT