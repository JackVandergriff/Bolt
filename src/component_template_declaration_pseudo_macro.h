//
// Copyright (c) 2020 Jack Vandergriff.
//

#if __cplusplus > 201703L // C++20 support
template<ComponentType C>
#else // stuck on C++17
template<typename C, class = typename std::enable_if<std::is_base_of<Component, C>::value>::type>
#endif