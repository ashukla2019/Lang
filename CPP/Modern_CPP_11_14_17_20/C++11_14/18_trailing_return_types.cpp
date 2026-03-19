C++11 allows functions and lambdas an alternative syntax for specifying their return types.

int f() {
  return 123;
}
// vs.
auto f() -> int {
  return 123;
}
auto g = []() -> int {
  return 123;
};
This feature is especially useful when certain return types cannot be resolved:

// NOTE: This does not compile!
template <typename T, typename U>
decltype(a + b) add(T a, U b) {
    return a + b;
}

// Trailing return types allows this:
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
