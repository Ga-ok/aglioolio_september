#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int a, b, cost;
};

bool cmp(Edge a, Edge b) {
	// ��� ���� �� �켱
	if (a.cost < b.cost) return true;
	if (a.cost > b.cost) return false;
	return false;
}

int N, M;
vector<Edge> v;
int parent[100001];

int Find(int node) {
	if (node == parent[node])
		return node;
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;

	parent[pb] = pa;
}

int kruskal() {
	// ����� ���� �ͺ��� ����
	sort(v.begin(), v.end(), cmp);

	int sum = 0; // ��� �� ��� ����
	int maxval = -2134567890; // �ִ���
	for (int i = 0; i < v.size(); i++) {
		Edge now = v[i];

		// �� ������ �̹� ����Ǿ� �ִ°�
		if (Find(v[i].a) == Find(v[i].b))
			continue;
		// �ƴ϶�� ���� ���ش�.
		sum += now.cost;
		// ���� ���� ���� �ִ밪���� ũ�� ����
		if (now.cost > maxval)
			maxval = now.cost;
		// ���� �������� ��ǥ ���� �����
		Union(v[i].a, v[i].b);
	}
	// ��� �����Ų �� ���� ��� �� ����
	return sum - maxval;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 1. ������ �� �� ���̿� ��ΰ� �׻� �����ؾ� �Ѵ�.
	// --> Union Find / MST

	// 2. ������ �� ���� �и�
	// --> MST�� ����� �� �߿��� ���� ����� ū ���� ����

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		v.push_back({ a,b,cost });
	}

	// parent �ʱ�ȭ
	for (int i = 1; i <= N; i++)
		parent[i] = i;

	int ans = kruskal();
	cout << ans;

	return 0;
}