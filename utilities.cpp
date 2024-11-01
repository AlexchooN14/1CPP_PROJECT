#include "utilities.h"
#include <algorithm>
#include <ctime>
#include <iomanip> // For get_time
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", "; // Add a comma and space between elements
        }
    }
    os << "]";
    return os;
}

ostream& operator<<(ostream& os, const tm& time) {
    // Using put_time to format the output
    os << put_time(&time, "%Y-%m-%d");
    return os;
}

bool stringToBool(const string& str) {
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return (lower_str == "true" || lower_str == "1" || lower_str == "yes");
}
