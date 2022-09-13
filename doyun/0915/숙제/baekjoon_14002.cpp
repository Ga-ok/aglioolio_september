#include <iostream>
#include <string>

using namespace std;

// ���� 14002 - ���� �� �����ϴ� �κ� ���� 4
// LIS, DP
// ��� 4

// max �� ���� �� �ڷ� ���鼭 LIS �ٽ� �����Ѵ�

int arr[1001];
int DP[1001];

int main()
{
	int n;
	cin >> n;

	// ���� ���� 
	DP[0] = 1;

	int max = 1; // ���� ����
	string LIS = "";

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		if (i == 0) LIS = to_string(arr[i]);

		int tmp = 0;

		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j] && tmp < DP[j])
			{
				tmp = DP[j];
			}
		}
		DP[i] = tmp + 1;
		if (max < DP[i])
		{
			max = DP[i];

			// LIS ����
			// �ڷ� ���鼭 1�� �����ذ��鼭 ����

			LIS = to_string(arr[i]);
			int tmp_r = DP[i] - 1;
			for (int j = i - 1; j >= 0; j--)
			{
				if (DP[j] == tmp_r)
				{
					LIS = to_string(arr[j]) + " " + LIS;
					tmp_r--;
				}
			}
		}

	}

	cout << max << '\n' << LIS;

	return 0;

}
