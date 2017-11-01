/*
 * LLSE.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: Michael Ly
 */

/* Michael Ly, Nikita Doskochynskyy
 * TA: Eeshita Biswas
 * 10/29/17
 * Lab 5
 * This file contains functions for Lab 5.
 */

#include "LLSE.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

LLSE::LLSE() {
	first = NULL;
	last = NULL;
	size = 0;
	wordcount = 0;
}

LLSE::~LLSE() {
	Node* temp;
	while (temp != NULL) {
		temp = first->next;
		temp->prev = NULL;
		delete first;
		first = temp;
	}
}

void LLSE::printLL() { // working
	Node* temp = first;
	while (temp != NULL) {
		if (temp != last) {
			cout << temp->word << ":" << temp->count << ", ";
		}
		if (temp == last) {
			cout << temp->word << ":" << temp->count << ".";
		}
		temp = temp->next;
	}
	cout << endl;
}

void LLSE::addFirst(string x) { // working
	Node* n = new Node(x);
	first = n;
	last = n;
	size += 1;
	wordcount += 1;
}

void LLSE::addAtFirst(string x) { // working
	Node* n = new Node(x);
	n->next = first;
	first->prev = n;
	n->prev = NULL;
	first = n;
	size += 1;
	wordcount += 1;
}

void LLSE::push(string x) { // working
	Node* n = new Node(x);
	n->next = NULL;
	last->next = n;
	n->prev = last;
	last = n;
	size += 1;
	wordcount += 1;
}

void LLSE::insertUnique(string x) { // working
	if (first == NULL) {
		addFirst(x);
	}
	else if (x < first->word) {
		addAtFirst(x);
	}
	else if (x > last->word) {
		push(x);
	}
	else {
		Node* insert = findInsert(x);
		if (insert != NULL) {
			Node* n = new Node(x);
			Node* temp = insert->next;
			insert->next = n;
			n->prev = insert;
			temp->prev = n;
			n->next = temp;
			size += 1;
			wordcount += 1;
		}
	}
}

Node* LLSE::findInsert(string x) { // working
	Node* temp = first;
	Node* insert;
	while (temp != NULL) {
		if (temp->word == x) {
			temp->count += 1;
			wordcount += 1;
			insert = NULL;
			break;
		}
		else if (temp->word > x) {
			insert = temp->prev;
			break;
		}
		temp = temp->next;
	}
	return insert;
}

void LLSE::normalizeCounts() { // working
	Node* temp = first;
	while (temp != NULL) {
		temp->count /= wordcount;
		temp = temp->next;
	}
}

string LLSE::remFirst() { // working
	Node* temp = first;
	string remWord = temp->word;
	size -= 1;
	wordcount -= temp->count;
	first = first->next;
	first->prev = NULL;
	first->next = temp->next->next;
	delete temp;
	return remWord;
}

string LLSE::pop() { // working
	Node* temp = last;
	string remWord = temp->word;
	size -= 1;
	wordcount -= temp->count;
	last = last->prev;
	last->next = NULL;
	last->prev = temp->prev->prev;
	delete temp;
	return remWord;
}

string LLSE::remNext(Node* n) { // working
	Node* temp = n->next;
	Node* temp2 = n->next->next;
	string remWord = temp->word;
	size -= 1;
	wordcount -= temp->count;
	n->next = temp2;
	temp2->prev = n;
	temp->prev = NULL;
	temp->next = NULL;
	delete temp;
	return remWord;
}

void LLSE::eliminateLowWords() { // working
	while (first->count < 0.004) {
		cout << "removing " << remFirst() << endl;
	}
	while (last->count < 0.004) {
		cout << "removing " << pop() << endl;
	}
	Node* temp = first;
	while (temp->next != NULL) {
		start:
		if (temp->next->count < 0.004) {
			cout << "removing " << remNext(temp) << endl;
			goto start;
		}
			temp = temp->next;
	}
}

