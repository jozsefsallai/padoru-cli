#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

std::vector<std::string> frames;

void load_frames() {
    for (int i = 0; i < 4; ++i) {
        std::string filename = "./frames/" + std::to_string(i) + ".txt";
        std::ifstream in(filename);

        if (!in.is_open()) {
            throw std::runtime_error("Could not open frame: " + filename);
        }

        std::string frame;
        in.seekg(0, std::ios::end);
        frame.reserve(in.tellg());
        in.seekg(0, std::ios::beg);

        frame.assign(
            std::istreambuf_iterator<char>(in),
            std::istreambuf_iterator<char>()
        );

        frames.push_back(frame);
    }
}

void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void draw_frame(int index) {
    std::cout << frames[index];
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    clear_screen();
}

int main() {
    load_frames();

    while (true) {
        for (int i = 0; i < frames.size(); ++i) {
            draw_frame(i);
        }
    }

    return 0;
}
