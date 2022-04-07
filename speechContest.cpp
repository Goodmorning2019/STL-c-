#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<deque>
#include<numeric>
#include<functional>

using namespace std;
/*
	��STL��̣�����������
	1)���ӡ������ѡ�ֵ����ֲ����ţ����Բ����ŵ���������
	2)��ӡÿһ�ֱ�����С������ɼ���С���������
*/

/*
	���������
	1������ѡ�֣�ABCDEFGHIJKLMNOPQRSTUVWX���������÷֡�ѡ�ֱ��
	2����1�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
	3����2�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
	4����2�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
*/

class Speaker
{
public:
	string m_Name;
	int m_Score[3];
};

void createSpeaker(vector<int> &v, map<int, Speaker> &m)
{
	string nameSeed = "ABCDEFGHIJKLMNOPQRSTUVWX";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		Speaker sp;
		string name;
		name = "ѡ��";
		name += nameSeed[i];
		sp.m_Name = name;

		for (int j = 0; j < 3; j++)
		{
			sp.m_Score[j] = 0;
		}

		v.push_back(i + 100); //���Ϊ100-123
		m.insert(make_pair(i + 100, sp));

	}

}

void speechDraw(vector<int> &v)
{
	random_shuffle(v.begin(), v.end()); //ϴ��
}

void speechContest(int index, vector<int> &v1, map<int, Speaker> &m, vector<int> &v2)
{
	multimap<int, int, greater<int>>groupMap;  //key �����  value ����
	int num = 0;
	for (vector<int>::iterator dit = v1.begin(); dit != v1.end(); dit++)
	{
		num++;
		deque<int>d;
		for (int i = 0; i < 10; i++) //10����ί
		{
			int score = rand() % 41 + 60; //��ַ�Χ60-100
			d.push_back(score);
		}
		sort(d.begin(), d.end()); //��10λ��ί��ֽ�����������
		d.pop_back(); //ȥ����߷�
		d.pop_front(); //ȥ����ͷ�
		int sum = accumulate(d.begin(), d.end(), 0); //�ۻ����� ��0�ۼ�
		int avg = sum / d.size(); //��ƽ����
		//��ƽ���ַ���m������
		m[*dit].m_Score[index - 1] = avg;

		//6����ȡǰ����һ������ȡǰ����
		// ��6�˷���������ʱ������
		groupMap.insert(make_pair(avg, *dit));

		if (num % 6 == 0)
		{
			//����

			cout << "--С��ɼ�--" << endl;
			for (multimap<int, int, greater<int>>::iterator it = groupMap.begin(); it != groupMap.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << m[it->second].m_Name << " ѡ�ֵ÷֣�" << it->first << endl;
			}


			//ȡǰ����
			int count = 0;
			for (multimap<int, int, greater<int>>::iterator it = groupMap.begin(); it != groupMap.end(), count < 3; it++, count++)
			{
				//����������ȡ����
				v2.push_back(it->second);
			}
			groupMap.clear(); //�����ʱ����

		}

	}
}

void showScore(int index, vector<int> &v, map<int, Speaker> &m)
{
	cout << "---�� " << index << " �ֱ������----" << endl;
	for (map<int, Speaker>::iterator mit = m.begin(); mit != m.end(); mit++)
	{
		cout << "ѡ�ֱ�ţ�" << mit->first << " ������" << mit->second.m_Name << " �÷֣�" << mit->second.m_Score[index - 1] << endl;
	}
	cout << "--�������---" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << endl;
	}
}


int main()
{
	vector<int>v1; //ѡ�ֱ��

	map<int, Speaker>m; //���ѡ�ֱ�� �;���ѡ��

	//����ѡ��
	createSpeaker(v1, m);

	//����
	//for (map<int, Speaker>::iterator ret = m.begin(); ret != m.end(); ret++)
	//{
	//	cout << "��ţ�" << (*ret).first << " ������" << ret->second.m_Name << endl;
	//}

	//��һ��
	//��ǩ
	speechDraw(v1);

	//����
	vector<int>v2; //�����߱��
	speechContest(1, v1, m, v2); //��һ��

	//�������
	showScore(1, v2, m); // ��1�� ������� ѡ����Ϣ


	//�ڶ���
	speechDraw(v2);
	vector<int>v3; //�������
	speechContest(2, v2, m, v3);
	showScore(2, v3, m); // ��2�� ������� ѡ����Ϣ

	//������
	speechDraw(v3);
	vector<int>v4; //�������
	speechContest(3, v3, m, v4);
	showScore(3, v4, m);

	return 0;
}