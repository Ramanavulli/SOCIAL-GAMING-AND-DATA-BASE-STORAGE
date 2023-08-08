#include <iostream>
#include <string>
#include <vector>

// Define structures for entities
struct Player {
    int playerId;
    std::string name;
    std::string registrationDate;
    // Structure to store game details for each player
    // You can expand this as needed.
    // For simplicity, let's assume gameId, scores, and prizes are integers.
    struct GameDetails {
        int gameId;
        int scores;
        int prizes;
    };
    std::vector<GameDetails> gamesPlayed;
    std::vector<std::string> gamePreferences;
};

struct GameMaster {
    int gameId;
    std::string name;
    std::string type;
    int numPlayersRequired;
};

struct GamesPlayed {
    int gameId;
    std::vector<int> playersId;
    std::vector<int> scores;
    std::vector<int> activeDays;
    std::string startDate;
    std::string endDate;
};

struct GuestUser {
    int id;
    std::string name;
    std::string date;
};

// Arrays to store database records
std::vector<Player> players;
std::vector<GameMaster> games;
std::vector<GamesPlayed> gamesHistory;
std::vector<GuestUser> guests;

// Helper functions
Player* findPlayerById(int playerId) {
    for (auto& player : players) {
        if (player.playerId == playerId) {
            return &player;
        }
    }
    return nullptr;
}

GameMaster* findGameById(int gameId) {
    for (auto& game : games) {
        if (game.gameId == gameId) {
            return &game;
        }
    }
    return nullptr;
}



// 1. Add/Update operations
void addUser(const std::string& name, const std::string& registrationDate, const std::vector<std::string>& gamePreferences) {
    int playerId = players.empty() ? 1 : players.back().playerId + 1;
    players.push_back({playerId, name, registrationDate, {}, gamePreferences});
}

void updateGamePlayedDetails(int playerId, int gameId, int score, int activeDays) {
    Player* player = findPlayerById(playerId);
    if (!player) {
        // If the player is not registered, make them a guest user.
        guests.push_back({playerId, "Guest", ""}); // Assuming date is not available for guest users.
        player = &guests.back();
    }

    player->gamesPlayed.push_back({gameId, score, 0, 0}); // Assuming prizes are not available at this point.

    // Update active days for guest user
    if (player == &guests.back()) {
        Guests* guest = static_cast<GuestUser*>(player);
        guest->date = "date"; // Update with actual date when the game is played.
        if (activeDays > 15) {
            // Guest user is playing for more than 15 days.
            // Prevent further play until registration is complete.
            return;
        }
    }
}




// 2. Search operations
std::vector<int> findOtherPlayersForGame(int playerId, int gameId) {
    std::vector<int> otherPlayers;
    for (const auto& game : gamesHistory) {
        if (game.gameId == gameId) {
            for (int i = 0; i < game.playersId.size(); ++i) {
                if (game.playersId[i] != playerId) {
                    otherPlayers.push_back(game.playersId[i]);
                }
            }
            break;
        }
    }
    return otherPlayers;
}

std::vector<int> findInactiveUsersForGame(int gameId) {
    std::vector<int> inactiveUsers;
    for (const auto& game : gamesHistory) {
        if (game.gameId == gameId && game.endDate.empty()) {
            for (int i = 0; i < game.playersId.size(); ++i) {
                Player* player = findPlayerById(game.playersId[i]);
                if (player && player->registrationDate.empty()) {
                    inactiveUsers.push_back(player->playerId);
                }
            }
            break;
        }
    }
    return inactiveUsers;
}

std::vector<Player> activeUsers(int k) {
    std::vector<Player> activeUsersList;
    for (const auto& player : players) {
        int activeGames = 0;
        for (const auto& game : player.gamesPlayed) {
            if (game.prizes > 0) { // Assuming a non-zero prize means the game is active.
                activeGames++;
            }
        }
        if (activeGames > k) {
            activeUsersList.push_back(player);
        }
    }
    return activeUsersList;
}




// 3. Sorting operations



bool compareGamesByPrizes(const GameMaster& game1, const GameMaster& game2) {
    // Sort in descending order of prizes won by players
    return game1.prizes > game2.prizes;
}

std::vector<GameMaster> gamesWithMostPrizes() {
    std::vector<GameMaster> sortedGames = games;
    std::sort(sortedGames.begin(), sortedGames.end(), compareGamesByPrizes);
    return sortedGames;
}

bool compareGamesByActiveDays(const GamesPlayed& game1, const GamesPlayed& game2) {
    // Sort in descending order of active days
    return game1.activeDays > game2.activeDays;
}

std::vector<GameMaster> top5GamesByActiveDays() {
    std::vector<GamesPlayed> activeGames;
    for (const auto& game : gamesHistory) {
        if (game.endDate.empty()) {
            activeGames.push_back(game);
        }
    }
    std::sort(activeGames.begin(), activeGames.end(), compareGamesByActiveDays);

    std::vector<GameMaster> top5Games;
    for (int i = 0; i < std::min(5, static_cast<int>(activeGames.size())); ++i) {
        GameMaster* game = findGameById(activeGames[i].gameId);
        if (game) {
            top5Games.push_back(*game);
        }
    }
    return top5Games;
}


