#include <iostream>
#include <string>

using namespace std;

// ���� 17609 - ȸ��
// ���ڿ�
// ��� 5

// �ǳʶپ�� �ϴ� �ֵ� ī��Ʈ & �ǳʶ�
// 0 �� : ȸ��
// 1 �� : ����ȸ��
// �� �̻� : 2 ���

// ó�� ���� ȸ�� �Ǵ� �͵� üũ
// ó�� ���� ȸ�� �ǰų�, �� �� ���� ȸ�� �Ǵ� �� üũ ����
// ȸ�� üũ �Լ� �ΰ� ����ؼ� �� ���� �� ���

int chkPal(string s)
{
	int start = 0;
	int end = s.length() - 1;

	int cnt = 0;
	while (start < end)
	{
		if (s[start] == s[end])
		{
			start++;
			end--;
		}
		else
		{
			cnt++;
			// ���� ������ Ȯ��
			if (s[start + 1] == s[end])
			{
				start++;
			}
			else if (s[start] == s[end - 1])
			{
				end--;
			}
			else start++;

		}
		if (cnt >= 2) return 2;
	}
	
	return cnt;
}

int chkPal2(string s)
{
	int start = 0;
	int end = s.length() - 1;

	int cnt = 0;
	while (start < end)
	{
		if (s[start] == s[end])
		{
			start++;
			end--;
		}
		else
		{
			cnt++;
			// ���� ������ Ȯ��
			if (s[start] == s[end - 1])
			{
				end--;
			}
			else if (s[start + 1] == s[end])
			{
				start++;
			}
			else start++;

		}
		if (cnt >= 2) return 2;
	}

	return cnt;
}


int main()
{
	string s;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		int res1 = chkPal(s);
		int res2 = chkPal2(s);
		if (res1 < res2) cout << res1 << '\n';
		else cout << res2 << '\n';
	}
	return 0;
}