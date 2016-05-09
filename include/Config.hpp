#pragma once

struct Config {

    bool MultiSamples = false;
    int NumberOfSamples = 2;

    int Width = 1280;
    int Height = 720;

    int EdgeLimit = 7000000;

    bool UseCircle = false;
    int CircleFragments = 100;

    int LineWidth = 2;

    static Config loadConfig(const char *path);

};
