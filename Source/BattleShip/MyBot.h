// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>

/**
 * 
 */
class MyBot
{
private:
	std::vector<int> shipsizes;
	std::vector<int> board;
	int hit;
	int target;
	bool wait;
	
	void bV(std::vector<int> dir, int square, int value);
	int sizeDir(int dir, int square);
	int firstDir(int dir, int square);
	std::vector<int> randomOrder(std::vector<int> v);
public:
	
	MyBot();
	bool ShotResult(int result);
	void setShipSizes(std::vector<int> s);
	int Shoot();
	void Reset();
	std::vector<int> CreateBoard();

	~MyBot();
	
};
