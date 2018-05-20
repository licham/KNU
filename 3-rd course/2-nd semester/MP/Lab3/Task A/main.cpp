#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

constexpr int N = 100;
constexpr int H = 1000;
int bowl = 0;
bool full = false;
mutex mute;
condition_variable cond_var;

void bear() {
	unique_lock<mutex> lock(mute);
	while (true) {
		while (!full) cond_var.wait(lock);
		bowl = 0;
		full = false;
		cout << "����i�� ����������, ��� �'�� i ������" << endl;
		cond_var.notify_all();
	}
}

void bee(int index) {
	while (true) {
		unique_lock<mutex> lock(mute);
		string info;
		while (full) {
			info = "������ " + to_string(index) + " ������.\n";
			cout << info;
			cond_var.wait(lock);
		}
		bowl++;
		info = "������ " + to_string(index) + "��������� ���. � ����i " + to_string(bowl) + " ����i� ����.\n";
		cout << info;
		if (bowl == H) {
			info = "������ " + to_string(index) + " ��������� ������ i ��������� �������.\n";
			full = true;
			cond_var.notify_all();
		}
	}
}

int main() {
	setlocale(LC_ALL, "Ukrainian");
	thread thr = thread(bear);
	vector<thread> bees(N);
	for (int i = 0; i < N; ++i) {
		bees[i] = thread(bee, i);
	}
	if (thr.joinable()) thr.join();
	for (thread& th : bees)
		if (th.joinable()) th.join();
	return 0;
}