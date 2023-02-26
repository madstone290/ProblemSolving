/*
문제: https://www.algospot.com/judge/problem/read/TSP1#
전략:
    - 완전 탐색
    - N, N-1,..., 1개의 경로에 대한 최소값을 재귀적으로 계산
문제점:
    - 전체 도시를 순환하는 것이 아니라 각 도시를 한번만 방문(순환X)
    - 시작 도시를 바꾸어 가며 비교
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define INF 987654321

/// @brief 주어진 도시에 대해 1번씩 순회할 때의 최소 거리를 계산한다.
/// @param distance_mat 거리 행렬
/// @return 최소 거리
double calcShortestPath(vector<vector<double>> &distance_mat);

/// @brief 주어진 도시에 대해 1번씩 순회할 때의 최소 거리를 계산한다.
/// @param distance_mat 거리 행렬
/// @param path 방문 경로
/// @param visited 도시 방문여부
/// @param current_distance 현재까지의 거리
/// @return 최소 거리
double calcShortestPath_internal(vector<vector<double>> &distance_mat, vector<int> &path, vector<int> &visited, double current_distance);

int main()
{
    int C = 0; // 테스트 케이스

    // input handling
    cin >> C;
    vector<vector<vector<double>>> all_cases_distance(C);
    for (int test_case = 0; test_case < C; ++test_case)
    {
        int N = 0;
        cin >> N;

        all_cases_distance[test_case] = vector<vector<double>>(N, vector<double>(N));
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> all_cases_distance[test_case][i][j];
            }
        }
    }

    for (int test_case = 0; test_case < C; ++test_case)
    {
        double distance = calcShortestPath(all_cases_distance[test_case]);
        cout << fixed << setprecision(10) << distance << endl;
    }
}

double calcShortestPath(vector<vector<double>> &distance_mat)
{
    // 모든 도시를 순회하므로 시작위치는 관계 없다.
    // 편의상 첫번째(index:0) 도시부터 순회한다.

    int city_count = distance_mat.size();
    vector<int> visited(city_count);
    vector<int> path;

    double distance = INF;
    for(int city = 0 ; city< city_count ; ++city){
        path.push_back(city);
        visited[city] = true;

        double candidate = calcShortestPath_internal(distance_mat, path, visited, 0);
        if(candidate < distance)
            distance = candidate;
        
        path.pop_back();
        visited[city] = false;
    }

    return distance;
}

double calcShortestPath_internal(vector<vector<double>> &distance_mat, vector<int> &path, vector<int> &visited, double current_distance)
{
    int city_count = visited.size();

    // 다 방문한 경우 종료
    if (path.size() == city_count)
        return current_distance;

    double distance = INF;

    // 다음 방문할 도시 선택
    for (int next_city = 0; next_city < city_count; ++next_city)
    {
        if (visited[next_city])
            continue;

        int current_city = path.back();

        path.push_back( next_city);
        visited[next_city] = true;

        double distance_to_next = distance_mat[current_city][next_city];
        double candidate = calcShortestPath_internal(distance_mat, path, visited, current_distance + distance_to_next);
        if (candidate < distance)
            distance = candidate;

        path.pop_back();
        visited[next_city] = false;
    }
    return distance;
}
