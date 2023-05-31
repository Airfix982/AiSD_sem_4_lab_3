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
    //��������-����������-�������� ������
    bool has_vertex(const Vertex_type& v) const;
    void add_vertex(const Vertex_type& v);
    bool remove_vertex(const Vertex_type& v);
    std::vector<Vertex_type> vertices() const;


    //��������-����������-�������� �����
    void add_edge(const Vertex_type& from, const Vertex_type& to,
        const Distance_type& d);
    bool remove_edge(const Vertex_type& from, const Vertex_type& to);
    bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(const Vertex_type& from, const Vertex_type& to) const;
    bool has_edge(const Edge& e); //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //�������
    size_t degree() const; //�������


    //����� ����������� ����
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //�����
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};
Graph<int>;
