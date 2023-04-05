#include <iostream>
#include "controller.h"

int main(int argc, char* argv[]) {

    bool isTesting = false;
    std::string floorPlanSrc = "FloorPlans/standard.txt";

    if (argc == 2) {
        isTesting = true;
        floorPlanSrc = argv[1];
    }

    // initialize controller with isTesting param + floorPlanSrc
    Controller c {isTesting, floorPlanSrc};
    c.startGame();

    // game loop
    while(true) {
        char cmd;
        bool isValidMove = false;
        std::cin >> cmd;

        if (cmd == 'r') {
            c.restartGame();
        } else if (cmd == 'q') {
            c.quitGame();
            break;
        } else if (cmd == 'a' || cmd =='u') {
            char dir1, dir2;
            std::cin >> dir1;
            std::cin >> dir2;
            isValidMove = c.playerAction(dir1, dir2, cmd);
        } else {
            char dir2;
            std::cin >> dir2;
            isValidMove = c.playerAction(cmd, dir2);
        }

        if (!isValidMove) {
            std::cout << c.getMsg();
            continue;
        } else {
            c.printGame();
        }

        if (c.isGameOver()) {
            std::cout << "Would you like to:\n(r) restart?\n(q) quit?" << std::endl;
            std::cin >> cmd;
            while (!(cmd == 'r' || cmd == 'q')) {
                std::cout << "Invalid input. Would you like to:\n(r) restart?\n(q) quit?" << std::endl;
                std::cin >> cmd;
            }
            if (cmd == 'r') {
                c.restartGame();
            } else {
                c.quitGame();
                break;
            }
        }

    }
}





// Game can have floorPlans field,
// it's constructor will initialize the grid, and then Game::generateFloor() will destroy and then continue reading file to generate the next floor
