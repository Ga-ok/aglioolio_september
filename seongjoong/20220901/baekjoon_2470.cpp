#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<int> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	//freopen("input.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		v.push_back(n);
	}

	// �������� ����
	sort(v.begin(), v.end());

	// two pointer
	int left = 0;
	int right = N - 1;
	// �ּ��� �� �����ϸ鼭 ���
	long long minval = 9999999999999999;
	int a = 0, b = 0;
	while (left < right) {
		// �� ����� ��
		long long sum = v[left] + v[right];
		// 0�� ����� ���� ã�ƾ� �ϹǷ� ���� **
		if (abs(sum) < minval) {
			minval = abs(sum);
			a = v[left];
			b = v[right];
		}

		// ���� 0���� ������ left �̵�
		if (sum < 0)
			left++;
		else if (sum > 0)
			right--;
		else // ���� 0�̸� ���̻� �� �ʿ� X
			break;
	}

	cout << a << " " << b;

	return 0;
}