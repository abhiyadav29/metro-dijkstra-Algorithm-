
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

// Class representing the Delhi Metro Map as a weighted graph
class MetroMap {
public:
    unordered_map<string, vector<pair<string, int>>> adj; // adjacency list

    // Add a connection between two stations
    void addConnection(string u, string v, int dist) {
        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist});
    }

    // Display all stations
    void displayStations() {
        cout << "\nAvailable Stations:\n";
        for (auto &p : adj)
            cout << "• " << p.first << endl;
    }

    // Display all connections (Metro Map)
    void displayMap() {
        cout << "\n======== METRO MAP (Station -> [ConnectedStation, Distance]) ========\n";
        for (auto &p : adj) {
            cout << p.first << " -> ";
            for (auto &nbr : p.second)
                cout << "[" << nbr.first << ", " << nbr.second << "km] ";
            cout << endl;
        }
    }

    // Dijkstra's Algorithm using Min Heap (Priority Queue)
    void shortestPath(string src, string dest) {
        if (adj.find(src) == adj.end() || adj.find(dest) == adj.end()) {
            cout << "\n Invalid Station Name!\n";
            return;
        }

        unordered_map<string, int> dist;
        unordered_map<string, string> parent;

        for (auto &p : adj)
            dist[p.first] = INT_MAX;

        dist[src] = 0;

        // Min-heap {distance, node}
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [currDist, node] = pq.top();
            pq.pop();

            if (currDist > dist[node])
                continue;

            for (auto &nbr : adj[node]) {
                string nextNode = nbr.first;
                int edgeWeight = nbr.second;

                if (dist[node] + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + edgeWeight;
                    parent[nextNode] = node;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        // If destination unreachable
        if (dist[dest] == INT_MAX) {
            cout << "\n⚠️ No path found between " << src << " and " << dest << ".\n";
            return;
        }

        // Print shortest distance
        cout << "\n🚇 Shortest Distance from " << src << " → " << dest << " = " << dist[dest] << " km\n";

        // Reconstruct path
        vector<string> path;
        for (string at = dest; at != ""; at = parent[at]) {
            path.push_back(at);
            if (at == src)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "🗺️  Path: ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " → ";
        }
        cout << endl;
    }
};

// Helper to build sample Delhi Metro Map
MetroMap buildDelhiMetro() {
    MetroMap m;

    m.addConnection("RajivChowk", "MandiHouse", 2);
    m.addConnection("MandiHouse", "CentralSecretariat", 3);
    m.addConnection("CentralSecretariat", "AIIMS", 5);
    m.addConnection("AIIMS", "GreenPark", 2);
    m.addConnection("GreenPark", "HauzKhas", 3);
    m.addConnection("RajivChowk", "KashmereGate", 5);
    m.addConnection("KashmereGate", "CivilLines", 2);
    m.addConnection("CivilLines", "RedFort", 3);
    m.addConnection("RedFort", "ChandniChowk", 1);
    m.addConnection("RajivChowk", "ChandniChowk", 4);

    return m;
}

// Main Program
int main() {
    MetroMap delhiMetro = buildDelhiMetro();
    int choice;

    while (true) {
        cout << "\n=============================\n";
        cout << "       DELHI METRO MAP     \n";
        cout << "=============================\n";
        cout << "1. Display All Stations\n";
        cout << "2. Display Metro Map\n";
        cout << "3. Find Shortest Distance & Path\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
            delhiMetro.displayStations();
        else if (choice == 2)
            delhiMetro.displayMap();
        else if (choice == 3) {
            string src, dest;
            cout << "\nEnter Source Station: ";
            cin >> src;
            cout << "Enter Destination Station: ";
            cin >> dest;
            delhiMetro.shortestPath(src, dest);
        } else if (choice == 4) {
            cout << "\n Thank you for using Delhi Metro Navigator!\n";
            break;
        } else {
            cout << "\n Invalid Choice! Try again.\n";
        }
    }

    return 0;
}
