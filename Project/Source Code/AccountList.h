#pragma once
#ifndef AccountList_H
#define AccountList_H
#include<iostream>
#include<fstream>
#include<string>

struct Account {
	std::string accnt;
	std::string psswrd;
	Account* nextStudent = nullptr;
};

void loadAccountStudent(Account*& accounts);
void loadAccountTeacher(Account*& accounts);
void addAccount(Account*& listHead, std::string account, std::string password);
bool findStudent(Account* listHead, std::string accnt, std::string psswrd);
bool findTeacher(Account* listHead, std::string accnt, std::string psswrd);

void delList(Account* listHead);
#endif