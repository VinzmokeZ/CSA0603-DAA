#include <stdio.h>
#include <limits.h>

#define N 100  
#define INF INT_MAX

typedef struct {
    int dest, cost, time;
} Edge;

typedef struct {
    Edge edges[N];
    int size;
} AdjList;

AdjList graph[N];
int dp[N][N];  

void addEdge(int src, int dest, int cost, int time) {
    graph[src].edges[graph[src].size].dest = dest;
    graph[src].edges[graph[src].size].cost = cost;
    graph[src].edges[graph[src].size].time = time;
    graph[src].size++;
}

int minCost(int src, int dest, int maxTime, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= maxTime; j++) {
            dp[i][j] = INF;
        }
    }
    dp[src][0] = 0;
    
    for (int time = 0; time <= maxTime; time++) {
        for (int node = 0; node < n; node++) {
            if (dp[node][time] == INF) continue;
            
            for (int i = 0; i < graph[node].size; i++) {
                Edge e = graph[node].edges[i];
                int newTime = time + e.time;
                if (newTime <= maxTime) {
                    dp[e.dest][newTime] = dp[node][time] + e.cost < dp[e.dest][newTime] ? dp[node][time] + e.cost : dp[e.dest][newTime];
                }
            }
        }
    }
    
    int result = INF;
    for (int time = 0; time <= maxTime; time++) {
        result = result < dp[dest][time] ? result : dp[dest][time];
    }
    return result == INF ? -1 : result;
}

int main() {
    int n, m, src, dest, maxTime;
    
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &m);
    
    printf("Enter source, destination, and maximum time: ");
    scanf("%d %d %d", &src, &dest, &maxTime);
    
    for (int i = 0; i < m; i++) {
        int u, v, cost, time;
        printf("Enter edge (u, v, cost, time): ");
        scanf("%d %d %d %d", &u, &v, &cost, &time);
        addEdge(u, v, cost, time);
    }
    
    int result = minCost(src, dest, maxTime, n);
    
    if (result != -1)
        printf("Minimum cost to reach destination: %d\n", result);
    else
        printf("No path found within the given time.\n");
    
    return 0;
}

