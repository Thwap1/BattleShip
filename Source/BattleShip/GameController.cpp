//Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "MyBlock.h"
#include "MyHUD.h"
#include "Engine/World.h"

#include <unordered_set>


// Sets default values
AGameController::AGameController()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameController::BeginPlay()
{
	Super::BeginPlay();
	GameState = 0;
	CreateGrids();
}

// Called every frame
void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
* Listens Userinput from board.
*  Gamestates go as:
*	0: player still making board
*   1: player still making board, but its valid to start shooting too
*   2:
*   4: playershoots
*   5: bot shoots
*   10: player wins
*   11: defeat
**/
void AGameController::BlockClick(int nro) {
	switch (GameState) {
	case  0: case 1:
		if (nro >= 0) {
			Board[0][nro]->gridvalue = -Board[0][nro]->gridvalue;
			GameStateChange(validateBoard(0) ? 1 : 0);
		}
		else {
			if (GameState == 1) {
				GameStateChange(5);
				CreateBoard(1);
				if (shoot(-nro - 1, 1) == 0) {
					while (shoot(FMath::RandRange(0, 99), 0) == -1 && GameState == 5);
				}
				if (GameState == 5) GameStateChange(4);
			}
		}
		break;


	case 4:
		if (nro < 0) {
			nro = -nro - 1;
			if (shoot(nro, 1) == 0) {
				GameState = 5;
				while (shoot(FMath::RandRange(0, 99), 0) != 0 && GameState == 5);
				if (GameState == 5)GameState = 4;
			}
		}
	}

}

bool AGameController::Victory(int nro) {
	for (AMyBlock* b : Board[nro]) {
		if (b->gridvalue == -1)return false;
	}
	GameStateChange(11 - nro);
	return true;
}


/**
* shoots on grid 
* return values
*  -1 cant shoot here
*  0 miss
*  1 hit
*  2 hit+ sink
*/
int AGameController::shoot(int nro, int boardNro) {

	if (Board[boardNro][nro]->gridvalue < -1)return -1;
	Board[boardNro][nro]->gridvalue -= 10;
	if (Board[boardNro][nro]->gridvalue == -11) {
		Board[boardNro][nro]->SetMaterial(3);
		int neighbour[] = { 1, -1, 10, -10, -9, -11, 9, 11 };
		std::unordered_set<int> surround;
		bool sink = true;

		for (const int i : {1, -1, 10, -10}) {
			int check = nro;
			do {
				if (Board[boardNro][check]->gridvalue == -11)
					for (const int n : neighbour) {
						if (check + n < 0 || check + n > 99 ||
							(check % 10 == 9 && (n == 11 || n == 1 || n == -9)) ||
							(check % 10 == 0 && (n == -11 || n == -1 || n == 9)))
							continue;
						surround.insert(check + n);
					}
				check += i;
				if (check < 0 || check > 99 ||
					(check % 10 == 9 && (i == -1)) ||
					(check % 10 == 0 && (i == 1))) break;

				if (Board[boardNro][check]->gridvalue == -1) sink = false;


			} while (sink && Board[boardNro][check]->gridvalue == -11);
		}
		if (sink) {
			for (const int i : surround)
				if (Board[boardNro][i]->gridvalue == 1) {
					Board[boardNro][i]->gridvalue -= 10;
					Board[boardNro][i]->SetMaterial(4);

				}
			Victory(boardNro);

		}
		else {
			for (int corners : {-9, -11, 9, 11}) {
				if (nro + corners < 0 || nro + corners > 99 ||
					(nro % 10 == 0 && (corners == -9 || corners == 9)) ||
					(nro % 10 == 9 && (corners == 11 || corners == -11))) continue;
				if (Board[boardNro][corners + nro]->gridvalue == 1) {
					Board[boardNro][corners + nro]->gridvalue -= 10;
					Board[boardNro][corners + nro]->SetMaterial(4);

				}
			}
			
		}
		return sink?2:1;
	}
	else {
		Board[boardNro][nro]->SetMaterial(2);
		return 0;
	}
}

