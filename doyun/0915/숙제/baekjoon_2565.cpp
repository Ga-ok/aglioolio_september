#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ���� 2565 - ������
// LIS, DP
// ��� 5

// A ���� ������������ �������� ��, B ������ ��� ���������̸� �������� �ʴ´�
// A ���� ������������ �����ϰ� B ������ ���� ���� ���� ����(LIS, Longest Increasing Subsequence) ã�Ƽ�
// ��ü N���� ���ָ� �ȴ�.

struct node
{
	int a;
	int b;
};

bool cmp(node n1, node n2)
{
	if (n1.a < n2.a) return true;
	else if (n1.a == n2.a && n1.b < n2.b) return true;
	return false;
}

int DP[101];

int main()
{
	vector<node> vec;

	int n;
	cin >> n;

	int a, b;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b;
		vec.push_back({ a, b });
	}

	// A ���� ������������ ����
	sort(vec.begin(), vec.end(), cmp);

	// LIS ���ϱ�

	// ���� ���� : �Ѱ��� �̷���� ������ �ִ� ���� 1
	DP[0] = 1;

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (vec[i].b > vec[j].b && tmp < DP[j]) tmp = DP[j];
		}
		DP[i] = tmp + 1;
		if (DP[i] > max) max = DP[i];
	}

	cout << n - max;

	return 0;
}