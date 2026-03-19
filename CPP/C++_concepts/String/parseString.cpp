1. Using std::stringstream

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string input = "This is an example sentence";
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    // Tokenize by spaces
    while (ss >> token) {
        tokens.push_back(token);
    }

    // Print tokens
    for (const auto& t : tokens) {
        std::cout << t << std::endl;
    }

    return 0;
}
In this example, std::stringstream reads words separated by whitespace. Each token is added to a std::vector.

2. Using std::getline with a delimiter
If you want to use a custom delimiter, std::getline can be used with a std::stringstream:

cpp
Copy code
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string input = "apple,orange,banana,grape";
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    // Tokenize by comma
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    // Print tokens
    for (const auto& t : tokens) {
        std::cout << t << std::endl;
    }

    return 0;
}
Here, std::getline splits the string using a comma as a delimiter.

3. Using std::strtok from C Standard Library
For a more C-like approach, you can use std::strtok:

cpp
Copy code
#include <iostream>
#include <cstring>

int main() {
    char input[] = "word1,word2,word3,word4";
    const char* delimiter = ",";

    // Tokenize
    char* token = std::strtok(input, delimiter);
    while (token != nullptr) {
        std::cout << token << std::endl;
        token = std::strtok(nullptr, delimiter);
    }

    return 0;
}
Note: std::strtok modifies the input string, so you should be careful if you need to preserve the original string.

4. Using std::regex (C++11 and above)
For more advanced tokenization, you can use regular expressions:

cpp
Copy code
#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::string input = "word1,word2,word3,word4";
    std::regex delimiter(",");
    std::sregex_token_iterator iter(input.begin(), input.end(), delimiter, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens(iter, end);

    // Print tokens
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
Here, the regular expression is used to split the string based on a delimiter.

Summary
std::stringstream: Simple and effective for whitespace or single character delimiters.
std::getline: Similar to std::stringstream, but more control over delimiters.
std::strtok: C-style tokenizer, modifies the original string.
std::regex: Flexible and powerful, but slower for simple cases.
