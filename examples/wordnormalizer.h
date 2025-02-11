#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <storm/bolt.h>
#include <storm/tuple.h>

class WordNormalizer : public storm::Bolt {
private:
    storm::OutputCollector collector;

public:
    void prepare(storm::Config conf, storm::TopologyContext& context, storm::OutputCollector& collector) override {
        this->collector = collector;
    }

    void execute(const storm::Tuple& input) override {
        std::string sentence = input.getString(0);
        std::vector<std::string> words = splitAndNormalize(sentence);

        for (const auto& word : words) {
            if (!word.empty()) {
                storm::Tuple newTuple({word});
                collector.emit(newTuple);
            }
        }
        collector.ack(input);
    }

    std::vector<std::string> splitAndNormalize(const std::string& sentence) {
        std::vector<std::string> words;
        std::stringstream ss(sentence);
        std::string word;

        while (ss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
        }
        return words;
    }

    void declareOutputFields(storm::OutputFieldsDeclarer& declarer) override {
        declarer.declare({"word"});
    }

    void cleanup() override {}
};

