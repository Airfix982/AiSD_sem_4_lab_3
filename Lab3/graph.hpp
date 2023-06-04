#pragma once
#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;

template<typename Vertex_type, typename Distance_type = double>
struct Edge
{
    Vertex_type to;
    Distance_type weight;
    Edge(Vertex_type to, Distance_type weight = 0) : to(to), weight(weight) {};
    Edge(const Edge& other_one) : to(other_one.to), weight(other_one.weight) {};
};
template<typename Vertex_type, typename Distance_type = double>
struct One_vertex
{
    Vertex_type id;
    vector<Edge<Vertex_type, Distance_type>> edges;
    int color = 0;
    Vertex_type prev = -1;
    One_vertex(Vertex_type id) : id(id) {};
    One_vertex(const One_vertex& other_one) : id(other_one.id), edges(other_one.edges) {};
};
template<typename Vertex_type, typename Distance_type = double>
class Graph {
public:
    void all_white()
    {
        for (auto u = graph.begin(); u != graph.end(); u++)
        {
            u->prev = -1;
            u->color = 0;
        }
    }
    Distance_type relax(const Vertex_type& from, const Vertex_type& to, const Vertex_type& betw, const Distance_type& dis);
    Graph()=default;
    ~Graph()=default;
    
private:
    vector<One_vertex<Vertex_type, Distance_type>> graph;

public:
    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex_type& v) const;
    void add_vertex(const Vertex_type& v);
    bool remove_vertex(const Vertex_type& v);
    vector<Vertex_type> vertices() const;
    void print() const;
    bool _empty();

    //проверка-добавление-удаление ребер
    void add_edge(const Vertex_type& from, const Vertex_type& to,
        const Distance_type& d);
    bool remove_edge(const Vertex_type& from, const Vertex_type& to);
    bool remove_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& weight); //c учетом расстояния
    bool has_edge(const Vertex_type& from, const Vertex_type& to) const;
    bool has_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& weight) const; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    vector<Edge<Vertex_type, Distance_type>> edges(const Vertex_type& vertex);

    size_t order() const; //порядок
    size_t degree() const; //степень


    //поиск кратчайшего пути
    vector<Vertex_type> shortest_path(const Vertex_type& from, const Vertex_type& to);  //Дейкстры

    friend void find_path(vector<Vertex_type>& victor, const One_vertex<Vertex_type, Distance_type>& id, const Graph<Vertex_type, Distance_type>& graph);
    //обход
    //std::vector<Vertex>  walk(const Vertex& start_vertex)const; В глубину
};
template Graph<int>;
template Edge<int>;
template One_vertex<int>;