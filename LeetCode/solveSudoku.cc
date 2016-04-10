#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>

using namespace std;

#define SUDOKU_SIZE 9
#define BLOCK_NO(row, column) ((row) / 3 * 3 + (column) / 3)
class Solution {
public:
  void solveSudoku(vector<vector<char>> &board) {
    analyseBoard(board);
    resolveBoard(board);
  }
  
private:
  class UnfilledCell {
  public:
    int row, column, block, number;
    
    UnfilledCell(int r, int c) : row(r), column(c), block(BLOCK_NO(r, c)), number(r * SUDOKU_SIZE + c),
                                 bitCount(SUDOKU_SIZE), bit(0), bits(0x1ff), bitLock(SUDOKU_SIZE, -1) { }
    
    bool operator< (const UnfilledCell &rhs) const {
      return bitCount > rhs.bitCount;
    }
    
    inline int getCandidateNumber() {
      return bitCount;
    }
    
    int getOneCandidate() {
      if (!bitCount)
        return 0;
      
      do {
        bit = (bit + 1) % SUDOKU_SIZE;
      } while (!bits[bit]);
      
      return bit + 1;
    }
    
    void addCandidate(int candidate, int cellNumber) {
      if (candidate > SUDOKU_SIZE || candidate <= 0)
        return;
      
      int i = candidate - 1;
      if (cellNumber == bitLock[i] && !bits[i]) {
        bits.set(i);
        ++bitCount;
      }
    }
    
    void removeCandidate(int candidate, int cellNumber) {
      if (candidate > SUDOKU_SIZE || candidate <= 0)
        return;
      
      int i = candidate - 1;
      if (bits[i]) {
        bits.reset(i);
        --bitCount;
        
        bitLock[i] = cellNumber;
      }
    }
    
    void removeCandidates(bitset<SUDOKU_SIZE> _bits) {
      bits = ~(~bits | _bits);
      bitCount = bits.count();
    }
    
  private:
    int bitCount;
    int bit;
    bitset<SUDOKU_SIZE> bits;
    vector<int> bitLock;
  };
  
  
  array<bitset<SUDOKU_SIZE>, SUDOKU_SIZE> rows, columns, blocks;
  vector<UnfilledCell> unfilledCells;
  
  bool analyseBoard(vector<vector<char>> &board) {
    char seed;
    int b;
    for (int r = 0; r != SUDOKU_SIZE; ++r)
      for (int c = 0; c != SUDOKU_SIZE; ++c) {
        seed = board[r][c];
        if (seed == '.') {
          unfilledCells.push_back(UnfilledCell(r, c));
          continue;
        }
        if (seed > '9' || seed < '1')
          return false;
        
        seed -= '1';
        if (rows[r][seed])
          return false;
        rows[r].set(seed);
        
        if (columns[c][seed])
          return false;
        columns[c].set(seed);
        
        b = BLOCK_NO(r, c);
        if (blocks[b][seed])
          return false;
        blocks[b].set(seed);
      }
    
    for (auto &cell : unfilledCells) {
      cell.removeCandidates(rows[cell.row] | columns[cell.column] | blocks[cell.block]);
    }
    
    return true;
  }
  
  bool resolveBoard(vector<vector<char>> &board) {
    if (unfilledCells.empty())
      return true;
    
    make_heap(unfilledCells.begin(), unfilledCells.end());
    
    auto cell = unfilledCells.front();
    auto candidateNumber = cell.getCandidateNumber();
    if (candidateNumber == 0)
      return false;
    
    pop_heap(unfilledCells.begin(), unfilledCells.end());
    unfilledCells.pop_back();
    
    for (; candidateNumber != 0; --candidateNumber) {
      auto chosen = cell.getOneCandidate();
      board[cell.row][cell.column] = '0' + chosen;
      
      int indexOfCells = 0;
      int unfilledNumber = unfilledCells.size();
      for (; indexOfCells < unfilledNumber; ++indexOfCells) {
        if (unfilledCells[indexOfCells].row == cell.row
            || unfilledCells[indexOfCells].column == cell.column
            || unfilledCells[indexOfCells].block == cell.block)
        {
          unfilledCells[indexOfCells].removeCandidate(chosen, cell.number);
          if (unfilledCells[indexOfCells].getCandidateNumber() == 0)
            break;
        }
      }
      
      if (indexOfCells == unfilledNumber) {
        if (resolveBoard(board))
          return true;
        
        --indexOfCells;
      }
      
      for (auto i = indexOfCells; i >= 0; --i) {
        if (unfilledCells[i].row == cell.row
            || unfilledCells[i].column == cell.column
            || unfilledCells[i].block == cell.block)
        {
          unfilledCells[i].addCandidate(chosen, cell.number);
        }
      }
    }
    
    board[cell.row][cell.column] = '.';
    unfilledCells.push_back(cell);
    
    return false;
  }
};

int main()
{
  Solution s;
  vector<string> data = {
    // "..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."
    "...2...63", "3....54.1", "..1..398.", ".......9.", "...538...", ".3.......", ".263..5..", "5.37....8", "47...1..."
  };
  vector<vector<char>> board;
  for (auto &str : data) {
    board.push_back(vector<char>(str.begin(), str.end()));
  }
  
  s.solveSudoku(board);
  
  for (auto row : board) {
    for (auto column : row)
      cout << column << ' ';
    cout << endl;
  }
  
  return 0;
}