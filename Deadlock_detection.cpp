#include <bits/stdc++.h>
using namespace std;

int main (void) 
{
	int total_resource[3] = {7, 2, 6};
	int  count_process = 5, count_resource = 3;

	int allocated[count_process][count_resource] = { {0, 1, 0},
													 {2, 0, 0},
													 {3, 0, 3},
													 {2, 1, 1},
													 {0, 0, 2} };

	int need[count_process][count_resource] = { {0, 0, 0},
												{2, 0, 2},
												{0, 1, 0}, /* will go to a deadlock state in 0, 2, 0 sequence */ 
												{4, 0, 0},
												{0, 0, 2} };

	int available[count_resource]; 
	bool finished[count_process]; 

	for (int i=0; i<count_process; ++i)
		finished[i] = false;

	for (int i=0; i<count_resource; ++i) {
		int temp = 0;

		for (int j=0; j<count_process; ++j)
			temp += allocated[j][i];

		available[i] = total_resource[i] - temp;
		//cout << available[i] << " ";
	}

	for (int loop_count=0; loop_count < count_process; ++loop_count) {
		for (int i=0; i<count_process; ++i) {
			if (!finished[i]) {

				bool update_available = true;

				for (int j=0; j<count_resource; ++j) {
					if (need[i][j] > available[j]) {
						update_available = false;
						break;
					}
				}

				if (update_available) {
					for (int j=0; j<count_resource; ++j)
						available[j] += allocated[i][j];

					finished[i] = true;
				}
			}
		}
	}

	bool isDeadlocked = false;

	for (int i=0; i<count_process; ++i)
		if (!finished[i]) {
			//cout << "P" << i << " "; 
			isDeadlocked = true;
			break;
		}

	if (isDeadlocked)
		cout << "Dead Locked\n";
	else
		cout << "Not Dead Locked\n";

	return 0;
}