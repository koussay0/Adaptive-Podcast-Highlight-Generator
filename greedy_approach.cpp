/* Github : @koussay0 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//Explanation:
//this method greedily replaces the lowest-engagement highlight whenever it sees a better candidate,
//ensuring that only the most engaging segments are kept.

struct Segment {
    int index;
    int engagement;

    // For min-heap: smallest engagement at top
    bool operator>(const Segment& other) const {
        return engagement > other.engagement;
    }
};

vector<Segment> greedyHighlightDetection(const vector<int>& engagement, int k) {
    // Min-heap to store top-k segments
    priority_queue<Segment, vector<Segment>, greater<Segment>> topSegments;

    for (int i = 0; i < engagement.size(); ++i) {
        Segment current = {i, engagement[i]};
        
        if (topSegments.size() < k) {
            topSegments.push(current);
        } else if (current.engagement > topSegments.top().engagement) {
            topSegments.pop();
            topSegments.push(current);
        }
    }
  
    vector<Segment> highlights;
    while (!topSegments.empty()) {
        highlights.push_back(topSegments.top());
        topSegments.pop();
    }

    // Optional: sort by index or engagement for output
    sort(highlights.begin(), highlights.end(), [](const Segment& a, const Segment& b) {
        return a.engagement > b.engagement;
    });

    return highlights;
}

int main() {
    vector<int> engagement = {2, 5, 8, 1, 10, 3, 7, 6, 2, 9};
    int topK = 3;

    vector<Segment> highlights = greedyHighlightDetection(engagement, topK);

    cout << "Top " << topK << " Highlight Segments (Greedy):\n";
    for (const auto& seg : highlights) {
        cout << "Segment " << seg.index << " (Engagement: " << seg.engagement << ")\n";
    }

    return 0;
}
