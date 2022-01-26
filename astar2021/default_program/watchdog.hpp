#pragma once

#include <thread>
#include <atomic>

class Watchdog {
public:
    Watchdog();
    Watchdog(unsigned int milliseconds, std::function<void()> callback);
    ~Watchdog();

    void Start(unsigned int milliseconds, std::function<void()> callback);
    void Stop();
    void Pet();

private:
    unsigned int _interval;
    std::atomic<unsigned int> _timer;
    std::atomic<bool> _running;
    std::thread _thread;
    std::function<void()> _callback;

    void Loop();
};

Watchdog::Watchdog() :
    _interval(10),
    _timer(0),
    _running(false) {
}

Watchdog::Watchdog(unsigned int milliseconds, std::function<void()> callback) {
    Start(milliseconds, callback);
}

Watchdog::~Watchdog() {
}

void Watchdog::Start(unsigned int milliseconds, std::function<void()> callback) {
    _interval = milliseconds;
    _timer = 0;
    _callback = callback;
    _running = true;
    _thread = std::thread(&Watchdog::Loop, this);
}

void Watchdog::Stop() {
    _running = false;
    _thread.join();
}

void Watchdog::Pet() {
    _timer = 0;
}

void Watchdog::Loop() {
    while (_running) {
        _timer++;

        if (_timer >= _interval) {
            _running = false;
            _callback();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

