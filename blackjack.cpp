#include <iostream>
#include <ctime>

using namespace std;

// Function declarations
void initializeDeck(int deck[], int numDecks);
int dealCard(int deck[]);
int calculateScore(int hand[], int numCards);
void displayHands(int playerHand[], int cpuHand[]);
void displayCard(int card);
void displayResult(int playerScore, int cpuScore);
const int numDecks = 6;
const int maxCards = 52 * numDecks;
int deck[maxCards];
int playerHand[10], cpuHand[10]; // Assuming maximum 10 cards per hand
int playerScore, cpuScore, playerBet, playerFunds;

int main() {

    srand(static_cast<unsigned>(time(0)));
    int alreadyOver = 0;

    // Game setup
    cout << "Welcome to Blackjack!\n";
    cout << "Enter your initial funds: ";
    cin >> playerFunds;

    while (playerFunds > 0) {
        initializeDeck(deck, numDecks);
        playerScore = 0;
        cpuScore = 0;

        // Get player bet
        cout << "Current funds: $" << playerFunds << endl;
        cout << "Enter your bet: ";
        cin >> playerBet;
        while(playerBet > playerFunds) {
            cout << "You can't bet more than you have, enter your bet Amount again." << endl;
            cout << endl;
            cin >> playerBet;
        }
        
        cout << " " << endl;
        cout << "Round Bet: $" << playerBet << endl;

        // Deal initial cards
        playerHand[0] = dealCard(deck);
        cpuHand[0] = dealCard(deck);
        playerHand[1] = dealCard(deck);
        cpuHand[1] = dealCard(deck);

        // Main game loop
        bool playerStand = false;
        while (!playerStand) {
            // Display hands
            displayHands(playerHand, cpuHand);

            // Player's turn
            cout << "Do you want to (1) Hit or (2) Stand? ";
            int choice;
            
            cin >> choice;
            cout << endl;
            while(choice != 1 && choice !=2) {
                cout << "Invalid input, (1) Hit or (2) Stand:" << endl;
                if(choice == 1 || choice == 2) {
                    break;
                }
                cin >> choice;
            }

            if (choice == 1) {
                int nextIndex = 0;
                while (playerHand[nextIndex] != 0) {
                    nextIndex++;
                }
                playerHand[nextIndex] = dealCard(deck);
            } else {
                playerStand = true;
            }

            // Check if player busted
            playerScore = calculateScore(playerHand, 10);
            if (playerScore > 21) {
                displayHands(playerHand, cpuHand);
                cout << "Busted! You lose $" << playerBet << endl;
                alreadyOver++;
                playerFunds -= playerBet;
                break;
            }
        }

        // CPU Player's turn
        while (calculateScore(cpuHand, 10) < 17) {
            int cpuIndex = 0;
            while (cpuHand[cpuIndex] != 0) {
                cpuIndex++;
            }

            cpuHand[cpuIndex] = dealCard(deck);
        }

        // Display final hands and results
        if(alreadyOver != 1) {
            displayHands(playerHand, cpuHand);
            playerScore = calculateScore(playerHand, 10);
            cpuScore = calculateScore(cpuHand, 10);
        }
        alreadyOver = 0;

        if (cpuScore > 21 || (playerScore <= 21 && playerScore > cpuScore)) {
            cout << "You win $" << playerBet << "!\n";
            playerFunds += playerBet;
        } else if (playerScore == cpuScore || (playerScore > 21 && cpuScore > 21)) {
            cout << "It's a tie. Your bet is returned.\n";
        } else if (cpuScore > playerScore){
            cout << "You lose $" << playerBet << ". Better luck next time.\n";
            playerFunds -= playerBet;
        }

        if(playerFunds == 0) {
            cout << "Your don't have enough funds." << endl;
            cout << endl;
            break;
        }

        // Ask if the player wants to play again
        char playAgain;
        
        cout << endl;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        for (int i = 0; i < 10; i++) {
            playerHand[i] = 0;
            cpuHand[i] = 0;
        }

        if (tolower(playAgain) == 'n') {
            break;
        }
    }

    cout << "Thanks for playing! Your final funds: $" << playerFunds << endl;

    return 0;
}


// Function definitions

void initializeDeck(int deck[], int numDecks) {
    for (int i = 0; i < 52 * numDecks; i++) {
        deck[i] = (i % 13) + 1;
    }
}

int dealCard(int deck[]) {
    int index = rand() % maxCards;

    while (deck[index] == 0) {
        index = rand() % maxCards;
    }

    int card = deck[index];
    deck[index] = 0; // Mark card as dealt
    return card;                   
}

int calculateScore(int hand[], int numCards) {
    int score = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; i++) {
        int cardValue = min(hand[i], 10); // Face cards have a value of 10
        score += cardValue;

        if (hand[i] == 1) {
            score += 10;
        }
    }

    // Handle Aces
    /*
    while (numAces > 0 && score + 10 <= 21) {
        score += 10;
        numAces--;
    }
    */

    return score;
}



void displayHands(int playerHand[], int cpuHand[]) {
    cout << "Your hand: ";
    for (int i = 0; playerHand[i] != 0; i++) {
        displayCard(playerHand[i]);
        cout << " ";
    }
    cout << "(" << calculateScore(playerHand, 10) << ")\n";

    cout << "CPU hand: ";
    for (int i = 0; cpuHand[i] != 0; i++) {
        displayCard(cpuHand[i]);
        cout << " ";
    }
    cout << "(" << calculateScore(cpuHand, 10) << ")\n";
}


void displayCard(int card) {
    switch (card) {
        case 1:
            cout << "A";
            break;
        case 11:
            cout << "J";
            break;
        case 12:
            cout << "Q";
            break;
        case 13:
            cout << "K";
            break;
        default:
            cout << card;
            break;
    }
}

void displayResult(int playerScore, int dealerScore) {
    cout << "Player Score: " << playerScore << endl;
    cout << "Dealer Score: " << dealerScore << endl;
}

