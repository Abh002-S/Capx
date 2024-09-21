## Approach

This project implements a **Dynamic Multilevel Caching System** designed to manage data efficiently across multiple cache levels. The system supports two popular eviction policies: **Least Recently Used (LRU)** and **Least Frequently Used (LFU)**, allowing for flexible data management based on usage patterns.

### Key Components

1. **CacheLevel Class**:
   - **Attributes**:
     - `size`: Defines the maximum number of entries that can be stored in this cache level.
     - `evictionPolicy`: Specifies the eviction policy (either "LRU" or "LFU") for this cache level.
     - `cacheList`: A doubly linked list that stores cache entries in order of usage. This allows for efficient addition, removal, and reordering of items.
     - `cacheMap`: An unordered map (hash table) that provides O(1) access to cache entries using their keys.
     - `frequencyMap`: An unordered map used in LFU policy to track how often each key is accessed.

   - **Methods**:
     - `get(string key)`: Retrieves the value for the given key. If the key is found, it updates the order of items based on the eviction policy. If using LFU, it increments the access frequency.
     - `put(string key, string value)`: Inserts a new key-value pair into the cache. If the cache is full, it invokes the `evict()` method to remove an entry based on the eviction policy.
     - `evict()`: Removes an entry according to the defined eviction policy. For LRU, it removes the least recently used item from the front of the list. For LFU, it finds and removes the least frequently used item.
     - `display()`: Prints the contents of the cache for debugging and visualization purposes.

2. **MultilevelCacheSystem Class**:
   - **Attributes**:
     - `cacheLevels`: A vector that dynamically holds multiple instances of `CacheLevel`, allowing for easy addition and management of various cache levels.

   - **Methods**:
     - `addCacheLevel(int size, string evictionPolicy)`: Adds a new cache level to the system with the specified size and eviction policy. This allows for flexible scaling of the cache system.
     - `removeCacheLevel(int level)`: Removes a cache level at the specified index, providing the ability to dynamically adjust the cache structure as needed.
     - `get(string key)`: Iterates through cache levels from L1 down to the last level to find the key. If found, it promotes the key to higher levels and returns its value.
     - `put(string key, string value)`: Inserts data into the L1 cache level. If the level is full, it handles eviction accordingly.
     - `displayCache()`: Displays the contents of all cache levels, providing a clear view of the current state of the caching system.

### Data Flow

- **Data Retrieval**:
  - When a user requests data using the `get()` method, the system starts by checking the highest-priority cache level (L1). If the data is found, it is promoted to L1 and removed from lower levels to maintain freshness.

- **Data Insertion**:
  - New data is added via the `put()` method, which places the data directly into L1. If L1 is full, the eviction process is triggered, removing the least recently or least frequently used item depending on the policy in place.

### Testing and Usage

The `main` function serves as a testing ground, illustrating how to utilize the `MultilevelCacheSystem`. It demonstrates:
- Adding cache levels with specific sizes and eviction policies.
- Inserting data into the cache.
- Retrieving data, including scenarios that trigger eviction.
- Displaying the state of all cache levels to track current contents.

This implementation provides an efficient and scalable caching mechanism, making it suitable for applications that require quick access to frequently used data while managing memory effectively.


 
 
