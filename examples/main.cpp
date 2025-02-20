#include <iostream>
#include <thread>
#include <chrono>
#include <storm/config.h>
#include <storm/local_cluster.h>
#include <storm/topology_builder.h>
#include "spouts/WordReader.h"
#include "bolts/WordNormalizer.h"
#include "bolts/WordCounter.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <wordsFile>" << std::endl;
        return 1;
    }

    // Topology Definition
    storm::TopologyBuilder builder;
    builder.setSpout("word-reader", std::make_shared<WordReader>());
    builder.setBolt("word-normalizer", std::make_shared<WordNormalizer>())
           .shuffleGrouping("word-reader");
    builder.setBolt("word-counter", std::make_shared<WordCounter>(), 2)
           .fieldsGrouping("word-normalizer", {"word"});

    // Configuration
    storm::Config conf;
    conf["wordsFile"] = argv[1];
    conf.setDebug(false);
    conf[storm::Config::TOPOLOGY_MAX_SPOUT_PENDING] = 1;

    // Run the topology
    storm::LocalCluster cluster;
    cluster.submitTopology("Getting-Started-Topology", conf, builder.createTopology());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    cluster.shutdown();

    return 0;
}

