#ifndef ARCS_H
#define ARCS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <utility> 
#include <vector>
#include <iterator>
#include <time.h> 
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include "Common/Uncompress.h"
#include "DataLayer/FastaReader.h"
#include "DataLayer/FastaReader.cpp"
// using sparse hash maps for k-merization
#include <google/sparse_hash_map>


namespace ARCS {

    /**
     * Parameters controlling ARCS run
     */
    struct ArcsParams {

        std::string file;
        std::string fofName;
        int seq_id;
        int min_reads;
	int k_value;
	int k_shift; 
        int min_links;
        int min_size;
        std::string base_name;
        int min_mult;
        int max_mult;
        int max_degree;
        int end_length;
        float error_percent;
        int verbose;

        ArcsParams() : file(), fofName(), seq_id(98), min_reads(5), k_value(30), k_shift(1), min_links(0), min_size(500), base_name(""), min_mult(50), max_mult(10000), max_degree(0), end_length(0), error_percent(0.05), verbose(0) {}

    };

	typedef std::string Kmer; 

    /* ContigKMap: <k-mer, pair(contig id, bool), hash<k-mer>, eqstr>
     * 	k-mer = string sequence
     *  contig id = string 
     *  bool = True for Head; False for Tail
     *  eqstr = equal key 
     */ 
	typedef google::sparse_hash_map<Kmer, pair<std::string, bool>> ContigKMap; 

    /* ScafMap: <pair(scaffold id, bool), count>, cout =  # times index maps to scaffold (c), bool = true-head, false-tail*/
    typedef std::map<std::pair<std::string, bool>, int> ScafMap;
    /* IndexMap: key = index sequence, value = ScafMap */
    typedef std::unordered_map<std::string, ScafMap> IndexMap; 
    /* PairMap: key = pair(first < second) of scaf sequence id, value = num links*/
    typedef std::map<std::pair<std::string, std::string>, std::vector<int>> PairMap; 

    struct VertexProperties {
        std::string id;
    };

    /* Orientation: 0-HH, 1-HT, 2-TH, 3-TT */
    struct EdgeProperties {
        int orientation;
        int weight;
        EdgeProperties(): orientation(0), weight(0) {}
    };

	typedef boost::undirected_graph<VertexProperties, EdgeProperties> Graph;
    typedef std::unordered_map<std::string, Graph::vertex_descriptor> VidVdesMap;
    typedef boost::graph_traits<ARCS::Graph>::vertex_descriptor VertexDes;
}

#endif