void AGameController::OnClickAgain() {
	for (AMyBlock* b : Board[0]) {
		if (b->gridvalue < -2) {
			b->gridvalue += 10;
		}
	}
	for (AMyBlock* b : Board[1]) {
		b->SetMaterial(0);
		
	}
	GameStateChange(validateBoard(0) ? 1 : 0);
	
}

void AGameController::OnClickRandom(int nro) {
	GameState = -1;
	CreateBoard(0);
	GameStateChange(validateBoard(0)?1:0);
	
}

void AGameController::GameStateChange(int state) {
	if (state == GameState)return;
	
	
			AMyHUD* MyHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if(MyHUD)MyHUD->SetGameState(state);
	GameState = state;
}

bool AGameController::validateBoard(int nro) {
	std::unordered_set<int> s;
	std::unordered_set<int>::iterator it = s.begin();
	std::vector<int> sizes{};
	for (int i = 0; i < 100; ++i) it = s.insert(it, i); // searchlist for set of numbers 0-99
	int neighbour[] = { 1, -1, 10, -10, -9, -11, 9, 11 }; // offset to neighboursquares
	int x_ok, y_ok; // ship has to be in x ways or y ways, not both.
	bool valid=true;

	while (!s.empty()) {
		
		int squareNro = *s.begin();
		s.erase(s.begin());
		int size = 0;
		if (Board[nro][squareNro]->gridvalue == 1)
			Board[nro][squareNro]->SetMaterial(-1);				//color emptysquare blue
		else {																		//found first hit 
			size++;

			x_ok = squareNro % 10;
			y_ok = squareNro / 10;

			std::unordered_set<int> checklist;
			std::unordered_set<int> ship;
			ship.insert(squareNro);

			for (const int i : neighbour) {											//put all neightbours to checklist

				if ((squareNro % 10 == 9 && (i == 11 || i == 1 || i == -9)) ||
					(squareNro % 10 == 0 && (i == -11 || i == -1 || i == 9)))
					continue;													// unless they they overlap on x side.

				std::unordered_set<int>::const_iterator got = s.find(squareNro + i);	//neightbour has to still exists (check everything only once)
				if (got != s.end()) {
					checklist.insert(*got);
					s.erase(got);													//remove it from orginal searchlist
				}
			}

			while (!checklist.empty()) {											//iterate checklist until empty
				squareNro = *checklist.begin();
				checklist.erase(checklist.begin());
				if (Board[nro][squareNro]->gridvalue == 1)
					Board[nro][squareNro]->SetMaterial(-1);		//color emptysquare blue
				else {																//found next shippart	
					ship.insert(squareNro);
					if (x_ok != squareNro % 10) x_ok = -1;
					if (y_ok != squareNro / 10) y_ok = -1;


					size++;
					for (const int i : neighbour) {									//again add neighbours to checklist

						if ((squareNro % 10 == 9 && (i == 11 || i == 1 || i == -9)) ||
							(squareNro % 10 == 0 && (i == -11 || i == -1 || i == 9)))
							continue; // no overlaping x borders 

						std::unordered_set<int>::const_iterator got = s.find(squareNro + i);
						if (got != s.end()) {
							checklist.insert(*got);
							s.erase(got);
						}
					}
				}
			}
			int mat = (x_ok == -1 && y_ok == -1 || size > 5) ? 3 : 1;				//color ship valid or not valid
			if (mat == 3)valid = false;
			else {
				UE_LOG(LogTemp, Warning, TEXT("found ship of size %d"),ship.size());
				sizes.push_back(ship.size());
			}
			for (const int i : ship) {
				Board[nro][i]->SetMaterial(mat);
			}


		}

	}
	UE_LOG(LogTemp, Warning, TEXT("end of validation"));
	shipsizes = sizes;
	return valid;
}

