#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

struct Point {
	unsigned int x, y;
};

mutex mute;
vector<unsigned int> locations;
unsigned int next_x = 0;
bool found = false;

void threadFunction(unsigned int group, Point Winnie) {
	string result;
	unsigned int current_x, current_y;
	while (!found && next_x != locations.size()) {
		mute.lock();
		current_x = next_x++;
		mute.unlock();
		current_y = 0;
		int lock_size = locations[current_x];
		while (++current_y < lock_size) {
			if (current_x == Winnie.x - 1 && current_y == Winnie.y) {
				result = "�i��i �������� ������� " + to_string(group) + " �� �i����i " + to_string(current_x + 1) + " � �����i� " + to_string(current_y) + "!!!\n";
				found = true;
				break;
			}
		}
		if (!found) 
			result = "�i��i �� �������� ������� " + to_string(group) + " �� �i����i " + to_string(current_x + 1) + ".\n";		
		cout << result;
	}
}

int main() {
	setlocale(LC_ALL, "");
	cout << "����i�� �i���i��� �i����� �� ���� ���i�" << endl;
	int n, k;
	cin >> n >> k;
	locations.resize(n);
	cout << "����i�� ����i� ����� � �i�����" << endl;
	for (unsigned int& size : locations)
		cin >> size;
	cout << "����i�� ���������� �i��i (����� �i����� �� �����i� � �i� �i����i)" << endl;
	Point Winnie;
	cin >> Winnie.x >> Winnie.y;

	vector<thread> bees(k);
	for (int i = 0; i < k; ++i) 
		bees[i] = thread(threadFunction, i + 1, Winnie);

	for (thread& thr : bees)
		if (thr.joinable())
			thr.join();

	system("pause");
	return 0;
}