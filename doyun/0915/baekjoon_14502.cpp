#include <iostream>
#include <queue>

using namespace std;

// ���� 14502 - ������
// ���Ʈ����, bfs
// ��� 4

// �� �ݵ�� 3�� ������ ��
// ��ĭ�� �ݵ�� 0�� üũ
// bfs
// �� ���� ���� ��� ������ �� �غ��� -> 8*8�̶� �ð��ʰ��� �� ����

int board[9][9]; // ���� ����
int tmp_board[9][9]; // �ùķ��̼��ϴ� ����
int chk[9][9];
int n, m;

int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };

struct node
{
	int y;
	int x;
};

queue<node> q_origin; // ���� �ʱ� 2�� ��� ť
queue<node> q;

void chkClear() // chk ����� ���� ���� ����
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			chk[i][j] = 0;
			tmp_board[i][j] = board[i][j];
		}
	}
}

int BFS()
{
	int pollu_n = 0; // �����Ǵ� ��
	//while (!q.empty()) q.pop();

	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < n &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < m &&
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0 &&
				tmp_board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] == 0)
			{
				chk[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 1;
				tmp_board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] = 2;
				q.push({ tmp.y + y_mov[i], tmp.x + x_mov[i] });
				pollu_n++;
			}
		}
	}
	return pollu_n;
}

int main()
{
	int wall_cnt = 0; // �� ����
	int p_n = 0; // ���� ������ �� ����

	cin >> n >> m;

	// 0�� �κ� �� �־����
	vector<node> zero_vec;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 1) wall_cnt++;
			else if (board[i][j] == 2)
			{
				// q�� push �̸� �ؾ� ��
				q_origin.push({ i, j });
				p_n++;
			}
			else
			{
				zero_vec.push_back({ i, j });
			}
		}
	}


	// �� 3�� ���Ƿ� �������� �ִ� �����
	// for�� 3��?
	int max = -1;
	for (int i = 0; i < zero_vec.size(); i++)
	{
		for (int j = i + 1; j < zero_vec.size(); j++)
		{
			for (int r = j + 1; r < zero_vec.size(); r++)
			{
				q = q_origin;
				chkClear();

				// �� 3�� �����
				tmp_board[zero_vec[i].y][zero_vec[i].x] = 1;
				tmp_board[zero_vec[j].y][zero_vec[j].x] = 1;
				tmp_board[zero_vec[r].y][zero_vec[r].x] = 1;

				int res = BFS();
				int tmp = n * m - res - wall_cnt - p_n;
				if (tmp > max) max = tmp;
				
			}
		}
	}

	cout << max - 3;

	return 0;
}