#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include <iostream>
#include <functional>
#include <math.h>    
#include <float.h>
#include <vector>
#include <set>
#include <string.h>
#include <string>
#include <sstream>

using namespace sf;
using namespace std;
vector<vector<bool>> sptSet;
int source_x = 10;
int source_y = 10;
int dest_x = 50;
int dest_y = 37;
int font_size = 25;
int button_width = 150;
int button_height = 50;
int box_size = 20;
int HEIGHT = VideoMode().getDesktopMode().height;
int WIDTH = VideoMode().getDesktopMode().width;
const int num_y = 60;
int num_x = (WIDTH - 3 * button_width / 2 - 100) / box_size;
vector<pair<int, int>> pathD;

