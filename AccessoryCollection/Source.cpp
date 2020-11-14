#pragma warning(disable : 4996)
// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>  // Needed for unique
#include <fstream>  // Needed for fout function & <<
#include <string>
#include <vector>


using namespace std;

vector<string> split_string(string);

bool preliminaryTest(long int L, long int A, int N, int D) {
    // string test{" "};
    bool preCheckFail{ false };

    if ((((N < D) || (L < N)) || ((L < D) || (A < D))) || ((L > A) && (N == D))) {
        preCheckFail = true;
        return preCheckFail;
    }

    return preCheckFail;
}

// Subset equals types and items purchased is equal to or less than item types
string subsetEqualsTypes(long int L, long int A, int N, int D) {
    long long int sum{0};
    string sumString{ " " };

    for (int i = 0; i < L; i++) {
        sum += A;  // Sum cost for L items
        A--;  // Decrement A
    }
    
    // Convert sum to string
    sumString = to_string(sum);

    return sumString;
}

// Items purchased is less than item types and subsets is greater than types in subset
string itemsPurchasedLessThanTypes(long int L, long int A, int N, int D) {
    long long int sum{ 0 };
    int numOfMax{ 0 };  // Number of A added to start
    int numOfRepeating{ 0 };  // Number of repeats of each A after first As are added
    string sumString{ " " };

    if(D != 2) {
        numOfMax = (N - D) + 1;

        // Add the value of A numOfMax times
        for (int i = 0; i < numOfMax; i++)
            sum += A;

        int test = (L - numOfMax);
        // Add the rest of the values starting from A - 1 down to L - 1
        for (int j = 0; j < test; j++) {
            A--;  // Decrement price
            sum += A;
        } 
    }
    else {
        numOfMax = (N - D) + 1;
        numOfRepeating = (N - D);
        // Add the value of A numOfMax times
        for (int i = 0; i < numOfMax; i++)
            sum += A;

        // Add the rest of the values starting from A - 1 down to L - 1
        for (int j = 0; j < (L - numOfMax);) {
            A--;  // Decrement price
            for (int k = 0; k < numOfRepeating; k++) {
                sum += A;  // Add in price of accessory, don't change price
                j++;  // Need to increment count
                if (j == (L - numOfMax))
                    break;
            }
        }
    }
   
    // Convert sum to string
    sumString = to_string(sum);

    return sumString;
}

// Items purchased is greater than item types and subsets is greater than types in subset
string itemsPurchasedGreaterThanTypes(long int L, long int A, int N, int D) {
    long long int sum{ 0 };
    int numOfMax{ 0 };  // Number of A added to start
    int numOfRepeating{ 0 };  // Number of repeats of each A after first As are added
    int lMax{ 0 };  // Max number of items that can be purchased based on the criteria
    string sumString{ " " };

    // Calculate the number of repeating numbers
    numOfMax = ((N - D) + 1);

    if (D != 2) {
        lMax = numOfMax + (A - 1);

        if (L > lMax)
        {
            sumString = "SAD";
            return sumString;
        }

        // Add the value of A numOfMax times
        for (int i = 0; i < numOfMax; i++)
            sum += A;

        // Add the rest of the values starting from A - 1 down to L - 1
        for (int j = 0; j < (L - numOfMax); j++) {
            A--;  // Decrement price
            sum += A;
        }
    }

    // D = 2
    else {
        lMax = (N - 1) * A;
        numOfMax = (N - 1);
        numOfRepeating = (N - 1);

        // Add the value of A numOfMax times
        for (int i = 0; i < numOfMax; i++)
            sum += A;

        // Add the rest of the values starting from A - 1 down to L - 1
        for (int j = 0; j < (L - numOfMax);) {
            A--;  // Decrement price
            for (int k = 0; k < numOfRepeating; k++) {
                sum += A;  // Add in price of accessory, don't change price
                j++;  // Need to increment count
                if (j == (L - numOfMax))
                    break;
            }
        }
    }

    // Convert sum to string
    sumString = to_string(sum);

    return sumString;
}

string acessoryCollection(long int L, long int A, int N, int D) {
    string result{" "};
    bool preCheckFail{ false };

    preCheckFail = preliminaryTest(L, A, N, D);  // Check for obvious combinations that will not work
    
    if (preCheckFail)
        return "SAD";  // Precheck failed

    if ((L <= A) && (N == D))
        result = subsetEqualsTypes(L, A, N, D);
    else if((L < A) && (N > D))
        result = itemsPurchasedLessThanTypes(L, A, N, D);
    else if(L >= A)
        result = itemsPurchasedGreaterThanTypes(L, A, N, D);

    return result;
}

int main()
{
    ifstream in_file("test1.txt");
    // ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    
    if (in_file)
    {
        in_file >> T;
        in_file.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int T_itr = 0; T_itr < T; T_itr++) {
            string LAND_temp;
            getline(in_file, LAND_temp);

            vector<string> LAND = split_string(LAND_temp);

            int L = stoi(LAND[0]);

            int A = stoi(LAND[1]);

            int N = stoi(LAND[2]);

            int D = stoi(LAND[3]);

            string result = acessoryCollection(L, A, N, D);

            // fout << result << "\n";
            cout << result << "\n";
        }

    }

    else
        cout << "File could not be open" << endl;

    in_file.close();
    // fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
