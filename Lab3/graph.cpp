#include<Windows.h>
#include<iostream>
#include"graph.hpp"
using namespace std;


template<typename Vertex, typename Distance>
struct Graph<Vertex, Distance>::Edge
{
	Vertex to;
	Distance height;
};
template<typename Vertex, typename Distance>
struct Graph<Vertex, Distance>::One_vertex
{
	Vertex id;
	vector<Edge> edges;
};
