#include<bits/stdc++.h>
#define pb push_back
using namespace std;

int width = 15, height = 15;
int map_width = width * 2 + 1;
int map_height = height * 2 + 1;

map<pair<int, int>, bool> used;
string map_map[1000][1000];
// up left down right
string walls[2][2][2][2] = {{{{"╬", "╣"}, {"╩", "╝"}}, {{"╠", "║"}, {"╚", "╨"}}}, {{{"╦", "╗"}, {"═", "╡"}}, {{"╔", "╥"}, {"╞", "▫"}}}};

void dfs(int x, int y){
    map_map[y][x] = " ";
    used[{x, y}] = 1;
    int dir[4] = {1, 2, 3, 4};
    random_shuffle(dir, dir+4);
    for(auto d: dir){
        if(d == 1 && y-2 > 0 && !used[{x, y-2}]){
            map_map[y-1][x] = " ";
            dfs(x, y-2);
        }
        else if(d == 2 && x+2 < map_width && !used[{x+2, y}]){
            map_map[y][x+1] = " ";
            dfs(x+2, y);
        }
        else if(d == 3 && y+2 < map_height && !used[{x, y+2}]){
            map_map[y+1][x] = " ";
            dfs(x, y+2);
        }
        else if(d == 4 && x-2 > 0 && !used[{x-2, y}]){
            map_map[y][x-1] = " ";
            dfs(x-2, y);
        }
    }
}

void do_maze(){
    used.clear();
    for(int i = 0; i < map_height; i++){
        for(int j = 0; j < map_width; j++){
            map_map[i][j] = "#"; 
        }
    }
    dfs(1, 1);
}

void apply_filter(){
    for(int i = 0; i < map_height; i++){
        for(int j = 0; j < map_width; j++){
            if(map_map[i][j] == " ") continue;

            bool up = 1, left = 1, down = 1, right = 1;
            
            if(i-1 >= 0)
                up = (map_map[i-1][j] == " ");
            if(j-1 >= 0)
                left = (map_map[i][j-1] == " ");
            if(i+1 < map_height)
                down = (map_map[i+1][j] == " ");
            if(j+1 < map_width)
                right = (map_map[i][j+1] == " ");
            map_map[i][j] = walls[up][left][down][right];
        }
    }
}

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    do_maze();
    apply_filter();
    for(int i = 0; i < map_height; i++){
        for(int j = 0; j < map_width; j++){
            cout<<map_map[i][j];
        }
        cout<<"\n";
    }
}
