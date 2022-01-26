/*
 * @Author: Kaizyn
 * @Date: 2022-01-24 23:39:50
 * @LastEditTime: 2022-01-26 16:58:42
 */
#include <thread>
#include "game.hpp"
#include <iostream>
#include <random>

int g_frame_id = 0;
int init() {
    g_frame_id = 0;
    return 0;
}

/*
enum COMMANDTYPE  { //命令类型
    PASS = 0, //此帧等待，不派遣飞船
    FLY, // 派遣飞船
};
struct Box { //表示星体位置坐标
    float x1,x2,y1,y2; // (x1,y1), (x2,y2)分别是左上角和右下角坐标
};
struct Command { //命令
    COMMANDTYPE command; // 命令：等待或派遣飞船
    float direction; // 如果命令是派遣飞船需要指出角度[0,360]
};
struct FrameInfo { //每帧获取到的观测信息
    std::vector<Box> stars; //观测区内所有星系的位置
};
*/

using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
constexpr unsigned M = 91377969;
constexpr double P = 52.1 / 60.0;
constexpr double PI = acos(-1);
constexpr double LD = atan(540.0 / 480.0) * 180.0 / PI;
constexpr double RD = 180.0 - LD;

inline double angle(double x, double y) {
    y = 540.0 - y;
    x = 480.0 - x;
    if (x >= 0) return atan(y / x) * 180.0 / PI;
    else return 180.0 - atan(-y / x) * 180.0 / PI;
}

inline double dist(double x, double y) {
    return sqrt((x - 480) * (x - 480) + (y - 540) * (y - 540));
}

inline double mark(Box &a) {
    return sqrt((a.x2 - a.x1) * (a.y2 - a.y1));
}

inline bool cmp(Box &a, Box &b) {
    return mark(a) > mark(b);
}

int process(FrameInfo frame_info, Command& cmd) {
    static vector<double> dir(60);
    static vector<double> val(60, 0);
    int chance = 50;
    /*
    if (g_frame_id == 0) {
        cmd.command = FLY;
        cmd.direction = 10;
    } else {
        cmd.command = PASS;
        cmd.direction = 100;
    }
    */
    std::vector<Box> &stars = frame_info.stars;
    sort(stars.begin(), stars.end(), cmp);
    for (Box &star : stars) {
        if (star.x1 < 0 || star.x2 < 0 || star.y1 < 0 || star.y2 < 0) continue;
        if (star.x1 > 960 || star.x2 > 960 || star.y1 > 540 || star.y2 > 540) continue;
        double x = (star.x1 + star.x2) / 2;
        double y = (star.y1 + star.y2) / 2;
        double dirct = angle(x, y);
        double dis = dist(x, y);
        double t = dis / 50;
        double xs = t - floor(t);
        /*
        if (xs < 0.33) tt = floor(t);
        else if (xs > 0.66) tt = floor(t) + 1;
        else continue;
        */
        int tt = floor(t) + (xs > 0.5 ? 1 : 0);
        tt = g_frame_id + 36 - tt;
        if (tt >= 60) continue;
        if (mark(star) > val[tt]) {
            val[tt] = mark(star);
            dir[tt] = dirct;
        }
    }
    cmd.command = FLY;
    if (val[g_frame_id] == 0) {
        dir[g_frame_id] = g_frame_id & 1 ? LD : RD;
        int cnt = 0;
        for (int i = g_frame_id + 1; i < 60; ++i) {
            cnt += val[g_frame_id] != 0;
        }
        if (cnt >= chance) cmd.command = PASS;
    }
    if (cmd.command == FLY) --chance;
    cmd.direction = dir[g_frame_id];
    g_frame_id ++;
    return 0;
}
