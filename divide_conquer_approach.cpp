/* Github : @koussay0 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Explanation:
//maintain a priority queue (max-heap or min-heap) of top-k segments.
//for each segment, greedily decide if it’s better than the current lowest top segment and insert it.

struct Segment {
    int index;
    int engagement;
};

bool compareByEngagement( Segment &a,  Segment &b) {
    return a.engagement > b.engagement;
}

// Divide and conquer function to find top engaged segments
vector<Segment> findHighlights( vector<int>& engagement, int left, int right) {
    if (left == right) {
        return {{left, engagement[left]}};
    }

    int mid = (left + right) / 2;

    vector<Segment> leftHighlights = findHighlights(engagement, left, mid);
    vector<Segment> rightHighlights = findHighlights(engagement, mid + 1, right);

    // Combine and keep top segments
    vector<Segment> combined = leftHighlights;
    combined.insert(combined.end(), rightHighlights.begin(), rightHighlights.end());

    // Sort combined by engagement
    sort(combined.begin(), combined.end(), compareByEngagement);

    // You can limit to top-k segments (e.g., top 3)
    int k = 3;
    if (combined.size() > k) combined.resize(k);

    return combined;
}

int main() {
    vector<int> engagement = {2, 5, 8, 1, 10, 3, 7, 6, 2, 9};

    vector<Segment> highlights = findHighlights(engagement, 0, engagement.size() - 1);

    cout << "Top Highlight Segments:\n";
    for ( auto& seg : highlights) {
        cout << "Segment " << seg.index << " (Engagement: " << seg.engagement << ")\n";
    }

    return 0;
}
