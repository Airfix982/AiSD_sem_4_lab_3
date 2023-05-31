#include<Windows.h>
#include<iostream>
#include"graph.hpp"
using namespace std;


template<typename Vertex_type, typename Distance_type>
struct Graph<Vertex_type, Distance_type>::Edge
{
	Vertex_type to;
	Distance_type weight;
	Edge(Vertex_type to, Distance_type weight = 0) : to(to), weight(weight) {};
	Edge(const Edge& other_one) : to(other_one.to), weight(other_one.weight) {};
};
template<typename Vertex_type, typename Distance_type>
struct Graph<Vertex_type, Distance_type>::One_vertex
{
	Vertex_type id;
	vector<Edge> edges;
	One_vertex(Vertex_type id) : id(id) {};
	One_vertex(const Vertex_type other_one) : id(other_one.id), edges(other_one.edges) {};
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::has_vertex(const Vertex_type& v) const
{
	return graph.contains(v);
};
template<typename Vertex_type, typename Distance_type>
void Graph<Vertex_type, Distance_type>::add_vertex(const Vertex_type& v)
{
	if (has_vertex(v)) throw "Vertex already exists";
	else graph.push_back(v);
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::remove_vertex(const Vertex_type& v)
{
	if (!has_vertex) throw "Vertex does not exist";
	else
	{
		for (auto e : graph[v].edges)
		{
			remove_edge(v, (*e).to);
		}
		for (auto i : graph)
		{
			for (auto e : (*i).edges)
			{
				if (*e.to == v)
				{
					remove_edge(*i, (*e).to);
				}
			}
		}
	}
};
template<typename Vertex_type, typename Distance_type>
vector<Vertex_type> Graph<Vertex_type, Distance_type>::vertices() const
{
	vector<Vertex_type> vec;
	for (auto v : graph)
	{
		vec.push_back(graph.id);
	}
	return vec;
}