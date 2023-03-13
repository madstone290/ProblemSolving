/*
문제: https://www.algospot.com/judge/problem/read/CLOCKSYNC
전략:
    - 완전 탐색
    - 각 스위치를 1,2,3번 눌러가면서 12시로 돌릴수 있는지 확인한다.
    - 스위치 1번부터 10번까지 재귀적으로 호출한다.
문제점:

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 100000
#define SWITCH_COUNT 10
#define CLOCK_COUNT 16

/// @brief 스위치와 시계의 연결 여부. y: 스위치, x: 시계
int is_linked[10][16] = {
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}};

/// @brief 시계를 12시로 맞춘다. 맞추기 위해 눌러야하는 스위치의 터치수를 반환한다. 불가능한 경우 -1을 반환한다.
/// @param clocks 시계정보
/// @return 12시로 맞추기 위한 스위치 최소 터치수
int sync_clock(vector<int> &clocks);

/// @brief 시계를 12시로 맞춘다. 맞추기 위해 눌러야하는 스위치의 터치수를 반환한다. 불가능한 경우 -1을 반환한다.
/// @param clock 시계정보
/// @param switch_num 스위치 번호
/// @return 12시로 맞추기 위한 스위치 최소 터치수
int sync_clock_internal(vector<int> &clock, int switch_num);

/// @brief 스위치를 누른다
/// @param clock 시계정보
/// @param switch_num 스위치 번호
void push_switch(vector<int> &clock, int switch_num);

int main()
{
    int C = 0; // 테스트 케이스

    // input handling
    cin >> C;

    vector<vector<int>> clocks_list(C, vector<int>());
    for (int test_case = 0; test_case < C; test_case++)
    {
        for (int clock = 0; clock < CLOCK_COUNT; clock++)
        {
            int direction = 0;
            cin >> direction;
            clocks_list[test_case].push_back(direction);
        }
    }

    for (int test_case = 0; test_case < C; test_case++)
    {
        auto result = sync_clock(clocks_list[test_case]);
        int answer = INF <= result ? -1 : result;
        cout << answer << endl;
    }
}

int sync_clock(vector<int> &clocks)
{
    return sync_clock_internal(clocks, 0);
}

bool all_synced(vector<int> &clocks){
    // c++20만 된다...
    // return all_of(clocks.begin(), clocks.end(), [](int direction)
    //                                { return direction == 12; });
    for(auto direction : clocks){
        if(direction != 12)
            return false;
    }
    return true;
}

int sync_clock_internal(vector<int> &clocks, int switch_num)
{

    // bool clock_synced = areAligned(clocks);
    // 시계가 맞춰졌고 마지막 스위치까지 확인한 경우
    if (switch_num == SWITCH_COUNT)
    {
        bool clock_synced = all_synced(clocks);
        return clock_synced ? 0 : INF;
    }

    int total_click_count = INF;
    for (int click_count = 0; click_count < 4; click_count++)
    {
        // 현재 스위치를 0,1,2,3회 눌러가면서 전체 클릭횟수를 확인한다.
        int temp_click_count = sync_clock_internal(clocks, switch_num + 1);
        total_click_count = std::min(temp_click_count + click_count, total_click_count);
        push_switch(clocks, switch_num); // 4번 누르면 원 상태로 돌아간다.
    }
    return total_click_count;
}

void push_switch(vector<int> &clocks, int switch_num)
{
    for (int clock_num = 0; clock_num < CLOCK_COUNT; clock_num++)
    {
        if (is_linked[switch_num][clock_num] == 1)
            clocks[clock_num] += 3;

        if (12 < clocks[clock_num])
            clocks[clock_num] %= 12;
    }
}
