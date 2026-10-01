#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

bool checkAccountStatus(string attr1){
    if (attr1=="A11" ){
        // A11: < 0 DM
        return false;
    }
    return true;
}

bool loan_Duration(string attr2){
    int duration = stoi(attr2);
    if(duration <= 24){
        return true;
    }
    return false;
}

bool creditHistory(string attr3){
    if(attr3=="A33" || attr3=="A34"){
        // A33: delay in paying off in the past
        // A34: critical account/other credits existing (not at this bank)
        return false;
    }
    return true;
}

bool riskScreening(string attr4){
    if(attr4=="A47" || attr4=="A48" || attr4=="A49" || attr4=="A410"){
        // A47: vacation - does not exist?
        // A48: retraining
        // A49: business
        // A410: others
        return true;
    }
    return true;
}

bool credAmount(string attr5){
    int amount = stoi(attr5);
    if(amount >= 7500){
        return false;
    }
    return true;
}

bool savings(string attr6){
    if(attr6=="A65"){
        // A65: unknown/ no savings account
        return false;
    }
    return true;
}

bool employment(string attr7){
    if(attr7== "A71" || attr7 == "A72"){
        // A71: unemployed
        // A72: < 1 year
        return false;
    }
    return true;
}

struct ruleResults{
    bool checkingAccountStatus, loanDuration, credithistory, RiskScreening, CredAmount, Savings, employment;
    bool allPassed(){
        return checkingAccountStatus && loanDuration && credithistory && CredAmount && Savings && employment;
    }

    int countFailed(){
        int count= 0;
        if(!checkingAccountStatus) count++;
        if(!loanDuration) count++;
        if(!credithistory) count++;
        if(!CredAmount)count++;
        if(!Savings) count++;
        if(!employment) count++;
        return count;
    }
};

void displaysummary(int totApplicant, int passed){
    cout<<endl;
    cout<<"==== summary ===="<<endl;
    cout<<"total Applicants: "<<totApplicant<<endl;
    cout<<"passed: "<< passed<<endl;
    cout<<"failed: "<<totApplicant - passed<<endl;
    cout<<"approval rate: "<< ((passed*100.0)/totApplicant) <<"%"<<endl;
    cout<<endl;
}

void runFullAnalysis(){
    ifstream file("german.data");
    int totApplicant = 0;
    int passed = 0;
    string line;

    if(!file.is_open()){
        cout<<"ERROR! Could not open german.data file"<<endl;
        return ;
    }
    cout<<endl;

    cout<<"==== Loan approval rule engine ===="<<endl;
    cout<<"==== checking account state ===="<<endl;
    cout<<endl;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1;
        ss>>attr1;
        bool result = checkAccountStatus(attr1);
        totApplicant++ ;

        if(result==true){
            passed++;
        }
        if(totApplicant<=29){
            cout<<"Applicant"<<totApplicant<<":"<<attr1<<"->"<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed) ;

    cout<<"=== checking the loan duration ==="<<endl ;
    file.clear();
    file.seekg(0);
    totApplicant=0;
    passed=0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2;
        ss>>attr1>>attr2;
        bool result= loan_Duration(attr2);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=10){
            cout<<"Applicant: "<<totApplicant<<";"<<attr2<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed);
    cout<<endl;

    file.clear();
    file.seekg(0);
    cout<<"=== Checking account history ==="<<endl;
    totApplicant = 0;
    passed = 0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2,attr3;
        ss>>attr1>>attr2>>attr3;
        bool result=creditHistory(attr3);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=9){
            cout<<"Applicant"<<totApplicant<<":"<<attr3<<"->"<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed) ;
    cout<<endl;

    file.clear();
    file.seekg(0);
    cout<<"=== checking Purpose-Based Risk Screening ==="<<endl;
    totApplicant=0;
    passed=0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2,attr3,attr4;
        ss>>attr1>>attr2>>attr3>>attr4;
        bool result=riskScreening(attr4);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=29){
            cout<<"Applicant"<<totApplicant<<":"<<attr4<<"->"<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed);
    cout<<endl;

    file.clear();
    file.seekg(0);
    cout<<"=== checking Bounded Credit Amounts ==="<<endl;
    totApplicant=0;
    passed=0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2,attr3,attr4,attr5;
        ss>>attr1>>attr2>>attr3>>attr4>>attr5;
        bool result=credAmount(attr5);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=9){
            cout<<"Applicant"<<totApplicant<<":"<<attr5<<"->"<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed);
    cout<<endl;

    file.clear();
    file.seekg(0);
    cout<<"=== checking savings account/bonds ==="<<endl;
    totApplicant=0;
    passed=0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2,attr3,attr4,attr5,attr6;
        ss>>attr1>>attr2>>attr3>>attr4>>attr5>>attr6;
        bool result=savings(attr6);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=9){
            cout<<"Applicant"<<totApplicant<<":"<<attr6<<"->"<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed);
    cout<<endl;

    cout<<"=== cheking the employment stability ==="<<endl;
    file.clear();
    file.seekg(0);
    totApplicant=0;
    passed=0;
    while(getline(file,line)){
        stringstream ss(line);
        string attr1,attr2,attr3,attr4,attr5,attr6,attr7;
        ss>>attr1>>attr2>>attr3>>attr4>>attr5>>attr6>>attr7;
        bool result= employment(attr7);
        totApplicant++;

        if(result==true){
            passed++;
        }
        if(totApplicant<=29){
            cout<<"Applicant: "<<totApplicant<<";"<<attr7<<(result ? "passed":"failed")<<endl;
        }
    }
    displaysummary(totApplicant,passed);
    cout<<endl;

    file.close();
}

