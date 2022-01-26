#pragma once

#include <iostream>
#include <fstream>
#include "json.hh"
#include "game.hpp"

using json = nlohmann::json;

enum COMMANDTYPE  {
    PASS = 0,
    FLY,
};

struct Box {
    float x1,x2,y1,y2;
};

struct Command {
    COMMANDTYPE command;
    float direction; // 弧度
};

struct FrameInfo {
    std::vector<Box> stars;
};

int process(FrameInfo frame_info, Command& cmd);
int init();


