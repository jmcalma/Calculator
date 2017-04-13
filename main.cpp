//  Jerahmeel Calma
//  CS 256 - Zaidi
//  Assignment 3
//
//  Created by Jerahmeel Calma on 5/29/16.
//  Copyright © 2016 Jerahmeel Calma. All rights reserved.

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

map<string, double> Eval(string var, string expression, map<string, double> variables) {
    double result = 0.0;
    double num1, num2;
    double output = 0;
    vector <double> numbers;
    
    for(int i = 1; i < expression.length(); i++) {
        if((expression[i] >= 'A' && expression[i] <= 'Z') || (expression[i] >= 'a' && expression[i] <= 'z')) {
            string key;
            while(expression[i] != ' ') {
                key += expression[i];
                i++;
            }
            numbers.push_back(variables[key]);
        }else if(expression[i] == '=') {
            variables[var] = numbers.back();
            numbers.pop_back();
            output = variables[var];
        }else if(expression[i] == '^') {
            output = variables[var];
            break;
        }else if(expression[i] == '+') {
            num2 = numbers.back();
            numbers.pop_back();
            num1 = numbers.back();
            numbers.pop_back();
            result = (num1 + num2);
            numbers.push_back(static_cast<double>(result));
        }else if(expression[i] == '-' && expression[i+1] == ' ') {
            num2 = numbers.back();
            numbers.pop_back();
            num1 = numbers.back();
            numbers.pop_back();
            result = (num1 - num2);
            numbers.push_back(static_cast<double>(result));
        }else if(expression[i] == '*') {
            num2 = numbers.back();
            numbers.pop_back();
            num1 = numbers.back();
            numbers.pop_back();
            result = (num1 * num2);
            numbers.push_back(static_cast<double>(result));
        }else if(expression[i] == '/') {
            num2 = numbers.back();
            numbers.pop_back();
            num1 = numbers.back();
            numbers.pop_back();
            result = (num1 / num2);
            numbers.push_back(static_cast<double>(result));
        }else if(expression[i] != ' ' && expression[i+1] != ' ') {
            string token;
            while(expression[i] != ' ') {
                token += expression[i];
                i++;
            }
            double item = stod(token);
            numbers.push_back(static_cast<double>(item));
        }else if(expression[i] == ' ') {
            continue;
        }else {
            numbers.push_back(static_cast<double>(expression[i] - '0'));
        }
    }
    return variables;
}

bool contains(string var, std::vector<string> list) {
    for(int i = 0; i < list.size(); i++) {
        if(list[i] == var) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    map<string, double> variables;
    vector<string> files;
    vector<string> varlist;
    string first;
    string var;
    string expression;
    string fileName;
    string header = "/Users/Jerahmeel/Desktop/";
    ifstream in;
    ofstream out;
    bool write = false;
    cout << "Input statements: " << endl << "To exit input 'QUIT'" << endl;
    
    while(true) {
        cin >> first;
        if(first == "QUIT") {
            break;
        }else if(first == "CREATE") {
            write = true;
            cin >> fileName;
            if(!contains(fileName, files)) {
                files.push_back(fileName);
            }
            string token = header + fileName;
            out.open(token, ios::out);
        }else if(first == "SAVE") {
            write = false;
            out.close();
        }else if(first == "RUN") {
            cin >> fileName;
            string token = header + fileName;
            in.open(token, ios::in);
            while(!in.eof()) {
                in >> var;
                getline(in, expression);
                variables = Eval(var, expression, variables);
                if(expression == " ^") {
                    if(in.eof()) {
                        break;
                    }
                    cout.precision(4);
                    cout << var << " = " << fixed << variables[var] << endl;
                }
            }
            in.close();
        }else if(first == "LIST") {
            for(int i = 0; i < files.size(); i++) {
                cout << files[i] << endl;
            }
        }else if(first == "VARLIST") {
            for(int i = 0; i < varlist.size(); i++) {
                cout << varlist[i] << " = " << variables[varlist[i]] << endl;
            }
        }else if(write == true) {
            if(!contains(first, varlist)) {
                varlist.push_back(first);
            }
            getline(cin, expression);
            out << first << expression << endl;
        }
    }
    return 0;
}