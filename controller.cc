#include "controller.h"

Controller::Controller(bool isTesting, std::string floorPlanSrc) : isTesting{isTesting}, floorPlanSrc{floorPlanSrc} {};

void Controller::startGame() {

}

void Controller::restartGame() {

}

void Controller::quitGame() {

}

void Controller::printGame() {

}

bool Controller::playerAction(char dir1, char dir2, char actionType) {

}

bool Controller::isGameOver() {

}

std::string Controller::getMsg() {
    return msg;
}
