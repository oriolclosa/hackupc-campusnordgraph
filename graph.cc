#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
#include <string>
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
            if(((*it).size()==2)&&((*it)[1].length()>1)){
                if((*it)[1]==to){
                    return true;
                }
                if((visited.find((*it)[1])==visited.end())&&(atoi((*it)[0].c_str())>=0)){
                    visited.insert((*it)[1]);
                    queue.push_back((*it)[1]);
                }
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
            if(((*it).size()==2)&&((*it)[1].length()>1)){
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
        {"A6-S1-0", {{"T"}, {"5", "A6-S1-9", "T"}}},
        {"A6-S1-1", {{"T"}, {"5", "A6-S1-2", "L"}}},
        {"A6-S1-2", {{"T"},{"5", "A6-S1-3", "L"}}},
        {"A6-S1-3", {{"T"},{"5", "A6-S1-4", "L"}}},
        {"A6-S1-4", {{"T"},{"5", "A6-S1-9", "L"}}},
        {"A6-S1-8", {{"T"},{"5", "A6-S1-7", "R"}}},
        {"A6-S1-7", {{"T"},{"5", "A6-S1-6", "R"}}},
        {"A6-S1-6", {{"T"},{"5", "A6-S1-5", "R"}}},
        {"A6-S1-5", {{"T"},{"5", "A6-S1-9", "R"}}},
        {"A6-S1-9", {{"T"},{"6", "A6-S1-10", "T"}}},
        {"A6-S1-10", {{"L", "R"},{"3", "A6-S1-11", "T"}}},
        {"A6-S1-11", {{"L", "R"}, {"4", "A6-S1-12", "T"}}},
        {"A6-S1-12", {{"T"}, {"1", "A6-S1-13", "T"}, {"1", "A6-S1-14", "T"}, {"2", "A6-S1-15", "L"}}},
        {"A6-S1-15", {{"L"}, {"10", "A5-0-10", "T"}}},
        {"A6-S1-13", {{"T"}, {"1", "A6-S1-12", "B"}}},
        {"A6-S1-14", {{"T"}, {"1", "A6-S1-12", "B"}}},
        {"A6-0-0", {{"T"}, {"25", "A5-0-0", "L"}, {"3", "A6-0-1", "T"}, {"12", "A6-0-2", "L"}, {"12", "A6-0-3", "R"}, {"12", "V-0-0", "R"}}},
        {"A6-0-1", {{"T"}, {"3", "A6-0-0", "B"}, {"11", "A6-0-2", "L"}, {"11", "A6-0-3", "R"}, {"2", "A6-0-4", "T"}}},
        {"A6-0-2", {{"T"}, {"3", "A5-0-3", "L"}, {"12", "A6-0-0", "B"}, {"11", "A6-0-1", "R"}, {"2", "A6-0-7", "T"}}},
        {"A6-0-3", {{"T"}, {"12", "A6-0-0", "B"}, {"11", "A6-0-1", "R"}, {"2", "A6-0-8", "T"}}},
        {"A6-0-4", {{"T"}, {"2", "A6-0-1", "B"}, {"2", "A6-0-5", "L"}, {"2", "A6-0-6", "R"}, {"-9", "A6-E-0", "T"}}},
        {"A6-0-5", {{"T"}, {"2", "A6-0-4", "R"}, {"8", "A6-0-7", "L"}}},
        {"A6-0-6", {{"T"}, {"2", "A6-0-4", "L"}, {"8", "A6-0-8", "R"}}},
        {"A6-0-7", {{"R"}, {"2", "A6-0-2", "B"}, {"8", "A6-0-5", "R"}, {"2", "A6-0-9", "T"}}},
        {"A6-0-8", {{"L"}, {"2", "A6-0-3", "B"}, {"8", "A6-0-6", "L"}, {"2", "A6-0-10", "T"}}},
        {"A6-0-9", {{"L"}, {"2", "A6-0-7", "T"}, {"9", "A6-E-1", "L"}}},
        {"A6-0-10", {{"R"}, {"2", "A6-0-8", "T"}, {"9", "A6-E-2", "R"}}},
        {"A6-E-0", {{"T"}, {"9", "A6-0-4", "T"}, {"11", "A6-E-1", "L"}, {"11", "A6-E-2", "R"}}},
        {"A6-E-1", {{"R"}, {"10", "A6-1-11", "T"}, {"-11", "A6-E-0", "R"}, {"9", "A6-0-9", "L"}}},
        {"A6-E-2", {{"L"}, {"10", "A6-1-9", "T"}, {"-11", "A6-E-0", "L"}, {"9", "A6-0-10", "R"}}},
        {"A6-1-0", {{"T"}, {"6", "A6-1-1", "L"}, {"6", "A6-1-2", "R"}, {"4", "A6-1-3", "L"}, {"4", "A6-1-4", "R"}, {"1", "A6-1-5", "B"}}},
        {"A6-1-1", {{"T"}, {"6", "A6-1-0", "R"}, {"2", "A6-1-3", "R"}, {"1", "A6-1-6", "B"}, {"2", "A6-1-8", "L"}}},
        {"A6-1-2", {{"T"}, {"6", "A6-1-0", "L"}, {"2", "A6-1-4", "L"}, {"1", "A6-1-7", "B"}, {"4", "A6-1-9", "R"}}},
        {"A6-1-3", {{"T"}, {"4", "A6-1-0", "B"}, {"2", "A6-1-1", "B"}}},
        {"A6-1-4", {{"T"}, {"4", "A6-1-0", "B"}, {"2", "A6-1-2", "B"}}},
        {"A6-1-5", {{"B"}, {"1", "A6-1-0", "T"}}},
        {"A6-1-6", {{"B"}, {"1", "A6-1-1", "T"}}},
        {"A6-1-7", {{"B"}, {"1", "A6-1-2", "T"}}},
        {"A6-1-8", {{"T"}, {"2", "A6-1-1", "R"}, {"2", "A6-1-10", "B"}, {"2", "A6-1-11", "L"}}},
        {"A6-1-9", {{"R"}, {"10", "A6-E-2", "T"}, {"4", "A6-1-2", "L"}, {"1", "A6-1-12", "B"}}},
        {"A6-1-10", {{"R"}, {"2", "A6-1-8", "T"}, {"3", "A6-1-14", "L"}}},
        {"A6-1-11", {{"L"}, {"10", "A6-E-1", "T"}, {"2", "A6-1-8", "R"}, {"1", "A6-1-13", "B"}}},
        {"A6-1-12", {{"R"}, {"1", "A6-1-9", "L"}, {"1", "A6-1-16", "B"}, {"10", "A6-2-9", "L"}}},
        {"A6-1-13", {{"L"}, {"1", "A6-1-11", "B"}, {"1", "A6-1-14", "B"}, {"10", "A6-2-11", "R"}}},
        {"A6-1-14", {{"T"}, {"3", "A5-1-17", "L"}, {"3", "A6-1-10", "R"}, {"1", "A6-1-13", "T"}, {"1", "A6-1-15", "B"}}},
        {"A6-1-15", {{"B"}, {"1", "A6-1-14", "T"}}},
        {"A6-1-16", {{"B"}, {"1", "A6-1-12", "T"}}},
        {"A6-2-0", {{"T"}, {"6", "A6-2-1", "L"}, {"6", "A6-2-2", "R"}, {"4", "A6-2-3", "L"}, {"4", "A6-2-4", "R"}, {"1", "A6-2-5", "B"}}},
        {"A6-2-1", {{"T"}, {"6", "A6-2-0", "R"}, {"2", "A6-2-3", "R"}, {"1", "A6-2-6", "B"}, {"2", "A6-2-8", "L"}}},
        {"A6-2-2", {{"T"}, {"6", "A6-2-0", "L"}, {"2", "A6-2-4", "L"}, {"1", "A6-2-7", "B"}, {"4", "A6-2-9", "R"}}},
        {"A6-2-3", {{"T"}, {"4", "A6-2-0", "R"}, {"2", "A6-2-1", "L"}}},
        {"A6-2-4", {{"T"}, {"4", "A6-2-0", "L"}, {"2", "A6-2-2", "R"}}},
        {"A6-2-5", {{"B"}, {"1", "A6-2-0", "T"}}},
        {"A6-2-6", {{"B"}, {"1", "A6-2-1", "T"}}},
        {"A6-2-7", {{"B"}, {"1", "A6-2-2", "T"}}},
        {"A6-2-8", {{"T"}, {"2", "A6-2-1", "R"}, {"2", "A6-2-10", "B"}, {"2", "A6-2-11", "L"}}},
        {"A6-2-9", {{"R"}, {"10", "A6-1-12", "T"}, {"4", "A6-2-2", "L"}, {"1", "A6-2-12", "B"}}},
        {"A6-2-10", {{"R"}, {"2", "A6-2-8", "T"}, {"3", "A6-2-14", "L"}}},
        {"A6-2-11", {{"L"}, {"10", "A6-1-13", "T"}, {"2", "A6-2-8", "R"}, {"1", "A6-2-13", "B"}}},
        {"A6-2-12", {{"R"}, {"1", "A6-2-16", "B"}, {"1", "A6-2-9", "L"}}},
        {"A6-2-13", {{"L"}, {"1", "A6-2-14", "B"}, {"10", "A6-2-11", "R"}}},
        {"A6-2-14", {{"T"}, {"3", "A5-2-17", "L"}, {"3", "A6-2-10", "R"}, {"1", "A6-2-13", "T"}, {"1", "A6-2-15", "B"}}},
        {"A6-2-15", {{"B"}, {"1", "A6-2-14", "T"}}},
        {"A6-2-16", {{"B"}, {"1", "A6-2-12", "T"}}},

        //Edifici A5
        {"A5-0-0", {{"T"}, {"25", "A4-0-0"}, {"3", "A5-0-1"}, {"12", "A5-0-2"}, {"12", "A5-0-3"}, {"25", "A6-0-0"}}},
        {"A5-0-1", {{"T"}, {"3", "A5-0-0"}, {"11", "A5-0-2"}, {"11", "A5-0-3"}, {"2", "A5-0-4"}}},
        {"A5-0-2", {{"T"}, {"3", "A4-0-3"}, {"12", "A5-0-0"}, {"11", "A5-0-1"}, {"2", "A5-0-7"}}},
        {"A5-0-3", {{"T"}, {"12", "A5-0-0"}, {"11", "A5-0-1"}, {"2", "A5-0-8"}, {"3", "A6-0-2"}}},
        {"A5-0-4", {{"L", "R"}, {"2", "A5-0-1"}, {"2", "A5-0-5"}, {"2", "A5-0-6"}, {"4", "A5-0-11"}}},
        {"A5-0-5", {{"T"}, {"2", "A5-0-4"}, {"8", "A5-0-7"}}},
        {"A5-0-6", {{"T"}, {"2", "A5-0-4"}, {"8", "A5-0-8"}}},
        {"A5-0-7", {{"R"}, {"2", "A5-0-2"}, {"8", "A5-0-5"}, {"2", "A5-0-9"}}},
        {"A5-0-8", {{"L"}, {"2", "A5-0-3"}, {"8", "A5-0-6"}, {"2", "A5-0-10"}}},
        {"A5-0-9", {{"L"}, {"2", "A5-0-7"}, {"9", "A5-E-1"}}},
        {"A5-0-10", {{"R"}, {"2", "A5-0-8"}, {"9", "A5-E-2"}, {"-10", "A6-S1-15"}}},
        {"A5-0-11", {{"T"}, {"4", "A5-0-4"}}},
        {"A5-E-1", {{"R"}, {"10", "A5-1-11"}, {"9", "A5-0-9"}}},
        {"A5-E-2", {{"L"}, {"10", "A5-1-9"}, {"9", "A5-0-10"}}},
        {"A5-1-0", {{"T"}, {"6", "A5-1-1"}, {"6", "A5-1-2"}, {"4", "A5-1-3"}, {"4", "A5-1-4"}, {"1", "A5-1-5"}}},
        {"A5-1-1", {{"T"}, {"6", "A5-1-0"}, {"2", "A5-1-3"}, {"1", "A5-1-6"}, {"2", "A5-1-8"}}},
        {"A5-1-2", {{"T"}, {"6", "A5-1-0"}, {"2", "A5-1-4"}, {"1", "A5-1-7"}, {"4", "A5-1-9"}}},
        {"A5-1-3", {{"T"}, {"4", "A5-1-0"}, {"2", "A5-1-1"}}},
        {"A5-1-4", {{"T"}, {"4", "A5-1-0"}, {"2", "A5-1-2"}}},
        {"A5-1-5", {{"B"}, {"1", "A5-1-0"}}},
        {"A5-1-6", {{"B"}, {"1", "A5-1-1"}}},
        {"A5-1-7", {{"B"}, {"1", "A5-1-2"}}},
        {"A5-1-8", {{"T"}, {"2", "A5-1-1"}, {"2", "A5-1-10"}, {"2", "A5-1-11"}}},
        {"A5-1-9", {{"L"}, {"10", "A5-E-2"}, {"4", "A5-1-2"}, {"1", "A5-1-12"}}},
        {"A5-1-10", {{"R"}, {"2", "A5-1-8"}, {"3", "A5-1-14"}}},
        {"A5-1-11", {{"L"}, {"10", "A5-E-1"}, {"2", "A5-1-8"}, {"1", "A5-1-13"}}},
        {"A5-1-12", {{"R"}, {"1", "A5-1-9"}, {"1", "A5-1-17"}, {"10", "A5-2-9"}}},
        {"A5-1-13", {{"L"}, {"1", "A5-1-11"}, {"1", "A5-1-14"}, {"10", "A5-2-11"}}},
        {"A5-1-14", {{"T"}, {"3", "A4-1-17"}, {"3", "A5-1-10"}, {"1", "A5-1-13"}, {"1", "A5-1-15"}}},
        {"A5-1-15", {{"B"}, {"1", "A5-1-14"}}},
        {"A5-1-16", {{"B"}, {"1", "A5-1-12"}}},
        {"A5-1-17", {{"B"}, {"1", "A5-1-12"}, {"1", "A5-1-16"}, {"3", "A6-1-14"}}},
        {"A5-2-0", {{"T"}, {"6", "A5-2-1"}, {"6", "A5-2-2"}, {"4", "A5-2-3"}, {"4", "A5-2-4"}, {"1", "A5-2-5"}}},
        {"A5-2-1", {{"T"}, {"6", "A5-2-0"}, {"2", "A5-2-3"}, {"1", "A5-2-6"}, {"2", "A5-2-8"}}},
        {"A5-2-2", {{"T"}, {"6", "A5-2-0"}, {"2", "A5-2-4"}, {"1", "A5-2-7"}, {"4", "A5-2-9"}}},
        {"A5-2-3", {{"T"}, {"4", "A5-2-0"}, {"2", "A5-2-1"}}},
        {"A5-2-4", {{"T"}, {"4", "A5-2-0"}, {"2", "A5-2-2"}}},
        {"A5-2-5", {{"B"}, {"1", "A5-2-0"}}},
        {"A5-2-6", {{"B"}, {"1", "A5-2-1"}}},
        {"A5-2-7", {{"B"}, {"1", "A5-2-2"}}},
        {"A5-2-8", {{"T"}, {"2", "A5-2-1"}, {"2", "A5-2-10"}, {"2", "A5-2-11"}}},
        {"A5-2-9", {{"L"}, {"10", "A5-1-12"}, {"4", "A5-2-2"}, {"1", "A5-2-12"}}},
        {"A5-2-10", {{"R"}, {"2", "A5-2-8"}, {"3", "A5-2-14"}}},
        {"A5-2-11", {{"L"}, {"10", "A5-1-13"}, {"2", "A5-2-8"}, {"1", "A5-2-13"}}},
        {"A5-2-12", {{"R"}, {"1", "A5-2-17"}, {"1", "A5-2-9"}}},
        {"A5-2-13", {{"L"}, {"1", "A5-2-14"}, {"10", "A5-2-11"}}},
        {"A5-2-14", {{"T"}, {"3", "A4-2-17"}, {"3", "A5-2-10"}, {"1", "A5-2-13"}, {"1", "A5-2-15"}}},
        {"A5-2-15", {{"B"}, {"1", "A5-2-14"}}},
        {"A5-2-16", {{"B"}, {"1", "A5-2-17"}}},
        {"A5-2-17", {{"B", "A5-2-12"}, {"1", "A5-2-16"}, {"3", "A6-2-14"}}},

        //Efifici A4
        {"A4-0-0", {{"T"}, {"25", "A3-0-0"}, {"3", "A4-0-1"}, {"12", "A4-0-2"}, {"12", "A4-0-3"}, {"25", "A5-0-0"}}},
        {"A4-0-1", {{"T"}, {"3", "A4-0-0"}, {"11", "A4-0-2"}, {"11", "A4-0-3"}, {"-2", "A5-0-4"}}},
        {"A4-0-2", {{"T"}, {"12", "A4-0-0"}, {"11", "A4-0-1"}, {"-2", "A4-0-7"}, {"1", "A4-0-14"}}},
        {"A4-0-3", {{"T"}, {"12", "A4-0-0"}, {"11", "A4-0-1"}, {"2", "A4-0-8"}, {"3", "A5-0-2"}}},
        {"A4-0-4", {{"T"}, {"-2", "A4-0-1"}, {"2", "A4-0-5"}, {"2", "A4-0-6"}}},
        {"A4-0-5", {{"T"}, {"2", "A4-0-4"}, {"-8", "A4-0-7"}}},
        {"A4-0-6", {{"T"}, {"2", "A4-0-4"}, {"-8", "A4-0-8"}}},
        {"A4-0-7", {{"R"}, {"-2", "A4-0-2"}, {"-8", "A4-0-5"}, {"2", "A4-0-9"}}},
        {"A4-0-8", {{"L"}, {"2", "A4-0-3"}, {"-8", "A4-0-6"}, {"2", "A4-0-10"}}},
        {"A4-0-9", {{"R"}, {"2", "A4-0-7"}, {"1", "A4-0-11"}, {"1", "A4-0-12"}, {"1", "A4-0-13"}}},
        {"A4-0-10", {{"R"}, {"2", "A4-0-8"}, {"9", "A4-E-2"}}},
        {"A4-0-11", {{"R"}, {"1", "A4-0-9"}}},
        {"A4-0-12", {{"R"}, {"1", "A4-0-9"}}},
        {"A4-0-13", {{"T"}, {"1", "A4-0-9"}, {"9", "A4-E-1"}}},
        {"A4-0-14", {{"L", "T"}, {"4", "A3-0-14"}, {"1", "A4-0-2"}, {"7", "D-0-2"}}},
        {"A4-E-1", {{"T"}, {"10", "A4-0-13"}, {"9", "A4-1-13"}}},
        {"A4-E-2", {{"L"}, {"10", "A4-0-10"}, {"9", "A4-1-9"}}},
        {"A4-1-0", {{"T"}, {"6", "A4-1-1"}, {"6", "A4-1-2"}, {"4", "A4-1-3"}, {"4", "A4-1-4"}}},
        {"A4-1-1", {{"T"}, {"6", "A4-1-0"}, {"2", "A4-1-3"}, {"2", "A4-1-6"}, {"1", "A4-1-8"}}},
        {"A4-1-2", {{"T"}, {"6", "A4-1-0"}, {"2", "A4-1-4"}, {"2", "A4-1-7"}, {"4", "A4-1-9"}}},
        {"A4-1-3", {{"T"}, {"4", "A4-1-0"}, {"2", "A4-1-1"}}},
        {"A4-1-4", {{"T"}, {"4", "A4-1-0"}, {"2", "A4-1-2"}}},
        {"A4-1-6", {{"B"}, {"2", "A4-1-1"}}},
        {"A4-1-7", {{"B"}, {"2", "A4-1-2"}}},
        {"A4-1-8", {{"T"}, {"2", "A4-1-1"}, {"2", "A4-1-10"}, {"2", "A4-1-11"}}},
        {"A4-1-9", {{"L"}, {"9", "A4-E-2"}, {"4", "A4-1-2"}, {"1", "A4-1-12"}}},
        {"A4-1-10", {{"R"}, {"2", "A4-1-8"}, {"3", "A4-1-14"}}},
        {"A4-1-11", {{"L"}, {"2", "A4-1-8"}, {"1", "A4-1-13"}, {"10", "A4-2-13"}}},
        {"A4-1-12", {{"R"}, {"1", "A4-1-9"}, {"1", "A4-1-17"}, {"10", "A4-2-9"}}},
        {"A4-1-13", {{"L"}, {"9", "A4-E-1"}, {"1", "A4-1-11"}, {"1", "A4-1-14"}}},
        {"A4-1-14", {{"T"}, {"3", "A3-1-14"}, {"3", "A4-1-10"}, {"1", "A4-1-13"}, {"1", "A4-1-15"}}},
        {"A4-1-15", {{"B"}, {"1", "A4-1-14"}}},
        {"A4-1-16", {{"B"}, {"1", "A4-1-17"}}},
        {"A4-1-17", {{"B"}, {"1", "A4-1-12"}, {"1", "A4-1-16"}, {"3", "A5-1-14"}}},
        {"A4-2-0", {{"T"}, {"6", "A4-2-1"}, {"6", "A4-2-2"}, {"2", "A4-2-5"}, {"2", "A4-2-18"}}},
        {"A4-2-1", {{"T"}, {"6", "A4-2-0"}, {"1", "A4-2-3"}, {"1", "A4-2-6"}, {"1", "A4-2-8"}}},
        {"A4-2-2", {{"T"}, {"6", "A4-2-0"}, {"1", "A4-2-4"}, {"1", "A4-2-7"}, {"10", "A4-2-9"}}},
        {"A4-2-3", {{"T"}, {"1", "A4-2-1"}}},
        {"A4-2-4", {{"T"}, {"1", "A4-2-2"}}},
        {"A4-2-5", {{"B"}, {"2", "A4-2-0"}}},
        {"A4-2-6", {{"B"}, {"1", "A4-2-1"}}},
        {"A4-2-7", {{"B"}, {"1", "A4-2-2"}}},
        {"A4-2-8", {{"T"}, {"2", "A4-2-1"}, {"2", "A4-2-10"}, {"2", "A4-2-11"}}},
        {"A4-2-9", {{"L"}, {"10", "A4-1-12"}, {"10", "A4-2-2"}, {"1", "A4-2-12"}}},
        {"A4-2-10", {{"R"}, {"2", "A4-2-8"}, {"3", "A4-2-14"}}},
        {"A4-2-11", {{"L"}, {"2", "A4-2-8"}, {"1", "A4-2-13"}}},
        {"A4-2-12", {{"R"}, {"1", "A4-2-9"}, {"1", "A4-2-17"}}},
        {"A4-2-13", {{"L"}, {"9", "A4-1-11"}, {"1", "A4-2-11"}, {"1", "A4-2-14"}}},
        {"A4-2-14", {{"T"}, {"3", "A3-2-14"}, {"3", "A4-2-10"}, {"1", "A4-2-13"}, {"1", "A4-2-15"}}},
        {"A4-2-15", {{"B"}, {"1", "A4-2-14"}}},
        {"A4-2-16", {{"B"}, {"1", "A4-2-17"}}},
        {"A4-2-17", {{"B"}, {"1", "A4-2-12"}, {"1", "A4-2-16"}, {"3", "A5-2-14"}}},
        {"A4-2-18", {{"T"}, {"2", "A4-2-0"}}},

        //Edifici A3
        {"A3-0-0", {{"T"}, {"3", "A3-0-1"}, {"12", "A3-0-2"}, {"12", "A3-0-3"}, {"25", "A4-0-0"}}},
        {"A3-0-1", {{"T"}, {"3", "A3-0-0"}, {"11", "A3-0-2"}, {"11", "A3-0-3"}, {"-2", "A3-0-4"}}},
        {"A3-0-2", {{"T"}, {"12", "A3-0-0"}, {"11", "A3-0-1"}, {"2", "A3-0-7"}}},
        {"A3-0-3", {{"T"}, {"12", "A3-0-0"}, {"11", "A3-0-1"}, {"-2", "A4-0-8"}, {"1", "A3-0-14"}}},
        {"A3-0-4", {{"T"}, {"-2", "A3-0-1"}, {"2", "A3-0-5"}, {"2", "A3-0-6"}}},
        {"A3-0-5", {{"T"}, {"2", "A3-0-4"}, {"-8", "A3-0-7"}}},
        {"A3-0-6", {{"T"}, {"2", "A3-0-4"}, {"-8", "A3-0-8"}}},
        {"A3-0-7", {{"L"}, {"2", "A3-0-2"}, {"-8", "A3-0-5"}, {"2", "A3-0-10"}}},
        {"A3-0-8", {{"R"}, {"-2", "A3-0-3"}, {"-8", "A3-0-6"}, {"2", "A3-0-9"}}},
        {"A3-0-9", {{"L"}, {"2", "A3-0-8"}, {"1", "A3-0-11"}, {"1", "A3-0-12"}, {"1", "A3-0-13"}}},
        {"A3-0-10", {{"L"}, {"2", "A3-0-7"}, {"9", "A3-E-1"}}},
        {"A3-0-11", {{"L"}, {"1", "A3-0-9"}}},
        {"A3-0-12", {{"L"}, {"1", "A3-0-9"}}},
        {"A3-0-13", {{"T"}, {"1", "A3-0-9"}, {"9", "A3-E-2"}}},
        {"A3-0-14", {{"R", "B"}, {"1", "A3-0-3"}, {"4", "A4-0-14"}, {"7", "D-0-1"}}},
        {"A3-E-1", {{"R"}, {"10", "A4-0-10"}, {"9", "A3-1-9"}}},
        {"A3-E-2", {{"T"}, {"10", "A3-0-13"}, {"9", "A3-1-13"}}},
        {"A3-1-0", {{"T"}, {"6", "A3-1-1"}, {"6", "A3-1-2"}, {"4", "A3-1-3"}, {"4", "A3-1-4"}}},
        {"A3-1-1", {{"T"}, {"6", "A3-1-0"}, {"2", "A3-1-3"}, {"2", "A3-1-6"}, {"1", "A3-1-8"}}},
        {"A3-1-2", {{"T"}, {"6", "A4-1-0"}, {"2", "A4-1-4"}, {"2", "A4-1-7"}, {"4", "A3-1-9"}}},
        {"A3-1-3", {{"T"}, {"4", "A3-1-0"}, {"2", "A3-1-1"}}},
        {"A3-1-4", {{"T"}, {"4", "A3-1-0"}, {"2", "A3-1-2"}}},
        {"A3-1-6", {{"B"}, {"2", "A3-1-1"}}},
        {"A3-1-7", {{"B"}, {"2", "A3-1-2"}}},
        {"A3-1-8", {{"T"}, {"2", "A3-1-1"}, {"2", "A3-1-10"}, {"2", "A3-1-11"}}},
        {"A3-1-9", {{"R"}, {"9", "A3-E-2"}, {"4", "A3-1-2"}, {"1", "A3-1-12"}}},
        {"A3-1-10", {{"L"}, {"2", "A3-1-8"}, {"3", "A3-1-14"}}},
        {"A3-1-11", {{"R"}, {"2", "A3-1-8"}, {"1", "A3-1-13"}, {"10", "A3-2-13"}}},
        {"A3-1-12", {{"L"}, {"1", "A3-1-9"}, {"1", "A3-1-17"}, {"10", "A3-2-9"}}},
        {"A3-1-13", {{"R"}, {"9", "A3-E-2"}, {"1", "A3-1-11"}, {"1", "A3-1-14"}}},
        {"A3-1-14", {{"T"}, {"3", "A3-1-10"}, {"1", "A3-1-13"}, {"1", "A3-1-15"}, {"3", "A4-1-14"}}},
        {"A3-1-15", {{"B"}, {"1", "A3-1-14"}}},
        {"A3-1-16", {{"B"}, {"1", "A3-1-17"}}},
        {"A3-1-17", {{"B"}, {"1", "A3-1-12"}, {"1", "A3-1-16"}}},
        {"A3-2-0", {{"T"}, {"6", "A3-2-1"}, {"6", "A3-2-2"}, {"2", "A3-2-5"}, {"2", "A3-2-18"}}},
        {"A3-2-1", {{"T"}, {"6", "A3-2-0"}, {"1", "A3-2-3"}, {"1", "A3-2-6"}, {"1", "A3-2-8"}}},
        {"A3-2-2", {{"T"}, {"6", "A3-2-0"}, {"1", "A3-2-4"}, {"1", "A3-2-7"}, {"10", "A3-2-9"}}},
        {"A3-2-3", {{"T"}, {"1", "A3-2-1"}}},
        {"A3-2-4", {{"T"}, {"1", "A3-2-2"}}},
        {"A3-2-5", {{"T"}, {"2", "A3-2-0"}}},
        {"A3-2-6", {{"T"}, {"1", "A3-2-1"}}},
        {"A3-2-7", {{"T"}, {"1", "A3-2-2"}}},
        {"A3-2-8", {{"T"}, {"2", "A3-2-1"}, {"2", "A3-2-10"}, {"2", "A3-2-11"}}},
        {"A3-2-9", {{"R"}, {"10", "A3-1-12"}, {"10", "A3-2-2"}, {"1", "A3-2-12"}}},
        {"A3-2-10", {{"L"}, {"2", "A3-2-8"}, {"3", "A3-2-14"}}},
        {"A3-2-11", {{"R"}, {"2", "A3-2-8"}, {"1", "A3-2-13"}}},
        {"A3-2-12", {{"L"}, {"1", "A3-2-9"}, {"1", "A3-2-17"}}},
        {"A3-2-13", {{"R"}, {"9", "A3-1-11"}, {"1", "A3-2-11"}, {"1", "A3-2-14"}}},
        {"A3-2-14", {{"T"}, {"3", "A3-2-10"}, {"1", "A3-2-13"}, {"1", "A3-2-15"}, {"3", "A4-2-14"}}},
        {"A3-2-15", {{"B"}, {"1", "A3-2-14"}}},
        {"A3-2-16", {{"B"}, {"1", "A3-2-17"}}},
        {"A3-2-17", {{"B"}, {"1", "A3-2-12"}, {"1", "A3-2-16"}}},
        {"A3-2-18", {{"T"}, {"2", "A3-2-0"}}},

        //Vèrtex
        {"V-0-0", {{"R"}, {"12", "A6-0-0"}, {"12", "V-0-1"}}},
        {"V-0-1", {{"L"}, {"4", "V-0-0"}, {"4", "V-0-2"}}},
        {"V-0-2", {{"L"}, {"4", "V-0-1"}, {"4", "V-0-3"}}},
        {"V-0-3", {{"L"}, {"4", "V-0-2"}, {"4", "V-0-4"}}},
        {"V-0-4", {{"L"}, {"4", "V-0-3"}, {"4", "V-0-5"}}},
        {"V-0-5", {{"L"}, {"4", "V-0-4"}, {"4", "V-0-6"}}},
        {"V-0-6", {{"L"}, {"4", "V-0-5"}, {"4", "V-0-7"}}},
        {"V-0-7", {{"L"}, {"4", "V-0-6"}, {"4", "V-0-8"}}},
        {"V-0-8", {{"L"}, {"4", "V-0-7"}, {"4", "V-0-9"}}},
        {"V-0-9", {{"L"}, {"4", "V-0-8"}, {"4", "V-0-10"}}},
        {"V-0-10", {{"T"}, {"4", "V-0-9"}, {"4", "V-0-11"}}},
        {"V-0-11", {{"B"}, {"4", "V-0-10"}, {"4", "V-0-12"}}},
        {"V-0-12", {{"R"}, {"4", "V-0-11"}, {"4", "V-0-13"}}},
        {"V-0-13", {{"R"}, {"4", "V-0-12"}, {"4", "V-0-14"}}},
        {"V-0-14", {{"B"}, {"4", "V-0-13"}, {"4", "V-0-15"}}},
        {"V-0-15", {{"R"}, {"4", "V-0-14"}, {"4", "V-0-16"}}},
        {"V-0-16", {{"R"}, {"4", "V-0-15"}}},

        //Poliesportiu
        {"D-0-0", {{"L", "R"}, {"3", "D-0-1"}, {"3", "D-0-2"}, {"100", "D-0-3"}}},
        {"D-0-1", {{"T", "L"}, {"7", "A3-0-14"}, {"3", "D-0-0"}, {"3", "D-0-2"}}},
        {"D-0-2", {{"T", "R"}, {"7", "A4-0-14"}, {"3", "D-0-0"}, {"3", "D-0-1"}}},
        {"D-0-3", {{"L", "R"}, {"100", "D-0-0"}}}
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
            set<string>::iterator it3 = it2->second.begin();
            pair<int, string> minPath(INF, "");
            while(it3!=(it2->second.end())){
                if((*it1)!=(*it3)){
                    pair<int, map<string, string>> path = dijkstra(university, *it1, *it3);
                    if((path.first!=0)&&(path.first<minPath.first)){
                        minPath.first = path.first;
                        minPath.second = *it3;
                    }
                }
                ++it3;
            }
            cout << "\t" << minPath.first << "m\t" << it2->first;
            if(it2->first.length()<8){
                cout << "\t";
            }
            if(it2->first.length()<16){
                cout << "\t";
            }
            cout << "\t" << minPath.second << endl;
            ++it2;
        }
        ++it1;
    }
}
