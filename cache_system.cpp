#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// Cache Level class for managing individual cache levels
class CacheLevel
{
public:
  int size;
  string evictionPolicy;
  list<pair<string, string>> cacheList;                                 // For LRU: a list to store cache items (key, value)
  unordered_map<string, list<pair<string, string>>::iterator> cacheMap; // Hash map for O(1) lookup
  unordered_map<string, int> frequencyMap;                              // For LFU: key -> frequency map

  CacheLevel(int s, string policy) : size(s), evictionPolicy(policy) {}

  // Get the value corresponding to the key
  string get(string key)
  {
    if (cacheMap.find(key) != cacheMap.end())
    {
      // For LRU, move the accessed item to the end (most recently used)
      if (evictionPolicy == "LRU")
      {
        cacheList.splice(cacheList.end(), cacheList, cacheMap[key]); // Move accessed element to end
      }
      // For LFU, increment frequency
      else if (evictionPolicy == "LFU")
      {
        frequencyMap[key]++;
      }
      return cacheMap[key]->second; // Return the value of the key
    }
    return ""; // If not found, return empty string
  }

  // Insert (key, value) pair into the cache
  void put(string key, string value)
  {
    if (cacheMap.find(key) != cacheMap.end())
    {
      // If the key is already present, update its value and adjust based on policy
      cacheMap[key]->second = value;
      if (evictionPolicy == "LRU")
      {
        cacheList.splice(cacheList.end(), cacheList, cacheMap[key]);
      }
      else if (evictionPolicy == "LFU")
      {
        frequencyMap[key]++;
      }
    }
    else
    {
      // If the cache is full, evict an item
      if (cacheList.size() >= size)
      {
        evict();
      }
      cacheList.push_back({key, value}); // Insert new item at the end
      cacheMap[key] = --cacheList.end(); // Store iterator in cacheMap
      if (evictionPolicy == "LFU")
      {
        frequencyMap[key] = 1; // Initialize frequency for LFU
      }
    }
  }

  // Evict an element based on the eviction policy (LRU or LFU)
  void evict()
  {
    if (evictionPolicy == "LRU")
    {
      // Evict the least recently used item (front of list)
      auto lru = cacheList.front();
      cacheMap.erase(lru.first);
      cacheList.pop_front();
    }
    else if (evictionPolicy == "LFU")
    {
      // Evict the least frequently used item
      string leastFrequentKey = min_element(frequencyMap.begin(), frequencyMap.end(),
                                            [](const pair<string, int> &a, const pair<string, int> &b)
                                            {
                                              return a.second < b.second;
                                            })
                                    ->first;
      cacheList.erase(cacheMap[leastFrequentKey]);
      cacheMap.erase(leastFrequentKey);
      frequencyMap.erase(leastFrequentKey);
    }
  }

  // Display the cache contents
  void display()
  {
    cout << "Cache (size " << size << ", " << evictionPolicy << "): ";
    for (auto &it : cacheList)
    {
      cout << "(" << it.first << ": " << it.second << ") ";
    }
    cout << endl;
  }
};

// Multilevel Cache System class
class MultilevelCacheSystem
{
public:
  vector<CacheLevel *> cacheLevels; // Dynamic list of cache levels

  // Add a new cache level with specified size and eviction policy
  void addCacheLevel(int size, string evictionPolicy)
  {
    cacheLevels.push_back(new CacheLevel(size, evictionPolicy));
    cout << "Added cache level with size " << size << " and eviction policy " << evictionPolicy << endl;
  }

  // Remove cache level at specified index
  void removeCacheLevel(int level)
  {
    if (level < cacheLevels.size())
    {
      cacheLevels.erase(cacheLevels.begin() + level);
      cout << "Removed cache level " << level + 1 << endl;
    }
    else
    {
      cout << "Cache level " << level + 1 << " does not exist." << endl;
    }
  }

  // Get data from the cache system
  string get(string key)
  {
    for (int i = 0; i < cacheLevels.size(); i++)
    {
      string value = cacheLevels[i]->get(key);
      if (!value.empty())
      {
        cout << "Found " << key << " at level " << i + 1 << endl;
        // Move the data to higher cache levels (promote to L1)
        for (int j = i; j > 0; j--)
        {
          cacheLevels[j - 1]->put(key, value);
          cacheLevels[j]->cacheMap.erase(key); // Remove from lower level
        }
        return value;
      }
    }
    cout << key << " not found in cache." << endl;
    return "";
  }

  // Insert key-value pair into L1 cache
  void put(string key, string value)
  {
    if (!cacheLevels.empty())
    {
      cacheLevels[0]->put(key, value);
      cout << "Inserted " << key << ": " << value << " into level 1" << endl;
    }
  }

  // Display all cache levels
  void displayCache()
  {
    for (int i = 0; i < cacheLevels.size(); i++)
    {
      cout << "Level " << i + 1 << ": ";
      cacheLevels[i]->display();
    }
  }
};

// Main function for testing
int main()
{
  MultilevelCacheSystem cacheSystem;

  // Add cache levels
  cacheSystem.addCacheLevel(3, "LRU"); // Add L1 with size 3 and LRU policy
  cacheSystem.addCacheLevel(2, "LFU"); // Add L2 with size 2 and LFU policy

  // Insert data
  cacheSystem.put("A", "1");
  cacheSystem.put("B", "2");
  cacheSystem.put("C", "3");

  // Retrieve data
  cacheSystem.get("A"); // Returns "1" from L1

  // Insert new data (eviction happens in L1)
  cacheSystem.put("D", "4"); // L1 is full, evicts least recently used

  // Fetch from L2 (C was moved to L2)
  cacheSystem.get("C"); // Fetches from L2 and promotes to L1

  // Display cache contents
  cacheSystem.displayCache();

  return 0;
}
