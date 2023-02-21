#pragma once
#include<string>
#include<map>
using namespace std;

class contestant {
private:
	/*int number;*/
	string name;
	double score[2] = {0,0};  // 最多有两轮得分
public:
	contestant() {} // 默认构造函数
	contestant(string name)
		:name(name)
	{}
	void changeScore(const int i,const double grade) {
		score[i] = grade;
	}
	string& retName() {
		return name;
	}
	// c++函数中 不能返回一个数组  
	// 但是数组就是指针  可以通过返回指针来返回数组
	double* retScore() {
		return score;
	}
};



class match {
private:
	// 比赛选手 容器 
	vector<int> v1;

	// 第一轮晋级容器
	vector<int> v2;

	// 胜利前三名容器
	vector<int> vWinner;

	// 存放编号 以及对应的具体选手
	map<int, contestant> Speakers;
	int Index;
	/*int allPersons;
	int winners;
	contestant matchers[];*/
public:
	match();
	void initSpeech();
	void createSpeaker();
	void startSpeech();
	void speechDraw();
	void speechConst();
	void showScore();
	void saveScore();
	map<int, contestant>& retSpeakers() {
		return Speakers;
	}
};

