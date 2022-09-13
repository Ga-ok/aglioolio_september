#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ���� 19238 - ��ŸƮ �ý�
// bfs
// ��� 3

// bfs1() : ���� ���� ����� ����� ã��
// bfs2() : ���������� �̵�
// ������� ��ĥ �� ��� �������� ��ĥ �� ����
// -> ����� board ���, �������� ���� ���ͷ�
// �Ÿ� ���� �� ���� ���� ����, ���� ���� ������ �ؾ� �� -> pq ���

struct node
{
	int wall; // ������
	int idx = -1; // ������ ���� ��ȣ
	int visit = 0; // �� ����� ���� �� ����� : 1, ��Ȱų� ������� �ƴϸ� : 0
};

struct arr_node // ������ ��� ����
{
	int y;
	int x;
	int dist; // bfs queue������ ���
};

bool operator<(arr_node a1, arr_node a2)
{
	if (a1.dist > a2.dist) return true;
	else if (a1.dist == a2.dist && a1.y > a2.y) return true;
	else if (a1.dist == a2.dist && a1.y == a2.y && a1.x > a2.x) return true;
	return false;
}

int n, m, fuel, now_y, now_x;
int cnt = 0;
vector<arr_node> vec; // ������ ��� ����
node board[21][21];
int chk[21][21];
queue<arr_node> q;
priority_queue<arr_node> pq;

int y_mov[] = { -1, 0, 1, 0 };
int x_mov[] = { 0, -1, 0, 1 };

void chkClear()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) chk[i][j] = 0;
	}
}

// �� �� �ִ� ����� ��� pq ���� -> �Ÿ� ��, �� ��, �� �� ����� ����
int BFS1(int start_y, int start_x) 
{
	while (!q.empty()) q.pop();
	while (!pq.empty()) pq.pop();
	chkClear();

	chk[start_y][start_x] = 1;
	q.push({ start_y, start_x, 0 });

	int idx = -1;

	while (!q.empty())
	{
		arr_node tmp = q.front();
		q.pop();

		if (board[tmp.y][tmp.x].visit == 1)
		{
			pq.push({ tmp.y, tmp.x, tmp.dist });
			/* => �̰� bfs ������ pq�� ����� ����
			board[tmp.y][tmp.x].visit = 0;
			idx = board[tmp.y][tmp.x].idx; // ������ ���� �ε���
			now_y = tmp.y;
			now_x = tmp.x;
			fuel -= tmp.dist;
			break;
			*/
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 1 && tmp.y + y_mov[i] <= n &&
				tmp.x + x_mov[i] >= 1 && tmp.x + x_mov[i] <= n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]].wall == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}
	return idx;
}

// ���������� �̵�
int BFS2(int start_y, int start_x, int end_y, int end_x)
{
	while (!q.empty()) q.pop();
	chkClear();

	chk[start_y][start_x] = 1;
	q.push({ start_y, start_x, 0 });

	while (!q.empty())
	{
		arr_node tmp = q.front();
		q.pop();

		if (tmp.y == end_y && tmp.x == end_x)
		{
			now_y = tmp.y;
			now_x = tmp.x;
			fuel -= tmp.dist;
			return tmp.dist;
		}

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 1 && tmp.y + y_mov[i] <= n &&
				tmp.x + x_mov[i] >= 1 && tmp.x + x_mov[i] <= n &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]].wall == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i], tmp.dist + 1 });
			}
		}
	}
	return -1; // �������� �̵� �� �� ���
}
int main()
{
	cin >> n >> m >> fuel;
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> board[i][j].wall;
		}
	}

	int start_y, start_x;
	cin >> start_y >> start_x;

	cnt = 0; // �̵���Ų �մ� ��

	int y, x;
	for (int i = 0; i < m; i++)
	{
		// �����
		cin >> y >> x;
		board[y][x].idx = i;
		board[y][x].visit = 1;

		// ������
		cin >> y >> x;
		vec.push_back({ y, x });
	}

	now_y = start_y;
	now_x = start_x;

	// bfs
	while (true)
	{
		int vec_idx = BFS1(now_y, now_x);
		if (pq.size() == 0) break;

		arr_node tmp = pq.top();

		board[tmp.y][tmp.x].visit = 0;
		vec_idx = board[tmp.y][tmp.x].idx; // ������ ���� �ε���
		now_y = tmp.y;
		now_x = tmp.x;
		fuel -= tmp.dist;
		
		if (fuel < 0)
		{
			break;
		}

		// ���������� �̵�
		int f = BFS2(now_y, now_x, vec[vec_idx].y, vec[vec_idx].x);
		if (fuel < 0 || f == -1) break;
		fuel += f * 2;
		cnt++;
	}

	if (fuel < 0 || cnt != m)
	{
		cout << -1;
	}
	else cout << fuel;

	return 0;
}