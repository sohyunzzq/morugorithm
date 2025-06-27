#define SZ 100'001

struct Node {
    int id;
    int ver;
    Node* next;

    Node() {}
    Node(int id, int ver) : id(id), ver(ver), next(nullptr) {}
    Node(int id, int ver, Node* next) : id(id), ver(ver), next(next) {}
}nodes[SZ * 2];

int cnt;
int num[SZ];
int version[SZ];

Node* MakeNode(int id, Node* next = nullptr) {
    Node* temp = &nodes[cnt++];
    temp->id = id;
    temp->ver = ++version[id];
    temp->next = next;

    return temp;
}

struct Team {
    Node* head[6];
    Node* tail[6];
}teams[6];

void init()
{
    cnt = 0;

    for (int i = 0; i < SZ; i++) {
        num[i] = 0;
        version[i] = 0;
    }

    for (int t = 1; t <= 5; t++) {
        for (int sc = 1; sc <= 5; sc++) {
            // 더미노드
            teams[t].head[sc] = teams[t].tail[sc] = MakeNode(0);
        }
    }
}

void hire(int mID, int mTeam, int mScore)
{
    Node* temp = MakeNode(mID);
    teams[mTeam].tail[mScore]->next = temp;
    teams[mTeam].tail[mScore] = temp;
    num[mID] = mTeam;
}

void fire(int mID)
{
    version[mID] = -1;
}

void updateSoldier(int mID, int mScore)
{
    hire(mID, num[mID], mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore < 0) {
        for (int i = 1; i <= 5; i++) {
            // i점인 병사 한 명도 없음
            if (teams[mTeam].head[i]->next == nullptr)
                continue;

            int result = i + mChangeScore;

            if (result < 1)
                result = 1;

            // 안 바뀌어도 됨 (1점 -> 1점)
            if (i == result)
                continue;

            // i점이 result점으로
            // result점 tail -> i점 head
            teams[mTeam].tail[result]->next = teams[mTeam].head[i]->next;
            teams[mTeam].tail[result] = teams[mTeam].tail[i];
            
            // i점 리스트 초기화
            teams[mTeam].head[i]->next = nullptr;
            teams[mTeam].tail[i] = teams[mTeam].head[i];
        }
    }
    else if (mChangeScore > 0) {
        for (int i = 5; i >= 1; i--) {
            // i점인 병사 한 명도 없음
            if (teams[mTeam].head[i]->next == nullptr)
                continue;

            int result = i + mChangeScore;

            if (result > 5)
                result = 5;

            // 안 바뀌어도 됨 (1점 -> 1점)
            if (i == result)
                continue;

            // i점이 result점으로
            // result점 tail -> i점 head
            teams[mTeam].tail[result]->next = teams[mTeam].head[i]->next;
            teams[mTeam].tail[result] = teams[mTeam].tail[i];

            // i점 리스트 초기화
            teams[mTeam].head[i]->next = nullptr;
            teams[mTeam].tail[i] = teams[mTeam].head[i];
        }
    }
}

int bestSoldier(int mTeam)
{
    int ans = 0;

    for (int i = 5; i >= 1; i--) {
        Node* cur = teams[mTeam].head[i]->next;

        // i점 없음
        if (cur == nullptr)
            continue;

        while (cur) {
            if (cur->ver == version[cur->id]) {
                if (ans < cur->id)
                    ans = cur->id;
            }
            cur = cur->next;
        }

        // i점에서 병사 나옴
        if (ans != 0)
            return ans;
    }
    return 0;
}
