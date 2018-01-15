#include <iostream>
#include <climits>
#include <string>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include "helper.h"
#include <deque>

using namespace std;
using namespace sdsl;

#define SEQUENCE_SEPARATOR_INT_VALUE (int('A'))

struct Node {
	uint64_t len;
	uint64_t lb;
	uint64_t size;
	uint64_t suffix_lb;

	Node(): len(0), lb(0), size(0), suffix_lb(0) {}; 
	Node(uint64_t len, uint64_t lb, uint64_t size, uint64_t suffix_lb) : len(len), lb(lb), size(size), suffix_lb(suffix_lb) {}
};

string S = "";
wt_blcd<> wt;

void createBitVectors(int k, string BWT, vector<Node>& graph, deque<uint64_t>& Q, bit_vector& Bl, bit_vector& Br) {
	// Construct WT used for C array from BWT
	construct_im(wt, BWT, 1);

	// Construct LCP from sequence
	lcp_bitcompressed<> lcp;
	construct_im(lcp, S, 1);

	// Compute the C array.
	uint64_t cSum = 0;

	vector<uint64_t> cArray(UCHAR_MAX, 0);

	for(int i = 0; i <= UCHAR_MAX; i++) {
		if(wt.rank(wt.size(), i) != 0) {
			cArray[i] = cSum;
			cSum += wt.rank(wt.size(), i);
		}
	}

	Bl = bit_vector(BWT.size(), 0);
	Br = bit_vector(BWT.size(), 0);

	cout << lcp.size() << endl;
	cout << S.size() << endl;
	cout << BWT.size() << endl;

	bool open = false;
	uint64_t lb = 1;
	uint64_t kIndex = 0;
	uint64_t lastDiff = 0;
	uint64_t counter = 0;

	//cout << lcp << endl;

	//vector<int> lcpFull(lcp.size()+1);

	uint64_t i;

	//cout << lcpFull << endl;

	//vector<char> BWTshifted(BWT.size()+1);

	//cout << BWTshifted.size() << endl;

	for(int i = 1; i <= lcp.size(); i++) {
		cArray[BWT[i-1]]++;
		if(lcp[i] >= k) {
		//	cout << "last lcp is " << lcpFull[i] << " and k is " << k << endl;
			open = true;
			kIndex = (lcp[i] == k ? i : kIndex);
		} else {
			if(open) {
				if(kIndex > lb) {
					Br[lb] = 1;
					Br[i-1] = 1;
					graph.push_back(Node(k, lb, i - lb, lb));
					Q.push_back(counter++);
				}
				if(lastDiff > lb) {
					for(int j = lb; j < i; j++) {
						char c = BWT[j];
//						cout << c  << "----" << cArray[c] << endl;
						if((c != 0) && (c != '%')) {
							Bl[cArray[c]-1] = 1;
						}
					}
				}
				open = false;
			}
			lb = i;
		}
            //                  std::cout << "lastDiff is "<< lastDiff << " and k_index is " << kIndex << " and lb is " << lb << std::endl;
		if(BWT[i] != BWT[i-1]) {
			lastDiff = i;
//			 std::cout << "lastDiff is "<< lastDiff << endl;
		}
	}
	open = false;

	for(int i = 0; i < lcp.size(); i++) {
		if(open) {
			Bl[i] = 0;
			if(Br[i]) open = false;
		} else if(Br[i]) {
			Bl[i] = 0;
			open = true;
		}
	}

	//cout << counter << endl;

	//cout << cArray << endl;

	//cout << "Vector Bl: " << Bl << endl;
	//cout << "Vector Br: " << Br << endl;
}

static bool cmp(const Node &a, const Node &b) {
    return a.lb < b.lb;
}

