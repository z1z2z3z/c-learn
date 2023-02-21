#pragma once
#include<string>
#include<map>
using namespace std;

class contestant {
private:
	/*int number;*/
	string name;
	double score[2] = {0,0};  // ��������ֵ÷�
public:
	contestant() {} // Ĭ�Ϲ��캯��
	contestant(string name)
		:name(name)
	{}
	void changeScore(const int i,const double grade) {
		score[i] = grade;
	}
	string& retName() {
		return name;
	}
	// c++������ ���ܷ���һ������  
	// �����������ָ��  ����ͨ������ָ������������
	double* retScore() {
		return score;
	}
};



class match {
private:
	// ����ѡ�� ���� 
	vector<int> v1;

	// ��һ�ֽ�������
	vector<int> v2;

	// ʤ��ǰ��������
	vector<int> vWinner;

	// ��ű�� �Լ���Ӧ�ľ���ѡ��
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

