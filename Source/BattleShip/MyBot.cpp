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
	if (target != -1) {

		
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
		if (hit == -99)
			for (int i : randomOrder({ -1,1,-10,10 })) {
				if (sizeDir(i, target) != 0) {
					hit = firstDir(i, target);
					break;
				}
			}

		if (hit != -99)
			return hit;

	}
	// hunt mode


	hit = Hunting();
	//hit = FMath::RandRange(0, 99);
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
			targetsize++;
			board[hit] = 3;
			if(target==-1) target= hit;
			bV({ -11,11,9,-9 }, hit, 0);
			
		}
		if (result == 2) {
			targetsize++;
			board[hit] = 3;
			for (int i = 0; i < 100; ++i) {
				if (board[i] == 3) {
					board[i] = 1;
					bV({ -11,11,9,-9,1,-1,10,-10 }, i, 0);
				}
			}
			target = -1;

			shipsizes.erase(std::remove(shipsizes.begin(), shipsizes.end(), targetsize), shipsizes.end());
			std::vector<int>::const_iterator it;
			it = max_element(shipsizes.begin(), shipsizes.end());
			maxship = *it;
			targetsize = 0;
			
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
	targetsize = 0;
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
	std::vector<int>::const_iterator it;
	it = max_element(shipsizes.begin(), shipsizes.end());
	maxship = *it;
}

int MyBot::sizeDir(int dir, int square) {
	int size = 0;
	bool valid = false;  //is there any empty squares.
	while (true) {
		if (square + dir < 0 || square + dir > 99 ||
			(square % 10 == 0 && (dir == -11 || dir == -1 || dir == 9)) ||
			(square % 10 == 9 && (dir == 11 || dir == 1 || dir == -9))
			|| (board[square + dir] == 0))break;
		size++;
		if (board[square + dir] == 10)valid = true;
		square += dir;
	}
	return valid ? size : 0;
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

int MyBot::Hunting() {
	
	
	std::unordered_set<int> where;											
	std::unordered_set<int>::iterator it = where.begin();
	
	int segment1[] = { 0,1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,91,92,93,94,95,96,97,98,99,19,29,39,49,59,69,79,89,99 }; //borders
	int segment2[] = { 33,34,35,36,43,44,45,46,53,54,55,56,63,64,65,66 }; //center;
	int checkerboard[] = { 0, 2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, 28, 31, 33, 35, 37, 39, 40, 42, 44, 46, 48, 51, 53, 55, 57, 59, 60, 62, 64, 66, 68, 71, 73, 75, 77, 79, 80, 82, 84, 86, 88, 91, 93, 95, 97, 99 };
	int check1 = 0;
	int check2 = 0;
	int seg1 = 0;
	int seg2 = 0;
	int rows[2][10];
	int columns[2][10];
	
	for (int i = 0; i < 100; ++i) {
		if (board[i] == 10) {
			where.insert(it, i);
			if (std::find(std::begin(checkerboard), std::end(checkerboard), i) != std::end(checkerboard))check1++;

			else check2++;
			/*for (int ship : shipsizes) */
			for (int dir : {1, 10})
				if (sizeDir(dir, i) >= maxship)
					for (int offset = 0; offset < maxship*dir; offset+=dir)
						for (int j = 0; j < maxship; j++)
							for(int k=0;k<5;k++)
								where.insert(it, i+ offset);
			
		}
		else if (board[i] == 0) {

			rows[0][i / 10]++;
			columns[0][i % 10]++;
		}
		else if (board[i] > 0) {

			if (std::find(std::begin(segment1), std::end(segment1), i) != std::end(segment1))seg1++;
			if (std::find(std::begin(segment2), std::end(segment2), i) != std::end(segment2))seg2++;
			rows[1][i / 10]++;
			columns[1][i % 10]++;
		}

	}
	/*int k = -1;
		for (int i : rows[0]) {
			k++;
			if (i < 2)
				for (int j = 0; j < 10; j++)
					where.insert(it, k * 10 + j);
		}
		k = -1;
		for (int i : columns[0]) {
			k++;
			if (i < 2)
				for (int j = 0; j < 10; j++)
					where.insert(it, k + j * 10);
		}
		k = -1;
		for (int i : rows[1]) {
			k++;
			if (i > 1)
				for (int j = 0; j < 10; j++)
					where.insert(it, k * 10 + j);
		}
		k = -1;
		for (int i : columns[1]) {
			k++;
			if (i > 1)
				for (int j = 0; j < 10; j++)
					where.insert(it, k + j * 10);
		}
		for (int i = 0; i < seg1; i++) {
			for (int j : segment1) {
				where.insert(it, j);
			}
		}
		for (int i = 0; i < seg2; i++) {
			for (int j : segment1) {
				where.insert(it,  j );
			}
		}*/
		
		if (maxship> 1 && check1 > 0 && check1 < check2) {
			do {
			
				it = where.begin();
				int shoot = FMath::RandRange(0, where.size() - 1);
				it = where.begin();
				std::advance(it, shoot);
				int val = *it;
			
				if (board[val] != 10)continue;
				if (std::find(std::begin(checkerboard), std::end(checkerboard), val) != std::end(checkerboard))return val;

			} while (true);
		}
		else if (maxship > 1 && check2 > 0)
			do {
			
				
				int shoot = FMath::RandRange(0, where.size()-1 );
				UE_LOG(LogTemp, Warning, TEXT("b SIze: %d,shoot %d"), where.size(),shoot);
				it = where.begin();
				std::advance(it, shoot);
				int val = *it;
				if (board[val] != 10)continue;
				if (std::find(std::begin(checkerboard), std::end(checkerboard), val) != std::end(checkerboard));
				else return val;

			} while (true);

			while (true) {
				int shoot = FMath::RandRange(0, where.size() - 1);
				it = where.begin();
				std::advance(it, shoot);
				int val = *it;
				if (board[val] != 10)continue;
				return val;
				
	}
		return 1;
		
		
}