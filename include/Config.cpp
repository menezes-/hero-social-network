#include "Config.hpp"
#include <ini.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

// tirado de: http://stackoverflow.com/questions/3613284/c-stdstring-to-boolean
static bool to_bool(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

static bool to_int(const std::string &str, int &value) {
    try {
        value = std::stoi(str);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}

static bool file_exists(const std::string &string) {
    std::ifstream f(string);
    return f.good();
}

static int handler(void *cfg, const char *section, const char *name, const char *value) {
    auto config = static_cast<Config *>(cfg);
    auto string_name = std::string{name};
    auto string_value = std::string{value};

    std::transform(string_name.begin(), string_name.end(), string_name.begin(), ::tolower);
    std::transform(string_value.begin(), string_value.end(), string_value.begin(), ::tolower);
    int pvalue;

    if (string_name == "multisamples") {
        config->MultiSamples = to_bool(string_value);
    } else if (string_name == "numberofsamples") {
        if (to_int(string_value, pvalue)) {
            config->NumberOfSamples = pvalue;
        }
    } else if (string_name == "width") {
        if (to_int(string_value, pvalue)) {
            config->Width = pvalue;
        }
    } else if (string_name == "height") {
        if (to_int(string_value, pvalue)) {
            config->Height = pvalue;
        }
    } else if (string_name == "edgelimit") {
        if (to_int(string_value, pvalue)) {
            config->EdgeLimit = pvalue;
        }
    } else if (string_name == "circlefragments") {
        if (to_int(string_value, pvalue)) {
            config->CircleFragments = pvalue;
        }
    } else if (string_name == "linewidth") {
        if (to_int(string_value, pvalue)) {
            config->LineWidth = pvalue;
        }
    } else if (string_name == "usecircle") {
        config->UseCircle = to_bool(string_value);
    } else if (string_name == "smoothlines") {
        config->SmoothLines = to_bool(string_value);
    } else if (string_name == "fontpath") {
        if (file_exists(string_value)) {
            config->FontPath = string_value;
        }
    } else if (string_name == "fontsize") {
        if (to_int(string_value, pvalue) && pvalue > 0) {
            config->FontSize = pvalue;
        }
    } else if (string_name == "mode") {
        if (to_int(string_value, pvalue) && pvalue >= 1 && pvalue <= 3) {
            config->Mode = pvalue;
        }
    } else if (string_name == "graphpath") {
        if (file_exists(string_value)) {
            config->GraphPath = string_value;
        }
    } else {
        return 0;
    }

    return 1;
}

Config Config::loadConfig(const char *path) {
    auto cfg = Config();
    if (ini_parse(path, handler, &cfg) < 0) {
        std::cerr << "WARNING::CONFIGURATION: Nao foi possivel carregar o arquivo de configuração. " << path <<
        ". Usando defaults." << std::endl;
    }
    return cfg;
}

Config Config::loadConfig(const std::string &path) {
    return loadConfig(path.c_str());
}
