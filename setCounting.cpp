#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

int countSets(const vector<int>& array) {
    int numSets = 0;
    for (size_t x = 0; x < array.size() - 2; ++x) {
        for (size_t y = x + 1; y < array.size() - 1; ++y) {
            for (size_t z = y + 1; z < array.size(); ++z) {
                if ((array[x] ^ array[y]) == array[z]) {
                    numSets++;
                }
            }
        }
    }
    return numSets;
}

int main() {
    int dim;
    cout << "What dimension do you want? ";
    cin >> dim;

    if (cin.fail()) {
        cout << "Invalid input. Please enter an integer." << endl;
        return 1;
    }
    cout << "The dimension is: " << dim << endl;

    int numCards = (1 << dim) - 1; // total possible cards

    int pickNum = numCards + 1;
    while (pickNum > numCards) {
        cout << "How many cards? ";
        cin >> pickNum;

        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            continue;
        }

        if (pickNum <= numCards) {
            cout << "Collections of size: " << pickNum << endl;
        } else {
            cout << "Too many cards! Max is: " << numCards << endl;
        }
    }

    int numCollections = 0; // counts possible collections
    vector<int> cards; // array of (pickNum) cards
    vector<int> maxs; // last possible collection of cards
    vector<int> setCounts; // number of sets in each possible collection

    // generate the starting cards and maxs array
    for (int num = 1; num <= pickNum; ++num) {
        cards.push_back(num);
        maxs.push_back(numCards - (pickNum - num));
    }
    cout << "\nStarting at: ";
    for (const auto& card : cards) cout << card << " ";
    cout << "\nEnding at: ";
    for (const auto& max : maxs) cout << max << " ";
    cout << endl;

    // cycle through all possible collections of (pickNum) cards, counting the number of sets in each
    while (cards[0] <= maxs[0]) {
        setCounts.push_back(countSets(cards));
        numCollections++;

        // if last card isn't maxed out, increase it
        // otherwise, find the next collection
        if (cards[pickNum - 1] < maxs[pickNum - 1]) {
            cards[pickNum - 1]++;
        } else if (cards[pickNum - 1] == maxs[pickNum - 1]) {
            // find the last card that isn't maxed out
            int index = pickNum - 1;
            while (cards[index] == maxs[index]) {
                index--;
                if (index == -1) {
                    break;
                }
            }

            if (index == -1) {
                index++; // just to not go out of bounds
            }
            cards[index]++; // increase the last card not maxed out
            while (index < pickNum - 1) {
                cards[index + 1] = cards[index] + 1;
                index++;
            }
        } else {
            cout << "last card went out of range" << endl;
        }
    }

    int maxSetCount = *max_element(setCounts.begin(), setCounts.end()); // highest number of sets in any possible collection
    cout << "\nMax Set Count: " << maxSetCount << endl;
    cout << "Number of possible collections: " << numCollections << endl;

    vector<int> setData(maxSetCount + 1, 0);
    for (const auto& count : setCounts) {
        setData[count]++;
    }

    cout << "\n--Set Data--" << endl;
    cout << "#Sets  Frequency" << endl;
    for (int x = 0; x <= maxSetCount; ++x) {
        cout << x << "\t " << setData[x] << endl;
    }

    return 0;
}
