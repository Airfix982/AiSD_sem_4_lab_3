#pragma once
#include<iostream>
#include<vector>
using namespace std;











template<typename Vertex_type, typename Distance_type = double>
class Graph {
public:
    struct Edge;
    struct One_vertex;
    Graph()=default;
    ~Graph()=default;
    
private:
    vector<One_vertex> graph;

public:
    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex_type& v) const;
    void add_vertex(const Vertex_type& v);
    bool remove_vertex(const Vertex_type& v);
    std::vector<Vertex_type> vertices() const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex_type& from, const Vertex_type& to,
        const Distance_type& d);
    bool remove_edge(const Vertex_type& from, const Vertex_type& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex_type& from, const Vertex_type& to) const;
    bool has_edge(const Edge& e); //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок
    size_t degree() const; //степень


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};
Graph<int>;
