#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <sstream>
#include <cmath>
using namespace std;

class Pair {
public:
    string vname;
    string path;
    int cost;
    Pair(string vname, string path, int cost)
        : vname(vname), path(path), cost(cost) {}
};

class myComparator {
public:
    bool operator()(Pair a, Pair b) { return a.cost > b.cost; }
};

class Graph {
public:
    unordered_map<string, unordered_map<string, int>> vtces;

    void addVertex(string name) {
        if (!vtces.count(name))
            vtces[name] = unordered_map<string, int>();
    }

    void addEdge(string v1, string v2, int value) {
        addVertex(v1);
        addVertex(v2);
        vtces[v1][v2] = value;
        vtces[v2][v1] = value;
    }

    void display_Map() {
        cout << "\nDelhi Metro Map:\n";
        for (auto &v : vtces) {
            cout << v.first << " -> ";
            for (auto &nbr : v.second)
                cout << nbr.first << "(" << nbr.second << " km)  ";
            cout << "\n";
        }
    }

    // Dijkstra’s algorithm – returns (distance, path)
    pair<int, vector<string>> dijkstra(string src, string dst, bool timeMode = false) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        unordered_map<string, bool> visited;

        for (auto &v : vtces) dist[v.first] = INT_MAX;
        dist[src] = 0;

        priority_queue<Pair, vector<Pair>, myComparator> pq;
        pq.push(Pair(src, src, 0));

        while (!pq.empty()) {
            Pair cur = pq.top();
            pq.pop();

            if (visited[cur.vname]) continue;
            visited[cur.vname] = true;

            if (cur.vname == dst) break;

            for (auto &nbr : vtces[cur.vname]) {
                if (!visited[nbr.first]) {
                    int weight = nbr.second;
                    if (timeMode)
                        weight = 120 + 40 * weight; // base time + per km
                    if (cur.cost + weight < dist[nbr.first]) {
                        dist[nbr.first] = cur.cost + weight;
                        parent[nbr.first] = cur.vname;
                        pq.push(Pair(nbr.first, "", dist[nbr.first]));
                    }
                }
            }
        }

        // reconstruct path
        vector<string> path;
        string cur = dst;
        if (parent.find(dst) == parent.end() && src != dst)
            return {INT_MAX, {}};
        while (cur != src) {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        return {dist[dst], path};
    }
};

int main() {
    Graph g;

    // Sample stations (you can add more)
    g.addEdge("Kashmere Gate", "Civil Lines", 2);
    g.addEdge("Civil Lines", "Vidhan Sabha", 1);
    g.addEdge("Vidhan Sabha", "Vishwavidyalaya", 2);
    g.addEdge("Vishwavidyalaya", "GTB Nagar", 2);
    g.addEdge("GTB Nagar", "Model Town", 1);
    g.addEdge("Model Town", "Azadpur", 2);
    g.addEdge("Azadpur", "Adarsh Nagar", 2);
    g.addEdge("Adarsh Nagar", "Jahangirpuri", 2);
    g.addEdge("Jahangirpuri", "Haiderpur Badli Mor", 2);

    while (true) {
        cout << "\n========== DELHI METRO SYSTEM ==========\n";
        cout << "1. List all stations\n";
        cout << "2. Show the metro map\n";
        cout << "3. Get shortest distance\n";
        cout << "4. Get shortest time\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if (choice == 5) break;

        vector<string> stationNames;
        for (auto &v : g.vtces) stationNames.push_back(v.first);

        if (choice == 1) {
            cout << "\nAll Stations:\n";
            for (int i = 0; i < (int)stationNames.size(); ++i)
                cout << i + 1 << ". " << stationNames[i] << "\n";
        }

        else if (choice == 2) {
            g.display_Map();
        }

        else if (choice == 3 || choice == 4) {
            cout << "\nSelect source and destination:\n";
            for (int i = 0; i < (int)stationNames.size(); ++i)
                cout << i + 1 << ". " << stationNames[i] << "\n";

            int srcIndex, dstIndex;
            cout << "Enter source index: ";
            cin >> srcIndex;
            cout << "Enter destination index: ";
            cin >> dstIndex;

            if (srcIndex < 1 || dstIndex < 1 ||
                srcIndex > (int)stationNames.size() || dstIndex > (int)stationNames.size()) {
                cout << "Invalid selection.\n";
                continue;
            }

            string src = stationNames[srcIndex - 1];
            string dst = stationNames[dstIndex - 1];

            auto res = g.dijkstra(src, dst, choice == 4);

            if (res.first == INT_MAX) {
                cout << "No path exists between " << src << " and " << dst << ".\n";
            } else {
                cout << "\nPath: ";
                for (size_t i = 0; i < res.second.size(); ++i) {
                    cout << res.second[i];
                    if (i != res.second.size() - 1) cout << " -> ";
                }
                cout << "\n";
                if (choice == 3)
                    cout << "Shortest Distance: " << res.first << " km\n";
                else
                    cout << "Shortest Time: " << ((res.first + 59) / 60) << " minutes\n";
            }
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    cout << "Thank you for using Delhi Metro System!\n";
    return 0;
}
