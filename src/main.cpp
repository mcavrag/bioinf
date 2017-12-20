#include <iostream>
#include <string>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sais.hxx>
#include "helper.h"

using namespace std;
using namespace sdsl;

struct Node {
	uint64_t id;
	uint64_t lb;
	uint64_t rb;
	uint64_t len;
	uint64_t suffix_lb;

	Node(uint64_t id, uint64_t lb, uint64_t rb, uint64_t len, uint64_t suffix_lb) : id(id), lb(lb), rb(rb), len(len), suffix_lb(suffix_lb) {}
};

string S = "";

void createBitVectors(uint64_t k, string BWT, vector<Node>& graph, queue<uint64_t>& Q, bit_vector& Bl, bit_vector& Br)
{
	lcp_bitcompressed<> lcp;
	construct_im(lcp, S, 1);

	//cout << lcp << endl;
}

void createCompressedGraph(uint64_t k, string BWT)
{
    vector<Node> graph;
    queue<uint64_t> Q;
    bit_vector Bl, Br;

    createBitVectors(k, BWT, graph, Q, Bl, Br);
}

int main(int argc, char** argv)
{
	// Check input parameters
	if(argc != 4)
	{
		cerr << "Error in passing parameters! The program should be called with: ./program_name input/input_file_name.fa output_file_name input/file_name_input.k" << endl;
		return 1;
	}

	if(Helper::readInputFa(argv[1], S))
	{
		cerr << "Error in reading input_file_name.fa!" << endl;
		return 1;
	}

	//cout << S << endl;

	uint64_t k;

	if(Helper::readInputK(argv[3], k))
	{
		cerr << "Error in reading file_name_input.k" << endl;
		return 1;
	}

	//cout << k << endl;

	// constructing SA
	csa_bitcompressed<> csa;
    construct_im(csa, S, 1);

    //cout << csa << endl << endl;

	// BWT of S
    string bwt = util::to_string(csa.bwt);

    //cout << bwt << endl;

	createCompressedGraph(k, bwt);

	return 0;
}