void runCombinedEngine(){
    ifstream file("german.data");
    string line;
    if (!file.is_open()) {
        cout << "ERROR! Could not open german.data file" << endl;
        return;
    }

    int total = 0;
    int approved = 0;

    cout << "=== Combined decision Engine ===" << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string attr[21];
        for (int i = 0; i < 21; i++) ss >> attr[i];

        total++;
        ruleResults r;
        r.checkingAccountStatus = checkAccountStatus(attr[0]);
        r.loanDuration = loan_Duration(attr[1]);
        r.credithistory = creditHistory(attr[2]);
        r.RiskScreening = riskScreening(attr[3]);
        r.CredAmount = credAmount(attr[4]);
        r.Savings = savings(attr[5]);
        r.employment = employment(attr[6]);

        bool finalpass = r.allPassed();
        if (finalpass) approved++;

        if (total < 10) {
            cout << "applicant number: " << total << endl;
            cout << "=== checking account status ---> " << (r.checkingAccountStatus ? "pass" : "fail") << endl;
            cout << "=== the loan duration ---> " << (r.loanDuration ? "pass" : "fail") << endl;
            cout << "=== the credit history ---> " << (r.credithistory ? "pass" : "fail") << endl;
            cout << "=== risk screening ---> " << (r.RiskScreening ? "pass" : "fail") << endl;
            cout << "=== credit amount ---> " << (r.CredAmount ? "pass" : "fail") << endl;
            cout << "=== savings ---> " << (r.Savings ? "pass" : "fail") << endl;
            cout << "=== employment ---> " << (r.employment ? "pass" : "fail") << endl;
            cout << "=== Decision ---> " << (finalpass ? "approved" : "declined")
                 << " (failed " << r.countFailed() << " rules)" << endl;

            if (!finalpass) {
                cout << "   >> Reason for denial: ";
                if (!r.checkingAccountStatus) cout << "[Checking Account] ";
                if (!r.loanDuration) cout << "[Loan Duration] ";
                if (!r.credithistory) cout << "[Credit History] ";
                if (!r.CredAmount) cout << "[Credit Amount] ";
                if (!r.Savings) cout << "[Savings] ";
                if (!r.employment) cout << "[Employment] ";
                cout << endl;
            }
            cout << endl;
        }
    }

    cout << "total: " << total << endl;
    cout << " approved: " << approved << " denied: " << (total - approved) << endl;
    cout << "rate: " << ((approved * 100.0) / total) << "%" << endl;

    file.close();
}

