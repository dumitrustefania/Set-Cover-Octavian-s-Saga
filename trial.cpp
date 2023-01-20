#include <bits/stdc++.h>

#include "task.h"

using namespace std;

class TaskTrial : public Task
{
    int N, M, K;
    unordered_map<int, vector<int>> subsets_containing_element;
    string status;
    vector<int> solution;
    ofstream fw;
    ifstream fr;

    void read_problem_data()
    {
        cin >> N >> M >> K;
        for (int i = 1; i <= M; i++)
        {
            int T;
            cin >> T;
            for (int j = 1; j <= T; j++)
            {
                int element;
                cin >> element;
                subsets_containing_element[element].push_back(i);
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
        fw << "p cnf " << M * K << " " << K + M * (K - 1) + K * M + N << "\n";

        // exista macar o submultime pentru fiecare element al acoperirii
        for (int r = 1; r <= K; r++)
        {
            for (int i = 1; i <= M; i++)
                add_variable(i, r, 1);
            fw << "0\n";
        }

        // o submultime se afla cel mult o data in acoperire
        for (int i = 1; i <= M; i++)
            for (int r = 1; r <= K; r++)
                for (int s = r + 1; s <= K; s++)
                {
                    add_variable(i, r, -1);
                    add_variable(i, s, -1);
                    fw << "0\n";
                }

        // cel mult o submultime e aleasa pentru un inex al acoperirii
        for (int r = 1; r <= K; r++)
            for (int i = 1; i <= M; i++)
                for (int j = i + 1; j <= M; j++)
                {
                    add_variable(i, r, -1);
                    add_variable(j, r, -1);
                    fw << "0\n";
                }

        // pentru fiecare intreg de la 1 la N, trebuie sa verific ca exista
        // in cel putin una din submultimile alese
        for (int element = 1; element <= N; element++)
        {
            for (int i = 0; i < subsets_containing_element[element].size(); i++)
            {
                int subset = subsets_containing_element[element][i];
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
    {   fr.open("sat.sol");
        fr >> status;
        if (!status.compare("True"))
        {
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
        }
        fr.close();
    }

    void write_answer()
    {
        cout << status << "\n";
        if (!status.compare("False"))
            return;
        cout << solution.size() << "\n";
        for (int i = 0; i < solution.size(); i++)
            cout << solution[i] << " ";
    }

public:
    void solve()
    {
        read_problem_data();
        formulate_oracle_question();
        ask_oracle();
        decipher_oracle_answer();
        write_answer();
    }
};

int main()
{
    TaskTrial trial;
    trial.solve();
}