#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<utility>
#include<queue>
#include<set>
#include"graph.hpp"
#define INF 1000000000
using namespace std;

template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::_empty()
{
	return graph.begin() == graph.end();
}

template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::has_vertex(const Vertex_type& v) const
{
	for (auto vec = graph.begin(); vec != graph.end(); vec++)
	{
		if (vec->id == v) return true;
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
			if (vec->id == v)
			{
				for (auto i = graph.begin(); i != graph.end(); i++)
				{
					if (i->id == v) continue;
					while(has_edge(i->id, v)) remove_edge(i->id, v);
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
		cout << vert.id << "  ---> " << "[";
		for (auto ed = vert.edges.begin(); ed != vert.edges.end(); ed++)
		{
			cout << "{" << ed->to << ", " << ed->weight << "}";
			if(ed+1 != vert.edges.end()) cout << ", ";
		}
		cout << "]" << endl;
	}
};

template<typename Vertex_type, typename Distance_type>
void Graph<Vertex_type, Distance_type>::add_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& d)
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end(); vert++)
	{
		if (vert->id == from)
		{
			Edge e(to, d);
			vert->edges.push_back(e);
			break;
		}
	}
};

template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::remove_edge(const Vertex_type& from, const Vertex_type& to)
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end();)
	{
		if (vert->id == from)
		{
			for (auto e = vert->edges.begin(); e != vert->edges.end();)
			{
				if (e->to == to)
				{
					e = vert->edges.erase(e);
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
bool Graph<Vertex_type, Distance_type>::remove_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& weight)
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end();)
	{
		if (vert->id == from)
		{
			for (auto e = vert->edges.begin(); e != vert->edges.end(); e++)
			{
				if (e->to == to && e->weight == weight)
				{
					e = vert->edges.erase(e);
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
	for (auto vert = graph.begin(); vert != graph.end(); vert++)
	{
		if (vert->id == from)
		{
			for (auto e = vert->edges.begin(); e!= vert->edges.end(); e++)
			{
				if (e->to == to)
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
};
template<typename Vertex_type, typename Distance_type>
bool Graph<Vertex_type, Distance_type>::has_edge(const Vertex_type& from, const Vertex_type& to, const Distance_type& weight) const
{
	if (!has_vertex(from) || !has_vertex(to)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end(); vert++)
	{
		if (vert->id == from)
		{
			for (auto e = vert->edges.begin(); e != vert->edges.end(); e++)
			{
				if (e->to == to && e->weight == weight)
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
};

template<typename Vertex_type, typename Distance_type>
vector<Edge<Vertex_type, Distance_type>> Graph<Vertex_type, Distance_type>::edges(const Vertex_type& vertex)
{
	if (!has_vertex(vertex)) throw "no vertex(es)";
	for (auto vert = graph.begin(); vert != graph.end(); vert++)
	{
		if (vert->id == vertex)
		{
			return vert->edges;
		}
	}
};

template<typename Vertex_type, typename Distance_type>
size_t Graph<Vertex_type, Distance_type>::order() const
{
	return size_t(size(graph));
};

template<typename Vertex_type, typename Distance_type>
size_t Graph<Vertex_type, Distance_type>::degree() const
{
	size_t degree = 0;
	for (auto vert = graph.begin(); vert != graph.end(); vert++)
	{
		degree += size_t(size(vert->edges));
	}
	return degree;
};

template<typename Vertex_type, typename Distance_type>
Distance_type Graph<Vertex_type, Distance_type>::relax(const Vertex_type& from, const Vertex_type& to, const Vertex_type& betw, const Distance_type& dis)
{
	Distance_type right;
	Distance_type through = INF;
	for (auto i = graph.begin(); i != graph.end(); i++)
	{
		if (i->id == from)
		{
			for (auto e = i->edges.begin(); e != i->edges.end(); e++)
			{
				if (e->to == to) right = e->weight;
			}
			for (auto j = graph.begin(); j != graph.end(); j++)
			{
				if (j->id == betw)
				{
					for (auto e = j->edges.begin(); e != j->edges.end(); e++)
					{
						if (e->to == to) through = e->weight + dis;
					}
				}
			}
		}
	}
	return min(right, through);
}

template<typename Vertex_type, typename Distance_type>
void sort_q(vector<pair<Vertex_type, Distance_type>>& Q)
{
	for (int i = 0; i < Q.size(); i++)
	{
		for (int j = i+1; j < Q.size(); j++)
		{
			if (Q[i].second > Q[j].second)
			{
				pair<Vertex_type, Distance_type> tmp = Q[i];
				Q[i] = Q[j];
				Q[j] = tmp;
			}
		}
	}
}

template<typename Vertex_type, typename Distance_type>
void find_path(vector<Vertex_type>& victor, const One_vertex<Vertex_type, Distance_type>& id, const vector<One_vertex<Vertex_type, Distance_type>>& graph)
{
	victor.insert(victor.begin(), id.prev);
	for (auto j = graph.begin(); j != graph.end(); j++)
	{
		if (j->id == id.prev)
		{
			if (j->prev == -1)
			{
				return;
			}
			else
			{
				find_path(victor, *j, graph);
			}
		}
	}
	return;
}

template<typename Vertex_type, typename Distance_type>
vector<Vertex_type> Graph<Vertex_type, Distance_type>::shortest_path(const Vertex_type& from, const Vertex_type& to)
{
	vector<One_vertex<Vertex_type, Distance_type>> S;
	all_white();
	vector<pair<Vertex_type, Distance_type>> Q;
	for (auto j = graph.begin(); j != graph.end(); j++)
	{
		if (j->id != from)
		{
			pair<Vertex_type, Distance_type> p(j->id, INF);
			Q.push_back(p);
		}
		else
		{
			pair<Vertex_type, Distance_type> p(j->id, 0);
			Q.push_back(p);
		}
	}
	sort_q(Q);

	while (!Q.empty())
	{
		Vertex_type u = Q[0].first;
		Distance_type u_dist = Q[0].second;
		Q.erase(Q.begin());// Функция сортировки очереди нормально не работает, очередь не изменяется

		for (auto v = graph.begin(); v != graph.end(); v++)
		{
			if (v->id == u) S.push_back(*v);
		}


		for (auto v = graph.begin(); v != graph.end(); v++)//Ищем кратчайшие пути до всех вершин, выходящих из u
		{
			if (v->id == u)// Нашли в графе вершину, до которой точно вычислен кратчайший путь
			{



				for (auto e = v->edges.begin(); e != v->edges.end(); e++)
				{

					// Для все верши, исходящих из вершины до кот вычислен кратчайший путь записываем ее в предыдущие,
					// если путь до нее из найденной вершины корче, чем уже определен
					for (auto v_q = Q.begin(); v_q != Q.end(); v_q++)
					{
						if (v_q->first == e->to && v_q->second > e->weight)
						{
							for (auto v2 = graph.begin(); v2 != graph.end(); v2++)
							{
								if (v2->id == e->to)
								{
									v2->prev = u;
								}
							}
						}
					}
				}
				for (auto e = v->edges.begin(); e != v->edges.end(); e++)
				{
					for (auto v_q = Q.begin(); v_q != Q.end(); v_q++)
					{
						if (v_q->first == e->to)
						{
							v_q->second = e->weight;//здесь надо к вкью секонд добавлять расстояние до вершины u 
							for (auto e1 = v->edges.begin(); e1 != v->edges.end(); e1++)
							{
								if(e1->to != e->to)
								{
									Distance_type a = relax(v->id, e->to, e1->to, e1->weight);
									if (a < e->weight)//записываем предыдущюю вершину через промежуточную и изменяем расстояние
									{
										for (auto v1 = graph.begin(); v1 != graph.end(); v1++)
										{
											if (v1->id == e->to)
											{
												v1->prev = e1->to;
											}
										}
										v_q->second = a;
									}
								}
							}
						}
					}
				}




			}
		}
		sort_q(Q);

	}
	vector<Vertex_type> victor;
	for (auto v1 = graph.begin(); v1 != graph.end(); v1++)
	{
		if (v1->id == to)
		{
			if (v1->prev == -1) throw "Can't reach this vertex";
			else
			{
				victor.push_back(to);
				find_path(victor, *v1, graph);
			}
		}
	}
	return victor;
}