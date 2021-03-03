//
// Created by Seven on 2021/3/3.
//
#include <signal.h>
#include <iostream>
#include "world.h"
#include <unistd.h>
#include <thread>

using namespace std;

void test1(World &world);

void test2(World &world);

bool s_bToClose = false;
int s_signum = 0;

void signalHandler(int signum) {
    cout << "Interrupt signal (" << signum << ") received." << endl;
    s_bToClose = true;
    s_signum = signum;
}

int main() {
    signal(SIGINT, signalHandler);
    cout << " ---- main ----" << endl;

    World world;

    thread t1(test1, ref(world));
    t1.detach();

    thread t2(test2, ref(world));
    t2.detach();

    while (true) {

        if (s_bToClose) {
            world.serverRunning = false;
            exit(s_signum);
        }

        // TODO main thread stuff...
        cout << "main: current count is " << world.count << "." << endl;
        sleep(1);
    }

    return 0;
}


void test1(World &world) {
    while (true) {
        if (!world.serverRunning) {
            exit(0);
        }

        world.count++;
        cout << "test1: setTo " << world.count << "." << endl;
        sleep(3);
    };
}

void test2(World &world) {
    while (true) {
        if (!world.serverRunning) {
            exit(0);
        }


        cout << "test2: show " << world.count << "." << endl;
        sleep(3);
    };
}