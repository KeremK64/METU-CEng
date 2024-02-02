
#include <iostream>
#include <vector>
#include <memory>
#include <utility>

using namespace std;

int parent[100];
int color[100];
int startTime[100];
int finishTime[100];

void addEdge(std::vector<std::vector<int>>& graph, int node1, int node2){
    graph[node1][node2] = 1;
}


std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &matrix)
{
    std::vector<std::vector<int>> transposed(matrix[0].size(), std::vector<int>());

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            transposed[j].push_back(matrix[i][j]);
        }
    }
    return transposed;
}


void DFSVisit(const std::vector<std::vector<int>>& graph, int node, int& time, bool& isCompilable, std::vector<std::vector<int>>& cyclicDependencies){
    int start, finish;

    time++;
    startTime[node] = time;
    color[node] = 1;

    for(int i = graph[0].size() - 1; i >= 0 ; i--){
        if(graph[node][i] == 1 && node != i && color[i] == 0){
            //cout << i << " " << node << "\n";
            parent[i] = node;
            DFSVisit(graph, i, time,isCompilable, cyclicDependencies);
        }

        else if(graph[node][i] == 1 && node !=i && color[i] == 1) {
            std::vector<int> cycle;
            for (int v = node; v != i; v = parent[v]) {
                cycle.push_back(v);
            }
            cycle.push_back(i);
            cyclicDependencies.push_back(cycle);
            isCompilable = false;
        }

    }
    color[node] = 2;
    time++;
    finishTime[node] = time;

}



void DFS(const std::vector<std::vector<int>>& graph, bool& isCompilable, std::vector<std::vector<int>>& cyclicDependencies){

    int time = 0;

    for(int i = graph[0].size() - 1; i >= 0 ; i--){
        if(color[i] == 0){
            DFSVisit(graph, i, time, isCompilable, cyclicDependencies);
        }
    }
}


void getOrder(std::vector<int>& compileOrder, int numNodes){

    std::vector<std::pair<int,int>> order;

    for(int i = 0; i < numNodes; i++){
        order.push_back(std::make_pair(finishTime[i], i));
    }

    for (int i = 0; i < numNodes; i++) {
        std::pair<int, int> temp = order[i];
        int j = i - 1;
        while (j >= 0 && order[j].first < temp.first) {
            order[j + 1] = order[j];
            j--;
        }
        order[j + 1] = temp;
    }

    for(int i = 0; i < numNodes; i++){
        compileOrder.at(i) = order[i].second;
    }

}

void run(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable, std::vector<int>& compileOrder,
         std::vector<std::vector<int>>& cyclicDependencies){
    int numNodes = dependencyMatrix[0].size();

    DFS(dependencyMatrix, isCompilable, cyclicDependencies);

    for(int i = 0; i < numNodes; i++){
        cout << finishTime[i] << " ";
    }

    getOrder(compileOrder, numNodes);

    for(int i = 0; i < numNodes; i++){
        cout << compileOrder[i] << " ";
    }

    int time = 0;


    if(!isCompilable){
        //re-initialize the arrays.
        for(int i = 0; i < numNodes; i++){
            color[i] = 0;
            parent[i] = -1;
            startTime[i] = 0;
            finishTime[i] = 0;

        }
        //re-run the DFS algorithm with transposed graph
        std::vector<std::vector<int>> transposed = transpose(dependencyMatrix);
        for(int i = 0; i < numNodes; i++){
            if(color[compileOrder[i]] == 0){
                DFSVisit(transposed, compileOrder[i], time, isCompilable, cyclicDependencies);
            }
        }

        std::vector<bool> visited(numNodes, 0);
        for (int i = 0; i < numNodes; i++) {
            int temp = compileOrder[i];
            std::vector<int> currentCycle;

            if(visited[temp]){
                continue;
            }

            while (parent[temp] != -1){
                visited[temp] = 1;
                currentCycle.push_back(temp);
                temp = parent[temp];
            }


            if (!currentCycle.empty()) {
                currentCycle.push_back(temp);
                cyclicDependencies.push_back(currentCycle);
            }
        }
    }
    for(int i = 0; i < numNodes; i++){
        cout << parent[i] << " ";
    }

}




int main()
{
    std::vector<std::vector<int>> graph(6, std::vector<int>(6, 0));
    std::vector<int> order(graph[0].size(), 0);
    std::vector<std::vector<int>> cyclicDependencies;

    bool isCompilable = true;
    addEdge(graph, 0,1);
    addEdge(graph, 0,2);
    addEdge(graph, 1,1);
    addEdge(graph, 2,3);
    addEdge(graph, 3,0);
    addEdge(graph, 4,3);
    addEdge(graph, 5,5);

    run(graph, isCompilable, order, cyclicDependencies);

    for(int i = 0; i < order.size(); i++){
        cout << order[i] << " ";
    }

    for(int i = 0; i < cyclicDependencies.size(); i++){
        cout << "\n";
        for(int j = 0; j < cyclicDependencies[i].size(); j++)
            cout << cyclicDependencies[i][j] << " ";
    }


    return 0;


}
