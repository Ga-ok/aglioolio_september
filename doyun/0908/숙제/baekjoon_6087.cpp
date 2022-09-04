#include <iostream>
#include <queue>

using namespace std;

// ���� 6087 - ������ ���
// dijkstra
// ��� 3
// ��� ĭ���� ����
// ���� �ƿ� ���� �� �ϰ� �����ϱ�
// �ſ��� �̻��ϰ� ����.
// ���� Ȯ�� �� ���� Ȯ���ؾ� �� -> X

// ���� �ϴ� �´�� �ִ� �ֵ��� �ſ� ���� üũ -> X

// ��Ʈ : �ѹ��� ��ĭ�� �������� ���� ���� ������ ���� �� ����! (�ſ��� ������ Ʋ ������)
// pq�� push�� ���� ���� ������ ����

struct vertex
{
	int dist = 1000000;
	int mirror = 1000000;
	int y;
	int x;
	int flag = -1; // 0 : ���� / 1 : ����
	int visit = 0;
};

bool operator<(vertex v1, vertex v2)
{
	if (v1.mirror > v2.mirror) return true;
	return false;
}

priority_queue<vertex> pq;
char board[101][101];
vertex arr[101][101];

int y_mov[] = { 1, -1, 0, 0 };
int x_mov[] = { 0, 0, 1, -1 };


int main()
{
	int w, h;
	cin >> w >> h;
	int start_y = -1;
	int start_x;
	int end_y, end_x;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			cin >> board[i][j];
			if (start_y == -1 && board[i][j] == 'C')
			{
				start_y = i;
				start_x = j;
			}
			else if (board[i][j] == 'C' && start_y != -1)
			{
				end_y = i;
				end_x = j;
			}
			arr[i][j].y = i;
			arr[i][j].x = j;
		}
	}

	arr[start_y][start_x].dist = 0;
	arr[start_y][start_x].mirror = 0;
	arr[start_y][start_x].visit = 1;

	// ���������κ��� �׹��� ������ �ſ� X, �Ÿ� 1�̹Ƿ� �ֱ�

	for (int i = 0; i < 4; i++)
	{
		int tmp = 1;

		// ���� ���� ������ �̵�
		while (start_y + y_mov[i] * tmp >= 0 && start_y + y_mov[i] * tmp < h &&
			start_x + x_mov[i] * tmp >= 0 && start_x + x_mov[i] * tmp < w &&
			arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp].visit == 0 &&
			board[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp] != '*')
		{
			arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp].dist = 1;
			arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp].mirror = 0;

			if (i < 2) arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp].flag = 0; // ����
			else arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp].flag = 1; // ����

			pq.push(arr[start_y + y_mov[i] * tmp][start_x + x_mov[i] * tmp]);
			tmp++;
		}
		/*
		if (start_y + y_mov[i] >= 0 && start_y + y_mov[i] < h &&
			start_x + x_mov[i] >= 0 && start_x + x_mov[i] < w &&
			arr[start_y + y_mov[i]][start_x + x_mov[i]].visit == 0 &&
			board[start_y + y_mov[i]][start_x + x_mov[i]] != '*')
		{
			arr[start_y + y_mov[i]][start_x + x_mov[i]].dist = 1;
			arr[start_y + y_mov[i]][start_x + x_mov[i]].mirror = 0;

			if (i < 2) arr[start_y + y_mov[i]][start_x + x_mov[i]].flag = 0; // ����
			else arr[start_y + y_mov[i]][start_x + x_mov[i]].flag = 1; // ����

			pq.push(arr[start_y + y_mov[i]][start_x + x_mov[i]]);
		}
		*/
	}

	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();

		if (arr[tmp.y][tmp.x].visit == 1) continue;
		arr[tmp.y][tmp.x].visit = 1;

		//cout << tmp.y << ' ' << tmp.x << '\n';


		for (int i = 0; i < 4; i++)
		{
			int t = 1;

			// ���� ���� ������ �̵�
			while (tmp.y + y_mov[i] * t >= 0 && tmp.y + y_mov[i] * t < h &&
				tmp.x + x_mov[i] * t >= 0 && tmp.x + x_mov[i] * t < w &&
				arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].visit == 0 &&
				board[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t] != '*')
			{
				if ((tmp.flag == 0 && i < 2) || (tmp.flag == 1 && i >= 2)) // flag ������
				{
					if (arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].mirror > arr[tmp.y][tmp.x].mirror)
					{
						arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].mirror = arr[tmp.y][tmp.x].mirror;
						arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].dist = arr[tmp.y][tmp.x].dist + 1;

						if (i < 2) arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].flag = 0;
						else arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].flag = 1;

						pq.push(arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t]);
					}
				}
				else // flag �ٸ��� -> mirror + 1�� ��
				{
					if (arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].mirror > arr[tmp.y][tmp.x].mirror + 1)
					{
						arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].mirror = arr[tmp.y][tmp.x].mirror + 1;
						arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].dist = arr[tmp.y][tmp.x].dist + 1;

						if (i < 2) arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].flag = 0;
						else arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t].flag = 1;

						pq.push(arr[tmp.y + y_mov[i] * t][tmp.x + x_mov[i] * t]);
					}
				}
				t++;
			}

			/*
			// i < 2 -> ����
			if (tmp.y + y_mov[i] >= 0 && tmp.y + y_mov[i] < h &&
				tmp.x + x_mov[i] >= 0 && tmp.x + x_mov[i] < w &&
				arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].visit == 0 &&
				board[tmp.y + y_mov[i]][tmp.x + x_mov[i]] != '*')
			{
				// mirror ���� ���� �ּҸ� �ֱ�
				if ((tmp.flag == 0 && i < 2) || (tmp.flag == 1 && i >= 2)) // flag ������
				{
					if (arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].mirror > arr[tmp.y][tmp.x].mirror)
					{
						arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].mirror = arr[tmp.y][tmp.x].mirror;
						arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].dist = arr[tmp.y][tmp.x].dist + 1;

						if (i < 2) arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].flag = 0;
						else arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].flag = 1;

						pq.push(arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]]);
					}
				}
				else // flag �ٸ��� -> mirror + 1�� ��
				{
					if (arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].mirror > arr[tmp.y][tmp.x].mirror + 1)
					{
						arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].mirror = arr[tmp.y][tmp.x].mirror + 1;
						arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].dist = arr[tmp.y][tmp.x].dist + 1;

						if (i < 2) arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].flag = 0;
						else arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]].flag = 1;

						pq.push(arr[tmp.y + y_mov[i]][tmp.x + x_mov[i]]);
					}
				}
			}
			*/
		}
	}

	/*
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (arr[i][j].mirror == 1000000) cout << "# ";
			else cout << arr[i][j].mirror << ' ';
		}
		cout << endl;
	}
	*/

	cout << arr[end_y][end_x].mirror;


	return 0;

}