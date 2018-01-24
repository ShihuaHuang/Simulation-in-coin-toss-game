// "How to lose as little as possible" by Addona, Wagon and Wilf
// 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include "Shihua_Huang_7.h"
using namespace std;

int main(int argc, char* argv[])
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_time;

	start = std::chrono::system_clock::now();//start calculating the time

	I_have_nothing_apropos_for_this_class x;
	double alice_success_prob, bob_success_prob;
	int no_of_trials;
	char output_filename;

	sscanf_s(argv[1], "%d", &no_of_trials);
	sscanf_s(argv[2], "%lf", &alice_success_prob);
	sscanf_s(argv[3], "%lf", &bob_success_prob);

	cout << "Number of trials = " << no_of_trials << endl;
	cout << "Probability of success for Alice = " << alice_success_prob << endl;
	cout << "Probability of success for Bob = " << bob_success_prob << endl;

	x.set_probability(alice_success_prob, bob_success_prob);

	int optimal = x.search_result();
	if (optimal > 0)
		cout << "The optimal number of coin tosses in each game is " << optimal << endl;
	else {
		cout << "The optimal number of coin tosses in each game exceeds 100... Quitting" << endl;
	}

	x.write_data(argv[4], no_of_trials);

	end = std::chrono::system_clock::now();//stop calculating the time
	elapsed_time = end - start;//calculate the time used
	cout << "Elapsed time to finish part1 & part2: " << elapsed_time.count() << "s\n" << endl;//output the time
	return 0;
}