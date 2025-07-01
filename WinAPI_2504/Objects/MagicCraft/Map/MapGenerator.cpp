#include "Framework.h"
#include "MapGenerator.h"


MapGenerator::MapGenerator(int width, int height, int roomCount)
    : width(width), height(height), roomCount(roomCount),
    map(height, std::vector<int>(width, WALL)),
    room_id_map(height, std::vector<int>(width, -1)),
    rng(static_cast<unsigned int>(time(0))),
    room_connections() {
}


void MapGenerator::generate() {
    placeRoomsRadially();
    for (size_t i = 0; i < rooms.size(); ++i) {
        generateRoomInterior(rooms[i], i);
    }
}

bool MapGenerator::isOverlap(const Room& a, const Room& b) {
    return !(a.x + a.w <= b.x || b.x + b.w <= a.x ||
        a.y + a.h <= b.y || b.y + b.h <= a.y);
}

// �� ������ ��ġ�� ���� ��ȯ
int MapGenerator::overlapLen(int a1, int a2, int b1, int b2) {
    int s = max(a1, b1);
    int e = min(a2, b2);
    return max(0, e - s + 1);
}

void MapGenerator::placeRoomsRadially() {
    uniform_int_distribution<int> sizeDist(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
    int centerX = width / 2;
    int centerY = height / 2;
    // ù �� �߾ӿ� ��ġ
    Room first = { centerX - ROOM_MIN_SIZE / 2, centerY - ROOM_MIN_SIZE / 2, ROOM_MIN_SIZE, ROOM_MIN_SIZE };
    rooms.push_back(first);
    carveRoom(first, 0);
    // �Ϲ� ��� ���� (���� �� ����)
    for (int i = 1; i < roomCount - 1; ++i) {
        bool placed = false;
        for (int tries = 0; tries < 200 && !placed; ++tries) {
            int baseIdx = uniform_int_distribution<int>(0, rooms.size() - 1)(rng);
            Room base = rooms[baseIdx];
            int w = sizeDist(rng);
            int h = sizeDist(rng);
            int dir = uniform_int_distribution<int>(0, 7)(rng);
            int nx = base.x, ny = base.y;
            int overlap_start, overlap_end, overlap_range;
            switch (dir) {
            case 0: // ��
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start;
                ny = base.y - h;
                break;
            case 1: // �Ʒ�
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start;
                ny = base.y + base.h;
                break;
            case 2: // ����
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x - w;
                ny = base.y + overlap_start;
                break;
            case 3: // ������
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + base.w;
                ny = base.y + overlap_start;
                break;
            case 4: // �»�
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start - w;
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_end = uniform_int_distribution<int>(0, overlap_range)(rng);
                ny = base.y + overlap_end - h;
                break;
            case 5: // ���
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start + base.w;
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_end = uniform_int_distribution<int>(0, overlap_range)(rng);
                ny = base.y + overlap_end - h;
                break;
            case 6: // ����
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start - w;
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_end = uniform_int_distribution<int>(0, overlap_range)(rng);
                ny = base.y + overlap_end + base.h;
                break;
            case 7: // ����
                overlap_range = min(base.w, w) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_start = uniform_int_distribution<int>(0, overlap_range)(rng);
                nx = base.x + overlap_start + base.w;
                overlap_range = min(base.h, h) - MIN_OVERLAP;
                if (overlap_range < 0) continue;
                overlap_end = uniform_int_distribution<int>(0, overlap_range)(rng);
                ny = base.y + overlap_end + base.h;
                break;
            }
            Room newRoom = { nx, ny, w, h };
            // �� ��� üũ
            /*
            if (newRoom.x < 1 || newRoom.y < 1 ||
                newRoom.x + newRoom.w >= width - 1 || newRoom.y + newRoom.h >= height - 1)
                continue;
           */
            if (newRoom.x < 1 + bossLayoutSizeX || newRoom.y < 1 + bossLayoutSizeY ||
                newRoom.x + newRoom.w >= width - 1 - bossLayoutSizeX || newRoom.y + newRoom.h >= height - 1 - bossLayoutSizeY)
                continue;

            // ��ħ üũ
            bool overlap = false;
            for (size_t j = 0; j < rooms.size(); ++j) {
                if (isOverlap(newRoom, rooms[j])) {
                    overlap = true;
                    break;
                }
            }
            // ���� ��ġ�� ������ 3ĭ �̻����� Ȯ��
            if (!overlap) {
                int overlapW = overlapLen(base.x, base.x + base.w - 1, newRoom.x, newRoom.x + newRoom.w - 1);
                int overlapH = overlapLen(base.y, base.y + base.h - 1, newRoom.y, newRoom.y + newRoom.h - 1);
                bool valid = false;
                if (dir == 0 || dir == 1) valid = (overlapW >= MIN_OVERLAP);
                else if (dir == 2 || dir == 3) valid = (overlapH >= MIN_OVERLAP);
                else valid = (overlapW >= MIN_OVERLAP && overlapH >= MIN_OVERLAP);
                if (!valid) continue;
                rooms.push_back(newRoom);
                carveRoom(newRoom, rooms.size() - 1);
                mergeBoundary(base, newRoom, dir);
                placed = true;
            }
        }
    }
    // ���� ����� ���� �� ���� ���� ��ġ (�� 4��)
    // 1. ������ ���� ��
    int bossW = ROOM_MAX_SIZE;
    int bossH = ROOM_MAX_SIZE;
    int rightBossX = width - bossW - 5;
    int rightBossY = height / 2 - bossH / 2;
    Room rightBossRoom = { rightBossX, rightBossY, bossW, bossH };

    // 2. ���� ���� ��
    int leftBossX = 5;
    int leftBossY = height / 2 - bossH / 2;
    Room leftBossRoom = { leftBossX, leftBossY, bossW, bossH };

    // 3. ���� ���� ��
    int topBossX = width / 2 - bossW / 2;
    int topBossY = 5;
    Room topBossRoom = { topBossX, topBossY, bossW, bossH };

    // 4. �Ʒ��� ���� ��
    int bottomBossX = width / 2 - bossW / 2;
    int bottomBossY = height - bossH - 5;
    Room bottomBossRoom = { bottomBossX, bottomBossY, bossW, bossH };

    // �� ���� ���� ���� ����� ��� ����
    vector<Room> bossRooms = { rightBossRoom, leftBossRoom, topBossRoom, bottomBossRoom };
    vector<int> closestRooms = { -1, -1, -1, -1 };

    for (size_t bossIdx = 0; bossIdx < bossRooms.size(); ++bossIdx) {
        int minDist = width * height;
        for (size_t i = 0; i < rooms.size(); ++i) {
            int dist = abs(rooms[i].cx() - bossRooms[bossIdx].cx()) + abs(rooms[i].cy() - bossRooms[bossIdx].cy());
            if (dist < minDist) {
                minDist = dist;
                closestRooms[bossIdx] = i;
            }
        }
    }

    // ���� ����� ���� ����� �� ��ó�� ��ġ
    if (closestRooms[0] != -1) { // ������ ���� ��
        Room& closest = rooms[closestRooms[0]];
        rightBossRoom.x = closest.x + closest.w;
        rightBossRoom.y = closest.y + (closest.h - bossH) / 2;
        if (rightBossRoom.x + rightBossRoom.w >= width - 1) {
            rightBossRoom.x = width - rightBossRoom.w - 1;
        }
    }

    if (closestRooms[1] != -1) { // ���� ���� ��
        Room& closest = rooms[closestRooms[1]];
        leftBossRoom.x = closest.x - bossW;
        leftBossRoom.y = closest.y + (closest.h - bossH) / 2;
        if (leftBossRoom.x < 1) {
            leftBossRoom.x = 1;
        }
    }

    if (closestRooms[2] != -1) { // ���� ���� ��
        Room& closest = rooms[closestRooms[2]];
        topBossRoom.x = closest.x + (closest.w - bossW) / 2;
        topBossRoom.y = closest.y - bossH;
        if (topBossRoom.y < 1) {
            topBossRoom.y = 1;
        }
    }

    if (closestRooms[3] != -1) { // �Ʒ��� ���� ��
        Room& closest = rooms[closestRooms[3]];
        bottomBossRoom.x = closest.x + (closest.w - bossW) / 2;
        bottomBossRoom.y = closest.y + closest.h;
        if (bottomBossRoom.y + bottomBossRoom.h >= height - 1) {
            bottomBossRoom.y = height - bottomBossRoom.h - 1;
        }
    }

    // ���� ����� �߰��ϰ� ����
    rooms.push_back(rightBossRoom);
    carveRoom(rightBossRoom, rooms.size() - 1);
    if (closestRooms[0] != -1) {
        mergeBoundary(rooms[closestRooms[0]], rightBossRoom, 3); // ������ ����
    }

    rooms.push_back(leftBossRoom);
    carveRoom(leftBossRoom, rooms.size() - 1);
    if (closestRooms[1] != -1) {
        mergeBoundary(rooms[closestRooms[1]], leftBossRoom, 2); // ���� ����
    }

    rooms.push_back(topBossRoom);
    carveRoom(topBossRoom, rooms.size() - 1);
    if (closestRooms[2] != -1) {
        mergeBoundary(rooms[closestRooms[2]], topBossRoom, 0); // ���� ����
    }

    rooms.push_back(bottomBossRoom);
    carveRoom(bottomBossRoom, rooms.size() - 1);
    if (closestRooms[3] != -1) {
        mergeBoundary(rooms[closestRooms[3]], bottomBossRoom, 1); // �Ʒ��� ����
    }
}

void MapGenerator::carveRoom(const Room& room, int room_id) {
    // map�� �ٴ��� �̸� ���� ����. room_id_map�� ���
    for (int y = room.y; y < room.y + room.h; ++y) {
        for (int x = room.x; x < room.x + room.w; ++x) {
            room_id_map[y][x] = room_id;
        }
    }
}

void MapGenerator::generateRoomInterior(Room& room, int room_id) {
    int rw = room.w, rh = room.h;
    vector<vector<int>> local(rh, vector<int>(rw, WALL));

    // ���� ���� ��� Ÿ���� �ٴ�
    if (room_id == 0) {
        for (int y = 0; y < rh; ++y)
            for (int x = 0; x < rw; ++x)
                local[y][x] = FLOOR;
    }
    // ���� ���� �̸� �غ�� ��ġ ��� (������ 4�� ��)
    else if (room_id >= rooms.size() - 4) {
        // 1. ���� ���� ���(��) ��ġ�� 7x7 �ٴ� ������Ʈ ���� (�� �а�)
        for (const auto& p : room_connections[room_id]) {
            int sx = p.first - room.x;
            int sy = p.second - room.y;
            for (int dy = -3; dy <= 3; ++dy)
                for (int dx = -3; dx <= 3; ++dx) {
                    int ny = sy + dy, nx = sx + dx;
                    if (0 <= ny && ny < rh && 0 <= nx && nx < rw)
                        local[ny][nx] = FLOOR;
                }
        }

        // 2. ���� ���� ��� �����ڸ��� �ٴ����� ����� ���� ����
        for (int y = 0; y < rh; ++y) {
            for (int x = 0; x < rw; ++x) {
                if (y == 0 || y == rh - 1 || x == 0 || x == rw - 1) {
                    local[y][x] = FLOOR;
                }
            }
        }

        // 3. ���� ���̾ƿ� ���� (���� ���� �����ڸ��� ����� ����)
        uniform_int_distribution<int> patternDist(0, bossLayouts.size() - 1);
        int selectedPattern = patternDist(rng);

        int layout_h = bossLayouts[selectedPattern].size();
        int layout_w = bossLayouts[selectedPattern][0].size();
        int start_y = (rh - layout_h) / 2;
        int start_x = (rw - layout_w) / 2;

        for (int y = 0; y < layout_h && start_y + y < rh; ++y) {
            for (int x = 0; x < layout_w && start_x + x < rw; ++x) {
                if (start_y + y >= 0 && start_x + x >= 0) {
                    // ���� ��質 �����ڸ��� �ƴ� ���� ���̾ƿ� ����
                    bool isProtectedArea = false;

                    // ���� ��� ���� üũ
                    for (const auto& p : room_connections[room_id]) {
                        int sx = p.first - room.x;
                        int sy = p.second - room.y;
                        if (abs(start_y + y - sy) <= 3 && abs(start_x + x - sx) <= 3) {
                            isProtectedArea = true;
                            break;
                        }
                    }

                    // �����ڸ� üũ
                    if (start_y + y == 0 || start_y + y == rh - 1 || start_x + x == 0 || start_x + x == rw - 1) {
                        isProtectedArea = true;
                    }

                    if (!isProtectedArea) {
                        /*
                        switch (bossLayouts[selectedPattern][y][x]) {
                        case WALL:


                        }*/

                        //local[start_y + y][start_x + x] = (bossLayouts[selectedPattern][y][x] == 1) ? FLOOR : WALL;
                        local[start_y + y][start_x + x] = bossLayouts[selectedPattern][y][x];
                    }
                }
            }
        }

        // 4. ���� ��踦 �ٽ� ���� (���� Ȯ��, �� �а�)
        for (const auto& p : room_connections[room_id]) {
            int sx = p.first - room.x;
            int sy = p.second - room.y;
            for (int dy = -3; dy <= 3; ++dy)
                for (int dx = -3; dx <= 3; ++dx) {
                    int ny = sy + dy, nx = sx + dx;
                    if (0 <= ny && ny < rh && 0 <= nx && nx < rw)
                        local[ny][nx] = FLOOR;
                }
        }

        // 5. ��� �����ڸ��� �ٽ� �ٴ����� ����
        for (int y = 0; y < rh; ++y) {
            for (int x = 0; x < rw; ++x) {
                if (y == 0 || y == rh - 1 || x == 0 || x == rw - 1) {
                    local[y][x] = FLOOR;
                }
            }
        }
    }
    // �Ϲ� ���� ���� ����
    else {
        // 1. ���� ���(��) ��ġ�� 5x5 �ٴ� ������Ʈ ���� (�ֿ켱)
        for (const auto& p : room_connections[room_id]) {
            int sx = p.first - room.x;
            int sy = p.second - room.y;
            for (int dy = -2; dy <= 2; ++dy)
                for (int dx = -2; dx <= 2; ++dx) {
                    int ny = sy + dy, nx = sx + dx;
                    if (0 <= ny && ny < rh && 0 <= nx && nx < rw)
                        local[ny][nx] = FLOOR;
                }
        }

        // 2. ���귯 ���丶Ÿ ���� (���� ���� ����)
        uniform_int_distribution<int> cellDist(0, 99);
        for (int y = 0; y < rh; ++y) {
            for (int x = 0; x < rw; ++x) {
                if (local[y][x] != FLOOR) { // �̹� �ٴ��� ���� ����
                    // ���� ��� �������� Ȯ��
                    bool isConnectionArea = false;
                    for (const auto& p : room_connections[room_id]) {
                        int sx = p.first - room.x;
                        int sy = p.second - room.y;
                        if (abs(y - sy) <= 2 && abs(x - sx) <= 2) {
                            isConnectionArea = true;
                            break;
                        }
                    }
                    if (!isConnectionArea) {
                        local[y][x] = (cellDist(rng) < 45) ? FLOOR : WATER;
                    }
                }
            }
        }

        vector<vector<int>> next = local;
        for (int y = 1; y < rh - 1; ++y) {
            for (int x = 1; x < rw - 1; ++x) {
                // ���� ��� ������ ���귯 ���丶Ÿ���� ����
                bool isConnectionArea = false;
                for (const auto& p : room_connections[room_id]) {
                    int sx = p.first - room.x;
                    int sy = p.second - room.y;
                    if (abs(y - sy) <= 2 && abs(x - sx) <= 2) {
                        isConnectionArea = true;
                        break;
                    }
                }

                if (!isConnectionArea) {
                    int cnt = 0;
                    for (int dy = -1; dy <= 1; ++dy)
                        for (int dx = -1; dx <= 1; ++dx)
                            if (local[y + dy][x + dx] == FLOOR) ++cnt;
                    if (cnt >= 5) next[y][x] = FLOOR;
                    else next[y][x] = WATER;
                }
            }
        }
        local = next;

        // 3. ��� �ٴ� ������Ʈ�� �ϳ��� ����ǵ��� �ݺ������� ���� (5x5 ��)
        int dy4[4] = { -1, 1, 0, 0 };
        int dx4[4] = { 0, 0, -1, 1 };
        while (true) {
            vector<vector<int>> comp(rh, vector<int>(rw, -1));
            int comp_id = 0;
            vector<pair<int, int>> rep;
            for (int y = 0; y < rh; ++y) {
                for (int x = 0; x < rw; ++x) {
                    if (local[y][x] == FLOOR && comp[y][x] == -1) {
                        queue<pair<int, int>> q;
                        q.push({ y, x });
                        comp[y][x] = comp_id;
                        rep.push_back({ y, x });
                        while (!q.empty()) {
                            int cy = q.front().first, cx = q.front().second; q.pop();
                            for (int d = 0; d < 4; ++d) {
                                int ny = cy + dy4[d], nx = cx + dx4[d];
                                if (0 <= ny && ny < rh && 0 <= nx && nx < rw && local[ny][nx] == FLOOR && comp[ny][nx] == -1) {
                                    comp[ny][nx] = comp_id;
                                    q.push({ ny, nx });
                                }
                            }
                        }
                        ++comp_id;
                    }
                }
            }
            if (comp_id <= 1) break;
            int min_dist = rh * rw, a = -1, b = -1;
            for (int i = 0; i < (int)rep.size(); ++i) {
                for (int j = i + 1; j < (int)rep.size(); ++j) {
                    int dist = abs(rep[i].first - rep[j].first) + abs(rep[i].second - rep[j].second);
                    if (dist < min_dist) { min_dist = dist; a = i; b = j; }
                }
            }
            vector<vector<pair<int, int>>> parent(rh, vector<pair<int, int>>(rw, { -1,-1 }));
            queue<pair<int, int>> q;
            q.push(rep[a]);
            vector<vector<bool>> visited(rh, vector<bool>(rw, false));
            visited[rep[a].first][rep[a].second] = true;
            bool reached = false;
            int ty = rep[b].first, tx = rep[b].second;
            while (!q.empty() && !reached) {
                int y = q.front().first, x = q.front().second; q.pop();
                for (int d = 0; d < 4; ++d) {
                    int ny = y + dy4[d], nx = x + dx4[d];
                    if (0 <= ny && ny < rh && 0 <= nx && nx < rw && !visited[ny][nx]) {
                        parent[ny][nx] = { y, x };
                        visited[ny][nx] = true;
                        q.push({ ny, nx });
                        if (ny == ty && nx == tx) { reached = true; break; }
                    }
                }
            }
            int py = ty, px = tx;
            int prevy = py, prevx = px;
            while (!(py == rep[a].first && px == rep[a].second)) {
                pair<int, int> pr = parent[py][px];
                prevy = pr.first; prevx = pr.second;
                int miny = min(py, prevy), maxy = max(py, prevy);
                int minx = min(px, prevx), maxx = max(px, prevx);
                for (int y = miny - 2; y <= maxy + 2; ++y)
                    for (int x = minx - 2; x <= maxx + 2; ++x)
                        if (0 <= y && y < rh && 0 <= x && x < rw)
                            local[y][x] = FLOOR;
                py = prevy; px = prevx;
            }
            for (int ddy = -2; ddy <= 2; ++ddy)
                for (int ddx = -2; ddx <= 2; ++ddx) {
                    int nny = rep[a].first + ddy, nnx = rep[a].second + ddx;
                    if (0 <= nny && nny < rh && 0 <= nnx && nnx < rw)
                        local[nny][nnx] = FLOOR;
                }
        }

        // 4. ���� ��踦 �ٽ� ���� (���� Ȯ��)
        for (const auto& p : room_connections[room_id]) {
            int sx = p.first - room.x;
            int sy = p.second - room.y;
            for (int dy = -2; dy <= 2; ++dy)
                for (int dx = -2; dx <= 2; ++dx) {
                    int ny = sy + dy, nx = sx + dx;
                    if (0 <= ny && ny < rh && 0 <= nx && nx < rw)
                        local[ny][nx] = FLOOR;
                }
        }
    }

    // �÷��̾� ������ ��ġ(���۹�)
    if (room_id == 0) {
        local[rh / 2][rw / 2] = PLAYER_SPAWN;
    }

    // ���� ������ ��ġ(�Ϲ� �游)
    if (room_id != 0 && room_id < rooms.size() - 4) {
        int enemySpawnerCount = rand() % 3 + 3;
        for (int i = 0; i < enemySpawnerCount; i++) {
            int x = rand() % rw;
            int y = rand() % rh;
            if (local[y][x] == FLOOR) {
                local[y][x] = ENEMY_SPAWN;
            }
            else i--;
        }
    }


    // �ʿ� �ݿ�
    for (int y = 0; y < rh; ++y) {
        for (int x = 0; x < rw; ++x) {
            map[room.y + y][room.x + x] = local[y][x];
            if (local[y][x] == FLOOR) room_id_map[room.y + y][room.x + x] = room_id;
        }
    }
}

void MapGenerator::mergeBoundary(const Room& a, const Room& b, int dir) {
    // a�� b�� ���� ��輱�� �ٴ����� ����
    int ax1 = a.x, ay1 = a.y, ax2 = a.x + a.w - 1, ay2 = a.y + a.h - 1;
    int bx1 = b.x, by1 = b.y, bx2 = b.x + b.w - 1, by2 = b.y + b.h - 1;
    vector<pair<int, int>> boundary_coords;
    if (dir == 0) { // ��
        int sx = max(ax1, bx1);
        int ex = min(ax2, bx2);
        int y = ay1;
        for (int x = sx; x <= ex; ++x) {
            map[y][x] = FLOOR;
            boundary_coords.push_back({ x, y });
        }
    }
    else if (dir == 1) { // �Ʒ�
        int sx = max(ax1, bx1);
        int ex = min(ax2, bx2);
        int y = ay2;
        for (int x = sx; x <= ex; ++x) {
            map[y][x] = FLOOR;
            boundary_coords.push_back({ x, y });
        }
    }
    else if (dir == 2) { // ����
        int sy = max(ay1, by1);
        int ey = min(ay2, by2);
        int x = ax1;
        for (int y = sy; y <= ey; ++y) {
            map[y][x] = FLOOR;
            boundary_coords.push_back({ x, y });
        }
    }
    else if (dir == 3) { // ������
        int sy = max(ay1, by1);
        int ey = min(ay2, by2);
        int x = ax2;
        for (int y = sy; y <= ey; ++y) {
            map[y][x] = FLOOR;
            boundary_coords.push_back({ x, y });
        }
    }
    else { // �밢��
        int sx = max(ax1, bx1);
        int ex = min(ax2, bx2);
        int sy = max(ay1, by1);
        int ey = min(ay2, by2);
        for (int y = sy; y <= ey; ++y) {
            for (int x = sx; x <= ex; ++x) {
                map[y][x] = FLOOR;
                boundary_coords.push_back({ x, y });
            }
        }
    }
    // b(�� ��)�� ���� ��� ��ǥ ����
    int b_idx = rooms.size() - 1;
    room_connections[b_idx].insert(room_connections[b_idx].end(), boundary_coords.begin(), boundary_coords.end());
}