void runXAI() {
    ifstream file("german.data");
    string line;
    if (!file.is_open()) {
        cout << "ERROR! Could not open german.data file" << endl;
        return;
    }

    int total = 0;
    int failChecking = 0, failDuration = 0, failCreditHist = 0, failRisk = 0;
    int failAmount = 0, failSavings = 0, failEmployment = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string attr[21];
        for (int i = 0; i < 21; i++) ss >> attr[i];

        total++;
        ruleResults r;
        r.checkingAccountStatus = checkAccountStatus(attr[0]);
        r.loanDuration = loan_Duration(attr[1]);
        r.credithistory = creditHistory(attr[2]);
        r.RiskScreening = riskScreening(attr[3]);
        r.CredAmount = credAmount(attr[4]);
        r.Savings = savings(attr[5]);
        r.employment = employment(attr[6]);

        if (!r.checkingAccountStatus) failChecking++;
        if (!r.loanDuration) failDuration++;
        if (!r.credithistory) failCreditHist++;
        if (!r.RiskScreening) failRisk++;
        if (!r.CredAmount) failAmount++;
        if (!r.Savings) failSavings++;
        if (!r.employment) failEmployment++;
    }

    cout << "=============================================" << endl;
    cout << "XAI: RULE IMPORTANCE (which rules deny most)" << endl;
    cout << "=============================================" << endl;
    cout << "Credit History:          " << failCreditHist << " failures ("
         << (failCreditHist * 100.0 / total) << "%)" << endl;
    cout << "Checking Account Status: " << failChecking << " failures ("
         << (failChecking * 100.0 / total) << "%)" << endl;
    cout << "Loan Duration:           " << failDuration << " failures ("
         << (failDuration * 100.0 / total) << "%)" << endl;
    cout << "Credit Amount:           " << failAmount << " failures ("
         << (failAmount * 100.0 / total) << "%)" << endl;
    cout << "Savings:                 " << failSavings << " failures ("
         << (failSavings * 100.0 / total) << "%)" << endl;
    cout << "Employment:              " << failEmployment << " failures ("
         << (failEmployment * 100.0 / total) << "%)" << endl;
    cout << "Risk Screening:          " << failRisk << " failures ("
         << (failRisk * 100.0 / total) << "%)" << endl;
    cout << "=============================================" << endl;

    file.close();
}

