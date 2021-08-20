#include <vector>
#include "utils.h"


void findmin(vector<vector<float>> dist, int& min_x, int& min_y){
    float min = FLT_MAX;
    for (int i = 0; i < num_x; ++i) {
        for (int j = 0; j < num_y; ++j) {
            if (!sptSet[i][j] && dist[i][j] < min) {
                min_x = i;
                min_y = j;
                min = dist[i][j];
            }
        }
    }
}

void dijkstra(int source_x,int source_y,int dest_x,int dest_y, vector<vector<int>> grid){
    pair<int,int> path[num_x][num_y];
    vector<vector<float>> dist;
    bool found=0;

    for (int i = 0; i < num_x; ++i) {
        vector<float> temp(num_y, FLT_MAX);
        dist.emplace_back(temp);
    }
    dist[source_x][source_y] = 0.0;
    
    for (int i = 0; i < num_x && !found; ++i) {
        for (int j = 0; j < num_y && !found; ++j) {
            int min_x = 0, min_y = 0;
            // Pick the minimum distance node from the set of coordinates not
            // yet processed.
            findmin(dist, min_x, min_y);
            sptSet[min_x][min_y] = true;
            if (sptSet[dest_x][dest_y]) {
                found = true;
                break;
            }
            sf::sleep(milliseconds(1));        //delay exploration
            vector<int> possibleX = {-1, 0, 1, -1, 1, -1, 0, 1};
            vector<int> possibleY = {-1, -1, -1, 0, 0, 1, 1, 1};

            // Update dist value of the adjacent nodes of the picked node.
            // Since a node is a cell, there are 8 adjacent cells to it.
            for(int v = 0; v < 8; ++v) {
                int newRow = min_x + possibleX[v];
                int newCol = min_y + possibleY[v];
                if (possibleX[v] != 0 && possibleY[v] != 0) {
                    if(newCol >= 0 && newRow >= 0 && newCol <= num_y && newRow <= num_x &&
                    grid[newRow][newCol] == 1 && sptSet[newRow][newCol] == false &&
                    dist[newRow][newCol] > dist[min_x][min_y] + 1.5){
                     dist[newRow][newCol] = dist[min_x][min_y] + 1.5;
                        path[newRow][newCol] = make_pair(min_x,min_y);
                    }
                } else {
                    if(newCol >= 0 && newRow >= 0 && newCol <= num_y && newRow <= num_x &&
                    grid[newRow][newCol] == 1 && sptSet[newRow][newCol] == false &&
                    dist[newRow][newCol] > dist[min_x][min_y] + 1.0){
                        dist[newRow][newCol] = dist[min_x][min_y] + 1.0;
                        path[newRow][newCol] = make_pair(min_x,min_y);
                    }
                }
            }
        }
    }
    cout << dist[dest_x][dest_y] << '\n';   
    while (path[dest_x][dest_y].first != source_x || path[dest_x][dest_y].second != source_y) {
        sf::sleep(milliseconds(10));
        cout << "Visiting x = " << path[dest_x][dest_y].first << "  " << "and y = " << path[dest_x][dest_y].second << endl;
        pathD.emplace_back(make_pair(path[dest_x][dest_y].first, path[dest_x][dest_y].second));
        int x = dest_x;
        int y = dest_y;
        dest_x = path[x][y].first;
        dest_y = path[x][y].second;
    }
}