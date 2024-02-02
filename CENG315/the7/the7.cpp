
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <utility>
#include <memory>

void addEdge(std::vector<std::vector<std::pair<int, int>>>& network, int from, int to, int weight){
    network[from].push_back(std::make_pair(to, weight));
}

/*int findMax(std::vector< std::vector<int> > adjMatrix){
    int willReturn = INT_MIN;
    for(int i = 0; i < adjMatrix.size(); i++){
        for(int j = 0; j < adjMatrix.size(); j++){
            if(adjMatrix[i][j] != INT_MAX && adjMatrix[i][j] > willReturn){ //lazy evaluation
                willReturn = adjMatrix[i][j];
            }
        }
    }
    return willReturn;
}*/
void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores){
    int graphSize = network.size();
    int maxDist = INT_MIN;

    std::vector< std::vector<int> > adjMatrix(graphSize, std::vector<int> (graphSize, INT_MAX));

    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < network[i].size(); j++){
            if(network[i][j].second > maxDist){
                maxDist = network[i][j].second;
            }
            adjMatrix[i][network[i][j].first] = network[i][j].second;
        }
    }

    for(int k = 0; k < graphSize; k++){
        for(int i = 0; i < graphSize; i++){
            for(int j = 0; j < graphSize; j++){
                if(adjMatrix[i][k] != INT_MAX && adjMatrix[k][j] != INT_MAX && adjMatrix[i][j] > adjMatrix[i][k] + adjMatrix[k][j]){ //lazy evaluation
                    if(adjMatrix[i][k] + adjMatrix[k][j] > maxDist){
                        maxDist = adjMatrix[i][k] + adjMatrix[k][j];
                    }
                    adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
                }

            }
        }
    }

    //int maxDist = findMax(adjMatrix);

    for(int i = 0; i < graphSize; i++){
        float temp = 0;
        for(int j = 0; j < graphSize; j++){
            if(i == j)
                continue;

            if(adjMatrix[i][j] == INT_MAX){
                temp += maxDist + 1;
            }
            else{
                temp += adjMatrix[i][j];
            }
        }
        infection_scores.push_back(1 / (temp / (graphSize - 1)));
    }


}


int main()
{
    int graphSize = 4;
    std::vector<std::vector<std::pair<int, int>>> network(graphSize, std::vector<std::pair<int,int> > ());
    std::vector<float> IS(0, graphSize);

    addEdge(network, 0, 1, 2);
    addEdge(network, 1, 2, 5);
    addEdge(network, 2, 3, 3);
    addEdge(network, 3, 1 ,2);
    addEdge(network, 3, 2, 7);

    get_infection_scores(network, IS);

    for(int i = 0; i < graphSize; i++){
        std::cout << i << ": " << IS[i] << " ";
    }

    return 0;
}
