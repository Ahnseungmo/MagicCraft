#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAP_WIDTH 50
#define MAP_HEIGHT 50

// 방 구조체 정의
struct Room {
    int x, y, width, height;

    // 방의 중심 좌표
    int centerX() const { return x + width / 2; }
    int centerY() const { return y + height / 2; }
};

// 방 템플릿을 정의
enum RoomType { NORMAL, BOSS, SHOP, PUZZLE };

// 방을 랜덤으로 생성
Room generateRandomRoom(int maxWidth, int maxHeight, int minSize, int maxSize, RoomType type) {
    Room room;
    room.width = rand() % (maxSize - minSize + 1) + minSize;
    room.height = rand() % (maxSize - minSize + 1) + minSize;
    room.x = rand() % (maxWidth - room.width);
    room.y = rand() % (maxHeight - room.height);

    // 방 타입에 따른 추가 설정 (예: 보스 방은 중앙에 보스 위치 설정)
    if (type == BOSS) {
        // 보스 방의 경우, 보스 위치는 중앙에 둔다.
        room.width += 5;
        room.height += 5;
    }

    return room;
}

// 방들을 연결하는 함수
std::vector<std::pair<Room, Room>> createConnections(const std::vector<Room>& rooms) {
    std::vector<std::pair<Room, Room>> connections;

    // 방들 간의 연결 생성 (간단히 직선 연결)
    for (size_t i = 0; i < rooms.size(); ++i) {
        for (size_t j = i + 1; j < rooms.size(); ++j) {
            connections.push_back({ rooms[i], rooms[j] });
        }
    }

    return connections;
}

// 타일맵을 출력하는 함수
void printMap(const std::vector<Room>& rooms, const std::vector<std::pair<Room, Room>>& connections, char emptyTile = '.', char roomTile = '#', char pathTile = '*') {
    std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, emptyTile));

    // 각 방을 타일맵에 표시
    for (const auto& room : rooms) {
        for (int i = room.y; i < room.y + room.height; ++i) {
            for (int j = room.x; j < room.x + room.width; ++j) {
                if (i >= 0 && i < MAP_HEIGHT && j >= 0 && j < MAP_WIDTH) {
                    map[i][j] = roomTile; // 방을 #으로 표시
                }
            }
        }
    }
    /*
    // 방 간의 연결 경로를 표시
    for (const auto& connection : connections) {
        int x1 = connection.first.centerX();
        int y1 = connection.first.centerY();
        int x2 = connection.second.centerX();
        int y2 = connection.second.centerY();

        // 직선 경로 생성 (Bresenham's line algorithm)
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (x1 >= 0 && x1 < MAP_WIDTH && y1 >= 0 && y1 < MAP_HEIGHT)
                map[y1][x1] = pathTile;

            if (x1 == x2 && y1 == y2) break;
            int e2 = err * 2;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
    */
    // 타일맵 출력
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // 난수 시드 초기화

    int numRooms = 10;        // 방의 개수
    int maxWidth = MAP_WIDTH;  // 맵의 가로 크기
    int maxHeight = MAP_HEIGHT; // 맵의 세로 크기
    int minSize = 5;          // 방 최소 크기
    int maxSize = 10;         // 방 최대 크기

    // 방 생성
    std::vector<Room> rooms;
    for (int i = 0; i < numRooms; ++i) {
        RoomType type = static_cast<RoomType>(rand() % 4);  // 방 타입 랜덤
        rooms.push_back(generateRandomRoom(maxWidth, maxHeight, minSize, maxSize, type));
    }

    // 방들 간의 연결 생성
    std::vector<std::pair<Room, Room>> connections = createConnections(rooms);

    // 타일맵 출력
    printMap(rooms, connections);

    return 0;
}
