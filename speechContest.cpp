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
	用STL编程，求解这个问题
	1)请打印出所有选手的名字参赛号，并以参赛号的升序排列
	2)打印每一轮比赛后，小组比赛成绩和小组晋级名单
*/

/*
	需求分析：
	1）产生选手（ABCDEFGHIJKLMNOPQRSTUVWX）姓名、得分、选手编号
	2）第1轮 选手抽签 选手比赛 查看比赛结果
	3）第2轮 选手抽签 选手比赛 查看比赛结果
	4）第2轮 选手抽签 选手比赛 查看比赛结果
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
		name = "选手";
		name += nameSeed[i];
		sp.m_Name = name;

		for (int j = 0; j < 3; j++)
		{
			sp.m_Score[j] = 0;
		}

		v.push_back(i + 100); //编号为100-123
		m.insert(make_pair(i + 100, sp));

	}

}

void speechDraw(vector<int> &v)
{
	random_shuffle(v.begin(), v.end()); //洗牌
}

void speechContest(int index, vector<int> &v1, map<int, Speaker> &m, vector<int> &v2)
{
	multimap<int, int, greater<int>>groupMap;  //key 存分数  value 存编号
	int num = 0;
	for (vector<int>::iterator dit = v1.begin(); dit != v1.end(); dit++)
	{
		num++;
		deque<int>d;
		for (int i = 0; i < 10; i++) //10个评委
		{
			int score = rand() % 41 + 60; //打分范围60-100
			d.push_back(score);
		}
		sort(d.begin(), d.end()); //对10位评委打分进行排序（升序）
		d.pop_back(); //去掉最高分
		d.pop_front(); //去掉最低分
		int sum = accumulate(d.begin(), d.end(), 0); //累积分数 从0累计
		int avg = sum / d.size(); //求平均分
		//将平均分放入m容器中
		m[*dit].m_Score[index - 1] = avg;

		//6个人取前三（一组六人取前三）
		// 将6人分数放入临时容器中
		groupMap.insert(make_pair(avg, *dit));

		if (num % 6 == 0)
		{
			//测试

			cout << "--小组成绩--" << endl;
			for (multimap<int, int, greater<int>>::iterator it = groupMap.begin(); it != groupMap.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << m[it->second].m_Name << " 选手得分：" << it->first << endl;
			}


			//取前三名
			int count = 0;
			for (multimap<int, int, greater<int>>::iterator it = groupMap.begin(); it != groupMap.end(), count < 3; it++, count++)
			{
				//晋级容器获取数据
				v2.push_back(it->second);
			}
			groupMap.clear(); //清空临时容器

		}

	}
}

void showScore(int index, vector<int> &v, map<int, Speaker> &m)
{
	cout << "---第 " << index << " 轮比赛结果----" << endl;
	for (map<int, Speaker>::iterator mit = m.begin(); mit != m.end(); mit++)
	{
		cout << "选手编号：" << mit->first << " 姓名：" << mit->second.m_Name << " 得分：" << mit->second.m_Score[index - 1] << endl;
	}
	cout << "--晋级编号---" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << endl;
	}
}


int main()
{
	vector<int>v1; //选手编号

	map<int, Speaker>m; //存放选手编号 和具体选手

	//创建选手
	createSpeaker(v1, m);

	//测试
	//for (map<int, Speaker>::iterator ret = m.begin(); ret != m.end(); ret++)
	//{
	//	cout << "编号：" << (*ret).first << " 姓名：" << ret->second.m_Name << endl;
	//}

	//第一轮
	//抽签
	speechDraw(v1);

	//比赛
	vector<int>v2; //晋级者编号
	speechContest(1, v1, m, v2); //第一轮

	//比赛结果
	showScore(1, v2, m); // 第1轮 晋级编号 选手信息


	//第二轮
	speechDraw(v2);
	vector<int>v3; //晋级编号
	speechContest(2, v2, m, v3);
	showScore(2, v3, m); // 第2轮 晋级编号 选手信息

	//第三轮
	speechDraw(v3);
	vector<int>v4; //晋级编号
	speechContest(3, v3, m, v4);
	showScore(3, v4, m);

	return 0;
}