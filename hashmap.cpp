#include <bits/stdc++.h>
using namespace std;

class MyHashMap {
private:
    static const int BUCKET_COUNT = 10007;
    vector<list<pair<int,int>>> buckets;
    int hash(int key) const {
        return key % BUCKET_COUNT;
    }

public:
    MyHashMap() : buckets(BUCKET_COUNT) { }
    void put(int key, int value) {
        int idx = hash(key);
        for (auto &kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        buckets[idx].emplace_back(key, value);
    }

    int get(int key) {
        int idx = hash(key);
        for (const auto &kv : buckets[idx]) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        return -1;
    }

    void remove(int key) {
        int idx = hash(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->first == key) {
                buckets[idx].erase(it);
                return;
            }
        }
    }
};

int main() {
    MyHashMap obj;

    obj.put(1, 10);
    obj.put(2, 20);
    cout << obj.get(1) << endl;
    cout << obj.get(3) << endl;
    obj.put(2, 30);
    cout << obj.get(2) << endl;
    obj.remove(2);
    cout << obj.get(2) << endl;

    return 0;
}
