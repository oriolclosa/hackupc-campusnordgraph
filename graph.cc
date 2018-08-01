#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
using namespace std;

#define INF 0x3f3f3f3f

bool bfs(map<string, set<vector<string>>> university, string from, string to){
    if(from==to){
        return true;
    }
    set<string> visited;
    list<string> queue;
    visited.insert(from);
    queue.push_back(from);
    list<string>::iterator i;
    while(!queue.empty()){
        string current = queue.front();
        queue.pop_front();
        set<vector<string>>::iterator it = university[current].begin();
        while(it!=university[current].end()){
            if((*it)[1]==to){
                return true;
            }
            if((visited.find((*it)[1])==visited.end())&&(atoi((*it)[0].c_str())>=0)){
                visited.insert((*it)[1]);
                queue.push_back((*it)[1]);
            }
            ++it;
        }
    }
    return false;
}

pair<int, map<string, string>> dijkstra(map<string, set<vector<string>>> university, string from, string to){
    map<string, string> path;
    map<string, int> dist;
    dist[from] = 0;
    set<pair<int, string>> q;
    q.insert({0, from});
    while(!q.empty()){
        auto top = q.begin();
        string u = top->second;
        q.erase(top);
        set<vector<string>>::iterator it = university[u].begin();
        while(it!=university[u].end()){
            int w = atoi((*it)[0].c_str());
            if(w>=0){
                string v = (*it)[1];
                int dv = INF;
                if(dist.find(v)!=dist.end()){
                    dv = dist[v];
                }
                if(dv > (dist[u]+w)){
                    if(q.find({dv, v})!=q.end()){
                        q.erase(q.find({dv, v}));
                    }
                    path[v] = u;
                    dist[v] = dist[u]+w;
                    q.insert({dist[v], v});
                }
            }
            ++it;
        }
    }
    return pair<int, map<string, string>>(dist[to], path);
}

