#pragma once
#ifndef AccountList_H
#define AccountList_H
#include<string>

struct Account {
	std::string accnt;
	std::string psswrd;
	Account* nextStudent = nullptr;
};

void addAccount(Account*& listHead, Account*& listLast, std::string account, std::string password);
bool findStudent(Account* listHead, std::string accnt, std::string psswrd);
void delList(Account* listHead);
#endif