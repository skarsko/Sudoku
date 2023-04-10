#include "field.hpp"
#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <thread>
#include <ctime>
#include "SDL_FontCache/SDL_FontCache.h"

//Pre-Delarations
int getMousePosition(std::vector<int> field);

Field::Field(int sz){
    assert(sz % 3 == 0); 
    size = sz;
    field = std::vector<int>(sz*sz);
    fixedFields = std::vector<bool>(sz*sz);
    editField = -1;
}


//Here we add the numbers to the field (will be extended later)
void Field::addNumbers(){
    int sz = size;
        /*
        //some assignment of numbers to the field (0 means empty field)
        field[0] = 7;
        field[1] = 4;
        field[7] = 6;
        field[8] = 5;
        field[9] = 8;
        field[17] = 7;
        field[20] = 1;
        field[21] = 6;
        field[23] = 4;
        field[24] = 9;
        field[27] = 3;
        field[31] = 5;
        field[35] = 1;
        field[37] = 8;
        field[38] = 7;
        field[40] = 9;
        field[42] = 6;
        field[43] = 2;
        field[47] = 9;
        field[51] = 7;
        field[64] = 2;
        field[66] = 5;
        field[68] = 1;
        field[70] = 7;
        field[73] = 7;
        field[74] = 8;
        field[75] = 3;
        field[77] = 6;
        field[78] = 5;
        field[79] = 1;       
      */
    //Here we generate a new field
    generateField(0.1);
    //All the fields which are 0 are not fixed, the others are
    for (int i = 0; i < sz*sz; i++){
        if(field[i] == 0){
            fixedFields[i] = false;
        }else{
            fixedFields[i] = true;
        }
    }
}

