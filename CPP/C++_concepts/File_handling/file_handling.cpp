#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
                    +------------------------+
                    |   ios                   |
                    +------------------------+
                             |
                             |
              +---------------------------+
              |                           |
       +--------------+            +-----------------+
       |  istream     |            |   ostream       |
       +--------------+            +-----------------+
            |                           |
            |                           |
    +---------------+          +-----------------+
    |   ifstream    |          |    ofstream     |
    +---------------+          +-----------------+
            |                           |
    +---------------+          +-----------------+
    |   filebuf     |          |    filebuf      |
    +---------------+          +-----------------+
*/

class FileWriter {
public:
    void writeToFile(string filename, string data) {
        ofstream file(filename);
        file << data;
        file.close();
    }
};

class FileReader {
public:
    vector<string> readFromFile(string filename) {
        vector<string> data;
        string line;
        ifstream file(filename);
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
        return data;
    }
};

class FileManager : public FileReader, public FileWriter {

};

int main() {
    FileManager file_manager;
    file_manager.writeToFile("data.txt", "Hello, World!");

    vector<string> data = file_manager.readFromFile("data.txt");
    for (string line : data) {
        cout << line << endl;
    }

    return 0;
}
