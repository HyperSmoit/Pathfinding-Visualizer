#include "dijkstra.h"

using namespace std;
using namespace sf;



int main() {
    vector<vector<int>> filled;
    vector<vector<int>> grid;
    for (int i = 0; i < num_x; ++i) {
        vector<int> temp(num_y, 1);
        grid.emplace_back(temp);
    }
    for (int i = 0; i < num_x; ++i) {
        vector<int> temp(num_y, 0);
        vector<bool> dummy(num_y, false);
        filled.emplace_back(temp);
        sptSet.push_back(dummy);
    }
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Grid");

    //Text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text1("Dijkstra",  font, font_size);
    sf::Text text2("A*", font, font_size);
    sf::Text text3("DFS", font, font_size);
    sf::Text text4("BFS", font, font_size);
    stringstream ss1,ss2;
    ss1<<pathD.size();

    //Shapes
    RectangleShape buttonStartD(Vector2f(button_width, button_height));   //Dijkstra button
    buttonStartD.setFillColor(Color::Red);

    RectangleShape buttonStartAs(Vector2f(button_width, button_height));   //Dijkstra A*
    buttonStartAs.setFillColor(Color::Blue);

    RectangleShape buttonStartDFS(Vector2f(button_width, button_height));   //Dijkstra DFS
    buttonStartDFS.setFillColor(Color::Magenta);

    RectangleShape buttonStartBFS(Vector2f(button_width, button_height));   //Dijkstra BFS
    buttonStartBFS.setFillColor(Color::Cyan);

    RectangleShape rectangle(Vector2f(box_size, box_size));      //default box :White
    rectangle.setFillColor(Color::White);

    RectangleShape brectangle(Vector2f(box_size, box_size));     //Black box
    brectangle.setFillColor(Color::Black);

    RectangleShape mrectangle(Vector2f(box_size, box_size));     //Magenta
    mrectangle.setFillColor(Color::Magenta);
    mrectangle.setOutlineThickness(2);
    mrectangle.setOutlineColor(Color::Red);

    RectangleShape blueRectangle(Vector2f(box_size, box_size));
    blueRectangle.setFillColor(Color::Blue);
    blueRectangle.setOutlineThickness(2);
    blueRectangle.setOutlineColor(Color::Black);

    RectangleShape grectangle(Vector2f(box_size, box_size));     //Green
    grectangle.setFillColor(Color::Green);

    RectangleShape rrectangle(Vector2f(box_size, box_size));
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(2);
    rrectangle.setOutlineColor(Color::Red);
    
    RectangleShape yrectangle(Vector2f(box_size, box_size));
    yrectangle.setFillColor(Color::Yellow);
    //Display
    while (window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int col = y / box_size;
                int row = x / box_size;
                cout << row << ' ' << col <<'\n';
                if (row < num_x && col < num_y && grid[row][col] == 0 ) {
                    grid[row][col] = 1;
                }
                else if (row < num_x && col < num_y) {
                    grid[row][col] = 0;
                }
                if (row >= ((WIDTH - 3 * button_width / 2) / box_size) && row <= WIDTH / box_size && col >= 0 && col <= button_height / box_size)
                    dijkstra(source_x, source_y, dest_x, dest_y, grid);
            }
        }
        window.clear();
        
        buttonStartD.setPosition(WIDTH - 3 * button_width / 2, 0);
        window.draw(buttonStartD);
        buttonStartAs.setPosition(WIDTH - 3 * button_width / 2, button_height + 100);
        window.draw(buttonStartAs);      //Astar launch
        
        text1.setPosition(WIDTH - 3 * button_width / 2, 0);       //Dijkstra text
        text2.setPosition(WIDTH - 3 * button_width / 2, button_height + 100);
        window.draw(text1);
        window.draw(text2);


        if(!pathD.empty()){
            for(int i = 0; i < int(pathD.size()); ++i){
                filled[pathD[i].first][pathD[i].second] = 1;
            }
        }
        blueRectangle.setPosition(source_x * box_size, source_y * box_size);
        window.draw(blueRectangle);     //source
       
        filled[source_x][source_y] = 1;
        rrectangle.setPosition(dest_x * box_size, dest_y * box_size);
        window.draw(rrectangle);        //destination
        filled[dest_x][dest_y] = 1;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 0) {
                    brectangle.setPosition(i * box_size, j * box_size);
                    window.draw(brectangle);    // Obstacle
                }

                if(sptSet[i][j] == true && filled[i][j] == 0) {
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setOutlineColor(Color::Blue);
                    yrectangle.setPosition(i * box_size, j * box_size);
                    window.draw(yrectangle);        // Explored Cells by dijkstra
                }

                if (grid[i][j] == 1 && filled[i][j] == 0 && !sptSet[i][j]) {     //not in dijkstra & A*
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Black);
                    rectangle.setPosition(i * box_size, j * box_size);
                    window.draw(rectangle);     //default white cells
                }
            }
        }
        window.display();
    }
    return 0;

}