#pragma once
#include <string>

struct Config {

    bool MultiSamples = false;
    bool SmoothLines = false;

    int NumberOfSamples = 2;

    int Width = 1280;
    int Height = 720;

    int EdgeLimit = 7000000;

    bool UseCircle = false;
    int CircleFragments = 100;

    int LineWidth = 2;

    int Mode = 3;

    std::string GraphPath{"hero-network-norm.csv"};

    std::string FontPath{"Aileron.otf"};
    unsigned int FontSize{48};

    static Config loadConfig(const char *path);
    static Config loadConfig(const std::string& path);
};
