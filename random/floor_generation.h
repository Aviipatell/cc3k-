#ifndef FLOOR_GENERATION_H
#define FLOOR_GENERATION_H

#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <string>

// Constants
extern const int WIDTH;
extern const int HEIGHT;
extern const char WALL;
extern const char HORIZONTAL_WALL;
extern const char FLOOR;
extern const char PASSAGE;
extern const char EMPTY;
enum quad { FIRST, SECOND, THIRD, FOURTH, MIDDLE };

// Function prototypes
void dfs(const std::vector<std::vector<char>> &floor_map, int row, int col, std::vector<std::pair<int, int>> &corner_tiles, std::vector<std::vector<bool>> &visited);
std::vector<std::vector<std::pair<int, int>>> detect_chamber_corner_tiles(const std::vector<std::vector<char>> &floor_map);
void drawLine(int x0, int y0, int x1, int y1, std::vector<std::vector<char>>& map);
float distance(std::pair<int, int> a, std::pair<int, int> b);
std::pair<int, int> generateRandomPoint(int x_min, int x_max, int y_min, int y_max);
std::vector<std::pair<int, int>> generateRandomPoints(int area_x_min, int area_x_max, int area_y_min, int area_y_max);
bool isCorner(std::vector<std::vector<char>> &floor, int x, int y);
bool isPointInChamber(std::vector<std::pair<int, int>> &chamber, int x, int y);
int getFloorNeighbours(std::vector<std::vector<char>> &floor, int x, int y);
bool floorInRange(std::vector<std::vector<char>> &floor, int x, int y);
void generateFloor(std::vector<std::vector<char>> &floor, std::vector<std::pair<int, int>> &points);

#endif
