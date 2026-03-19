Allows non-static data members to be initialized where they are declared, potentially 
cleaning up constructors of default initializations.

// Default initialization prior to C++11
class Human {
    Human() : age{0} {}
  private:
    unsigned age;
};
// Default initialization on C++11
class Human {
  private:
    unsigned age {0};
};
