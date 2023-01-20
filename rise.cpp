#include <bits/stdc++.h>

#include "task.h"

using namespace std;

class TaskRise : public Task
{
    int P, K;
    vector<string> cards_wanted;
    unordered_map<string, vector<int>> subsets_containing_card;
    string status;
    vector<int> solution;
    ofstream fw;
    ifstream fr;

    void read_problem_data()
    {
        int N, M;
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
            // adaug in vectorul cartilor dorite doar pe cele pe care nu le am deja
            if (find(cards_possesed.begin(), cards_possesed.end(), card) == cards_possesed.end())
                cards_wanted.push_back(card);
        }

        for (int i = 1; i <= P; i++)
        {
            int no;
            cin >> no;
            getline(cin, dummy);

            for (int j = 0; j < no; j++)
            {
                getline(cin, card);
                subsets_containing_card[card].push_back(i);
            }
        }
    }

    // determin codificarea variabilei y(i,r) pentru formatul cnf
    void add_variable(int i, int r, int mul)
    {
        fw << ((i - 1) * K + r) * mul << " ";
    }

    void formulate_oracle_question()
    {
        fw.open("sat.cnf");

        int N = cards_wanted.size();
        fw << "p cnf " << P * K << " " << K + P * (K - 1) + K * P + N << "\n";

        // exista macar o submultime pentru fiecare element al acoperirii
        for (int r = 1; r <= K; r++)
        {
            for (int i = 1; i <= P; i++)
                add_variable(i, r, 1);
            fw << "0\n";
        }

        // o submultime se afla cel mult o data in acoperire
        for (int i = 1; i <= P; i++)
            for (int r = 1; r <= K; r++)
                for (int s = r + 1; s <= K; s++)
                {
                    add_variable(i, r, -1);
                    add_variable(i, s, -1);
                    fw << "0\n";
                }

        // cel mult o submultime e aleasa pentru un inex al acoperirii
        for (int r = 1; r <= K; r++)
            for (int i = 1; i <= P; i++)
                for (int j = i + 1; j <= P; j++)
                {
                    add_variable(i, r, -1);
                    add_variable(j, r, -1);
                    fw << "0\n";
                }

        // pentru fiecare carte din cards_wanted, trebuie sa verific
        // ca a fost ales cel putin unul din pachetelele care o contine
        for (int l = 0; l < cards_wanted.size(); l++)
        {
            string card = cards_wanted[l];
            for (int i = 0; i < subsets_containing_card[card].size(); i++)
            {
                int subset = subsets_containing_card[card][i];
                for (int r = 1; r <= K; r++)
                {
                    add_variable(subset, r, 1);
                }
            }
            fw << "0\n";
        }
        fw.close();
    }

    void decipher_oracle_answer()
    {
        fr.open("sat.sol");
        fr >> status;
        int size, x;
        fr >> size;
        for (int i = 1; i <= size; i++)
        {
            int variable;
            fr >> variable;

            if (variable > 0)
            {
                int subset_no = (variable - 1) / K + 1;
                solution.push_back(subset_no);
            }
        }
        fr.close();
    }

    void write_answer()
    {
        cout << solution.size() << "\n";
        for (int i = 0; i < solution.size(); i++)
            cout << solution[i] << " ";
    }

public:
    void solve()
    {
        read_problem_data();

        // incerc sa descopar K minim folosindu-ma de binary search
        int l = 1, r = P , mid =-1;
        while (l <= r)
        {   if(mid == (l + r) / 2)
                break;
            mid = (l + r) / 2;
            K = mid;
            formulate_oracle_question();
            ask_oracle();

            fr.open("sat.sol");
            fr >> status;
            fr.close();

            if (!status.compare("True"))
                r = mid;
            else
                l = mid + 1;
        }

        // pentru K minim descoperit, descifrez raspunsul oracolului
        decipher_oracle_answer();
        write_answer();
    }
};

int main()
{
    TaskRise rise;
    rise.solve();
}
