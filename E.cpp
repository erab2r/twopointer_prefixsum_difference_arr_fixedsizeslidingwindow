#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

template <typename T>
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    pbds<pair<long long,int>> left, right;
    long long sum_left = 0, sum_right = 0;

    auto add = [&](pair<long long,int> p){
        left.insert(p);
        sum_left += p.first;
        // balance
        while(left.size() > (k+1)/2){
            auto it = prev(left.end());
            sum_left -= it->first;
            sum_right += it->first;
            right.insert(*it);
            left.erase(it);
        }
    };

    auto remove = [&](pair<long long,int> p){
        if(left.find(p) != left.end()){
            left.erase(p);
            sum_left -= p.first;
        } else {
            right.erase(p);
            sum_right -= p.first;
        }
        // balance
        while(left.size() < (k+1)/2){
            auto it = right.begin();
            sum_right -= it->first;
            sum_left += it->first;
            left.insert(*it);
            right.erase(it);
        }
    };

    for(int i=0;i<k;i++) add({a[i],i});

    auto get_cost = [&](){
        long long md = prev(left.end())->first;
        return md*left.size() - sum_left + sum_right - md*right.size();
    };

    cout << get_cost() << " ";

    for(int i=k;i<n;i++){
        add({a[i],i});
        remove({a[i-k],i-k});
        cout << get_cost() << " ";
    }
    cout << "\n";
}
