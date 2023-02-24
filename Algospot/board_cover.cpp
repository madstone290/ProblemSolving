/*
문제: https://algospot.com/judge/problem/read/BOARDCOVER
전략:
    * 완전 탐
    * 흰칸이 3의 배수인지 확인
    * 모든 흰칸에 대해 L자 블록 4가지 배치를 적용
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_map(vector<vector<int>> &map)
{
    cout << "------" << endl;
    for (auto row : map)
    {
        for (auto cell : row)
        {
            cout << cell;
        }
        cout << endl;
    }
    cout << "------" << endl;
}

/// @brief 지도를 채울수 있는 모든 방법의 수를 구한다.
/// @param map 지도
/// @return 방법의 수
int cover(vector<vector<int>> &map);

/// @brief 지도를 채울수 있는 모든 방법의 수를 재귀적으로 구한다.
/// @param map 지도
/// @return 방법의 수
int cover_recursive(vector<vector<int>> &map);

bool put(vector<vector<int>> &map, int y, int x, int type);
bool unput(vector<vector<int>> &map, int y, int x, int type);

/// @brief 지도의 한 지점에 블록을 놓는다.
/// @param map 블록 상태를 보관할 지도
/// @param y 블록 위치 y
/// @param x 블록 위치 x
/// @param type 블록 배치 유형. 0~3중 하나
/// @param delta 블록 설정, 해제 여부. 놓는 경우:1 or 치우는 경우:-1
/// @return 블록배치시 배치성공 여부. 배치해제인 경우 항상 성공.
bool put_internal(vector<vector<int>> &map, int y, int x, int type, int delta);

/// @brief 블록 배치유형별 위치.
/// *   **  **   *
/// **  *    *  **
int block_layout_pos[4][3][2] = {
    {{0, 0},
     {1, 0},
     {1, 1}},
    {{0, 0},
     {0, 1},
     {1, 0}},
    {{0, 0},
     {0, 1},
     {1, 1}},
    {{0, 0},
     {1, 0},
     {1, -1}}};

int main()
{
    int C = 0;    // 테스트 케이스
    int H, W = 0; // 높이,너비

    // input handling
    cin >> C;

    // 지도 0인경우 화이트, 1이면 블랙
    vector<vector<vector<int>>> maps(C);
    for (int i = 0; i < C; i++)
    {
        cin >> H;
        cin >> W;
        maps[i] = vector<vector<int>>(H, vector<int>(W));
        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                char c;
                cin >> c;
                maps[i][y][x] = c == '.' ? 0 : 1;
            }
        }
    }

    for (auto map : maps)
    {
        int total = cover(map);
        cout << total << endl;
    }
}

int cover(vector<vector<int>> &map)
{
    int total_white = 0;
    for (auto row : map)
    {
        total_white += count(row.begin(), row.end(), 0);
    }
    if (total_white % 3 != 0)
        return 0;

    return cover_recursive(map);
}

int cover_recursive(vector<vector<int>> &map)
{
    // 흰칸 탐색
    int y, x;
    bool found = false;
    for (y = 0; y < map.size(); y++)
    {
        for (x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == 0)
            {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    // 모든 칸이 다 채워져 흰칸이 없는 경우 케이스 1증가
    if (!found)
        return 1;

    int total = 0;
    for (int type = 0; type < 4; ++type)
    {
        bool success = put(map, y, x, type);
        if (success)
        {
            total += cover(map);
        }
        unput(map, y, x, type);
    }
    return total;
}

bool put(vector<vector<int>> &map, int y, int x, int type)
{
    return put_internal(map, y, x, type, 1);
}

bool unput(vector<vector<int>> &map, int y, int x, int type)
{
    return put_internal(map, y, x, type, -1);
}

bool put_internal(vector<vector<int>> &map, int y, int x, int type, int delta)
{
    auto block_pos = block_layout_pos[type];
    bool success = true;
    for (int i = 0; i < 3; i++)
    {
        int ny = y + (*(block_pos + i))[0];
        int nx = x + (*(block_pos + i))[1];
        if (map.size() <= ny || map[0].size() <= nx)
        {
            success = false;
            continue;
        }

        map[ny][nx] += delta;

        // 검은색이거나 다른 블록이 위치한 경우
        if (1 < map[ny][nx])
            success = false;
    }
    return success;
}
