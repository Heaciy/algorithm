#include<iostream>
#include<vector>
#include <unordered_map>
using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        int len = nums.size();
        for(int i=0;i<len-1;i++)
        for (int j = i+1; j < len; j++)
        {
            if(nums[i]==target-nums[j])
            return {i,j};
        }
        return {};
    }

    vector<int> twoSum1(vector<int> &nums, int target){
        unordered_map<int, int> m;

        for (int i = 0; i < nums.size(); i++)
            m[nums[i]] = i; //向map中添加元素

        for (int i = 0; i < nums.size(); i++) {
            if (m.find(target - nums[i]) != m.end() &&
                m[target - nums[i]] != i) //如果m中存在对应的键值，并且不为i
                return {i, m[target - nums[i]]};
        }
        return {};
    }

    vector<int> twoSum2(vector<int> &nums, int target){
        unordered_map<int, int> m;

        for (int i = 0; i < nums.size(); i++) {
            if (m.find(target - nums[i]) != m.end()) // m中存在对应的键值
                return {
                    m[target - nums[i]],
                    i}; //因为i为较大的元素，此时添加进去的键值都还小于i，所以i在后面

            m[nums[i]] = i; //向map中添加元素
        }
        return {};
    }
};