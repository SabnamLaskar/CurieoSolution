#include <bits/stdc++.h>

using namespace std;
struct LogEntry {
    long long timestamp;
    string logType;
    double severity;
};

vector<LogEntry> logEntries;

void addLogEntry(long long timestamp, const string &logType, double severity) {
    logEntries.push_back({timestamp, logType, severity});
        cout << "No output\n";
        return;
}

void printStats(const vector<double>& severities) {
    if (severities.empty()) {
        cout << "No output\n";
        return;
    }
    double minSeverity = *min_element(severities.begin(), severities.end());
    double maxSeverity = *max_element(severities.begin(), severities.end());
    double meanSeverity = accumulate(severities.begin(), severities.end(), 0.0) / severities.size();
    
    cout << "Min: " << fixed << setprecision(2) << minSeverity
              << ", Max: " << maxSeverity
              << ", Mean: " << meanSeverity << '\n';
}

void queryByLogType(const string &logType) {
    vector<double> severities;
    for (const auto& entry : logEntries) {
        if (entry.logType == logType) {
            severities.push_back(entry.severity);
        }
    }
    printStats(severities);
}

void queryBeforeTimestamp(long long timestamp) {
   vector<double> severities;
    for (const auto& entry : logEntries) {
        if (entry.timestamp < timestamp) {
            severities.push_back(entry.severity);
        }
    }
    printStats(severities);
}

void queryAfterTimestamp(long long timestamp) {
   vector<double> severities;
    for (const auto& entry : logEntries) {
        if (entry.timestamp > timestamp) {
            severities.push_back(entry.severity);
        }
    }
    printStats(severities);
}

void queryBeforeLogTypeTimestamp(const string &logType, long long timestamp) {
    vector<double> severities;
    for (const auto& entry : logEntries) {
        if (entry.logType == logType && entry.timestamp < timestamp) {
            severities.push_back(entry.severity);
        }
    }
    printStats(severities);
}

void queryAfterLogTypeTimestamp(const string &logType, long long timestamp) {
    vector<double> severities;
    for (const auto& entry : logEntries) {
        if (entry.logType == logType && entry.timestamp > timestamp) {
            severities.push_back(entry.severity);
        }
    }
    printStats(severities);
}

string trim(const string &str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        int cmd;
        iss >> cmd;
        if (cmd == 1) {
            long long timestamp;
            string logType;
            double severity;
            char semicolon;
            iss >> timestamp >> semicolon;
            getline(iss, logType, ';');
            iss >> severity;
            logType = trim(logType);
            addLogEntry(timestamp, logType, severity);
        } else if (cmd == 2) {
            string logType;
            getline(iss >> ws, logType);
            logType = trim(logType);
            queryByLogType(logType);
        } else if (cmd == 3) {
            string dummy, when;
            long long timestamp;
            iss >> dummy >> when >> timestamp; 
            if (dummy == "BEFORE") {
                queryBeforeTimestamp(timestamp);
            } else if (dummy == "AFTER") {
                queryAfterTimestamp(timestamp);
            }
        } else if (cmd == 4) {
            string dummy, when, logType;
            long long timestamp;
            iss >> dummy >> logType >> when >> timestamp; 
            logType = trim(logType);
            if (when == "BEFORE") {
                queryBeforeLogTypeTimestamp(logType, timestamp);
            } else if (when == "AFTER") {
                queryAfterLogTypeTimestamp(logType, timestamp);
            }
        }
    }
    return 0;
}
