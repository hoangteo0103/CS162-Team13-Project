#include "AccountList.h"

void loadAccount(Account*& accounts) {
	std::ifstream fin1;
	fin1.open("StudentAccount.txt");
	std::ifstream fin2;
	fin2.open("StudentPassword.txt");
	while (!fin1.eof()) {
		std::string tmpAcc, tmpPwrd;
		fin1 >> tmpAcc; fin2 >> tmpPwrd;
		addAccount(accounts, tmpAcc, tmpPwrd);
	}
	fin1.close(); fin2.close();
}

void addAccount(Account*& listHead, std::string account, std::string password) {
	if (!listHead) {
		listHead = new Account;
		listHead->accnt = account;
		listHead->psswrd = password;
		listHead->nextStudent = nullptr;
		return;
	}

	Account* tmp = new Account;
	tmp->accnt = account;
	tmp->psswrd = password;
	tmp->nextStudent = listHead;
	listHead = tmp;
}

bool findStudent(Account* listHead, std::string accnt, std::string psswrd) {
	for (Account* i = listHead; i; i = i->nextStudent) {
		if (!(i->accnt.compare(accnt)) && !(i->psswrd.compare(psswrd))) {
			return true;
		}
	}
	return false;
}

void delList(Account* listHead) {
	if (listHead->nextStudent) {
		delList(listHead->nextStudent);
	}
	delete listHead;
}