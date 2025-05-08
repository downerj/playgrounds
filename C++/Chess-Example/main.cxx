#include <iostream> // cout, ostream
#include <memory> // unique_ptr, make_unique
#include <vector> // vector

#ifdef _DEBUG
#define DEBUG
#endif
#ifdef DEBUG
#define DEBUG_LOG(s) do { std::cout << s; } while (false);
#define DEBUG_ERROR(s) do { std::cerr << s; } while (false);
#define DEBUG_LOG_LINE(s) do { std::cout << s << '\n'; } while (false);
#define DEBUG_ERROR_LINE(s) do { std::cerr << s << '\n'; } while (false);
#define DEBUG_LOG_NEWLINE() do { std::cout << '\n'; } while (false);
#define DEBUG_ERROR_NEWLINE() do { std::cerr << '\n'; } while (false);
#else
#define DEBUG_LOG(s)
#define DEBUG_ERROR(s)
#define DEBUG_LOG_LINE(s)
#define DEBUG_ERROR_LINE(s)
#define DEBUG_LOG_NEWLINE()
#define DEBUG_ERROR_NEWLINE()
#endif

enum class Color {
  BLACK,
  WHITE
};

enum class Character {
  PAWN = 'P',
  ROOK = 'R',
  KNIGHT = 'N',
  BISHOP = 'B',
  QUEEN = 'Q',
  KING = 'K'
};

constexpr const char* colorReset{"\x1b[0m"};
constexpr const char* colorWhite{"\x1b[1;32m"}; // Green
constexpr const char* colorBlack{"\x1b[1;31m"}; // Red

class Piece {
public:
  Color color;
  Character character;
  virtual ~Piece() {}
  virtual bool isMoveValid() const = 0;
};

class Pawn : public Piece {
public:
  Pawn(Color color) {
    this->color = color;
    character = Character::PAWN;
  };
  virtual bool isMoveValid() const override { return true; };
};

class Rook : public Piece {
public:
  Rook(Color color) {
    this->color = color;
    character = Character::ROOK;
  };
  virtual bool isMoveValid() const override { return true; };
};

class Knight : public Piece {
public:
  Knight(Color color) {
    this->color = color;
    character = Character::KNIGHT;
  };
  virtual bool isMoveValid() const override { return true; };
};

class Bishop : public Piece {
public:
  Bishop(Color color) {
    this->color = color;
    character = Character::BISHOP;
  };
  virtual bool isMoveValid() const override { return true; };
};

class Queen : public Piece {
public:
  Queen(Color color) {
    this->color = color;
    character = Character::QUEEN;
  };
  virtual bool isMoveValid() const override { return true; };
};

class King : public Piece {
public:
  King(Color color) {
    this->color = color;
    character = Character::KING;  
  };
  virtual bool isMoveValid() const override { return true; };
};

class Player {
public:
  std::vector<Piece*> deadPieces{};
};

class Tile {
public:
  std::unique_ptr<Piece> piece;
  Tile();
  friend std::ostream& operator<<(std::ostream& out, const Tile& tile) {
    if (tile.piece) {
      out << colorReset << '['
          << (tile.piece->color == Color::BLACK ? colorBlack : colorWhite)
          << static_cast<char>(tile.piece->character)
          << colorReset << ']';
    } else {
      out << "[ ]";
    }
    return out;
  }
};

Tile::Tile() : piece{nullptr} {}

class Board {
public:
  Tile tiles[8][8];
  Board();
  void display();
};

/*
  0 1 2 3 4 5 6 7
0 R N B Q K B N R
1 P P P P P P P P
2
3
4
5
6 P P P P P P P P
7 R N B Q K B N R
*/

Board::Board() {
  // TODO: Create these pieces inside their own array, and then
  // copy their pointers into the respective tile objects.
  tiles[0][0].piece = std::make_unique<Rook>(Color::BLACK);
  tiles[0][7].piece = std::make_unique<Rook>(Color::BLACK);
  tiles[0][1].piece = std::make_unique<Knight>(Color::BLACK);
  tiles[0][6].piece = std::make_unique<Knight>(Color::BLACK);
  tiles[0][2].piece = std::make_unique<Bishop>(Color::BLACK);
  tiles[0][5].piece = std::make_unique<Bishop>(Color::BLACK);
  tiles[0][3].piece = std::make_unique<Queen>(Color::BLACK);
  tiles[0][4].piece = std::make_unique<King>(Color::BLACK);
  tiles[1][0].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][1].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][2].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][3].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][4].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][5].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][6].piece = std::make_unique<Pawn>(Color::BLACK);
  tiles[1][7].piece = std::make_unique<Pawn>(Color::BLACK);

  tiles[7][0].piece = std::make_unique<Rook>(Color::WHITE);
  tiles[7][7].piece = std::make_unique<Rook>(Color::WHITE);
  tiles[7][1].piece = std::make_unique<Knight>(Color::WHITE);
  tiles[7][6].piece = std::make_unique<Knight>(Color::WHITE);
  tiles[7][2].piece = std::make_unique<Bishop>(Color::WHITE);
  tiles[7][5].piece = std::make_unique<Bishop>(Color::WHITE);
  tiles[7][3].piece = std::make_unique<Queen>(Color::WHITE);
  tiles[7][4].piece = std::make_unique<King>(Color::WHITE);
  tiles[6][0].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][1].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][2].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][3].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][4].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][5].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][6].piece = std::make_unique<Pawn>(Color::WHITE);
  tiles[6][7].piece = std::make_unique<Pawn>(Color::WHITE);
}

void Board::display() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      std::cout << tiles[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

class Game {
public:
  Board board{};
};

int main(int, char**) {
  auto game{std::make_unique<Game>()};
  game->board.display();
}