void Field::start(){
    //First we need to initialize SDL and the font library TTF
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    //Now we can create a window for the soduko grid
    //The width and height per cell is 50 pixels
    int cellSize = 75;
    SDL_Window* window = SDL_CreateWindow("Soduko", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size*cellSize, size*cellSize, SDL_WINDOW_SHOWN);
    //We need a renderer to draw the grid
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Now we render the window using an event loop (we need to keep the window open)
    //Quit becomes positive when the user closes the window
    //finished becomes positive when the user (or algorithm)has solved the soduko
    bool quit = false;
    bool finished = false;
    SDL_Event event;

    //Here we load the font we want to use for the numbers on the grid
    int fontSize = 40;
    FC_Font* font = FC_CreateFont(); 
    FC_LoadFont(font, renderer, "../rsc//fonts/Anuphan.ttf", fontSize, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL); 

    FC_Font* playerFont = FC_CreateFont();
    FC_LoadFont(playerFont, renderer, "../rsc//fonts/Anuphan.ttf", fontSize, FC_MakeColor(190,190,190,255), TTF_STYLE_NORMAL);         

    //This variable keeps track of which number we want to add to the field (-1 means no number)
    int addNumber = -1;

    //The solveThread is the thread which solves the whole soduko
    std::thread solveThread;
    //This variable keeps track of whether the algorithm should start solving
    bool startedSolving = false;


    //This is now the game loop, where all the things are drawn constantely
    while (!quit)
    {
        //Clear the window with the background-color black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
        SDL_RenderClear(renderer);
        //Draw the grid
        for (int i = 1; i < size; i++)
        {
            if(i%3==0){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }else{
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            SDL_RenderDrawLine(renderer, 0, i*cellSize, size*cellSize, i*cellSize);
            SDL_RenderDrawLine(renderer, i*cellSize, 0, i*cellSize, size*cellSize);
        }

        //Now we check, if the player has won
        //Count the number of empty fields using std::count
        int emptyFields = std::count(field.begin(), field.end(), 0);
        //If there are no empty fields and the field is correct, the player has won
        if(!finished && emptyFields == 0 && this->checkField()){
           finished = true; 
        }


    

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){quit = true;}
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                editField = getMousePosition(field);
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_1){
                    addNumber = 1;
                }
                if(event.key.keysym.sym == SDLK_2){
                    addNumber = 2;
                }
                if(event.key.keysym.sym == SDLK_3){
                    addNumber = 3;
                }
                if(event.key.keysym.sym == SDLK_4){
                    addNumber = 4;
                }
                if(event.key.keysym.sym == SDLK_5){
                    addNumber = 5;
                }
                if(event.key.keysym.sym == SDLK_6){
                    addNumber = 6;
                }
                if(event.key.keysym.sym == SDLK_7){
                    addNumber = 7;
                }
                if(event.key.keysym.sym == SDLK_8){
                    addNumber = 8;
                }
                if(event.key.keysym.sym == SDLK_9){
                    addNumber = 9;
                }
                if(event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_DELETE){
                    addNumber = 0;
                }
                //Spacebar starts the solving algorithm
                if(event.key.keysym.sym == SDLK_SPACE && !startedSolving){
                    startedSolving = true;
                    solveThread = std::thread{&Field::solve, this, 2}; 
                }
                //Pressing of the letter "h" gives a hint
                if(event.key.keysym.sym == SDLK_h){
                  //This works on the same thread
                  //We make a copy of the field and solve it
                  auto fieldCopy = *this;
                  fieldCopy.solve(0);
                  //Now we select a random field which is not fixed and empty
                  while(true){
                    int randomField = rand()%(size*size);
                    if(fixedFields[randomField]==false && field[randomField]==0){
                        field[randomField] = fieldCopy.field[randomField];
                        fixedFields[randomField] = true;
                        break;
                    }
                  }
                    
                }
                //Pressing of the letter "r" resets the field
                if(event.key.keysym.sym == SDLK_r){
                    if(solveThread.joinable()){
                    solveThread.join();
                    }
                    finished = false;
                    startedSolving = false;
                    for(int i = 0; i < size*size; i++){
                        if(fixedFields[i] == false){
                            field[i] = 0;
                        }
                    }
                }
                //Pressing of the letter "g" generates a new field
                if(event.key.keysym.sym == SDLK_g){
                    if(solveThread.joinable()){
                    solveThread.join();
                    }
                    finished = false;
                    startedSolving = false;
                    generateField(0.2);   
                   
                }
            }
        }    

        //Now we color the selected field in dark blue using getMousePosition()
        if(editField != -1){
            if(fixedFields[editField]){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            }else{
                SDL_SetRenderDrawColor(renderer, 5, 20, 114, 100);
            }
         int mousePos = editField;
         int x = mousePos%size;
         int y = mousePos/size;
         SDL_Rect rect = {x*cellSize+1, y*cellSize+1, cellSize-1, cellSize-1};
         SDL_RenderFillRect(renderer, &rect);
        }

        //If the user presses a number key, we change the field (if it is not fixed)
        if(addNumber != -1){
            if(!fixedFields[editField]){
                auto fieldCopy = *this;
                fieldCopy.field[editField] = addNumber;
                    if(fieldCopy.checkField()){
                        field[editField] = addNumber;
                    }
                }
            addNumber = -1;
        }
        
    
        //Draw the numbers
        for (int i = 0; i < size*size; i++)
        {
            int x = i%size;
            int y = i/size;
            if(field[i] != 0){
                if(fixedFields[i]){
                    FC_Draw(font, renderer, x*cellSize+0.38*cellSize, y*cellSize+0.18*cellSize, "%d", field[i]);  
                }else{
                    FC_Draw(playerFont, renderer, x*cellSize+0.38*cellSize, y*cellSize+0.18*cellSize, "%d", field[i]);
                }
            }
        }
        
        
        //Update the window
        SDL_RenderPresent(renderer);
        //Wait a bit
        SDL_Delay(0);

    } //end game loop$

    //We need to clean up the memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    FC_FreeFont(font);

}

