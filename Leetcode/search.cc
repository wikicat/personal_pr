#include <vector>
#include <string>
#include <stack>
#include <utility> //pair
#include <iostream>
#include <cstdlib> //size_t
#include <algorithm> //std::max
#include <queue>
#include <set>

using namespace std;

namespace hh695 {
class Solution {
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = m ? grid[0].size() : 0;
        int local_area = 0;
        int area = 0;
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (!grid[i][j]) {
                    continue;
                }
                grid[i][j] = 0;
                local_area = 1;
                stack<pair<int, int>> island_coord;
                island_coord.push({i, j});
                while (!island_coord.empty()) {
                    auto cur_coord = island_coord.top();
                    island_coord.pop();
                    for (size_t d = 0; d < 4; ++d) {
                        int new_i = cur_coord.first + dir[d];
                        int new_j = cur_coord.second + dir[d + 1];
                        if (0 <= new_i && new_i < m &&
                            0 <= new_j && new_j < n &&
                            grid[new_i][new_j]) {
                            grid[new_i][new_j] = 0;
                            ++local_area;
                            island_coord.push({new_i, new_j});
                        }
                    }
                }
                area = std::max(area, local_area);
            }
        }
        return area;
    }

private:
    vector<int> dir {-1, 0, 1, 0, -1};
};

class Solution1 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = m ? grid[0].size() : 0;
        int area = 0;
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    area = std::max(area, dfs(grid, i, j));
                }
            }
        }
        return area;
    }

private:
    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (grid[i][j] == 0) {
            return 0;
        }
        grid[i][j] = 0;
        int area = 1;
        for (size_t d = 0; d < 4; ++d) {
            int new_i = i + dir[d];
            int new_j = j + dir[d + 1];
            if (0 <= new_i && new_i < grid.size() &&
                0 <= new_j && new_j < grid[0].size()) {
                area += dfs(grid, new_i, new_j);
            }
        }
        return area;
    }
private:
    vector<int> dir {-1, 0, 1, 0, -1};
};
}

namespace hh547 {
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int num_province = 0;
        vector<bool> visited(isConnected.size(), false);
        for (size_t i = 0; i < isConnected.size(); ++i) {
            if (!visited[i]) {
                dfs(isConnected, i, visited);
                ++num_province;
            }
        }
        return num_province;
    }
private:
    void dfs(vector<vector<int>>& isConnected, int i, vector<bool>& visited) {
        visited[i] = true;
        for (size_t j = 0; j < isConnected.size(); ++j) {
            if (isConnected[i][j] == 1 && !visited[j]) {
                dfs(isConnected, j, visited);
            }
        }
    }
};
}

namespace hh417 {
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const int m = heights.size();
        const int n = m ? heights[0].size() : 0;
        vector<vector<int>> ans;
        vector<vector<bool>> can_reach_pacific(m, vector<bool>(n, false));
        vector<vector<bool>> can_reach_atlantic(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            dfs(heights, can_reach_pacific, i, 0);
            dfs(heights, can_reach_atlantic, i, n - 1);
        }

        for (int i = 0; i < n; ++i) {
            dfs(heights, can_reach_pacific, 0, i);
            dfs(heights, can_reach_atlantic, m - 1, i);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (can_reach_atlantic[i][j] && can_reach_pacific[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;
    }
private:
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& rpa, int i, int j) {
        if (rpa[i][j]) {
            return;
        }
        rpa[i][j] = true;
        for (size_t d = 0; d < 4; ++d) {
            int new_i = i + dir[d];
            int new_j = j + dir[d + 1];
            if (0 <= new_i && new_i < heights.size() &&
                0 <= new_j && new_j < heights[0].size() &&
                heights[new_i][new_j] >= heights[i][j]) {
                dfs(heights, rpa, new_i, new_j);
            }
        }
    }
private:
    vector<int> dir {-1, 0, 1, 0, -1};
};
}

