## Approach

This project implements a **Dynamic Multilevel Caching System** aimed at efficiently managing data across multiple cache levels. It supports two popular eviction policies: **Least Recently Used (LRU)** and **Least Frequently Used (LFU)**, which allows flexible data management based on usage patterns.

### Key Components

1. **CacheLevel Class**:
   - **Attributes**:
     - `size`: Maximum number of entries the cache level can hold.
     - `evictionPolicy`: Determines the eviction strategy ("LRU" or "LFU").
     - `cacheList`: A doubly linked list storing cache entries in order of usage, enabling efficient addition, removal, and reordering.
     - `cacheMap`: An unordered map for O(1) access to cache entries by key.
     - `frequencyMap`: Used in LFU policy to track how often each key is accessed.

   - **Methods**:
     - `get(string key)`: Retrieves the value associated with the key. Updates item order for LRU or increments frequency for LFU.
     - `put(string key, string value)`: Inserts a key-value pair into the cache. If full, calls `evict()` to remove an entry based on the eviction policy.
     - `evict()`: Removes an entry based on the defined policy—either the least recently used item (LRU) or the least frequently used item (LFU).
     - `display()`: Prints the current contents of the cache for debugging and visualization.

2. **MultilevelCacheSystem Class**:
   - **Attributes**:
     - `cacheLevels`: A vector storing multiple `CacheLevel` instances for easy addition and management.

   - **Methods**:
     - `addCacheLevel(int size, string evictionPolicy)`: Adds a new cache level with the specified size and eviction policy, allowing the cache system to scale.
     - `removeCacheLevel(int level)`: Removes a cache level by its index, enabling dynamic adjustment of the cache structure.
     - `get(string key)`: Searches through cache levels from L1 to the last level for the key. If found, it promotes the key to higher levels.
     - `put(string key, string value)`: Inserts data into L1. If L1 is full, it manages eviction as needed.
     - `displayCache()`: Displays the contents of all cache levels, providing a comprehensive view of the caching system's state.

### Data Flow

- **Data Retrieval**:
  - When a user requests data via `get()`, the system first checks L1. If the data is found, it is promoted to L1 and removed from lower levels to maintain freshness.

- **Data Insertion**:
  - New data is added using the `put()` method, which places the data directly into L1. If L1 is full, the eviction process is triggered to remove the least recently or least frequently used item, depending on the policy.

### Testing and Usage

The `main` function serves as a demonstration of the `MultilevelCacheSystem` in action, illustrating:
- The addition of cache levels with defined sizes and eviction policies.
- Inserting and retrieving data, including scenarios that trigger eviction.
- Displaying the current state of all cache levels to track their contents.

This implementation provides an efficient and scalable caching mechanism, making it well-suited for applications that require quick access to frequently used data while effectively managing memory.


 
 
