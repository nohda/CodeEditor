//Subject.cpp
/*
���ϸ� : Subject.cpp
�ۼ����� : 2019�� 03�� 29��
�ۼ��� : �迵��
��� :
���� :
*/

#include "Subject.h"
#include "Observer.h"

int CompareObservers(void *one, void *other);

Subject::~Subject() {
}

Subject::Subject(Long capacity) :observers(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

void Subject::SubjectAttach(Observer *observer) {
	if (this->capacity > this->length) {
		this->observers.Store(this->length, observer);
	}
	else {
		this->observers.AppendFromRear(observer);
		this->capacity++;
	}
	this->length++;
}

void Subject::SubjectDetach(Observer *observer) {
	Long index;
	index = this->observers.LinearSearchUnique(observer, CompareObservers);
	this->observers.Delete(index);
}

void Subject::Notify(){
	Long i = 0;

	while (i < this->length) {
		this->observers[i]->Update();
		i++;
	}
}

int CompareObservers(void *one, void *other) {
	int ret =-1;

	if (one == other) {
		ret = 0;
	}
	
	return ret;
}