#include <iostream>
#include "controller.h"

int main(int argc, char* argv[]) {

    bool isTesting = false;
    std::string floorPlanSrc = "FloorPlans/standard.txt";

    if (argc == 2) {
        isTesting = true;
        floorPlanSrc = argv[1];
    }

    // initialize controller w/ isTesting param
    Controller c;
    c.startGame(isTesting, floorPlanSrc); // maybe swap for private fields in Controller to keep track

    // GAME LOOP --------------------

    while(true) {

        char cmd;
        bool isValidMove = false;
        std::cin >> cmd;

        if (cmd == 'r') {
            c.restartGame(isTesting, floorPlanSrc);
        } else if (cmd == 'q') {
            c.quitGame();
            break;
        } else if (cmd == 'a' || cmd =='u') {
            char dir1, dir2;
            isValidMove = c.playerAction(dir1, dir2, cmd);
        } else {
            char dir2;
            isValidMove = c.playerAction(cmd, dir2);
        }

        if (isValidMove) {
            // print game
        }

        if (c.getIsFinished()) {
            std::cout << "Would you like to:\n(r) restart?\n(q) quit?" << std::endl;
            std::cin >> cmd;
            // add validity check
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
