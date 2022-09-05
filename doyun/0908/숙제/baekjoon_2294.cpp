#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// ���� 2294 - ���� 2
// ��� 5
// DP

vector<int> coin; // ����
int DP[10001];

bool cmp(int a, int b)
{
	if (a < b) return true;
	return false;
}

int main()
{
	int n, k;
	cin >> n >> k;

	int c;
	for (int i = 0; i < n; i++)
	{
		cin >> c;
		coin.push_back(c);
	}

	for (int i = 1; i <= k; i++) DP[i] = 100001; // ����

	// ���� ���� ��������
	sort(coin.begin(), coin.end(), cmp);

	// ó���� �׳� �ֱ� (���� ���� ��������)
	for (int j = coin[0]; j <= k; j++)
	{
		DP[j] = DP[j - coin[0]] + 1;
	}


	for (int i = 1; i < n; i++)
	{
		for (int j = coin[i]; j <= k; j++)
		{
			// ���� �������� �������� ���� ������ ����� �� ������ ����
			if (DP[j] > DP[j - coin[i]] + 1)
			{
				DP[j] = DP[j - coin[i]] + 1;
			}
		}
	}


	// ���� �� ������ -1 ���
	// ���� �� ���� �� : ���� ���� ������ k���� ũ�ų�, �������� ������ k ���� �� ���� ���
	// DP[k] == 100001�� X
	if (DP[k] > 100001 || coin[0] > k) cout << -1;
	else cout << DP[k];

	return 0;

}