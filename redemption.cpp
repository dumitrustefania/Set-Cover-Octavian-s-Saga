#include <bits/stdc++.h>

#include "task.h"

using namespace std;

class TaskRedemption
{
    vector<string> cards_wanted;
    vector<vector<string>> packages;

    void read()
    {
        int N, M, P;
        cin >> N >> M >> P;
        string dummy;
        getline(cin, dummy);

        vector<string> cards_possesed;

        string card;
        for (int i = 0; i < N; i++)
        {
            getline(cin, card);
            cards_possesed.push_back(card);
        }

        for (int i = 0; i < M; i++)
        {
            getline(cin, card);
            if (find(cards_possesed.begin(), cards_possesed.end(), card) == cards_possesed.end())
                cards_wanted.push_back(card);
        }

        for (int i = 1; i <= P; i++)
        {
            int no;
            cin >> no;
            getline(cin, dummy);
            vector<string> package;
            for (int j = 0; j < no; j++)
            {
                getline(cin, card);
                package.push_back(card);
            }
            packages.push_back(package);
        }
    }

public:
    void solve()
    {    read();
        
        // implementare greedy a minimum set cover
        // sursa: chatGPT :)

        vector<int> sol;
        while (cards_wanted.size())
        {
            int maxCoverage = -1, maxSet = -1;

            // gaseste pachetelul cu nr. maxim de carti dorite
            for (int i = 0; i < packages.size(); i++)
            {
                int coverage = 0;
                for (int j = 0; j < packages[i].size(); j++)
                {
                    string card = packages[i][j];
                    if (find(cards_wanted.begin(), cards_wanted.end(), card) != cards_wanted.end())
                        coverage++;
                }
                if (coverage > maxCoverage)
                {
                    maxCoverage = coverage;
                    maxSet = i;
                    
                }
            }

            // elimina cartile obtinute din cards_wanted
            vector<string>::iterator it;
            for (int j = 0; j < packages[maxSet].size(); j++)
            {
                string card = packages[maxSet][j];
                it = find(cards_wanted.begin(), cards_wanted.end(), card);
                if (it != cards_wanted.end())
                    cards_wanted.erase(it);
            }

            // aauga pachetelul la solutie
            sol.push_back(maxSet + 1);
        }

        cout << sol.size() << "\n";
        for (int i = 0; i < sol.size(); i++)
            cout << sol[i] << " ";
    }
};

int main()
{
    TaskRedemption redemption;
    redemption.solve();
}
