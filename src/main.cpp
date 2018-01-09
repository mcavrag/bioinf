#include <iostream>
#include <climits>
#include <string>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include "helper.h"
#include <typeinfo> 

using namespace std;
using namespace sdsl;

#define SEQUENCE_SEPARATOR_INT_VALUE (int('A'))
#define ALPHABET_SIZE 6

struct Node {
	uint64_t len;
	uint64_t lb;
	uint64_t size;
	uint64_t suffix_lb;

	Node(uint64_t len, uint64_t lb, uint64_t size, uint64_t suffix_lb) : len(len), lb(lb), size(size), suffix_lb(suffix_lb) {}
};

string S = "";
wt_huff<> wt;
vector<uint64_t> cArray(UCHAR_MAX + 1, 0);

void createBitVectors(uint64_t k, string BWT, vector<Node>& graph, queue<uint64_t>& Q, bit_vector& Bl, bit_vector& Br)
{
	// Construct WT used for C array from BWT
	construct_im(wt, BWT, 1);

	// Construct LCP from sequence
	lcp_bitcompressed<> lcp;
	construct_im(lcp, S, 1);

	// Compute the C array.
	uint64_t cSum = 0;

	for(int i = 0; i < UCHAR_MAX + 1; i++) 
	{
		if(wt.rank(wt.size(), i) != 0)
		{
			cArray[i] = cSum;
			cSum += wt.rank(wt.size(), i);
		}
	}

	cout << cArray << endl;

	Bl = bit_vector(BWT.size(), 0);
	Br = bit_vector(BWT.size(), 0);

	cout << lcp.size() << endl;
	cout << S.size() << endl;
	cout << BWT.size() << endl;

	bool open = false;
	uint64_t lb = 1;
	uint64_t kIndex = 0;
	uint64_t lastDiff = 0;
	uint64_t counter = 1;

	for(int i = 1; i < lcp.size(); i++)
	{
		if(lcp[i] >= k)
		{
			open = true;
			kIndex = (lcp[i] == k ? i : kIndex);
		}
		else
		{
			if(open)
			{
				if(kIndex > lb)
				{
					Br[lb] = 1;
					Br[i-1] = 1;
					graph.push_back(Node(k, lb, i - lb, lb));
					Q.push(counter++);
				}
				if(lastDiff > lb)
				{
					for(int j = lb; j < i-1; j++)
					{
						char c = BWT[j];
						if((c != '\0') && (c != '%'))
						{
							Bl[cArray[c]] = 1;
						}
					}
				}
				open = false;
			}
			lb = i;
		}

		if(BWT[i] != BWT[i-1]) lastDiff = i;
	}
	open = false;

	for(int i = 0; i < S.size(); i++)
	{
		if(open)
		{
			Bl[i] = 0;
			if(Br[i]) open = false;
		} 
		else if(Br[i])
		{
			Bl[i] = 0;
			open = true;
		}
	}

	cout << counter << endl;

	//cout << "Vector Bl: " << Bl << endl;
	cout << "Vector Br: " << Br << endl;
}

void createCompressedGraph(uint64_t k, string BWT)
{
    vector<Node> graph;
    queue<uint64_t> Q;
    bit_vector Bl, Br;

    createBitVectors(k, BWT, graph, Q, Bl, Br);

    bit_vector::rank_1_type Br_rank(&Br);
    bit_vector::rank_1_type Bl_rank(&Bl);
 
    uint64_t rightMax = Br_rank(S.size())/2.;
    //uint64_t leftMax = Bl_rank(S.size());

   	cout << "Right max: " << rightMax << endl;
   	//cout << "Left max: " << leftMax << endl;

	for(int s = 1; s <= cArray[SEQUENCE_SEPARATOR_INT_VALUE]; s++) 
	{
		int id = rightMax + s;
		graph.push_back(Node(1, s, 1, s));
		Q.push(id);
		Bl[s] = 0;
	}

	cout << "Queue size " << Q.size() << endl;

	cout << "wt sigma is " << wt.sigma << endl;

	uint64_t quantity;
	vector<uint8_t> list(wt.sigma);
    vector<uint64_t> rank_c_i(wt.sigma);
    vector<uint64_t> rank_c_j(wt.sigma);

	while(!Q.empty())
	{
		int id = Q.front();
		Q.pop();
		bool extendable;

		int count = 0;
		uint64_t lb = 0;
		uint64_t rb = 0;
	
		do {
			extendable = false;

			lb = graph.at(id-1).lb;
			rb = lb + graph.at(id-1).size - 1;

			cout << "interval is " << lb << ".."  << rb << endl << endl;
			
			cout << "len is " << graph.at(id-1).len << " ";
			cout << "lb is " << graph.at(id-1).lb << " ";
			cout << "size is " << graph.at(id-1).size << " ";
			cout << "suffix_lb " << graph.at(id-1).suffix_lb << endl;

			interval_symbols(wt, lb, rb, quantity, list, rank_c_i, rank_c_j);

			cout << "\n" << "quantity is " << quantity << endl;

			for(uint64_t i = 0; i < quantity; i++) 
			{
				char c = list.at(i);
				lb = cArray[c] + rank_c_i[i] - 1;
				cout << "left bound is " << lb << endl;
				uint64_t ones = Br_rank(lb);
				//cout << "ones is " << ones << endl;
				if(!(ones % 2) && !Br[lb]) {
					if(c != '\0' || c != '%') {
						if(quantity == 1) {
							extendable = true;
							graph.at(id-1).len += 1;
							graph.at(id-1).lb = lb;
						}
					}
				}

			}

			cout << "len after change is " << graph.at(id-1).len << " ";
			cout << "lb after change is " << graph.at(id-1).lb << " ";
			cout << "size after change is " << graph.at(id-1).size << " ";
			cout << "suffix_lb after change is " << graph.at(id-1).suffix_lb << endl;

			if(++count == 2) return;

		} while(extendable);
	}

	//cout << graph.size() << endl;

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