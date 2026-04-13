//Chain Of Responsibility

// Leave Request System : This is presented as a homework problem, often asked in interviews. In this scenario, an employee submits a leave request, and it goes through a hierarchy of approvers:
// Requests for two or fewer days are approved by the team lead .
// Requests for more than two but fewer than five days go to the manager .
// Requests that the manager cannot approve (e.g., exceeding five days) go to the director .

#include<iostream>
using namespace std;

//Abstract Handler(Base Class)
class LeaveHandler {
    protected:
        LeaveHandler *nextHandler;

    public:
        LeaveHandler() {
            this->nextHandler = nullptr;
        }

        void setNextHandler(LeaveHandler *next) {
            nextHandler = next;
        }

        virtual void handleRequest(int days) = 0;
};

class TeamLeadHandler : public LeaveHandler {
        void handleRequest(int days) override {
            if(days<=2) {
                cout<< "Team Lead approved "<< days << "Days of Leave "<<endl;
            }
            else {
                if(nextHandler != nullptr) nextHandler->handleRequest(days);
                else cout<< "Enter a valid Leave Days Request"<<endl;
            }
        }
};

class ManagerHandler : public LeaveHandler {
        void handleRequest(int days) override {
            if(days>2 && days<5) {
                cout<< "Manager approved "<< days << "Days of Leave "<<endl;
            }
            else {
                if(nextHandler != nullptr) nextHandler->handleRequest(days);
                else cout<< "Enter a valid Leave Days Request"<<endl;
            }
        }
};
class DirectorHandler : public LeaveHandler {
        void handleRequest(int days) override {
            if(days>=5) {
                cout<< "Director approved "<< days << "Days of Leave "<<endl;   
            }
            else {
                if(nextHandler != nullptr) nextHandler->handleRequest(days);
                else cout<< "Enter a valid Leave Days Request"<<endl;
            }
        }
};

int main() {
    LeaveHandler *teamLeadHandler = new TeamLeadHandler();
    LeaveHandler *managerHandler = new ManagerHandler();
    LeaveHandler *directorHandler = new DirectorHandler();  

    teamLeadHandler->setNextHandler(managerHandler);
    managerHandler->setNextHandler(directorHandler);

    int leaveDays=7;
    cout<<"Requested "<<leaveDays<<" Days of Leave"<<endl;
    teamLeadHandler->handleRequest(leaveDays);

    return 0;
}
