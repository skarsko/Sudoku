#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

class Field
{
private:
    //width/size of the field
    int size;
    //the difficulty of the field
    //bool solveDifficulty;
    //vector containing the numbers on the field (0-9) where 0 means "empty field"
    std::vector<int> field;
    //A vector containing bools which are true if the field is fixed and false if it is not
    std::vector<bool> fixedFields;
    //The field which is currently edited (if -1 no field is edited)
    int editField;
    //A function to check if the field is valid
    bool checkField();
    //A function to solve the field 
    bool solve(int delay);
    //A backtracking function to solve the field
    bool backTrack(int pos, int delay, int startTime);
    //A function to generate a new field
    //The "difficulty" is the percentage of fields which are fixed, so 0.2 means 20% of the fields are fixed
    //Therefor the lower the double "difficulty" is the harder the field is
    void generateField(double difficulty);
public:
    //default constructor
    Field(int sz);    
    //add numvbres to field   
    void addNumbers();
    //start the visualisation of the grid
    void start();

};

#endif //FIELD_HPP