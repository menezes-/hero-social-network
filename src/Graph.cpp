#include "../include/Graph.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

Graph::Graph(const std::string & filename) : filename{filename}  {

    vertices = std::unordered_map<std::string, std::size_t>();

    matrix = std::vector<bool>(100, false);
    appearances = std::vector<int>();

    load();

}

std::size_t Graph::getArrPos(std::size_t x, std::size_t y) const {
    return vertices_size * x + y;
}


void Graph::addEdge(const std::string &source, const std::string &target) {
    auto a = addVertice(source);
    auto b = addVertice(target);
    matrix[getArrPos(a, b)] = true;
    matrix[getArrPos(b, a)] = true;
    appearances[a] += 1;
    appearances[b] += 1;

}

std::size_t Graph::addVertice(std::string name) {
    auto idx = mat_idx++; // aponta para a próxima posição.

    auto inserted = vertices.emplace(name, idx);
    if (inserted.second) { // se a chave não existia previamente
        return idx;
    } else {
        // se a chave já existia eu não faço nada, e decremento a posição anterior e retorno o id antigo
        --mat_idx;
        return (inserted.first)->second;
    }
}

std::string Graph::getName(std::size_t idx) const {
    for (const auto &i: vertices) {
        if (i.second == idx) {
            return i.first;
        }
    }
    throw std::out_of_range("Indice invalido");
}

void Graph::load() {
    auto file = std::ifstream{filename, std::ios::in | std::ios::binary};

    if (!file.is_open()) {
        throw std::runtime_error{"Não foi possível abrir o grafo"};
    }

    /**
     * A primeira linha do programa contém quantos super-heróis existem no arquiv
     * ela pode estar no formato de comentário: #12345 ou diretamente um número (12346)
     */
    std::string l1;
    std::getline(file, l1);
    if (l1[0] == '#') {
        l1 = l1.substr(1, l1.size());
    }
    std::size_t hero_n{0};
    try {
        hero_n = std::stoull(l1);
    } catch (const std::exception &e) {
        throw std::runtime_error{"Não foi possível ler o número de super-heróis do arquivo"};
    }

    matrix.resize(hero_n*hero_n, false);

    vertices_size = hero_n;
    appearances.resize(hero_n, 0);

    file.seekg(0, std::ios::beg);


    io::CSVReader<2, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>, io::throw_on_overflow, io::single_and_empty_line_comment<'#'> >
            reader(filename, file);

    reader.read_header(io::ignore_extra_column, "source", "target");

    if (!reader.has_column("source") || !reader.has_column("target")) {
        throw std::runtime_error{"Arquivo em formato incorreto! Defina as colunas source e target"};
    }

    std::string source, target;

    while (reader.read_row(source, target)) {
        addEdge(source, target);
    }

}

std::size_t Graph::getId(const std::string &name) {
    auto pos = vertices.find(name);
    if (pos != vertices.end()) {
        return pos->second;
    }
    else {
        throw std::out_of_range("Vertice nao existe");
    }
}

std::size_t Graph::getId(const char *name) {
    return getId(std::string{name});
}


