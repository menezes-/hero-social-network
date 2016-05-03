#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <csv.h>
#include <random>
#include <glm/glm.hpp>

class Graph {

private:
    std::size_t vertices_size = 0;
    std::size_t mat_idx = 0;
    std::unordered_map<std::string, std::size_t> vertices; //indice de nome vs id
    std::vector<bool> matrix;
    std::vector<int> appearances;
    const std::string &filename;

    friend class Scene;

  /**
  * apesar de usarmos um array de uma única dimensão vamos trabalhar com duas dimensões
  * portanto essa função serve para receber um par x, y e retornar o indice do array.
  * Ela precisa ser o mais rápida possível por isso vai ser marcada como pura usando
  * os atributos de função do GCC
  * ( https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes)
  */
    std::size_t getArrPos(std::size_t x, std::size_t y) const __attribute__ ((pure));

    std::size_t addVertice(std::string name);

    void load();


public:
    /**
     * Construtor com o número de vertices conhecidos
     */
    Graph(const std::string &);


    void addEdge(const std::string &, const std::string &);

    std::string getName(std::size_t idx) const;

    std::size_t getId(const char *name);

    std::size_t getId(const std::string &name);


};