#Semantically similar to using a typedef however, type aliases with using are easier
to read and are compatible with templates.

template <typename T>
using Vec = std::vector<T>;
Vec<int> v; // std::vector<int>

using String = std::string;
String s {"foo"};
