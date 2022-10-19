#include "../include/Player.h"
#include "../include/CheckersBoard.h"
#include "../include/Button.h"
#include "../include/GameState.h"

//Método que permite al usuario jugar
Player::Player(bool topSideOfBoard, CheckersBoard *board, Button buttons[]){
    Board = board;
    boardButtons = buttons;
    topSide = topSideOfBoard;
    currentIndex = 0;
    initTeam();
    if (topSideOfBoard) {
        ONE = 1;
        turn = false;
    }
    else{
        ONE = -1;
        turn = true;
    }
}

//Constructor de la clase
Player::~Player(){
    team.clear();
    //delete Board;
    Board = NULL;
    //delete boardButtons;
    boardButtons = NULL;
}

//-- que ejecuta el proceso en ejecución tras la carga del núcleo y el que a su vez genera todos los demás procesos
void Player::initTeam() {
    if (topSide) {
        //----------------------------BLACK TEAM----------------------------\\
        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 0
        team[0].x = 1;
        team[0].y = 0;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 1
        team[1].x = 3;
        team[1].y = 0;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 2
        team[2].x = 5;
        team[2].y = 0;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 3
        team[3].x = 7;
        team[3].y = 0;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 4
        team[4].x = 0;
        team[4].y = 1;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 5
        team[5].x = 2;
        team[5].y = 1;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 6
        team[6].x = 4;
        team[6].y = 1;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 7
        team[7].x = 6;
        team[7].y = 1;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 8
        team[8].x = 1;
        team[8].y = 2;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 9
        team[9].x = 3;
        team[9].y = 2;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 10
        team[10].x = 5;
        team[10].y = 2;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 11
        team[11].x = 7;
        team[11].y = 2;

        //Sets TEAM_NUMBER
        TEAM_NUMBER = BLACK_PIECE;
        ENEMY_TEAM_NUMBER = RED_PIECE;
    }
    else {
        //-----------------------------RED TEAM----------------------------\\
        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 0
        team[0].x = 0;
        team[0].y = 7;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 1
        team[1].x = 2;
        team[1].y = 7;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 2
        team[2].x = 4;
        team[2].y = 7;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 3
        team[3].x = 6;
        team[3].y = 7;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 4
        team[4].x = 1;
        team[4].y = 6;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 5
        team[5].x = 3;
        team[5].y = 6;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 6
        team[6].x = 5;
        team[6].y = 6;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 7
        team[7].x = 7;
        team[7].y = 6;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 8
        team[8].x = 0;
        team[8].y = 5;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 9
        team[9].x = 2;
        team[9].y = 5;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 10
        team[10].x = 4;
        team[10].y = 5;

        //Push back new chip created with default constructor.
        team.push_back(Piece());
        //Vector now has 1 element @ index 11
        team[11].x = 6;
        team[11].y = 5;


        //Sets TEAM_NUMBER
        TEAM_NUMBER = RED_PIECE;
        ENEMY_TEAM_NUMBER = BLACK_PIECE;
    }

        // Update Virtual board after init //

    for (int teamIndex = 0; teamIndex < team.size(); teamIndex++) {
        Board->virtualBoard[team[teamIndex].x][team[teamIndex].y] = topSide + 1;
    }
}

//Método que permite al jugador escoger el movimiento que tendrán las fichas
bool Player::makeMove(SDL_Event *){
    return false;
}

//Método que identifica que las fichas son del mismo equipo
bool Player::sameTeam(int value1, int value2){
    // checks if two peices are on the same team
    if (value1%2 == value2%2 && value1 != EMPTY_PIECE) {
        return true;
    }
    return false;
}

//Método que permite al jugador mover las fichas
void Player::movePiece(vector<vector<int>> &pBoard, vector<Piece>& teamMove, int teamIndex, int newX, int newY){
    // Moves piece by its selected teamIndex to its (newX, newY) location
    if (abs(newX - teamMove[teamIndex].x) == 2 && abs(newY - teamMove[teamIndex].y) == 2) {
        // Kills piece at average location
        killPiece(pBoard , abs(newX + teamMove[teamIndex].x)/2, abs(newY + teamMove[teamIndex].y)/2);
        // Gives player knowledge on which piece made the kill
        killerPeiceIndex = teamIndex;
    }
    pBoard[newX][newY] = pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y];
    pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y] = EMPTY_PIECE;
    teamMove[teamIndex].x = newX;
    teamMove[teamIndex].y = newY;

    // Prints virtualBoard at end of move
    //cout<<pBoard<<endl;
}

//Método que permite al jugador comer fichas del oponente
void Player::killPiece(vector<vector<int>> &pBoard, int x, int y) {
    pBoard[x][y] = EMPTY_PIECE;
    killWasMade = true;
}

//Método que actualiza al equipo del usuario
void Player::updateTeam() {
    // Updates team when team.size() has been altered
    bool updateMade = false;
    for(int index=0;index<team.size();index++){
        if (!sameTeam(Board->virtualBoard[team[index].x][team[index].y], TEAM_NUMBER)) {
            team.erase(team.begin()+index);
            index--;
            updateMade = true;
            cout<<"Team:\t"<<TEAM_NUMBER<<"\thas a team.size():\t" << team.size() <<endl;
        }
    }
    if (updateMade) {
        cout<<"*Team updated"<<endl;
    }
}

//Método que actualiza las Reinas del equipo del usuario
void Player::updateKings() {

    int yToMakeKing = 7 * topSide;
    bool updateMade = false;
    for(int index=0;index<team.size();index++){
        if (team[index].y == yToMakeKing && !team[index].isKing()) {
            team[index].makeKing();
            Board->virtualBoard[team[index].x][team[index].y] += 2;
            updateMade = true;
        }
    }
    if (updateMade) {
        cout<<"*Kings updated"<<endl;
    }
}

//Método que obtiene el índice de la posicion en "x" y "y " de la pieza en el tablero
int Player::pieceTeamIndexByXY(int x, int y) {
    // Gets a piece's index from its x-y location on the board
    int index=0;
    for(;index<team.size();index++){
        if((team[index].x == x) && (team[index].y == y)){
            break;
        }
    }
    return index;
}
