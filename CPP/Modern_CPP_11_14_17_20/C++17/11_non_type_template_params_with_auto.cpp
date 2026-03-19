non-type template parameters with auto:
template <auto N>
void printNTTP() {
    std::cout << "N = " << N << "\n";
}

int main() {
    printNTTP<42>();      // OK, deduced as int
    printNTTP<'A'>();     // OK, deduced as char
}
