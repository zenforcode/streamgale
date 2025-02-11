#include <iostream>
#include <unordered_map>
#include <string>
#include <storm/bolt.h>
#include <storm/tuple.h>

class WordCounter : public storm::Bolt {
private:
    int id;
    std::string name;
    std::unordered_map<std::string, int> counters;
    storm::OutputCollector collector;

public:
    void prepare(storm::Config conf, storm::TopologyContext& context, storm::OutputCollector& collector) override {
        this->collector = collector;
        this->name = context.getThisComponentId();
        this->id = context.getThisTaskId();
    }

    void execute(const storm::Tuple& input) override {
        std::string word = input.getString(0);

        // Increment word count in map
        counters[word]++;

        // Acknowledge tuple
        collector.ack(input);
    }

    void cleanup() override {
        std::cout << "-- Word Counter [" << name << "-" << id << "] --" << std::endl;
        for (const auto& entry : counters) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }

    void declareOutputFields(storm::OutputFieldsDeclarer& declarer) override {}
};

