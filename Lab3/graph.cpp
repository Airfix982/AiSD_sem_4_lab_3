#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include"graph.hpp"
using namespace std;




template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::has_vertex(const Vertex_type& v) const
{
	for (auto vec : graph)
	{
		if (vec.id == v) return true;
	}
	return false;
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
	if (!has_vertex(v)) throw "Vertex does not exist";
	else
	{
		for ( auto vec = graph.begin(); vec != graph.end(); )
		{
			if ((*vec).id == v)
			{
				for (auto e : (*vec).edges)
				{
					remove_edge(v, e.to);
				}
				for (auto i : graph)
				{
					if (i.id == v) continue;
					if (has_edge(i.id, v)) remove_edge(i.id, v);
				}
				vec = graph.erase(vec);
				break;
			}
			++vec;
		}
	}
};


template<typename Vertex_type, typename Distance_type>
vector<Vertex_type> Graph<Vertex_type, Distance_type>::vertices() const
{
	vector<Vertex_type> vec;
	for (auto v : graph)
	{
		vec.push_back(v.id);
	}
	return vec;
};
template<typename Vertex_type, typename Distance_type>
void Graph<Vertex_type, Distance_type>::print() const
{
	for (auto vert: graph)
	{
		cout << vert.id << "   " << "[";
		for (auto ed : vert.edges)
		{
			cout << ed.to << ", ";
		}
		cout << "]";
	}
};
template<typename Vertex_type, typename Distance_type>
void Graph<Vertex_type, Distance_type>::add_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& d)
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert : graph)
	{
		if (vert.id == from)
		{
			Edge e(to, d);
			vert.edges.push_back(e);
		}
		break;
	}
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::remove_edge(const Vertex_type& from, const Vertex_type& to)
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end();)
	{
		if ((*vert).id == from)
		{
			for (auto e = (*vert).edges.begin(); e != (*vert).edges.end();)
			{
				if ((*e).to == to)
				{
					e = (*vert).edges.erase(e);
					return true;
				}
				++e;
			}
			return false;
		}
		vert++;
	}
	return false;
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::remove_edge(const Edge& ed, const Vertex_type& from)
{
	if (!has_vertex(from) || !has_vertex(ed.to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end();)
	{
		if ((*vert).id == from)
		{
			for (auto e = (*vert).edges.begin(); e != (*vert).edges.end();)
			{
				if ((*e).to == ed.to && (*e).weight == ed.weight)
				{
					e = (*vert).edges.erase(e);
					return true;
				}
			}
			return false;
		}
		vert++;
	}
	return false;
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::has_edge(const Vertex_type& from, const Vertex_type& to) const
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert : graph)
	{
		if (vert.id == from)
		{
			for (auto e : vert.edges)
			{
				if (e.to == to)
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
};
