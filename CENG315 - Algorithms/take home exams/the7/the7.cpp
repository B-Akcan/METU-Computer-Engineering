#include "the7.h"

// do not add extra libraries here

std::vector<std::vector<int>> floyd_warshall(const std::vector<std::vector<std::pair<int, int>>> &network) {
    int N = network.size();
    std::vector<std::vector<int>> dist(N, std::vector<int>(N, INT32_MAX));

    for (int i = 0; i < N; ++i) {
        for (const auto &neighbor : network[i]) {
            int j = neighbor.first;
            int weight = neighbor.second;
            dist[i][j] = weight;
        }
    }

    for (int i = 0; i < N; ++i) {
        dist[i][i] = 0;
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][k] != INT32_MAX &&
                    dist[k][j] != INT32_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

int find_maximum_distance(const std::vector<std::vector<int>> &distances) {
    int max_distance = INT32_MIN;
    for (const auto &row : distances) {
        for (int distance : row) {
            if (distance != INT32_MAX && distance > max_distance) {
                max_distance = distance;
            }
        }
    }
    return max_distance;
}

void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores){
                              
    int N = network.size();

    if (N > 1) {
        std::vector<std::vector<int>> all_pairs_shortest_paths = floyd_warshall(network);
        int maxDist = find_maximum_distance(all_pairs_shortest_paths);
        
        for (int i = 0; i < N; ++i) {
            long double AIS = 0.0;
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    if (all_pairs_shortest_paths[i][j] != INT32_MAX)
                        AIS += all_pairs_shortest_paths[i][j];
                    else
                        AIS += maxDist + 1.0;
                }
            }
    
            AIS /= N-1;
            long double IS = 1.0 / AIS;
            infection_scores.push_back(IS);
        }
    }
}