void createCompressedGraph(int k, string BWT, bool originalPrint) {
    vector<Node> graph;
    deque<uint64_t> Q;
    bit_vector Bl, Br;

    createBitVectors(k, BWT, graph, Q, Bl, Br);

    bit_vector::rank_1_type Br_rank(&Br);
    bit_vector::rank_1_type Bl_rank(&Bl);
 
    uint64_t rightMax = Br_rank(BWT.size()+1)/2.;
    uint64_t leftMax = Bl_rank(BWT.size()+1);

   	cout << "Right max: " << rightMax << endl;
   	cout << "Left max: " << leftMax << endl;

   	vector<uint64_t> cArray(UCHAR_MAX, 0);

   	int cSum = 0;

	for(int i = 0; i <= UCHAR_MAX; i++) {
		if(wt.rank(wt.size(), i) != 0) {
			cArray[i] = cSum;
			cSum += wt.rank(wt.size(), i);
		}
	}

    graph.resize(rightMax + leftMax + cArray['A']);

	for(int s = 0; s < cArray['A']; s++) {
		int id = rightMax + leftMax + s;
		//cout << "id is " << id << endl;
		graph[id] = Node(1, s, 1, s);
		Q.push_back(id);
		Bl[s] = 0;
	}

	// cout << "Queue size " << Q.size() << endl;

	// cout << "wt sigma is " << wt.sigma << endl;

	uint64_t quantity;
	vector<uint8_t> list(wt.sigma);
    vector<uint64_t> rank_c_i(wt.sigma);
    vector<uint64_t> rank_c_j(wt.sigma);

    // cout << wt << endl;

    for(int i = 0; i < wt.size(); i++) {
    	// if(wt[i] == 0) {cout << i << endl;}
    }

	int count = 0;
	uint64_t id = 0;

	uint64_t queueStartSize = Q.size();

	while(!Q.empty()) {
		if(count < queueStartSize) {
			id = Q.front();
			Q.pop_front();
		} else {
			id = Q.back();
			Q.pop_back();
		}

		count++;

		bool extendable;

		uint64_t lb = graph.at(id).lb;
		uint64_t rb = lb + graph.at(id).size - 1;

		uint64_t l = 0;
		uint64_t r = 0;
		uint64_t len = graph.at(id).len;
	
		do {
			extendable = false;	

			interval_symbols(wt, lb, rb+1, quantity, list, rank_c_i, rank_c_j);

			for(uint64_t i = 0; i < quantity; i++) {
				char c = list[i];

				//cout << "c is " << c << " and cArray is " << cArray[c] << endl;

				l = cArray[c] + rank_c_i[i];
				r = cArray[c] + rank_c_j[i] - 1;

				//std::cout << "left bound is " << l << " and right bound is " << r << " and size is " << quantity << std::endl;

				uint64_t ones = Br_rank(l);

				if(!(ones % 2) && !Br[l]) {
					if(c != 0 && c != '%') {
						if(quantity == 1) {
							extendable = true;
							graph.at(id).lb = l;
							len++;
							graph.at(id).len = len;
							lb = l;
							rb = r;
						} else {
							uint64_t newId = rightMax + Bl_rank(l);

							graph[newId] = Node(k, l, r-l+1, l);

							Q.push_back(newId);
						}
					} else {
						graph.at(id).lb = lb;
						graph.at(id).len = len;						
					}
				}
			}

		} while(extendable);
	}

		vector<Node> G(graph.size());
		for(int i = 0; i < graph.size(); ++i) {
			G.push_back(graph[i]);
		}
		sort(G.begin(), G.end(), cmp);

		for (int i = 0; i < G.size(); ++i) {
			if(!G[i].len) {
				continue;
			} else if (originalPrint) {
				cout << G[i].len << " " <<  G[i].lb << endl;
			} else {
				cout << G[i].len << " " <<  G[i].lb << " " << G[i].size << " " << G[i].suffix_lb << endl;
			};
		}
}

int main(int argc, char** argv) {
	
	bool originalPrint = false;
	// Check input parameters
	if(argc != 3 && argc != 4) {
		cerr << "Error in passing parameters! The program should be called with: ./program_name input/input_file_name.fa -k=<Integer> --orginalPrint" << endl;
		return 1;
	}

	if(Helper::readInputFa(argv[1], S)) {
		cerr << "Error in reading input_file_name.fa!" << endl;
		return 1;
	}

	//cout << S << endl;

	string kString = argv[2];
	int k = stoi(kString.substr(kString.size() - 3, kString.size()));

	if ((argc == 4) && ((string)argv[3] == "--orginalPrint")) {
 		orginalPrint = true;
 	}

	//cout << k << endl;

	// constructing SA
	csa_bitcompressed<> csa;
    construct_im(csa, S, 1);

    //cout << csa << endl << endl;

	// BWT of S
    string bwt = util::to_string(csa.bwt);

    //cout << bwt << endl;

	createCompressedGraph(k, bwt, originalPrint);

	return 0;
}