std::vector<Player> getPlayersPlayingGame(int gameId) {
    std::vector<Player> playersPlaying;
    for (const auto& player : players) {
        for (const auto& game : player.gamesPlayed) {
            if (game.gameId == gameId && game.prizes > 0) { // Assuming a non-zero prize means the game is active.
                playersPlaying.push_back(player);
                break; // Assuming a player plays a game only once, so no need to check other games.
            }
        }
    }
    return playersPlaying;
}




// 4. Delete operation
// Function to delete guest users who are active for more than 20 days
void remove_guest(const std::string& currentDate) {
    // Use the std::remove_if algorithm to remove guest users who are active for more than 20 days.
    guests.erase(std::remove_if(guests.begin(), guests.end(), [&](const GuestUser& guest) {
        for (const auto& game : gamesHistory) {
            if (game.endDate.empty() && game.startDate <= currentDate && game.playersId.end() != std::find(game.playersId.begin(), game.playersId.end(), guest.id)) {
                // Calculate the number of active days for the guest user in this game.
                // For demonstration, I'll assume guest's start date as "2020-08-01".
                int activeDays = 5; // Replace this with actual calculation.

                if (activeDays > 20) {
                    // Remove guest user from gamesHistory.
                    for (auto& player : players) {
                        if (player.playerId == guest.id) {
                            for (auto it = player.gamesPlayed.begin(); it != player.gamesPlayed.end();) {
                                if (it->gameId == game.gameId) {
                                    it = player.gamesPlayed.erase(it);
                                } else {
                                    ++it;
                                }
                            }
                            break;
                        }
                    }
                    return true; // Remove guest from guests vector.
                }
            }
        }
        return false; // Do not remove guest from guests vector.
    }), guests.end());
}



int main() {
    int ch, ch1, ch2;
    while (true) {
        std::cout << "\n1. Add_user";
        std::cout << "\n2. Search";
        std::cout << "\n3. Sorting";
        std::cout << "\n4. Delete";
        std::cout << "\n0. Exit";

        std::cout << "\n\nEnter your choice: ";
        std::cin >> ch;

        switch (ch) {
            case 1:
                int playerId;
   		 std::string name, registrationDate;
   		 std::vector<std::string> gamePreferences;

   		 std::cout << "Enter Player ID: ";
   		 std::cin >> playerId;

    		std::cout << "Enter Player Name: ";
   		std::cin.ignore();
    		std::getline(std::cin, name);

    		std::cout << "Enter Registration Date (YYYY-MM-DD): ";
    		std::cin >> registrationDate;

   		 std::cout << "Enter Game Preferences (comma-separated): ";
    		std::cin.ignore();
    		std::string preferences;
   		 std::getline(std::cin, preferences);
   		 size_t pos = 0;
    		while ((pos = preferences.find(',')) != std::string::npos) {
        	gamePreferences.push_back(preferences.substr(0, pos));
        	preferences.erase(0, pos + 1);
    		}
    		gamePreferences.push_back(preferences);

    		// Call the actual function to add the user with the collected input


    		addUser(playerId, name, registrationDate, gamePreferences);


                break;
            case 2:
                std::cout << "\n1. SearchfindOtherPlayersForGame";
                std::cout << "\n2. Search findInactiveUsersForGame";
		std::cout << "\n3. Search activeUsers";
                std::cout << "\nEnter your choice: ";
                std::cin >> ch1;
                switch (ch1) {
                    case 1:
			cout<<"provide game id and player id";
			int gameid,player id;
			cin>>gameid >> player id;
                        SearchfindOtherPlayersForGame(playerid,gameid);
                        break;
		    case 2:
			cout<<"provide gameid";
			int gameid;
			cin>>gameid;
			findInactiveUsersForGame(gameid);
			break;
                    case 3:
			cout<<"provide the games number";		
			int k;
			cin>>k;
                        search_active_user(k);
                        break;
                    default:
                        std::cout << "\nInvalid choice for search operation.";
                        break;
                }
                break;
            case 3:
                std::cout << "\n1. Sorting Games by Most Prizes";
                std::cout << "\n2. Top 5 Games by Active Days";
                std::cout << "\n3. Display Player Details for Game";
                std::cout << "\nEnter your choice: ";
                std::cin >> ch2;
                switch (ch2) {
                    case 1:
                        Sorting_mostprizes();
                        break;
                    case 2:
                        top_5games();
                        break;
                    case 3:
                        int gameId;
                        std::cout << "\nEnter Game ID: ";
                        std::cin >> gameId;
                        Display_Details_G(gameId);
                        break;
                    default:
                        std::cout << "\nInvalid choice for sorting operation.";
                        break;
                }
                break;
            case 4:
                std::cout << "Enter the current date (YYYY-MM-DD): ";
                std::string currentDate;
                std::cin >> currentDate;
                remove_guest(currentDate);
                break;
            case 0:
                return 0;
            default:
                std::cout << "\nInvalid choice.";
                break;
        }
    }

    return 0;
}