namespace hh46 {
class Solution{
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        backtracking(nums, 0, ans);
        for (auto v : ans) {
            for (int i : v) {
                cout << i << " ";
            }
            cout << endl;
        }
        return ans;
    }
private:
    void backtracking(vector<int>& nums, int level, vector<vector<int>>& ans) {
        if (level == nums.size() - 1) {
            ans.push_back(nums);
            return;
        }
        for (int i = level; i < nums.size(); ++i) {
            swap(nums[i], nums[level]);
            backtracking(nums, level + 1, ans);
            swap(nums[i], nums[level]);
        }
    }
};
}

namespace hh77 {
class Solution{
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> comb(k, 0);
        int count = 0;
        backtracking(ans, comb, count, 1, n, k);
        return ans;
    }
private:
    void backtracking(vector<vector<int>>& ans, vector<int> comb,
                      int& count, int pos, int n, int k) {
        if (count == k) {
            ans.push_back(comb);
            return;
        }
        for (int i = pos; i <= n - (k - ans.size()) + 1; ++i) {
            comb[count++] = i;
            backtracking(ans, comb, count, i + 1, n, k);
            --count;
        }
    }
};
}

namespace hh79 {
class Solution {
    bool exist(vector<vector<char>>& board, string word) {
        const int m = board.size();
        const int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                visited[i][j] = true;
                if (board[i][j] == word[0] &&
                    backtracking(board, word, visited, i, j, 0)) {
                    return true;
                }
                visited[i][j] = false;
            }
        }
        return false;
    }
private:
    bool backtracking(vector<vector<char>>& board, const std::string& word,
                      vector<vector<bool>>& visited, int i, int j, int pos) {
        if (pos == word.length() - 1) {
            return true;
        }
        for (int d = 0; d < 4; ++d) {
            int new_i = i + dir[d];
            int new_j = j + dir[d + 1];
            if (0 <= new_i && new_i < board.size() &&
                0 <= new_j && new_j < board[0].size()) {
                if (visited[new_i][new_j] || board[new_i][new_j] != word[pos + 1]) {
                    continue;
                }
                visited[new_i][new_j] = true;
                if (backtracking(board, word, visited, new_i, new_j, pos + 1)) {
                    return true;
                }
                visited[new_i][new_j] = false;
            }
        }
        return false;
    }
private:
    vector<int> dir {-1, 0, 1, 0, -1};
};
}

namespace hh51 {
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        if (!n) return ans;
        vector<string> board(n, string(n, '.'));
        vector<bool> column(n, false), ldiag(2 * n - 1, false), rdiag(2 * n - 1, false);
        backtracking(ans, board, column, ldiag, rdiag, 0, n);
        return ans;
    }
private:
    void backtracking(vector<vector<string>>& ans, vector<string>& board,
                      vector<bool>& column, vector<bool>& ldiag,
                      vector<bool>& rdiag, int row, int n) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (column[i] || ldiag[n - row + i - 1] || rdiag[row + i + 1]) {
                continue;
            }
            board[row][i] = 'Q';
            column[i] = ldiag[n - row + i - 1] = rdiag[row + i + 1] = true;
            backtracking(ans, board, column, ldiag, rdiag, row + 1,  n);
            board[row][i] = '.';
            column[i] = ldiag[n - row + i - 1] = rdiag[row + i + 1] = false;
        }
    }
};

class Solution1 {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<vector<bool>> board;
        std::set<int> col, ldiag, rdiag;
        dfs(res, board, col, ldiag, rdiag, 0, n);
        return res;
    }
private:
    void dfs(vector<vector<string>>& res, vector<vector<bool>>& board, set<int>& col,
             set<int>& ldiag, set<int>& rdiag, int i, int n) {
        if (i == n) {
            vector<string> tmp;
            for (int x = 0; x < n; ++x) {
                string str;
                for (int y = 0; y < n; ++y) {
                    if (board[x][y]) {
                        str += "Q";
                    } else {
                        str += ".";
                    }
                }
                tmp.push_back(str);
            }
            res.push_back(tmp);
            return;
        }
        for (int j = 0; j < n; ++j) {
            if (col.count(i) || ldiag.count(i + j) || rdiag.count(i - j)) {
                continue;
            }
            board[i][j] = true;
            col.insert(i);
            ldiag.insert(i + j);
            rdiag.insert(i - j);
            dfs(res, board, col, ldiag, rdiag, i + 1, n);
            col.erase(i);
            ldiag.erase(i + j);
            rdiag.erase(i - j);
            board[i][j] = false;
        }
    }

};
}

