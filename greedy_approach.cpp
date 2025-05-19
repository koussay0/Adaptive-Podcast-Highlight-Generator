/* Github : @koussay0 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Segment structure to store index and engagement
struct Segment {
    int index;
    int engagement;

    // For min-heap: lowest engagement has highest priority
    bool operator>(const Segment& other) const {
        return engagement > other.engagement;
    }
};

// Greedy function to find top-k segments with highest engagement
vector<Segment> greedyHighlightDetection(const vector<int>& engagement, int k) {
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

    // Convert heap to sorted list
    vector<Segment> highlights;
    while (!topSegments.empty()) {
        highlights.push_back(topSegments.top());
        topSegments.pop();
    }

    sort(highlights.begin(), highlights.end(), [](const Segment& a, const Segment& b) {
        return a.engagement > b.engagement;
    });

    return highlights;
}

int main() {
    int totalLengthSec;
    int topK = 3;
    const int segmentDuration = 30;

    cout << "Enter total length of podcast/video (in seconds): ";
    cin >> totalLengthSec;

    int segmentCount = (totalLengthSec + segmentDuration - 1) / segmentDuration;

    cout << "Podcast will be split into " << segmentCount << " segments (each 30 seconds)\n";

    vector<int> engagement(segmentCount);
    cout << "Enter engagement scores for each segment:\n";
    for (int i = 0; i < segmentCount; ++i) {
        cout << "Segment " << i << " (from " << i * segmentDuration << "s to "
             << min((i + 1) * segmentDuration, totalLengthSec) << "s): ";
        cin >> engagement[i];
    }

    vector<Segment> highlights = greedyHighlightDetection(engagement, topK);

    cout << "\n Top " << topK << " Highlight Segments (Greedy):\n";
    for (const auto& seg : highlights) {
        int startTime = seg.index * segmentDuration;
        int endTime = min((seg.index + 1) * segmentDuration, totalLengthSec);
        cout << "- Segment " << seg.index << " (Time: " << startTime << "s to " << endTime
             << "s, Engagement: " << seg.engagement << ")\n";
    }

    return 0;
}
