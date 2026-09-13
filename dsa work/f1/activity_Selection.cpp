#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold an activity's details
struct Activity {
    int id;
    int start;
    int finish;
};

// Comparator function to sort activities according to their finish time
bool activityCompare(Activity a1, Activity a2) {
    return (a1.finish < a2.finish);
}

// Function to select the maximum number of non-overlapping activities
void selectMaxActivities(vector<Activity>& activities) {
    // Step 1: Sort activities based on their finish time in ascending order
    sort(activities.begin(), activities.end(), activityCompare);

    cout << "\n==================================================\n";
    cout << "  SELECTED ACTIVITIES (Maximum Non-Overlapping Set)\n";
    cout << "==================================================\n";
    cout << "Activity ID\tStart Time\tFinish Time\n";
    cout << "--------------------------------------------------\n";

    // Step 2: Always select the first activity after sorting
    int i = 0;
    cout << "   A" << activities[i].id << "\t\t    " 
         << activities[i].start << "\t\t    " 
         << activities[i].finish << "\n";

    int count = 1;

    // Step 3: Check remaining activities
    for (int j = 1; j < activities.size(); j++) {
        // If the start time of activity j is >= finish time of previous activity i
        if (activities[j].start >= activities[i].finish) {
            cout << "   A" << activities[j].id << "\t\t    " 
                 << activities[j].start << "\t\t    " 
                 << activities[j].finish << "\n";
            i = j; // Update index to current selected activity
            count++;
        }
    }

    cout << "--------------------------------------------------\n";
    cout << "Total Activities Selected: " << count << "\n";
    cout << "==================================================\n";
}

int main() {
    // Sample dataset of activities {ID, Start Time, Finish Time}
    vector<Activity> activities = {
        {1, 1, 4},
        {2, 3, 5},
        {3, 0, 6},
        {4, 5, 7},
        {5, 3, 9},
        {6, 5, 9},
        {7, 6, 10},
        {8, 8, 11},
        {9, 8, 12},
        {10, 2, 14},
        {11, 12, 16}
    };

    selectMaxActivities(activities);

    return 0;
}