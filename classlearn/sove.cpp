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
	// ������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vWinner.clear();
	this->Speakers.clear();
	// ��ʼ����������
	this->Index = 1;
}

match::match() {
	// ��ʼ������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();
}

void match::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
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
	cout << "��" << this->Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	if (this->Index == 1)
	{
		// ��v1����˳��
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// ����v2��˳��
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

void match::speechConst() {
	cout << "------------- ��" << this->Index << "����ʽ������ʼ��------------- " << endl;
	//��ʱ����������key������value ѡ�ֱ��
	multimap<double, int, greater<int>> groupScore;

	//��¼��Ա����6��Ϊ1��
	int num = 0;

	// ��������Ա����
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
		// ��ί���

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

		// capacity ��ǰvector����Ĵ�С
		// size ��ǰʹ�����ݵĴ�С

		double avg = sum / (double)d.size();

		// ��ƽ���ָ�����ǰѡ��
		Speakers[*it].changeScore(Index - 1, avg);

		// 6��һ�飬����ʱ��������  �ɴ�С ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();
				it != groupScore.end(); it++)
			{
				cout << "���: "
					<< it->second
					<< " ������ "
					<< this->Speakers[it->second].retName()
					<< " �ɼ��� "
					<< this->Speakers[it->second].retScore()[Index - 1]
					<< endl;
			}

			int count = 0;
			// ȡǰ����
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();
				it != groupScore.end() && count < 3; it++, count++)
			{
				if (Index == 1) {
					//��Ϊmultimap �ɴ�С ��˳��ž���
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

	cout << "------------- ��" << this->Index << "�ֱ������  ------------- " << endl;

}

void match::showScore() {
	cout << "---------��" << Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
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
		cout << "ѡ�ֱ�ţ�"
			<< *it
			<< "������"
			<< Speakers[*it].retName()
			<< "�÷֣�"
			<< Speakers[*it].retScore()[Index - 1]
			<< endl;
	}
	cout << endl;
}


void match::saveScore() {
	ofstream ofs;
	// ������ķ�ʽ���ļ�   -----д�ļ�
	ofs.open("speech.csv", ios::out | ios::app);

	//��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); it++)
	{
		ofs << *it
			<< ","
			<< Speakers[*it].retScore()[Index - 1]
			<< ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
}


void match::startSpeech() {
	// ��һ�ֱ���
	// ��ǩ
	cout << "Index��" << Index << endl;
	speechDraw();

	// ����
	speechConst();

	// ��ʾ�������
	showScore();

	Index++;

	// �ڶ��ֱ���
	// ��ǩ
	cout << "Index��" << Index << endl;
	speechDraw();

	// ����
	speechConst();

	// ��ʾ���ս��
	showScore();

	// �������
	saveScore();

	cout << "���speech" << endl;
}

int main() {
	match mc;
	// ���Դ���
	for (map<int, contestant>::iterator it = mc.retSpeakers().begin();
		it != mc.retSpeakers().end(); it++)
	{
		cout << "ѡ�ֱ��" << it->first
			<< "������" << it->second.retName()
			<< "�ɼ���" << it->second.retScore()[0] << endl;
	}
	mc.startSpeech();

	
}