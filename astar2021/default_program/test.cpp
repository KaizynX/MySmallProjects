#include "game.hpp"
#include "io.hpp"
#include "watchdog.hpp"

int main(int argc, char** argv) {
    std::ifstream i(argv[1]);
    std::string dumppath = argv[2];
    json input_map;
    i >> input_map;
    init();
    std::vector<Command> cmds;
    std::vector<FrameInfo> frame_infos;
    parse_frame_from_json(input_map, frame_infos);
    for (auto framinfo: frame_infos) {
        for (auto box: framinfo.stars) {
            std::cout << box.x1 << "," << box.x2 << "," << box.y1 << "," << box.y2 << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