void runfilter(){
    ifstream file("german.data") ;
    string line ;
    int filterChoice = 0;

    while (filterChoice != 4) {
        cout << "========================================" << endl;
        cout << "  FILTER RESULTS" << endl;
        cout << "========================================" << endl;
        cout << "  1. Show only APPROVED applicants" << endl;
        cout << "  2. Show only DENIED applicants" << endl;
        cout << "  3. Show a specific applicant by ID" << endl;
        cout << "  4. Return to main menu" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> filterChoice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<" Invalid input, pls enter a number. "<<endl;
            continue ;
        }

        if (filterChoice >= 1 && filterChoice <= 3) {
            int target = 0;
            if (filterChoice == 3){
                cout << "Enter applicant ID (1-1000): ";
                cin >> target;
                if(cin.fail()){
                    cin.clear() ;
                    cin.ignore(1000,'\n');
                    cout<<" Invalid input "<<endl ;
                    continue;
                }
            }

            file.clear();
            file.seekg(0);
            int count = 0;
            bool wantApproved = (filterChoice == 1);

            while (getline(file, line)) {
                stringstream ss(line);
                string attr[21];
                for (int i = 0; i < 21; i++) ss >> attr[i];

                count++;
                ruleResults r;
                r.checkingAccountStatus = checkAccountStatus(attr[0]);
                r.loanDuration = loan_Duration(attr[1]);
                r.credithistory = creditHistory(attr[2]);
                r.RiskScreening = riskScreening(attr[3]);
                r.CredAmount = credAmount(attr[4]);
                r.Savings = savings(attr[5]);
                r.employment = employment(attr[6]);
                bool passed = r.allPassed();

                if (filterChoice == 3 && count == target) {
                    cout << "\n--- Applicant " << count << " ---" << endl;
                    cout << "Checking Account: " << (r.checkingAccountStatus ? "PASS" : "FAIL")
                         << " (value is " << attr[0] << ", where " << attr[0] << " means "
                         << (attr[0]=="A11" ? "the account balance is below 0 DM"
                           : attr[0]=="A12" ? "the account balance is between 0 and 200 DM"
                           : attr[0]=="A13" ? "the account balance is 200 DM or more, with salary assignments for at least 1 year"
                           : "the applicant has no checking account")
                         << ")" << endl;
                    cout << "Loan Duration:    " << (r.loanDuration ? "PASS" : "FAIL")
                         << " (value is " << attr[1] << " months, where the maximum allowed is 24 months)" << endl;
                    cout << "Credit History:   " << (r.credithistory ? "PASS" : "FAIL")
                         << " (value is " << attr[2] << ", where " << attr[2] << " means "
                         << (attr[2]=="A30" ? "no credits have been taken and all credits have been paid back duly"
                           : attr[2]=="A31" ? "all credits at this bank have been paid back duly"
                           : attr[2]=="A32" ? "existing credits have been paid back duly until now"
                           : attr[2]=="A33" ? "there was a delay in paying off in the past"
                           : "the applicant has a critical account, with other credits existing not at this bank")
                         << ")" << endl;
                    cout << "Risk Screening:   " << (r.RiskScreening ? "PASS" : "FAIL")
                         << " (value is " << attr[3] << ", where " << attr[3] << " means the loan purpose is "
                         << (attr[3]=="A40" ? "a new car"
                           : attr[3]=="A41" ? "a used car"
                           : attr[3]=="A42" ? "furniture or equipment"
                           : attr[3]=="A43" ? "radio or television"
                           : attr[3]=="A44" ? "domestic appliances"
                           : attr[3]=="A45" ? "repairs"
                           : attr[3]=="A46" ? "education"
                           : attr[3]=="A47" ? "a vacation"
                           : attr[3]=="A48" ? "retraining"
                           : attr[3]=="A49" ? "business"
                           : "something else")
                         << ")" << endl;
                    cout << "Credit Amount:    " << (r.CredAmount ? "PASS" : "FAIL")
                         << " (value is " << attr[4] << " DM, where the maximum allowed is 7499 DM)" << endl;
                    cout << "Savings:          " << (r.Savings ? "PASS" : "FAIL")
                         << " (value is " << attr[5] << ", where " << attr[5] << " means the savings balance is "
                         << (attr[5]=="A61" ? "below 100 DM"
                           : attr[5]=="A62" ? "between 100 and 500 DM"
                           : attr[5]=="A63" ? "between 500 and 1000 DM"
                           : attr[5]=="A64" ? "1000 DM or more"
                           : "unknown, or the applicant has no savings account")
                         << ")" << endl;
                    cout << "Employment:       " << (r.employment ? "PASS" : "FAIL")
                         << " (value is " << attr[6] << ", where " << attr[6] << " means the applicant has been "
                         << (attr[6]=="A71" ? "unemployed"
                           : attr[6]=="A72" ? "employed for less than 1 year"
                           : attr[6]=="A73" ? "employed between 1 and 4 years"
                           : attr[6]=="A74" ? "employed between 4 and 7 years"
                           : "employed for 7 years or more")
                         << ")" << endl;
                    cout << "Decision:         " << (passed ? "APPROVED" : "DENIED") << endl;
                    break;
                }
                else if (filterChoice < 3 && passed == wantApproved) {
                    cout << "Applicant " << count << ": "
                         << (passed ? "APPROVED" : "DENIED")
                         << " (failed " << r.countFailed() << " rule/s)" << endl;
                }
            }
            if (filterChoice == 3 && count < target)
                cout << "Applicant " << target << " not found." << endl;
        }
        else if (filterChoice == 4) {
            cout << " Returning to main menu..." << endl;
        }
        else {
            cout << " Invalid choice. Please enter 1-4." << endl;
        }
    }
}

void showMenu(){
    cout<<"========================================="<<endl;
    cout<<" LOAN APPROVAL SYSTEM - MAIN MENU "<<endl;
    cout<<"========================================="<<endl;
    cout<<" 1. Run full engine analysis. "<<endl;
    cout<<" 2. Run combined rule engine. "<<endl;
    cout<<" 3. Show rules that are mostly denied. "<<endl;
    cout<<" 4. Filter by results. "<<endl;
    cout<<" 5. Exit. "<<endl;
    cout<<"========================================="<<endl;
    cout<<" Please enter your choice(1-5): "<<endl<<endl;
}

int main(){
    int choice = 0;
    while(choice != 5){
        showMenu();
        cin>>choice;

        if(cin.fail()){
            cin.clear() ;
            cin.ignore(1000,'\n') ;
            cout<<" invalid input. Please enter a number. "<<endl;
            continue ;
        }

        if(choice == 1){
            runFullAnalysis();
        }
        else if(choice == 2){
            runCombinedEngine();
        }
        else if(choice == 3){
            runXAI();
        }else if(choice == 4){
            runfilter();
        }else if(choice == 5){
            cout<<"Exiting the system, Goodbye. "<<endl;
        }else {
            cout<<"Invalid choice. please enter a choice from 1 to 5. "<<endl;
        }
    }
    return 0;
}
