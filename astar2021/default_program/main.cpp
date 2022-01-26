#include "game.hpp"
#include "io.hpp"
#include "watchdog.hpp"

int main(int argc, char** argv) {
    std::ifstream i(argv[1]);
    std::string dumppath = argv[2];
    int num_frames = 0;
    json input_map;
    i >> input_map;
    json star_frames = input_map["starFrames"];
    num_frames = star_frames.size();
    init();
    std::vector<Command> cmds;
    cmds.resize(num_frames);
    for (auto& cmd: cmds) {
        cmd.command = PASS;
    }
    Watchdog watch_dog(10, [&]() {
            std::cerr << "Time Limit Exceeded" << std::endl;
            dump_cmds_to_file(cmds, dumppath);
            std::terminate();
            });
    for (int frame_idx = 0; frame_idx < num_frames; frame_idx+=10) {
        FrameInfo frame_info;
        parse_frame_from_json(star_frames[frame_idx], frame_info);
        watch_dog.Pet();
        process(frame_info, cmds[frame_idx]);
    }
    dump_cmds_to_file(cmds, dumppath);
    watch_dog.Stop();
    return 0;
}
