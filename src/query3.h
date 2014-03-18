//File: query3.h
//Date: Tue Mar 18 14:22:31 2014 +0800

#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <map>
#include "data.h"

struct Query3 {
	int k, hop;
	std::string place;

	Query3(int _k, int _h, const std::string & p):
		k(_k), hop(_h), place(p){}
};

struct Answer3 {
	int com_interest, p1, p2;

	Answer3(int _c = 0, int _p1 = 0, int _p2 = 0):
		com_interest(_c), p1(_p1), p2(_p2)
	{
		if (p1 > p2)
		{
			p1 ^= p2;
			p2 ^= p1;
			p1 ^= p2;
		}
	}

	bool operator<(const Answer3& r) const
	{
		if (com_interest != r.com_interest)
			return com_interest > r.com_interest;
		if (p1 != r.p1)
			return p1 < r.p1;
		return p2 < r.p2;
	}
};

class Query3Calculator {
	public :
		void work(int k, int h, const std::string &p, std::vector<Answer3> &ans);
		void calcInvertedList();
		void moveOneStep(int g, int h, int f);
		void init(const std::string &p);
		void insHeap(Answer3 cur, int g, int f);
		
	protected:
		int sum = 0;
		int heapSize = 0, qk;
		PersonSet pset;
		std::set<int> pinplace;
		std::vector<int> people;
		std::vector<Answer3> first;
		std::map<int, int> invPeople;
		std::set<Answer3> answerHeap;
		std::vector<Answer3> answers;
		std::vector<std::vector<std::set<int> > > invList;
		std::vector<std::set<int>::iterator> map_itr;
		std::vector<int> i_itr, zero_itr, curRound;
		std::vector<std::map<int, int> > candidate;
		std::vector<std::vector<std::set<int> > > pool;
		std::vector<std::set<int> > forsake;
		std::vector<std::set<std::pair<int, int> > > oneHeap;
				
};

class Query3Handler {
	public:
		std::mutex mt_work_done;
		void add_query(int k, int h, const std::string& p, int index);

		void work();

		void print_result();		// TODO

		void bfs(int, int, int);		// for version2
		void bfs(int, int);				// for force

		std::vector<std::vector<Answer3> > global_answer;	

};