int main(){
    //Pesos negatius indiquen pas tallat
    map<string, set<vector<string>>> university = {
        //Edifici A6
        {"A6-S1-0", {{"5", "A6-S1-9"}}},
        {"A6-S1-1", {{"5", "A6-S1-2"}}},
        {"A6-S1-2", {{"5", "A6-S1-3"}}},
        {"A6-S1-3", {{"5", "A6-S1-4"}}},
        {"A6-S1-4", {{"5", "A6-S1-9"}}},
        {"A6-S1-8", {{"5", "A6-S1-7"}}},
        {"A6-S1-7", {{"5", "A6-S1-6"}}},
        {"A6-S1-6", {{"5", "A6-S1-5"}}},
        {"A6-S1-5", {{"5", "A6-S1-9"}}},
        {"A6-S1-9", {{"6", "A6-S1-10"}}},
        {"A6-S1-10", {{"3", "A6-S1-11"}}},
        {"A6-S1-11", {{"4", "A6-S1-12"}}},
        {"A6-S1-12", {{"1", "A6-S1-13"}, {"1", "A6-S1-14"}, {"2", "A6-S1-15"}}},
        {"A6-S1-15", {{"10", "A5-0-10"}}},
        {"A6-0-0", {{"25", "A5-0-0"}, {"3", "A6-0-1"}, {"12", "A6-0-2"}, {"12", "A6-0-3"}, {"12", "V-0-0"}}},
        {"A6-0-1", {{"3", "A6-0-0"}, {"11", "A6-0-2"}, {"11", "A6-0-3"}, {"2", "A6-0-4"}}},
        {"A6-0-2", {{"3", "A5-0-3"}, {"12", "A6-0-0"}, {"11", "A6-0-1"}, {"2", "A6-0-7"}}},
        {"A6-0-3", {{"12", "A6-0-0"}, {"11", "A6-0-1"}, {"2", "A6-0-8"}}},
        {"A6-0-4", {{"2", "A6-0-1"}, {"2", "A6-0-5"}, {"2", "A6-0-6"}, {"-9", "A6-E-0"}}},
        {"A6-0-5", {{"2", "A6-0-4"}, {"8", "A6-0-7"}}},
        {"A6-0-6", {{"2", "A6-0-4"}, {"8", "A6-0-8"}}},
        {"A6-0-7", {{"2", "A6-0-2"}, {"8", "A6-0-5"}, {"2", "A6-0-9"}}},
        {"A6-0-8", {{"2", "A6-0-3"}, {"8", "A6-0-6"}, {"2", "A6-0-10"}}},
        {"A6-0-9", {{"2", "A6-0-7"}, {"9", "A6-E-1"}}},
        {"A6-0-10", {{"2", "A6-0-8"}, {"9", "A6-E-2"}}},
        {"A6-E-0", {{"9", "A6-0-4"}, {"11", "A6-E-1"}, {"11", "A6-E-2"}}},
        {"A6-E-1", {{"10", "A6-1-11"}, {"-11", "A6-E-0"}, {"9", "A6-0-9"}}},
        {"A6-E-2", {{"10", "A6-1-9"}, {"-11", "A6-E-0"}, {"9", "A6-0-10"}}},
        {"A6-1-0", {{"6", "A6-1-1"}, {"6", "A6-1-2"}, {"4", "A6-1-3"}, {"4", "A6-1-4"}, {"1", "A6-1-5"}}},
        {"A6-1-1", {{"6", "A6-1-0"}, {"2", "A6-1-3"}, {"1", "A6-1-6"}, {"2", "A6-1-8"}}},
        {"A6-1-2", {{"6", "A6-1-0"}, {"2", "A6-1-4"}, {"1", "A6-1-7"}, {"4", "A6-1-9"}}},
        {"A6-1-3", {{"4", "A6-1-0"}, {"2", "A6-1-1"}}},
        {"A6-1-4", {{"4", "A6-1-0"}, {"2", "A6-1-2"}}},
        {"A6-1-5", {{"1", "A6-1-0"}}},
        {"A6-1-6", {{"1", "A6-1-1"}}},
        {"A6-1-7", {{"1", "A6-1-2"}}},
        {"A6-1-8", {{"2", "A6-1-1"}, {"2", "A6-1-10"}, {"2", "A6-1-11"}}},
        {"A6-1-9", {{"10", "A6-E-2"}, {"4", "A6-1-2"}, {"1", "A6-1-12"}}},
        {"A6-1-10", {{"2", "A6-1-8"}, {"3", "A6-1-14"}}},
        {"A6-1-11", {{"10", "A6-E-1"}, {"2", "A6-1-8"}, {"1", "A6-1-13"}}},
        {"A6-1-12", {{"1", "A6-1-9"}, {"1", "A6-1-16"}, {"10", "A6-2-9"}}},
        {"A6-1-13", {{"1", "A6-1-11"}, {"1", "A6-1-14"}, {"10", "A6-2-11"}}},
        {"A6-1-14", {{"3", "A5-1-17"}, {"3", "A6-1-10"}, {"1", "A6-1-13"}, {"1", "A6-1-15"}}},
        {"A6-1-15", {{"1", "A6-1-14"}}},
        {"A6-1-16", {{"1", "A6-1-12"}}},
        {"A6-2-0", {{"6", "A6-2-1"}, {"6", "A6-2-2"}, {"4", "A6-2-3"}, {"4", "A6-2-4"}, {"1", "A6-2-5"}}},
        {"A6-2-1", {{"6", "A6-2-0"}, {"2", "A6-2-3"}, {"1", "A6-2-6"}, {"2", "A6-2-8"}}},
        {"A6-2-2", {{"6", "A6-2-0"}, {"2", "A6-2-4"}, {"1", "A6-2-7"}, {"4", "A6-2-9"}}},
        {"A6-2-3", {{"4", "A6-2-0"}, {"2", "A6-2-1"}}},
        {"A6-2-4", {{"4", "A6-2-0"}, {"2", "A6-2-2"}}},
        {"A6-2-5", {{"1", "A6-2-0"}}},
        {"A6-2-6", {{"1", "A6-2-1"}}},
        {"A6-2-7", {{"1", "A6-2-2"}}},
        {"A6-2-8", {{"2", "A6-2-1"}, {"2", "A6-2-10"}, {"2", "A6-2-11"}}},
        {"A6-2-9", {{"10", "A6-1-12"}, {"4", "A6-2-2"}, {"1", "A6-2-12"}}},
        {"A6-2-10", {{"2", "A6-2-8"}, {"3", "A6-2-14"}}},
        {"A6-2-11", {{"10", "A6-1-13"}, {"2", "A6-2-8"}, {"1", "A6-2-13"}}},
        {"A6-2-12", {{"1", "A6-2-16"}, {"1", "A6-2-9"}}},
        {"A6-2-13", {{"1", "A6-2-14"}, {"10", "A6-2-11"}}},
        {"A6-2-14", {{"3", "A5-2-17"}, {"3", "A6-2-10"}, {"1", "A6-2-13"}, {"1", "A6-2-15"}}},
        {"A6-2-15", {{"1", "A6-2-14"}}},
        {"A6-2-16", {{"1", "A6-2-12"}}},

        //Edifici A5
        {"A5-0-0", {{"25", "A4-0-0"}, {"3", "A5-0-1"}, {"12", "A5-0-2"}, {"12", "A5-0-3"}, {"25", "A6-0-0"}}},
        {"A5-0-1", {{"3", "A5-0-0"}, {"11", "A5-0-2"}, {"11", "A5-0-3"}, {"2", "A5-0-4"}}},
        {"A5-0-2", {{"3", "A4-0-3"}, {"12", "A5-0-0"}, {"11", "A5-0-1"}, {"2", "A5-0-7"}}},
        {"A5-0-3", {{"12", "A5-0-0"}, {"11", "A5-0-1"}, {"2", "A5-0-8"}, {"3", "A6-0-2"}}},
        {"A5-0-4", {{"2", "A5-0-1"}, {"2", "A5-0-5"}, {"2", "A5-0-6"}, {"4", "A5-0-11"}}},
        {"A5-0-5", {{"2", "A5-0-4"}, {"8", "A5-0-7"}}},
        {"A5-0-6", {{"2", "A5-0-4"}, {"8", "A5-0-8"}}},
        {"A5-0-7", {{"2", "A5-0-2"}, {"8", "A5-0-5"}, {"2", "A5-0-9"}}},
        {"A5-0-8", {{"2", "A5-0-3"}, {"8", "A5-0-6"}, {"2", "A5-0-10"}}},
        {"A5-0-9", {{"2", "A5-0-7"}, {"9", "A5-E-1"}}},
        {"A5-0-10", {{"2", "A5-0-8"}, {"9", "A5-E-2"}, {"-10", "A6-S1-15"}}},
        {"A5-0-11", {{"4", "A5-0-4"}}},
        {"A5-E-1", {{"10", "A5-1-11"}, {"9", "A5-0-9"}}},
        {"A5-E-2", {{"10", "A5-1-9"}, {"9", "A5-0-10"}}},
        {"A5-1-0", {{"6", "A5-1-1"}, {"6", "A5-1-2"}, {"4", "A5-1-3"}, {"4", "A5-1-4"}, {"1", "A5-1-5"}}},
        {"A5-1-1", {{"6", "A5-1-0"}, {"2", "A5-1-3"}, {"1", "A5-1-6"}, {"2", "A5-1-8"}}},
        {"A5-1-2", {{"6", "A5-1-0"}, {"2", "A5-1-4"}, {"1", "A5-1-7"}, {"4", "A5-1-9"}}},
        {"A5-1-3", {{"4", "A5-1-0"}, {"2", "A5-1-1"}}},
        {"A5-1-4", {{"4", "A5-1-0"}, {"2", "A5-1-2"}}},
        {"A5-1-5", {{"1", "A5-1-0"}}},
        {"A5-1-6", {{"1", "A5-1-1"}}},
        {"A5-1-7", {{"1", "A5-1-2"}}},
        {"A5-1-8", {{"2", "A5-1-1"}, {"2", "A5-1-10"}, {"2", "A5-1-11"}}},
        {"A5-1-9", {{"10", "A5-E-2"}, {"4", "A5-1-2"}, {"1", "A5-1-12"}}},
        {"A5-1-10", {{"2", "A5-1-8"}, {"3", "A5-1-14"}}},
        {"A5-1-11", {{"10", "A5-E-1"}, {"2", "A5-1-8"}, {"1", "A5-1-13"}}},
        {"A5-1-12", {{"1", "A5-1-9"}, {"1", "A5-1-17"}, {"10", "A5-2-9"}}},
        {"A5-1-13", {{"1", "A5-1-11"}, {"1", "A5-1-14"}, {"10", "A5-2-11"}}},
        {"A5-1-14", {{"3", "A4-1-17"}, {"3", "A5-1-10"}, {"1", "A5-1-13"}, {"1", "A5-1-15"}}},
        {"A5-1-15", {{"1", "A5-1-14"}}},
        {"A5-1-16", {{"1", "A5-1-12"}}},
        {"A5-1-17", {{"1", "A5-1-12"}, {"1", "A5-1-16"}, {"3", "A6-1-14"}}},
        {"A5-2-0", {{"6", "A5-2-1"}, {"6", "A5-2-2"}, {"4", "A5-2-3"}, {"4", "A5-2-4"}, {"1", "A5-2-5"}}},
        {"A5-2-1", {{"6", "A5-2-0"}, {"2", "A5-2-3"}, {"1", "A5-2-6"}, {"2", "A5-2-8"}}},
        {"A5-2-2", {{"6", "A5-2-0"}, {"2", "A5-2-4"}, {"1", "A5-2-7"}, {"4", "A5-2-9"}}},
        {"A5-2-3", {{"4", "A5-2-0"}, {"2", "A5-2-1"}}},
        {"A5-2-4", {{"4", "A5-2-0"}, {"2", "A5-2-2"}}},
        {"A5-2-5", {{"1", "A5-2-0"}}},
        {"A5-2-6", {{"1", "A5-2-1"}}},
        {"A5-2-7", {{"1", "A5-2-2"}}},
        {"A5-2-8", {{"2", "A5-2-1"}, {"2", "A5-2-10"}, {"2", "A5-2-11"}}},
        {"A5-2-9", {{"10", "A5-1-12"}, {"4", "A5-2-2"}, {"1", "A5-2-12"}}},
        {"A5-2-10", {{"2", "A5-2-8"}, {"3", "A5-2-14"}}},
        {"A5-2-11", {{"10", "A5-1-13"}, {"2", "A5-2-8"}, {"1", "A5-2-13"}}},
        {"A5-2-12", {{"1", "A5-2-17"}, {"1", "A5-2-9"}}},
        {"A5-2-13", {{"1", "A5-2-14"}, {"10", "A5-2-11"}}},
        {"A5-2-14", {{"3", "A4-2-17"}, {"3", "A5-2-10"}, {"1", "A5-2-13"}, {"1", "A5-2-15"}}},
        {"A5-2-15", {{"1", "A5-2-14"}}},
        {"A5-2-16", {{"1", "A5-2-17"}}},
        {"A5-2-17", {{"1", "A5-2-12"}, {"1", "A5-2-16"}, {"3", "A6-2-14"}}},

        //Efifici A4
        {"A4-0-0", {{"25", "A3-0-0"}, {"3", "A4-0-1"}, {"12", "A4-0-2"}, {"12", "A4-0-3"}, {"25", "A5-0-0"}}},
        {"A4-0-1", {{"3", "A4-0-0"}, {"11", "A4-0-2"}, {"11", "A4-0-3"}, {"-2", "A5-0-4"}}},
        {"A4-0-2", {{"12", "A4-0-0"}, {"11", "A4-0-1"}, {"-2", "A4-0-7"}, {"1", "A4-0-14"}}},
        {"A4-0-3", {{"12", "A4-0-0"}, {"11", "A4-0-1"}, {"2", "A4-0-8"}, {"3", "A5-0-2"}}},
        {"A4-0-4", {{"-2", "A4-0-1"}, {"2", "A4-0-5"}, {"2", "A4-0-6"}}},
        {"A4-0-5", {{"2", "A4-0-4"}, {"-8", "A4-0-7"}}},
        {"A4-0-6", {{"2", "A4-0-4"}, {"-8", "A4-0-8"}}},
        {"A4-0-7", {{"-2", "A4-0-2"}, {"-8", "A4-0-5"}, {"2", "A4-0-9"}}},
        {"A4-0-8", {{"2", "A4-0-3"}, {"-8", "A4-0-6"}, {"2", "A4-0-10"}}},
        {"A4-0-9", {{"2", "A4-0-7"}, {"1", "A4-0-11"}, {"1", "A4-0-12"}, {"1", "A4-0-13"}}},
        {"A4-0-10", {{"2", "A4-0-8"}, {"9", "A4-E-2"}}},
        {"A4-0-11", {{"1", "A4-0-9"}}},
        {"A4-0-12", {{"1", "A4-0-9"}}},
        {"A4-0-13", {{"1", "A4-0-9"}, {"9", "A4-E-1"}}},
        {"A4-0-14", {{"4", "A3-0-14"}, {"1", "A4-0-2"}, {"7", "D-0-2"}}},
        {"A4-E-1", {{"10", "A4-0-13"}, {"9", "A4-1-13"}}},
        {"A4-E-2", {{"10", "A4-0-10"}, {"9", "A4-1-9"}}},
        {"A4-1-0", {{"6", "A4-1-1"}, {"6", "A4-1-2"}, {"4", "A4-1-3"}, {"4", "A4-1-4"}}},
        {"A4-1-1", {{"6", "A4-1-0"}, {"2", "A4-1-3"}, {"2", "A4-1-6"}, {"1", "A4-1-8"}}},
        {"A4-1-2", {{"6", "A4-1-0"}, {"2", "A4-1-4"}, {"2", "A4-1-7"}, {"4", "A4-1-9"}}},
        {"A4-1-3", {{"4", "A4-1-0"}, {"2", "A4-1-1"}}},
        {"A4-1-4", {{"4", "A4-1-0"}, {"2", "A4-1-2"}}},
        {"A4-1-6", {{"2", "A4-1-1"}}},
        {"A4-1-7", {{"2", "A4-1-2"}}},
        {"A4-1-8", {{"2", "A4-1-1"}, {"2", "A4-1-10"}, {"2", "A4-1-11"}}},
        {"A4-1-9", {{"9", "A4-E-2"}, {"4", "A4-1-2"}, {"1", "A4-1-12"}}},
        {"A4-1-10", {{"2", "A4-1-8"}, {"3", "A4-1-14"}}},
        {"A4-1-11", {{"2", "A4-1-8"}, {"1", "A4-1-13"}, {"10", "A4-2-13"}}},
        {"A4-1-12", {{"1", "A4-1-9"}, {"1", "A4-1-17"}, {"10", "A4-2-9"}}},
        {"A4-1-13", {{"9", "A4-E-1"}, {"1", "A4-1-11"}, {"1", "A4-1-14"}}},
        {"A4-1-14", {{"3", "A3-1-14"}, {"3", "A4-1-10"}, {"1", "A4-1-13"}, {"1", "A4-1-15"}}},
        {"A4-1-15", {{"1", "A4-1-14"}}},
        {"A4-1-16", {{"1", "A4-1-17"}}},
        {"A4-1-17", {{"1", "A4-1-12"}, {"1", "A4-1-16"}, {"3", "A5-1-14"}}},
        {"A4-2-0", {{"6", "A4-2-1"}, {"6", "A4-2-2"}, {"2", "A4-2-5"}, {"2", "A4-2-18"}}},
        {"A4-2-1", {{"6", "A4-2-0"}, {"1", "A4-2-3"}, {"1", "A4-2-6"}, {"1", "A4-2-8"}}},
        {"A4-2-2", {{"6", "A4-2-0"}, {"1", "A4-2-4"}, {"1", "A4-2-7"}, {"10", "A4-2-9"}}},
        {"A4-2-3", {{"1", "A4-2-1"}}},
        {"A4-2-4", {{"1", "A4-2-2"}}},
        {"A4-2-5", {{"2", "A4-2-0"}}},
        {"A4-2-6", {{"1", "A4-2-1"}}},
        {"A4-2-7", {{"1", "A4-2-2"}}},
        {"A4-2-8", {{"2", "A4-2-1"}, {"2", "A4-2-10"}, {"2", "A4-2-11"}}},
        {"A4-2-9", {{"10", "A4-1-12"}, {"10", "A4-2-2"}, {"1", "A4-2-12"}}},
        {"A4-2-10", {{"2", "A4-2-8"}, {"3", "A4-2-14"}}},
        {"A4-2-11", {{"2", "A4-2-8"}, {"1", "A4-2-13"}}},
        {"A4-2-12", {{"1", "A4-2-9"}, {"1", "A4-2-17"}}},
        {"A4-2-13", {{"9", "A4-1-11"}, {"1", "A4-2-11"}, {"1", "A4-2-14"}}},
        {"A4-2-14", {{"3", "A3-2-14"}, {"3", "A4-2-10"}, {"1", "A4-2-13"}, {"1", "A4-2-15"}}},
        {"A4-2-15", {{"1", "A4-2-14"}}},
        {"A4-2-16", {{"1", "A4-2-17"}}},
        {"A4-2-17", {{"1", "A4-2-12"}, {"1", "A4-2-16"}, {"3", "A5-2-14"}}},
        {"A4-2-18", {{"2", "A4-2-0"}}},

        //Edifici A3
        {"A3-0-0", {{"3", "A3-0-1"}, {"12", "A3-0-2"}, {"12", "A3-0-3"}, {"25", "A4-0-0"}}},
        {"A3-0-1", {{"3", "A3-0-0"}, {"11", "A3-0-2"}, {"11", "A3-0-3"}, {"-2", "A3-0-4"}}},
        {"A3-0-2", {{"12", "A3-0-0"}, {"11", "A3-0-1"}, {"2", "A3-0-7"}}},
        {"A3-0-3", {{"12", "A3-0-0"}, {"11", "A3-0-1"}, {"-2", "A4-0-8"}, {"1", "A3-0-14"}}},
        {"A3-0-4", {{"-2", "A3-0-1"}, {"2", "A3-0-5"}, {"2", "A3-0-6"}}},
        {"A3-0-5", {{"2", "A3-0-4"}, {"-8", "A3-0-7"}}},
        {"A3-0-6", {{"2", "A3-0-4"}, {"-8", "A3-0-8"}}},
        {"A3-0-7", {{"2", "A3-0-2"}, {"-8", "A3-0-5"}, {"2", "A3-0-10"}}},
        {"A3-0-8", {{"-2", "A3-0-3"}, {"-8", "A3-0-6"}, {"2", "A3-0-9"}}},
        {"A3-0-9", {{"2", "A3-0-8"}, {"1", "A3-0-11"}, {"1", "A3-0-12"}, {"1", "A3-0-13"}}},
        {"A3-0-10", {{"2", "A3-0-7"}, {"9", "A3-E-1"}}},
        {"A3-0-11", {{"1", "A3-0-9"}}},
        {"A3-0-12", {{"1", "A3-0-9"}}},
        {"A3-0-13", {{"1", "A3-0-9"}, {"9", "A3-E-2"}}},
        {"A3-0-14", {{"1", "A3-0-3"}, {"4", "A4-0-14"}, {"7", "D-0-1"}}},
        {"A3-E-1", {{"10", "A4-0-10"}, {"9", "A3-1-9"}}},
        {"A3-E-2", {{"10", "A3-0-13"}, {"9", "A3-1-13"}}},
        {"A3-1-0", {{"6", "A3-1-1"}, {"6", "A3-1-2"}, {"4", "A3-1-3"}, {"4", "A3-1-4"}}},
        {"A3-1-1", {{"6", "A3-1-0"}, {"2", "A3-1-3"}, {"2", "A3-1-6"}, {"1", "A3-1-8"}}},
        {"A3-1-2", {{"6", "A4-1-0"}, {"2", "A4-1-4"}, {"2", "A4-1-7"}, {"4", "A3-1-9"}}},
        {"A3-1-3", {{"4", "A3-1-0"}, {"2", "A3-1-1"}}},
        {"A3-1-4", {{"4", "A3-1-0"}, {"2", "A3-1-2"}}},
        {"A3-1-6", {{"2", "A3-1-1"}}},
        {"A3-1-7", {{"2", "A3-1-2"}}},
        {"A3-1-8", {{"2", "A3-1-1"}, {"2", "A3-1-10"}, {"2", "A3-1-11"}}},
        {"A3-1-9", {{"9", "A3-E-2"}, {"4", "A3-1-2"}, {"1", "A3-1-12"}}},
        {"A3-1-10", {{"2", "A3-1-8"}, {"3", "A3-1-14"}}},
        {"A3-1-11", {{"2", "A3-1-8"}, {"1", "A3-1-13"}, {"10", "A3-2-13"}}},
        {"A3-1-12", {{"1", "A3-1-9"}, {"1", "A3-1-17"}, {"10", "A3-2-9"}}},
        {"A3-1-13", {{"9", "A3-E-2"}, {"1", "A3-1-11"}, {"1", "A3-1-14"}}},
        {"A3-1-14", {{"3", "A3-1-10"}, {"1", "A3-1-13"}, {"1", "A3-1-15"}, {"3", "A4-1-14"}}},
        {"A3-1-15", {{"1", "A3-1-14"}}},
        {"A3-1-16", {{"1", "A3-1-17"}}},
        {"A3-1-17", {{"1", "A3-1-12"}, {"1", "A3-1-16"}}},
        {"A3-2-0", {{"6", "A3-2-1"}, {"6", "A3-2-2"}, {"2", "A3-2-5"}, {"2", "A3-2-18"}}},
        {"A3-2-1", {{"6", "A3-2-0"}, {"1", "A3-2-3"}, {"1", "A3-2-6"}, {"1", "A3-2-8"}}},
        {"A3-2-2", {{"6", "A3-2-0"}, {"1", "A3-2-4"}, {"1", "A3-2-7"}, {"10", "A3-2-9"}}},
        {"A3-2-3", {{"1", "A3-2-1"}}},
        {"A3-2-4", {{"1", "A3-2-2"}}},
        {"A3-2-5", {{"2", "A3-2-0"}}},
        {"A3-2-6", {{"1", "A3-2-1"}}},
        {"A3-2-7", {{"1", "A3-2-2"}}},
        {"A3-2-8", {{"2", "A3-2-1"}, {"2", "A3-2-10"}, {"2", "A3-2-11"}}},
        {"A3-2-9", {{"10", "A3-1-12"}, {"10", "A3-2-2"}, {"1", "A3-2-12"}}},
        {"A3-2-10", {{"2", "A3-2-8"}, {"3", "A3-2-14"}}},
        {"A3-2-11", {{"2", "A3-2-8"}, {"1", "A3-2-13"}}},
        {"A3-2-12", {{"1", "A3-2-9"}, {"1", "A3-2-17"}}},
        {"A3-2-13", {{"9", "A3-1-11"}, {"1", "A3-2-11"}, {"1", "A3-2-14"}}},
        {"A3-2-14", {{"3", "A3-2-10"}, {"1", "A3-2-13"}, {"1", "A3-2-15"}, {"3", "A4-2-14"}}},
        {"A3-2-15", {{"1", "A3-2-14"}}},
        {"A3-2-16", {{"1", "A3-2-17"}}},
        {"A3-2-17", {{"1", "A3-2-12"}, {"1", "A3-2-16"}}},
        {"A3-2-18", {{"2", "A3-2-0"}}},

        //Vèrtex
        {"V-0-0", {{"12", "A6-0-0"}, {"12", "V-0-1"}}},
        {"V-0-1", {{"4", "V-0-0"}, {"4", "V-0-2"}}},
        {"V-0-2", {{"4", "V-0-1"}, {"4", "V-0-3"}}},
        {"V-0-3", {{"4", "V-0-2"}, {"4", "V-0-4"}}},
        {"V-0-4", {{"4", "V-0-3"}, {"4", "V-0-5"}}},
        {"V-0-5", {{"4", "V-0-4"}, {"4", "V-0-6"}}},
        {"V-0-6", {{"4", "V-0-5"}, {"4", "V-0-7"}}},
        {"V-0-7", {{"4", "V-0-6"}, {"4", "V-0-8"}}},
        {"V-0-8", {{"4", "V-0-7"}, {"4", "V-0-9"}}},
        {"V-0-9", {{"4", "V-0-8"}, {"4", "V-0-10"}}},
        {"V-0-10", {{"4", "V-0-9"}, {"4", "V-0-11"}}},
        {"V-0-11", {{"4", "V-0-10"}, {"4", "V-0-12"}}},
        {"V-0-12", {{"4", "V-0-11"}, {"4", "V-0-13"}}},
        {"V-0-13", {{"4", "V-0-12"}, {"4", "V-0-14"}}},
        {"V-0-14", {{"4", "V-0-13"}, {"4", "V-0-15"}}},
        {"V-0-15", {{"4", "V-0-14"}, {"4", "V-0-16"}}},
        {"V-0-16", {{"4", "V-0-15"}}},

        //Poliesportiu
        {"D-0-0", {{"3", "D-0-1"}, {"3", "D-0-2"}, {"100", "D-0-3"}}},
        {"D-0-1", {{"7", "A3-0-14"}, {"3", "D-0-0"}, {"3", "D-0-2"}}},
        {"D-0-2", {{"7", "A4-0-14"}, {"3", "D-0-0"}, {"3", "D-0-1"}}},
        {"D-0-3", {{"100", "D-0-0"}}}
    };

    /*map<string, set<vector<string>>>::iterator it = university.begin();
    while(it!=university.end()){
        cout << it->first << endl;
        ++it;
    }*/

    map<string, set<string>> placesTo = {
        {"Cafeteria", {"A6-1-10"}},
        {"Info-desk", {"A5-0-11"}},
        {"Baggage check-in", {"A5-0-11"}},
        {"Hardware lab", {"A5-0-11"}},
        {"Talk Room 1", {"A5-0-5"}},
        {"Talk Room 2", {"A5-0-6"}},
        {"Food", {"A5-0-0"}},
        {"Showers", {"D-0-3"}},
        {"Auditorium", {"V-0-16"}},
        {"Men Bathroom", {"A6-1-15", "A6-2-15", "A5-1-15", "A5-2-15", "A4-1-15", "A4-2-15", "A3-1-16", "A3-2-16", "A6-S1-14"}},
        {"Women Bathroom", {"A6-1-16", "A6-2-16", "A5-1-16", "A5-2-16", "A4-1-16", "A4-2-16", "A3-1-15", "A3-2-15", "A6-S1-13"}}
    };

    set<vector<string>> placesFrom = {
        {"A3-1-3", "Sleeping Room"},
        {"A3-1-4", "Sleeping Room"},
        {"A3-1-6", "Sleeping Room"},
        {"A3-1-7", "Sleeping Room"},
        {"A3-2-3", "Sleeping Room"},
        {"A3-2-4", "Sleeping Room"},
        {"A3-2-6", "Sleeping Room"},
        {"A3-2-7", "Sleeping Room"},
        {"A3-2-18", "Sleeping Room"},
        {"A4-1-3", "Hacking Room"},
        {"A4-1-4", "Hacking Room"},
        {"A4-1-6", "Hacking Room"},
        {"A4-1-7", "Hacking Room"},
        {"A4-2-3", "Sleeping Room"},
        {"A4-2-4", "Sleeping Room"},
        {"A4-2-6", "Sleeping Room"},
        {"A4-2-7", "Sleeping Room"},
        {"A4-2-18", "Sleeping Room"},
        {"A5-1-3", "Hacking Room"},
        {"A5-1-4", "Hacking Room"},
        {"A5-1-5", "Hacking Room"},
        {"A5-1-6", "Hacking Room"},
        {"A5-1-7", "Hacking Room"},
        {"A5-2-3", "Hacking Room"},
        {"A5-2-4", "Hacking Room"},
        {"A5-2-5", "Hacking Room"},
        {"A5-2-6", "Hacking Room"},
        {"A5-2-7", "Hacking Room"},
        {"A6-1-3", "Hacking Room"},
        {"A6-1-4", "Hacking Room"},
        {"A6-1-5", "Hacking Room"},
        {"A6-1-7", "Hacking Room"},
        {"A6-2-3", "Hacking Room"},
        {"A6-2-4", "Hacking Room"},
        {"A6-2-5", "Hacking Room"},
        {"A6-2-6", "Hacking Room"},
        {"A6-2-7", "Hacking Room"},
        {"A6-S1-10", "Check-in"},
        {"A6-1-10", "Cafeteria"},
        {"A5-0-11", "Info-desk"},
        {"A5-0-11", "Baggage check-in"},
        {"A5-0-11", "Hardware lab"},
        {"A5-0-5", "Talk Room 1"},
        {"A5-0-6", "Talk Room 2"},
        {"A5-0-0", "Food"},
        {"D-0-3", "Showers"},
        {"V-0-16", "Auditorium"}
    };

    set<string> placesSigns = {
        "A5-0-8",
        "A5-0-7",
        "A4-0-3",
        "A6-2-9"
    };

    /*cout << "CHECKING CONNECTIVITY" << endl;
    bool allConnected = true;

    set<vector<string>>::iterator it1 = placesFrom.begin();
    while(it1!=placesFrom.end()){
        set<vector<string>>::iterator it2 = placesTo.begin();
        while(it2!=placesTo.end()){
            if(it1!=it2){
                cout << (*it1)[1] << " (" << (*it1)[0] << ") to " << (*it2)[1] << " (" << (*it2)[0] << ")";
                if(bfs(university, (*it1)[0], (*it2)[0])){
                    cout << " is connected." << endl;
                }
                else{
                    cout << " is NOT connected." << endl;
                    allConnected = false;
                }
            }
            ++it2;
        }
        ++it1;
    }

    if(allConnected){
        cout << "ALL PLACES CONNECTED!" << endl;
    }
    else{
        cout << "SOME PLACES ARE NOT CONNECTED!" << endl;
    }
    cout << endl;*/

    /*cout << "DIJKSTRA TEST" << endl;
    string from = "A3-2-3", to = "D-0-3";
    pair<int, map<string, string>> path = dijkstra(university, from, to);

    vector<string> pathReal;
    if(path.first>=0){
        string current = to;
        pathReal.push_back(current);
        while(current!=from){
            current = path.second[current];
            pathReal.push_back(current);
        }
    }

    for(int i=pathReal.size()-1; i>=0; --i){
        cout << pathReal[i] << endl;
    }
    cout << "DISTANCE: " << path.first << "m" << endl;*/

    cout << "SIGN DIRECTIONS" << endl;

    set<string>::iterator it1 = placesSigns.begin();
    while(it1!=placesSigns.end()){
        map<string, set<string>>::iterator it2 = placesTo.begin();
        cout << *it1 << endl;
        while(it2!=placesTo.end()){
            cout << "\t" << it2->first;
            set<string>::iterator it3 = it2->second.begin();
            pair<int, string> minPath(INF, "");
            while(it3!=(it2->second.end())){
                if((*it1)!=(*it3)){
                    pair<int, map<string, string>> path = dijkstra(university, *it1, *it3);
                    if(path.first<minPath.first){
                        minPath.first = path.first;
                        minPath.second = *it3;
                    }
                }
                ++it3;
            }
            cout << " (" << minPath.second << ") at " << minPath.first << "m" << endl;
            ++it2;
        }
        ++it1;
    }
}
