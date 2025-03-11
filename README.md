# StreamGale (Work In Progress) 🌪️

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![C++](https://img.shields.io/badge/language-C%2B%2B-00599C)

**StreamGale** is a high-performance, distributed real-time stream processing engine written in **C++** and **Rust**. Inspired by **Apache Storm**, it enables developers to process unbounded streams of data with low latency, scalability, and fault tolerance.

## 🚀 Features
- **Real-time Processing** – Processes data streams with ultra-low latency.
- **Scalability** – Distributed architecture with parallel processing.
- **Fault Tolerance** – Ensures continuous processing even in case of node failures.
- **Flexible Topology** – Define custom processing pipelines with **Spouts** (data sources) and **Bolts** (processing nodes).
- **Machine Learning Support** – Integrate real-time ML models with **ONNX, TensorFlow, or PyTorch**.
- **Multi-Language Support** – Extendable to support Python, Java, and more.
- **Lightweight** – Optimized for high throughput with minimal resource usage.

## 🔧 Installation
### Prerequisites
- **C++17 or later**
- **CMake**
- **Boost Libraries** (for networking and threading)
- **ZeroMQ** (for distributed messaging)
- **ONNX Runtime** (for machine learning inference)

### Build from Source
```bash
git clone https://github.com/yourusername/StreamGale.git
cd StreamGale
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## 📜 Quick Start

### Define a Simple Topology
Create a simple **word count topology** using StreamGale:

```cpp
#include "streamgale.h"

class WordSpout : public Spout {
public:
    void emit(Stream &stream) override {
        std::vector<std::string> words = {"hello", "world", "stream", "gale"};
        for (const auto &word : words) {
            stream.emit({word});
        }
    }
};

class CountBolt : public Bolt {
private:
    std::unordered_map<std::string, int> wordCount;
public:
    void process(const Tuple &tuple, Stream &stream) override {
        std::string word = tuple.getValue(0);
        wordCount[word]++;
        std::cout << "Word: " << word << ", Count: " << wordCount[word] << std::endl;
    }
};

int main() {
    TopologyBuilder builder;
    builder.setSpout("word-spout", new WordSpout());
    builder.setBolt("count-bolt", new CountBolt()).shuffleGrouping("word-spout");

    StreamGale::submitTopology("word-count-topology", builder.createTopology());
    return 0;
}
```

## 🤖 Machine Learning Integration
StreamGale supports real-time **machine learning inference** using **ONNX Runtime, TensorFlow, or PyTorch**.

### Example: Real-time Sentiment Analysis with ONNX
```cpp
#include "onnxruntime/core/providers/cpu/cpu_provider_factory.h"
#include "onnxruntime/core/session/onnxruntime_cxx_api.h"

class SentimentBolt : public Bolt {
private:
    Ort::Env env;
    Ort::Session session;
public:
    SentimentBolt() : env(ORT_LOGGING_LEVEL_WARNING, "SentimentAnalysis"),
                      session(env, "sentiment_model.onnx", Ort::SessionOptions{}) {}

    void process(const Tuple &tuple, Stream &stream) override {
        std::string text = tuple.getValue(0);
        int sentiment_score = infer(text);
        stream.emit({text, sentiment_score});
    }

    int infer(const std::string &text) {
        // Run ONNX model inference (simplified example)
        return text.find("good") != std::string::npos ? 1 : 0;
    }
};
```

## 📚 Architecture Overview
### **Core Components**
- **Spout:** Data sources that emit tuples (e.g., from Kafka, files, sensors).
- **Bolt:** Processing units that transform, filter, and aggregate data.
- **Topology:** A DAG (Directed Acyclic Graph) defining the flow of data.
- **Stream:** The communication channel between spouts and bolts.

## 🛠️ Configuration
Modify the `config.yaml` file to adjust settings:
```yaml
workers: 4
logging_level: INFO
network:
  port: 5555
  protocol: zmq
```

## 🚀 Roadmap
- [ ] Distributed Cluster Support
- [ ] Persistent State Management
- [ ] Trident API for Exactly-Once Processing
- [ ] Kubernetes & Docker Integration
- [ ] Python API for User-Friendly Development
- [ ] Advanced ML Pipeline Support (Streaming ML Inference)

## 🤝 Contributing
Contributions are welcome! Please open an issue or submit a pull request.

## 📝 License
**StreamGale** is licensed under the **MIT License**.

---
### 🌟 Star the repo if you like it! ⭐
