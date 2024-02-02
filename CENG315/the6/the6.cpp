
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>


void addEdge(std::vector < std::vector <std::pair<int, int> > >& adj, int u,
             int v, int wt)
{
    adj[u].push_back(std::make_pair(v, wt));
    adj[v].push_back(std::make_pair(u, wt));
}

int MST(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure){
    std::vector<int> key(bond_energies.size(), INT_MAX);
    std::vector<int> parent(bond_energies.size(), -1);

    std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>> , std::greater<std::pair<int, int>> > pq;

    std::vector<bool> isVisited(bond_energies.size(), false);

    pq.push(std::make_pair(0,0)); // Starting node is 0th, randomly chosen
    key[0] = 0;

    while(!pq.empty()){
        int temp = pq.top().second;
        pq.pop();

        if(isVisited[temp]){
            continue;
        }

        if(parent[temp] != -1){
            lowest_energy_structure[temp].push_back(std::make_pair(parent[temp], key[temp]));
            lowest_energy_structure[parent[temp]].push_back(std::make_pair(temp, key[temp]));
        }

        isVisited[temp] = true;

        for(auto pair : bond_energies[temp]){

            int node = pair.first;
            int weight = pair.second;

            if(!isVisited[node] && key[node] > weight){
                key[node] = weight;
                pq.push(std::make_pair(key[node], node));
                parent[node] = temp;
                parent[temp] = node;
            }
        }
    }


    int energy = 0;

    for(int i = 0; i < key.size(); i++){
        energy += key[i];
    }

    return energy;

}

int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) {
    //Implement Minimum spanning tree. While obtainging MST, construct the structure and then find energy from keys.
    int lowest_total_energy = 0;
    lowest_total_energy = MST(bond_energies, lowest_energy_structure);

    return lowest_total_energy;
}

std::pair<int,int> getBFS(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, int root, std::vector<int>& parent){
    std::vector<int> color(molecule_structure.size(), 0); // 0 white, 1 gray, 2 black
    std::vector<int> distance(molecule_structure.size(), INT_MAX);

    color[root] = 1;
    distance[root] = 0;

    std::queue<int> queue;

    queue.push(root);

    std::vector<bool> isParent(molecule_structure.size(), false);

    while(!queue.empty()){
        int temp = queue.front();
        queue.pop();
        for(auto x : molecule_structure[temp]){
            if(color[x.first] == 0){
                color[x.first] = 1;
                distance[x.first] = distance[temp] + 1;
                parent[x.first] = temp;
                //parent[temp] = x.first;
                queue.push(x.first);
            }
            isParent[temp] = true;
            color[temp] = 2;
        }
    }

    int dist = 0;
    int node;

    for(int i = 0; i < molecule_structure.size(); i++){
        if(distance[i] >= dist){
            dist = distance[i];
            node = i;
        }
    }

    return std::make_pair(node , dist);
}


int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain){
    // Apply two BFS's. First one to find endpoint of path. According to that node, find the chain structure by applying BFS second time. Increment size while iterating.

    int longest_chain_size = 0;
    std::pair<int, int> maxPair;
    std::pair<int,int> otherMaxPair;
    std::vector<int> parent(molecule_structure.size(), -1);

    maxPair = getBFS(molecule_structure, 0, parent);
    parent.clear();
    parent.resize(molecule_structure.size(), -1);
    otherMaxPair = getBFS(molecule_structure, maxPair.first, parent);

    int node = otherMaxPair.first;

    while(parent[node] != -1){
        chain.push_back(node);
        node = parent[node];
        longest_chain_size++;
    }

    chain.push_back(node);
    longest_chain_size++;

    int start = 0;
    int end = chain.size() - 1;

    while (start < end)
    {
        int temp = chain[start];
        chain[start] = chain[end];
        chain[end] = temp;
        start++;
        end--;
    }

    return longest_chain_size;
}

int main()
{
    std::vector< std::vector <std::pair<int, int> > > adj(5, std::vector<std::pair<int,int> > ());
    std::vector< std::vector<std::pair<int,int> > > lowest_energy_structure(5, std::vector<std::pair<int,int> > ());
    std::vector<int> chain;

    addEdge(adj , 0 , 1 , 6);
    addEdge(adj , 0 , 3 , 9);
    addEdge(adj , 0 , 4 , 4);
    addEdge(adj , 1 , 2 , 3);
    addEdge(adj , 1 , 3 , 7);
    addEdge(adj , 2 , 3 , 2);
    addEdge(adj , 2 , 4 , 1);
    addEdge(adj , 3 , 4 , 12);

    int a = find_structure(adj, lowest_energy_structure);

    std::cout << a << "\n";

    for(int i = 0; i < lowest_energy_structure.size(); i++){
        for(int j = 0; j < lowest_energy_structure[i].size(); j++){
            std::cout <<  i << ": "<< lowest_energy_structure[i][j].first << " " << lowest_energy_structure[i][j].second << "| ";
        }
    }

    int b = find_longest_chain(lowest_energy_structure, chain);

    std::cout << "\n" << b << "\n";

    for(int i = 0; i < chain.size(); i++){
        std::cout << chain[i] << " ";
    }
}
