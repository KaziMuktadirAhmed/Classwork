#include <bits/stdc++.h>
using namespace std;

int main(void) 
{
	int total_resource[3] = {10, 5, 7};
	int  count_process = 5, count_resource = 3;

	int allocated[count_process][count_resource] = { {0, 1, 0},
													 {2, 0, 0},
													 {3, 0, 2},
													 {2, 1, 1},
													 {0, 0, 2} };

	int max_need[count_process][count_resource] = { {7, 5, 3},
													{3, 2, 2},
													{9, 0, 2},
													{2, 2, 2},
													{4, 3, 3} };

	int available[count_resource]; 
	vector <int> safe;
	bool finished[count_process]; 
	int current_need[count_process][count_resource];

	for (int i=0; i<count_process; ++i)
		finished[i] = false;

	for (int i=0; i<count_process; ++i)
		for (int j=0; j<count_resource; ++j)
			current_need[i][j] = max_need[i][j] - allocated[i][j];

	for (int i=0; i<count_resource; ++i) {
		int temp = 0;

		for (int j=0; j<count_process; ++j)
			temp += allocated[j][i];

		available[i] = total_resource[i] - temp;
	}

	for (int loop_count=0; loop_count < count_process; ++loop_count) {
		for (int i=0; i<count_process; ++i) {
			if (!finished[i]) {

				bool update_avialable = true;

				for(int j=0; j<count_resource; ++j) {
					if (current_need[i][j] > available[j]) {
						update_avialable = false;
						break;
					}
				}

				if (update_avialable) {
					safe.push_back(i);

					for (int j=0; j<count_resource; ++j)
						available[j] += allocated[i][j];

					finished[i] = true;
				}
			}
		}
	}

	cout << "Safe sequence\n";
	for (int i=0; i<safe.size(); ++i) {
		cout << " P" << safe[i];

		if (i < safe.size()-1)
			cout << " ->";
	} cout << endl;

	return 0;
}