#include <iostream>

using namespace std;

// ���� 11053 - ���� �� �����ϴ� �κ� ����
// LIS (Longest Increasing Subsequence), DP
// �ǹ� 2

int arr[1001];
int DP[1001];

int main()
{
	int n;
	cin >> n;

	// ���� ���� : �ϳ��� ���� �� ���� �� ������ ���̴� 1�̴�
	DP[0] = 1;

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j])
			{
				if (tmp < DP[j]) tmp = DP[j];
			}
		}

		DP[i] = tmp + 1;
		if (DP[i] > max) max = DP[i];
	}

	// �� ������ ���� �ִ��� ���� �ƴϴ�
	cout << max;

	return 0;
}