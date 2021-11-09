#pragma once

/* Represents a Thread */
class Thread {
public:
    Thread(Thread *childThread);
    ~Thread();
    void run();
    void start();
private:
    void *state;
    Thread *childThread;
};
