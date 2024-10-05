The **Proxy Pattern** is a structural design pattern that provides an object representing another object. It acts as an intermediary, controlling access to the original object while adding additional functionalities like lazy initialization, access control, logging, etc.

The Proxy Pattern is useful when you want to:
- Control access to an object.
- Add additional behavior (like caching or logging) without modifying the original object's code.
- Delay resource-intensive operations until they're actually needed.

---

### Key Concepts
- **Subject**: The interface that both the Real Subject and the Proxy implement.
- **Real Subject**: The actual object that the proxy represents.
- **Proxy**: The intermediary object that controls access to the Real Subject.

---

### Example 1: Image Proxy

In this example, the Proxy Pattern is used to control access to a heavy image object that might require significant resources to load. The proxy can load the image only when needed.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Subject Interface
class Image {
public:
    virtual void display() = 0;
};

// Real Subject
class RealImage : public Image {
private:
    std::string filename;

public:
    RealImage(const std::string& name) : filename(name) {
        loadFromDisk();
    }

    void loadFromDisk() {
        std::cout << "Loading " << filename << " from disk.\n";
    }

    void display() override {
        std::cout << "Displaying " << filename << ".\n";
    }
};

// Proxy
class ProxyImage : public Image {
private:
    RealImage* realImage;
    std::string filename;

public:
    ProxyImage(const std::string& name) : realImage(nullptr), filename(name) {}

    void display() override {
        // Lazy initialization
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage; // Clean up
    }
};

// Client code
int main() {
    Image* image = new ProxyImage("example.jpg");

    // Image is loaded from disk only when display() is called
    image->display();
    std::cout << "\n--- Second time calling display() ---\n";
    image->display(); // No loading from disk again

    delete image; // Clean up

    return 0;
}
```

#### Explanation:
- **Subject**: The `Image` interface defines the method `display()`.
- **Real Subject**: The `RealImage` class implements the `Image` interface and has the actual image loading logic.
- **Proxy**: The `ProxyImage` class holds a reference to a `RealImage` and loads it only when `display()` is called for the first time (lazy initialization).
- **Client**: The client interacts only with the `ProxyImage`, benefiting from the controlled access to the `RealImage`.

---

### Example 2: Virtual Proxy for Network Access

In this example, the Proxy Pattern is used to control access to a network resource. The proxy checks whether the client has permission to access the resource before forwarding the request.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Subject Interface
class NetworkResource {
public:
    virtual void access() = 0;
};

// Real Subject
class RealNetworkResource : public NetworkResource {
public:
    void access() override {
        std::cout << "Accessing sensitive network resource.\n";
    }
};

// Proxy
class ProxyNetworkResource : public NetworkResource {
private:
    RealNetworkResource* realResource;
    std::string userRole;

public:
    ProxyNetworkResource(const std::string& role) : realResource(new RealNetworkResource()), userRole(role) {}

    void access() override {
        if (userRole == "admin") {
            realResource->access();
        } else {
            std::cout << "Access denied: insufficient permissions.\n";
        }
    }

    ~ProxyNetworkResource() {
        delete realResource; // Clean up
    }
};

// Client code
int main() {
    NetworkResource* adminResource = new ProxyNetworkResource("admin");
    NetworkResource* userResource = new ProxyNetworkResource("user");

    // Admin has access
    adminResource->access();

    // Regular user does not have access
    userResource->access();

    delete adminResource; // Clean up
    delete userResource; // Clean up

    return 0;
}
```

#### Explanation:
- **Subject**: The `NetworkResource` interface defines the method `access()`.
- **Real Subject**: The `RealNetworkResource` class implements the `NetworkResource` interface and contains the logic to access the resource.
- **Proxy**: The `ProxyNetworkResource` class checks the user’s role before allowing access to the real resource.
- **Client**: The client interacts with the proxy, which ensures that only users with the proper permissions can access the sensitive network resource.

---

### Example 3: Caching Proxy

In this example, a caching proxy is used to avoid redundant data fetching. If a request for the same data is made multiple times, the proxy returns the cached data instead of querying the real subject.

#### Code Example:
```cpp
#include <iostream>
#include <string>
#include <unordered_map>

// Subject Interface
class Data {
public:
    virtual std::string fetchData(int id) = 0;
};

// Real Subject
class RealData : public Data {
public:
    std::string fetchData(int id) override {
        std::cout << "Fetching data for ID " << id << " from database...\n";
        return "Data for ID " + std::to_string(id);
    }
};

// Proxy
class ProxyData : public Data {
private:
    RealData* realData;
    std::unordered_map<int, std::string> cache;

public:
    ProxyData() : realData(new RealData()) {}

    std::string fetchData(int id) override {
        if (cache.find(id) != cache.end()) {
            std::cout << "Returning cached data for ID " << id << ".\n";
            return cache[id];
        } else {
            std::string data = realData->fetchData(id);
            cache[id] = data; // Cache the fetched data
            return data;
        }
    }

    ~ProxyData() {
        delete realData; // Clean up
    }
};

// Client code
int main() {
    Data* dataProxy = new ProxyData();

    // Fetching data multiple times
    std::cout << dataProxy->fetchData(1) << std::endl;
    std::cout << dataProxy->fetchData(1) << std::endl; // This should hit the cache
    std::cout << dataProxy->fetchData(2) << std::endl;

    delete dataProxy; // Clean up

    return 0;
}
```

#### Explanation:
- **Subject**: The `Data` interface defines the method `fetchData()`.
- **Real Subject**: The `RealData` class implements the `Data` interface and fetches the data from a database (simulated here).
- **Proxy**: The `ProxyData` class caches the results of previously fetched data, returning cached data if available.
- **Client**: The client interacts with the proxy, benefiting from the cached data and reducing the number of database queries.

---

### Key Points:
- The **Proxy Pattern** provides controlled access to an object, allowing for additional behavior (e.g., caching, access control, or logging) without modifying the original object's code.
- It is particularly useful when you need to add functionality such as lazy initialization, access control, logging, or caching to an object.
- The pattern maintains a clean separation of concerns by encapsulating additional behavior in the proxy while keeping the real subject focused on its core functionality.
