#include <iostream>
#include <climits>
#include <string>
#include <sdsl/suffix_arrays.hpp>
#include <sdsl/lcp.hpp>
#include <sais.hxx>
#include "helper.h"

using namespace std;
using namespace sdsl;

#define SEQUENCE_SEPARATOR__INT_VALUE ('%' - 48)

struct Node {
	uint64_t id;
	uint64_t lb;
	uint64_t rb;
	uint64_t len;
	uint64_t suffix_lb;

	Node(uint64_t id, uint64_t lb, uint64_t rb, uint64_t len, uint64_t suffix_lb) : id(id), lb(lb), rb(rb), len(len), suffix_lb(suffix_lb) {}
};

string S = "";
vector<uint64_t> cArray(UCHAR_MAX + 1, 0);

void createBitVectors(uint64_t k, string BWT, vector<Node>& graph, queue<uint64_t>& Q, bit_vector& Bl, bit_vector& Br)
{
	// Construct WT used for C array from BWT
	wt_huff<> wt;
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

	Bl = bit_vector(S.size(), 0);
	Br = bit_vector(S.size(), 0);

	cout << lcp.size() << endl;
	cout << S.size() << endl;

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
					graph.push_back(Node(k, lb, i - lb, lb, 0));
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

	cout << "Vector Bl: " << Bl << endl;
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
    uint64_t leftMax = Bl_rank(S.size());

   	cout << "Right max: " << rightMax << endl;
   	cout << "Left max: " << leftMax << endl;

	for(int s = 1; s <= cArray[SEQUENCE_SEPARATOR__INT_VALUE]; s++) 
	{
		int id = rightMax + leftMax + s;
		graph.push_back(Node(1, s, 1, s, 0));
		Q.push(id);
		Bl[s] = 0;
	}

	/*while(!Q.empty())
	{

	}*/

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