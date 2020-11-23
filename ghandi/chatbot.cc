#include <iostream>
#include <vector>

using namespace std;

string welcome = 
    "I need to make sure I can trust you before I can give you the secret password. "
    "Please answer some questions that only you would know the answer to."
;
struct QuestionAnswer {
    string question;
    string answer;
};
vector<QuestionAnswer> parseQuestionAnswers(int argc,char **argv) {
    vector<QuestionAnswer> parsed;
    for (int i=1;i<argc-1;i+=2)
        parsed.push_back(QuestionAnswer {argv[i],argv[i+1]});
    return parsed;
};

bool isNegative(string answer) {
    return answer=="shut up" || answer=="heck";
}

int main(int argc, char **argv) {
    uint8_t trust = 100;
    cout<<welcome<<endl;

    vector<QuestionAnswer> questionAnswers =
        parseQuestionAnswers(argc,argv);

    for (const auto &qa : questionAnswers) {
        cout<<qa.question<<endl;
        string reply;
        getline(cin,reply);
        if (reply==qa.answer) trust+=30;
        if (isNegative(reply)) trust-=40;
    }
    if (trust>230) {
        cout<<"I trust you. The password is "<<argv[argc-1]<<endl;
    }
    else {
        cout<<"Sorry, I don't trust you. Maybe you made a typo?"<<endl;
    }
}