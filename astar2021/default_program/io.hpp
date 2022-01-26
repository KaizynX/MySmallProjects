#include "game.hpp"
int parse_frame_from_json(json frame, FrameInfo frame_infos) {
    for(auto obj: frame) {
        float x1=0, y1=0, x2=0, y2=0;
        x1 = obj["x"];
        x2 = float(obj["width"]) + x1; 
        y1 = obj["y"];
        y2 = float(obj["height"]) + y1;
        frame_infos.stars.push_back(Box{x1, x2, y1, y2});
    }
    return 0;
}

void to_json(json& j, const Command cmd) {
    j["command"] = cmd.command;
    j["direction"] = cmd.direction;
}

int dump_cmds_to_file(std::vector<Command>& cmds, std::string dumppath) {
    int frame_id = 0;
    json output_json = cmds;
    std::ofstream outs(dumppath);
    outs << output_json;
    return 0;
}

