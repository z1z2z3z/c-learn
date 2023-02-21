#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<deque>
#include<numeric>
#include<fstream>
#include "head1.h"
using namespace std;

//vector<int>& randperm(int start, int end, int num) {
//	vector<int> temp;
//	vector<int> randInt;
//	for (int i = start; i < end; i++)
//	{
//		temp.push_back(i);
//	}
//	random_shuffle(temp.begin(), temp.end());
//	for (int i = 0; i < num; i++)
//	{
//		randInt[i] = temp[i];
//	}
//	return randInt;
//}

void match::initSpeech() {
	// 容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vWinner.clear();
	this->Speakers.clear();
	// 初始化比赛轮数
	this->Index = 1;
}

match::match() {
	// 初始化属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();
}

void match::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		contestant sp(name);
		/*for (int i = 0; i < 2; i++)
		{
			sp.changeScore(i, 0);
		}*/
		this->v1.push_back(i + 10001);

		this->Speakers.insert(make_pair(i + 10001, sp));

	}
}

void match::speechDraw() {
	cout << "第" << this->Index << "轮比赛选手正在抽签" << endl;
	if (this->Index == 1)
	{
		// 将v1打乱顺序
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// 打乱v2的顺序
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

void match::speechConst() {
	cout << "------------- 第" << this->Index << "轮正式比赛开始：------------- " << endl;
	//临时容器，保存key分数，value 选手编号
	multimap<double, int, greater<int>> groupScore;

	//记录人员数，6个为1组
	int num = 0;

	// 比赛的人员容器
	vector<int> src_v;
	if (Index == 1) {
		src_v = v1;
	}
	else
	{
		src_v = v2;
	}
	for (vector<int>::iterator it = src_v.begin(); it != src_v.end(); it++) {
		num++;
		// 评委打分

		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);

		// capacity 当前vector分配的大小
		// size 当前使用数据的大小

		double avg = sum / (double)d.size();

		// 把平均分给到当前选手
		Speakers[*it].changeScore(Index - 1, avg);

		// 6人一组，用临时容器保存  由大到小 插入排序
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();
				it != groupScore.end(); it++)
			{
				cout << "编号: "
					<< it->second
					<< " 姓名： "
					<< this->Speakers[it->second].retName()
					<< " 成绩： "
					<< this->Speakers[it->second].retScore()[Index - 1]
					<< endl;
			}

			int count = 0;
			// 取前三名
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();
				it != groupScore.end() && count < 3; it++, count++)
			{
				if (Index == 1) {
					//因为multimap 由大到小 按顺序放就行
					v2.push_back((*it).second);
				}
				else
				{
					// 
					vWinner.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}

	cout << "------------- 第" << this->Index << "轮比赛完毕  ------------- " << endl;

}

void match::showScore() {
	cout << "---------第" << Index << "轮晋级选手信息如下：-----------" << endl;
	vector<int>v;
	if (Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vWinner;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号："
			<< *it
			<< "姓名："
			<< Speakers[*it].retName()
			<< "得分："
			<< Speakers[*it].retScore()[Index - 1]
			<< endl;
	}
	cout << endl;
}


void match::saveScore() {
	ofstream ofs;
	// 用输出的方式打开文件   -----写文件
	ofs.open("speech.csv", ios::out | ios::app);

	//将每个人数据写入到文件中
	for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); it++)
	{
		ofs << *it
			<< ","
			<< Speakers[*it].retScore()[Index - 1]
			<< ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();
	cout << "记录已经保存" << endl;
}


void match::startSpeech() {
	// 第一轮比赛
	// 抽签
	cout << "Index：" << Index << endl;
	speechDraw();

	// 比赛
	speechConst();

	// 显示晋级结果
	showScore();

	Index++;

	// 第二轮比赛
	// 抽签
	cout << "Index：" << Index << endl;
	speechDraw();

	// 比赛
	speechConst();

	// 显示最终结果
	showScore();

	// 保存分数
	saveScore();

	cout << "完成speech" << endl;
}

int main() {
	match mc;
	// 测试代码
	for (map<int, contestant>::iterator it = mc.retSpeakers().begin();
		it != mc.retSpeakers().end(); it++)
	{
		cout << "选手编号" << it->first
			<< "姓名：" << it->second.retName()
			<< "成绩：" << it->second.retScore()[0] << endl;
	}
	mc.startSpeech();

	
}