bool Field::checkField(){

    //Check that rows and columns have no duplicate numbers
    //First for the rows
    for(int i = 0; i < size; i++){
        //Iterating over the rows
        std::vector<int> row;
        for(int j = 0; j < size; j++){
            row.push_back(field[i*size+j]);
        }
        //Now we check if the row has duplicates 
        //For that, we first sort the row
        std::sort(row.begin(), row.end());
        //Now we check if there are duplicates
        for(int i = 1; i < size; i++){
            if(row[i] == row[i-1] && row[i] != 0){
                return false;
            }
        }
    }

    //Now we check the columns
    for(int i = 0; i < size; i++){
        //Iterating over the columns
        std::vector<int> col;
        for(int j = 0; j < size; j++){
            col.push_back(field[j*size+i]);
        }
        //Now we check if the column has duplicates 
        //For that, we first sort the column
        std::sort(col.begin(), col.end());
        //Now we check if there are duplicates
        for(int i = 1; i < size; i++){
            if(col[i] == col[i-1] && col[i] != 0){
                return false;
            }
        }
    }

    //Now we check the boxes
    for(int i = 0; i < size; i += 3){
        for(int j = 0; j < size; j += 3){
            std::vector<int> box;
            for(int k = 0; k < 3; k++){
                for(int l = 0; l < 3; l++){
                    box.push_back(field[(i+k)*size+j+l]);
                }
            }


            //Now we check if the box has duplicates
            //For that, we first sort the box
            std::sort(box.begin(), box.end());

            //Now we check if there are duplicates
            for(int i = 1; i < 9; i++){
                if(box[i] == box[i-1] && box[i] != 0){
                    return false;
                }
            }
        }
    }
    //If we get here, the field is valid
    return true;
}

//This function returns the position of the mouse in the field
int getMousePosition(std::vector<int> field){
    //Get the mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    //Now we need to find, where the mouse is in the field the position corresponds to
    int size = sqrt(field.size());
    double cellSize = 75.0;
    double y = mouseY/cellSize;
    double x = mouseX/cellSize;
    //Now we need to round the values to the nearest integer down
    int yInt = floor(y);
    int xInt = floor(x);
    
    return yInt*size+xInt; 
    
}

bool Field::backTrack(int pos, int delay, int startTime){
    //We add a little delay to make the backtracking visible
    SDL_Delay(delay);

    if(time(0) - startTime > 3){
        return false;
    }

    //We need to check if the field is valid
    if(!this->checkField()){
        return false;
    }
    //We need to check if the field is solved
    if(std::count(this->field.begin(), this->field.end(), 0) == 0){
        return true;
    }
    //Now we need to find the next empty field
    int nextPos = pos;
    while(this->field[nextPos] != 0){
        nextPos++;
    }
    //Now we need to try all numbers
    for(int i = 1; i <= 9; i++){
        this->field[nextPos] = i;
        if(backTrack(nextPos, delay, startTime)){
            return true;
        }
    }
    //If we get here, we need to backtrack
    this->field[nextPos] = 0;
    return false;
}

//This function solves the field
bool Field::solve(int delay){    
    //We use a backtracking algorithm to solve the field
    bool solvedState = false;
    
    //We try to solve the field 10 times (in case the backtracking somehow gets stuck (idk why(shouldnt be here(will get fixed(one day(later maybe)))))))))))
    for(int i = 0; i < 10; i++){
      solvedState = this->backTrack(0,delay,time(0));
      if(solvedState){break;}
    }

    if(solvedState && delay > 0){
        std::cout << "Solved!" << std::endl;
    }else if(delay > 0){
        std::cout << "Could not solve the field" << std::endl;
    }

    return solvedState;
}

//This function generates a random field
void Field::generateField(double difficulty){
    //We use the time as a seed
    srand(time(NULL));
    while(true){
        //We need to reset the field
        for(int i = 0; i < size*size; i++){
            field[i] = 0;
            fixedFields[i] = false;
        }
        //We generate difficulty * size * size random numbers
        for(int i = 0; i < size*size*difficulty; i++){
            int random = rand() % (size*size);
            if(field[random] == 0){
                field[random] = rand() % 9 + 1;
                fixedFields[random] = true;
            }else{
                i--;
            }
        }
 
        //We create a copy of the field and try to solve it
        auto fieldCopy = *this;
        if(fieldCopy.solve(0)){
            break;
        }
    }
    std::cout << "Field generated" << std::endl;
}