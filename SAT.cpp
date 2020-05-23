#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int ans;

class Formula {
public:
    Formula() {}
    vector<int> literals;
    vector<int> literal_frequency;
    vector<int> literal_polarity;
    vector<vector<int>> clauses;
};

class SATSolver {
public:
    SATSolver() {}
    void initialize();
    void solve();

private:
    Formula formula;
    int literal_count;
    int clause_count;
    int unit_propagate(Formula &);
    int DPLL(Formula);
    int removes(Formula &, int);
    void show(Formula &, int);
};

void SATSolver::initialize() {
    char c = cin.get();
    while (c == 'c') {
        while (c != '\n')
            c = cin.get();
        c = cin.get();
    }
    string cnfline;
    cin >> cnfline >> literal_count >> clause_count;

    formula.literals.resize(literal_count, -1);
    formula.clauses.resize(clause_count);
    formula.literal_frequency.resize(literal_count, 0);
    formula.literal_polarity.resize(literal_count, 0);

    int liter;
    int polar_pos = 0;
    int polar_neg = 0;
    for (int i=0;i<clause_count;i++) {
        while (cin >> liter && liter != 0){
            if (liter > 0)
            {
                formula.clauses[i].push_back(2*(liter-1));
                formula.literal_frequency[liter-1]++;
                formula.literal_polarity[liter-1]++;
                polar_pos++;
            } else{
                formula.clauses[i].push_back(2*((-1)*liter-1)+1);
                formula.literal_frequency[-1-liter]++;
                formula.literal_polarity[-1-liter]--;
                polar_neg++;
            }
        }
    }
    if(polar_pos==0 || polar_neg==0){
        ans = 1;
        show(formula, ans);
    }
}

void SATSolver::solve() {
    if(ans != 1){
        for (int i=0;i<=formula.literal_frequency.size();i++) {
            if(formula.literal_frequency[i] == formula.literal_polarity[i]){
                for(int j=0;j<formula.clauses.size();j++){
                    for(int k=0;k<formula.clauses.size();k++){
                        if(formula.clauses[j][k] == 2*i){
                            formula.clauses[j].erase(formula.clauses[j].begin()+k);
                            k--;
                        }
                    }
                }
                formula.literal_frequency[i] = -1;
            }
            else if(formula.literal_frequency[i] == (-1)*formula.literal_polarity[i]){
                for(int j=0;j<formula.clauses.size();j++){
                    for(int k=0;k<formula.clauses.size();k++){
                        if(formula.clauses[j][k] == 2*i+1){
                            formula.clauses[j].erase(formula.clauses[j].begin()+k);
                            k--;
                        }
                    }
                }
                formula.literal_frequency[i] = -1;
            }
        }
        int result = DPLL(formula);
        if(result == 3){
            show(formula, 2);
        }
    }
}

int SATSolver::DPLL(Formula f) {
    int result = unit_propagate(f);
    if (result == 1){
        show(f, result);
        ans = 4;
        return ans;
    }else if (result == 2){
        ans = 3;
        return ans;
    }
    else{
        int maxi = distance(f.literal_frequency.begin(), max_element(f.literal_frequency.begin(), f.literal_frequency.end()));
        for (int j=0;j<2;j++) {
            Formula new_f = f;
            if (new_f.literal_polarity[maxi] > 0){
                new_f.literals[maxi] = j;
            }else{
              new_f.literals[maxi] = (j+1)%2;
            }
            int transform_result = removes(new_f, maxi);
            if(transform_result == 1){
                show(new_f, transform_result);
                ans = 4;
                return ans;
            }
            else if(transform_result == 2){
              continue;
            }
            int dpll_result = DPLL(new_f);
            if(dpll_result == 4){
                return dpll_result;
            }
        }
    }


    ans = 3;
    return ans;
}

int SATSolver::unit_propagate(Formula &f) {
    bool unit_found = false;
    if (f.clauses.empty()){
        ans = 1;
        return ans;
    }
    do{
        unit_found = false;
        for (int i=0;i<f.clauses.size();i++) {
            if (f.clauses[i].size() == 1){
                unit_found = true;
                f.literals[f.clauses[i][0]/2] = f.clauses[i][0] % 2;
                int result = removes(f, f.clauses[i][0]/2);
                if(result == 1 || result == 2){
                  return result;
                }
                break;
            }else if (f.clauses[i].empty()){
                ans = 2;
                return ans;
            }
        }
    } while (unit_found);

    ans = 3;
    return ans;
}

int SATSolver::removes(Formula &f, int apply_literal) {
    int apply_value = f.literals[apply_literal];
    f.literal_frequency[apply_literal] = -1;
    for (int i=0;i<f.clauses.size();i++) {
        for (int j=0;j<f.clauses[i].size();j++) {
            if (f.clauses[i][j] == (2*apply_literal + apply_value)) {
                f.clauses.erase(f.clauses.begin()+i);
                i--;
                if (f.clauses.empty()){
                    ans = 1;
                    return ans;
                }
                break;
            }else if (f.clauses[i][j]/2 == apply_literal){
                f.clauses[i].erase(f.clauses[i].begin()+j);
                j--;
                if (f.clauses[i].empty()){
                    ans = 2;
                    return ans;
                }
                break;
            }
        }
    }
    ans = 3;
    return ans;
}

void SATSolver::show(Formula &f, int result) {
    if(result == 1){
        cout << "sat" << endl;
    }else{
        cout << "unsat" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    SATSolver solver;
    solver.initialize();
    solver.solve();
    return 0;
}
