#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Position {
    int row;
    int col;
};

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Invalid amount of args. Pass in a Floor Plan Source." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> grid;

    std::vector<std::vector<Position>> chamberPositions;
    int chamberCount = 0;
    int row = 0;
    int col = 0;


    std::ifstream myfile{argv[1]};
    if (myfile.is_open()) {
        std::string currentLine;
        while(std::getline(myfile, currentLine)) {
            std::vector<char> curCellRow;
            std::istringstream iss{currentLine};
            char c;
            while (iss >> std::noskipws >> c) {
                curCellRow.push_back(c);

                if (c == '.') {

                    if (grid[row])





                }


                ++col;
            }

            grid.push_back(curCellRow);
            ++row;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }

    // print grid
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
