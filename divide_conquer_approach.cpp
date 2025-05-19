/* Github : @koussay0 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
    int index;
    int engagement;
};

bool compareByEngagement(Segment &a, Segment &b) {
    return a.engagement > b.engagement;
}

// Divide and conquer function to find top-k engaged segments
vector<Segment> findHighlights(vector<int>& engagement, int left, int right, int k = 3) {
    if (left == right) {
        return {{left, engagement[left]}};
    }

    int mid = (left + right) / 2;

    vector<Segment> leftHighlights = findHighlights(engagement, left, mid, k);
    vector<Segment> rightHighlights = findHighlights(engagement, mid + 1, right, k);
    vector<Segment> combined = leftHighlights;
    combined.insert(combined.end(), rightHighlights.begin(), rightHighlights.end());

    sort(combined.begin(), combined.end(), compareByEngagement);

    if (combined.size() > k) combined.resize(k);

    return combined;
}

int main() {
    int totalLengthSec;
    cout << "Enter total length of podcast (in seconds): ";
    cin >> totalLengthSec;

    int segmentDuration = 30;
    int segmentCount = (totalLengthSec + segmentDuration - 1) / segmentDuration; // round up

    cout << "Total segments: " << segmentCount << " (each 30 seconds)" << endl;

    vector<int> engagement(segmentCount);
    cout << "Enter engagement score for each segment:\n";
    for (int i = 0; i < segmentCount; ++i) {
        cout << "Segment " << i << ": ";
        cin >> engagement[i];
    }
    vector<Segment> highlights = findHighlights(engagement, 0, segmentCount - 1);
    
    cout << "\n Top Highlight Segments:\n";
    for (auto& seg : highlights) {
        int startTime = seg.index * segmentDuration;
        int endTime = min((seg.index + 1) * segmentDuration, totalLengthSec);
        cout << "- Segment " << seg.index << " (Time: " << startTime << "s to " << endTime << "s" << ", Engagement: " << seg.engagement << ")\n";
    }

    return 0;
}
