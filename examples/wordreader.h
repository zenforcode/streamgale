#include <iostream>
#include <fstream>
#include <thread>
#include <storm/spout.h>
#include <storm/tuple.h>

class WordReader : public storm::Spout {
private:
    std::ifstream fileReader;
    bool completed = false;

public:
    void open(storm::Config conf, storm::TopologyContext& context, storm::SpoutOutputCollector& collector) override {
        std::string fileName = conf["wordsFile"];
        fileReader.open(fileName);

        if (!fileReader.is_open()) {
            throw std::runtime_error("Error reading file [" + fileName + "]");
        }
    }

    void nextTuple() override {
        if (completed) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }

        std::string line;
        if (std::getline(fileReader, line)) {
            storm::Tuple tuple({line});
            emit(tuple);
        } else {
            completed = true;
        }
    }

    void ack(const std::string& msgId) override {
        std::cout << "OK: " << msgId << std::endl;
    }

    void fail(const std::string& msgId) override {
        std::cout << "FAIL: " << msgId << std::endl;
    }

    void close() override {
        if (fileReader.is_open()) {
            fileReader.close();
        }
    }

    void declareOutputFields(storm::OutputFieldsDeclarer& declarer) override {
        declarer.declare({"line"});
    }
};