namespace hh934 {
class Solution {
public:
    /**Mark:
     * using dfs to find one island -> refer to LC 200.
     */ 
    int shortestBridge(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        queue<pair<int, int>> points;
        //find one island using dfs
        bool found = false;
        for (int i = 0; i < m && !found; ++i) {
            for (int j = 0; j < n && !found; ++j) {
                if (grid[i][j]) {
                    dfs(points, grid, m, n, i, j);
                    found = true;
                }
            }
        }

        int level = 0;
        while (!points.empty()) {
            int num = points.size();
            while (num--) {
                auto [r, c] = points.front();
                points.pop();
                for (int d = 0; d < 4; ++d) {
                    int new_r = r + dir[d];
                    int new_c = c + dir[d + 1];
                    if (0 <= new_r && new_r < m &&
                        0 <= new_c && new_c < n) {
                        if (grid[new_r][new_c] == 2) {
                            continue;
                        }
                        if (grid[new_r][new_c] == 1) {
                            return level;
                        }
                        points.emplace(new_r, new_c);
                        grid[new_r][new_c] = 2;
                    }
                }
            }
            ++level;
        }
        return 0;
    }
private:
    void dfs(queue<pair<int, int>>& points, vector<vector<int>>& grid,
             int m, int n, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1) {
            return;
        }
        grid[i][j] = 2;
        points.emplace(i, j);
        dfs(points, grid, m, n, i - 1, j);
        dfs(points, grid, m, n, i + 1, j);
        dfs(points, grid, m, n, i, j - 1);
        dfs(points, grid, m, n, i, j + 1);
    }
private:
    vector<int> dir {-1, 0, 1, 0, -1};
};
}

namespace hh127 {
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //BFS -> bidirectional BFS
        /**pseudo code for BFS
         * q.push(start)
         * step = 0
         * while not q.empty
         *  ++step
         *  size = q.size()
         *  while size-- > 0
         *    node = q.pop()
         *    new_node = expand(node)
         *    if goal in new node: return step + 1
         *    q.append(new_node)
         * return NOT_FOUND
         * ****************************************************************
         * pesudo code for bidirectional BFS
         * s1.insert(start)
         * s2.insert(end)
         * step = 0
         * while not (s1.empty() || s2.empty())
         *   ++step
         *   swap*(s1, s2)
         *   s = {}
         *   for node in s1:
         *     new_nodes = expand(node)
         *     if any(new_nodes) in s2: return step + 1
         *     s.append(new_nodes)
         *   s1 = s
         * return NOT_FOUND
         */ 
        unordered_set<string> dict (wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0;

        queue<string> q;
        //unordered_map<string, int> words;
        words[beginWord] = -1;
        q.push(beginWord);

        int l = beginWord.length();
        int step = 0;
        while (!q.empty()) {
            ++step;
            for (int i = q.size(); i > 0; --i) {
                string w = q.front();
                q.pop();
                //int loc = words[w];
                for (int j = 0; j < l; ++j) {
                    //if (j == loc) continue;
                    char ch = w[i];
                    for (int k = 'a'; k <= 'z'; ++k) {
                        w[j] = k;
                        if (w == endWord) 
                            return step + 1;
                        if (dict.count(w)) continue;
                        //words[w] = j;
                        dict.erase(w);
                        q.push(w);
                    }
                    w[i] = ch;
                }
            }
        }
        return 0;
    }
}
}

namespace hh126 {
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

    }
};
}

int main() {
    return 0;
}
