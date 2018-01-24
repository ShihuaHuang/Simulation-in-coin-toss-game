/*
*  alice_and_bob.h
*  Loosing as little as possible
*
*
*/
#ifndef ALICE_AND_BOB
#define ALICE_AND_BOB

#include <cmath>

using namespace std;

class I_have_nothing_apropos_for_this_class
{
private:
	double alice_probability, bob_probability;

	// private member function: uniform RV generator
	double get_uniform()
	{
		// write the appropriate code here
		return((double)rand() / RAND_MAX);
	}

	// private member function: nCi (i.e. n-take-i) 
	double take(int n, int i)
	{
		// write a **RECURSIVE** implementation of n-take-i. 
		// If you made it non-recurisive (i.e. n!/((n-i)!i!)) -- it 
		// will take too long for large sizes 
		/*double **mem;
		mem = new double*[n + 1];//create a array of n+1 terms
		for (int k = 0; k <= n; k++)
		{
			mem[k] = new double[i + 1];//create a array of i+1 terms
			for (int j = 0; j <= i; j++)
				mem[k][j] = -1;//value of the (n+1)*(i+1) matrix is set to -1
		}
		if (n < i) return 0;
		if (n == i) return 1;
		if (i == 0) return 1;
		if (mem[n][i] != -1) return mem[n][i];//use memoization to store the calculated value in order to call them in future calculation
		else
			return take(n - 1, i - 1) + take(n - 1, i);*/
		double *array;
		array = new double[n + 1];
		array[0] = 1.0;
		for (int j = 1; j <= n; j++)
		{
			array[j] = j*array[j - 1];
		}
		return array[n] / array[n - i] / array[i];
	}

	// this routine implements the probability that Alice has more 
	// heads than Bob after n-many coin tosses
	double theoretical_value(double q, double p, int n)
	{
		// implement equation 1.1 of Addona-Wagon-Wilf paper
		double v = 0;
		for (int r = 0; r < n; r++)
		{
			double v1 = 0;
			for (int s = r + 1; s <= n; s++)
			{
				v1 = v1 + take(n, s)*pow(q, s)*pow(1 - q, n - s);
			}
			v = v + v1*take(n, r)*pow(p, r)*pow(1 - p, n - r);
		}
		return v;
	}

public:
	// public function: 
	void set_probability(double alice_p, double bob_p)
	{
		alice_probability = alice_p;
		bob_probability = bob_p;
	}

	// probability of Alice winning the game.
	double simulated_value(int number_of_coin_tosses_in_each_game, int no_of_trials)
	{
		int no_of_wins_for_alice = 0;
		for (int i = 0; i < no_of_trials; i++)
		{
			int number_of_heads_for_alice = 0;
			int number_of_heads_for_bob = 0;
			for (int j = 0; j < number_of_coin_tosses_in_each_game; j++)
			{
				if (get_uniform() < alice_probability)
					number_of_heads_for_alice++;
				if (get_uniform() < bob_probability)
					number_of_heads_for_bob++;
			}
			if (number_of_heads_for_alice > number_of_heads_for_bob)
				no_of_wins_for_alice++;
		}
		return (((double)no_of_wins_for_alice) / ((double)no_of_trials));
	}

	int search_result()
	{
		// implememt a discrete-search procedure for the optimal n-value. 
		// start with n = 1 and find the discrete-value of n that has 
		// the largest probability for Alice winning.  Why would this work?
		// See Theorem 2.2 of the paper for the reason!
		for (int i = 1; i <= 100; i++)
		{
			/*double a1 = theoretical_value(alice_probability, bob_probability, i);
			double a2 = theoretical_value(alice_probability, bob_probability, i + 1);
			double a3 = theoretical_value(alice_probability, bob_probability, i + 2);
			cout << i << " " << a1 << " " << a2 << " " << a3 << " " << endl;
			if ((a1>=a2) && (a1>=a3))
				return i;*/
			double temp= theoretical_value(alice_probability, bob_probability, i + 1) - theoretical_value(alice_probability, bob_probability, i);
			//cout << i << " " << temp << " " << endl;
			if (temp <= 0)
				return i;
		}
		return 0;
	}
	void write_data(char* file_name,int no_of_trials)
	{
		ofstream out_filename(file_name);
			if (out_filename.is_open())
			{
				for (int i = 1; i <= 30; i++)
				{
					double theoretical = theoretical_value(alice_probability, bob_probability, i);
					double simulate = simulated_value(i, no_of_trials);
					out_filename << i << " , " << simulate << " , " << theoretical << endl;
				}
			}
		out_filename.close();
	}


};
#endif