void::AGameController::CreateBoard(int nro) {
	int shots = 100;																// shooting random holes before setting board
	bool gotship = false;														// ships done
	std::unordered_set<int> ships;
	
	std::vector<int> shipstemp = shipsizes;
	if (shipsizes.size() == 0)
		shipstemp = std::vector<int>{ 5,4,3,3,2 };
	std::unordered_set<int> numerot;											// set with 0-99 numbers
	std::unordered_set<int>::iterator it = numerot.begin();
	int neighbour[] = { 1, -1, 10, -10, -9, -11, 9, 11 };
	for (int i = 0; i < 100; ++i) it = numerot.insert(it, i);


	/* stays in this loop until all ships fit */
	/* first damages grid at random, then suffles postions */
	/* then starts fitting ships */
	/* if grid too damaged will loop again with one less shot*/
	do {
		ships.clear();
		std::unordered_set<int> s = numerot;									// copy constructor 

		for (int i = 0; i < shots; i++) {
			std::unordered_set<int>::const_iterator got = s.find(FMath::RandRange(0, 99));
			if (got != s.end()) s.erase(got);									// erasing possible places
		}

		for (int ship : shipstemp) {
			gotship = false;
			std::unordered_set<int> s3;											//suffle
			std::unordered_set<int>::iterator it2 = s3.begin();					//suffle
			while (!s.empty()) {												//suffle
				int random = (FMath::RandRange(0, s.size() - 1));				//suffle
				std::unordered_set<int>::iterator it3 = s.begin();				//suffle
				std::advance(it3, random);										//suffle
				s3.insert(it2, *it3);											//suffle
				s.erase(it3);													//suffle
			}
			s = s3;																//copy constructor


			while (!s3.empty() && !gotship) {									//now trying to fit ships
				int beginSquare = *s3.begin();
				int dir = (FMath::RandRange(0, 1) == 1) ? 1 : 10;					//randomize axis


				for (int j = 0; j < 2; j++) {

					if (FMath::RandRange(0, 1) == 1)dir = -dir;					//randomize testing direction 
					int size = -1;
					if (ship == 1) dir = 0; // ship of size 1 
					for (int i = 0; i < 2; i++) {								//flip testing direction
						dir = -dir;
						int squareNro = beginSquare;
						while (!gotship) {
							if ((squareNro % 10 == 9 && dir == 1) || (squareNro % 10 == 0 && dir == -1) || s3.find(squareNro) == s3.end()) break;

							if (++size == ship) {								//ship fits here, now reverse direction and place it.
								std::unordered_set<int> checklist;
								gotship = true;
								while (size-- > 0) {
									ships.insert(squareNro);
									s.erase(squareNro);
									for (int n : neighbour) {					//clear bordering areas too 
										if ((squareNro % 10 == 9 && (n == 11 || n == 1 || n == -9)) ||
											(squareNro % 10 == 0 && (n == -11 || n == -1 || n == 9)))
											continue;
										std::unordered_set<int>::const_iterator got = s.find(squareNro + n);
										if (got != s.end()) {
											s.erase(got);
										}
									}
									squareNro -= dir;
								}
							}

							if (s3.find(squareNro + dir) == s3.end())break;
							squareNro += dir;
						}
					}
					
					if (dir == 1 || dir == -1) dir = 10;						//change direction try to fit on other axis too.
						else dir = 1;
				}
				s3.erase(s3.begin());
			}
			if (!gotship)break;													//could not fit a ship break loop and try again with one less "shot" to grid
		}
		shots--;
	} while (!gotship);
	for (AMyBlock* b : Board[nro]) {
		b->gridvalue = 1;
	}
	for (int i : ships) {
		Board[nro][i]->gridvalue = -1;
	}
}

void AGameController::CreateGrids() {
	
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++) {
			const float XOffset = x * 105 - 1050;
			const float YOffset = y * 105 - 550;
			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
			AMyBlock* NewBlock = GetWorld()->SpawnActor<AMyBlock>(BlockLocation, FRotator(0, 0, 0));
			if (NewBlock != nullptr)
			{
				NewBlock->GC = this;
				NewBlock->nro = (x + y * 10) ;
				Board[0][x + y * 10] = NewBlock;

			}
			const float XOffset2 = x * 105+105;
			const FVector BlockLocation2 = FVector(XOffset2, YOffset, 0.f) + GetActorLocation();
			NewBlock = GetWorld()->SpawnActor<AMyBlock>(BlockLocation2, FRotator(0, 0, 0));
			if (NewBlock != nullptr)
			{
				NewBlock->GC = this;
				NewBlock->nro = -(x+y * 10)-1;
				Board[1][x + y * 10] = NewBlock;
			}
		}



}

