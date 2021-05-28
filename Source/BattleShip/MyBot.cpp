// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBot.h"
#include <unordered_set>
#include <algorithm>
#include <random>

MyBot::MyBot()
{
	Reset();
}

MyBot::~MyBot()
{
}

int MyBot::Shoot() {

	hit = -99;
	if (target!=-1) {
		
		std::unordered_set<int> s;
		std::unordered_set<int>::iterator it = s.begin();
		int xmin = sizeDir(-1, target);
		int xmax = sizeDir(1, target);
		int ymin = sizeDir(-10, target);
		int ymax = sizeDir(10, target);
		
		if (xmax * xmin > ymin * ymax) {
			if (ymin != 0) hit = firstDir(-10, target);
			else if (ymax != 0) hit = firstDir(10, target);
		}
		else if (xmax * xmin < ymin * ymax) {
			if (xmin != 0)hit = firstDir(-1, target);
			else if (xmax != 0)hit = firstDir(1, target);
		}
		if(hit==-99)
			for (int i : randomOrder({ -1,1,-10,10 })) {
				if (sizeDir(i, target) != 0) {
					hit = firstDir(i, target);
					break;
				}
			}
		
		if(hit !=-99)
			return hit;
		
	}

	
	hit = FMath::RandRange(0, 99);
	return hit;
}
/**
* 2=sink, 1=hit, 0=miss, -1 nothing.
**/
bool MyBot::ShotResult(int result) {
	UE_LOG(LogTemp, Warning, TEXT("result %d"), result);
	if (result != -1) {
		
		board[hit] = result;
		if (result == 1) {
			board[hit] = 3;
			if(target==-1)target= hit;
			bV({ -11,11,9,-9 }, hit, 0);
			
		}
		if (result == 2) {
			board[hit] = 3;
			for (int i = 0; i < 100;++i) {
				if (board[i] == 3) {
					board[i] = 1;
					bV({ -11,11,9,-9,1,-1,10,-10 }, i, 0);
				}
			}
			target = -1;
			
		}
		
	} 

	return (result != 0);
}

void MyBot::bV(std::vector<int> dirs, int square, int value) {
	for (int dir : dirs) {
		if (square + dir < 0 || square + dir > 99 ||
			(square % 10 == 0 && (dir == -11 || dir == -1 || dir == 9)) ||
			(square % 10 == 9 && (dir == 11 || dir == 1 || dir == -9)) || board[square+dir]!=10
			)continue;
		
		board[square + dir] = value;
	}
}

void MyBot::Reset() {
	wait=true;
	target = -1;
	hit = -1;
	board.clear();
	std::vector<int>::iterator it = board.begin();
	for (int i = 0; i < 100; ++i) it = board.insert(it, 10);
	wait = false;
}

std::vector<int> MyBot::CreateBoard() {
	return board;
}

void MyBot::setShipSizes(std::vector<int> s) {
	shipsizes = s;
};

int MyBot::sizeDir(int dir, int square) {
	int size = 0;
	bool valid = false;  //is there any empty squares.
	while(true){
		if (square + dir < 0 || square + dir > 99 ||
			(square % 10 == 0 && (dir == -11 || dir == -1 || dir == 9)) ||
			(square % 10 == 9 && (dir == 11 || dir == 1 || dir == -9))
			|| (board[square + dir] == 0))break;
			size++;
			if (board[square+dir] == 10)valid = true;
			square += dir;
	}
	return valid?size:0;
}
int MyBot::firstDir(int dir, int square) {
	UE_LOG(LogTemp, Warning, TEXT("I %d running:%d"), dir, square);
	
	while (board[square] != 10) {
		square += dir;
	} 
	return square;
}

std::vector<int> MyBot::randomOrder(std::vector<int> v) {
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(v), std::end(v), rng);
	return v;
}