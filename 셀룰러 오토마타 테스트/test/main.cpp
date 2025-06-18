#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <map>
#include <utility>
#include <windows.h>
using namespace std;

const char WALL = '#';
const char FLOOR = '.';
const char START = 'S';
const char END = 'E';


typedef vector<vector<char>> Map;

int countWallNeighbors(const Map& map, int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if (dx == 0 && dy == 0) continue;

            if (ny < 0 || ny >= map.size() || nx < 0 || nx >= map[0].size())
                count++; // 바깥은 벽으로 간주
            else if (map[ny][nx] == WALL)
                count++;
        }
    }
    return count;
}

Map generateCave(int width, int height, float fillProb = 0.45f, int steps = 5, int birthLimit = 4, int deathLimit = 3) {
    srand(time(nullptr));
    Map map(height, vector<char>(width, WALL));

    // 초기 랜덤 생성
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = (float(rand()) / RAND_MAX < fillProb) ? WALL : FLOOR;
        }
    }

    // 진화
    for (int s = 0; s < steps; s++) {
        Map newMap = map;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int wallCount = countWallNeighbors(map, x, y);

                if (map[y][x] == WALL) {
                    newMap[y][x] = (wallCount >= deathLimit) ? WALL : FLOOR;
                }
                else {
                    newMap[y][x] = (wallCount >= birthLimit) ? WALL : FLOOR;
                }
            }
        }

        map = newMap;
    }

    return map;
}


struct Region {
    int id;
    int size;
    vector<POINT> tiles;
};

vector<Region> floodFillRegions(Map& map) {
    int width = map[0].size();
    int height = map.size();

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<Region> regions;
    int regionId = 1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == FLOOR && !visited[y][x]) {
                Region region;
                region.id = regionId++;
                region.size = 0;

                queue<POINT> q;
                q.push({ x, y });
                visited[y][x] = true;

                while (!q.empty()) {
                    POINT p = q.front(); q.pop();
                    region.tiles.push_back(p);
                    region.size++;

                    // 4방향 탐색
                    std::vector<POINT> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

                    for (auto dir : directions) {
                        int nx = p.x + dir.x;
                        int ny = p.y + dir.y;

                        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                            !visited[ny][nx] && map[ny][nx] == FLOOR) {
                            visited[ny][nx] = true;
                            q.push({ nx, ny });
                        }
                    }
                }

                regions.push_back(region);
            }
        }
    }

    return regions;
}
void keepLargestRegionOnly(Map& map) {
    auto regions = floodFillRegions(map);

    if (regions.empty()) return;

    // 가장 큰 영역 찾기
    auto largest = *max_element(regions.begin(), regions.end(),
        [](const Region& a, const Region& b) {
            return a.size < b.size;
        });

    // 나머지 영역은 모두 벽으로 변경
    for (const auto& region : regions) {
        if (region.id != largest.id) {
            for (const auto& p : region.tiles) {
                map[p.y][p.x] = WALL;
            }
        }
    }
}


void printMap(const Map& map) {
    for (const auto& row : map) {
        for (char c : row) cout << c;
        cout << '\n';
    }
}

int main() {
    int width = 100;
    int height = 80;

    Map cave = generateCave(width, height, 0.3f, 5, 4, 3);

    keepLargestRegionOnly(cave); // ✨ 연결된 하나의 던전만 남기기

    printMap(cave);

    return 0;
}