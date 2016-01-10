#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Exception.hpp"

using namespace std;



struct Matrix
{
    
    int _width;
    
    int _height;
    
    vector<vector<bool>> data;
    
    void init_random(size_t w, size_t h)//;
    {
        _width = w;
        _height = h;
        
        data.resize(w, vector<bool>(h));
        
        for (size_t i = 0; i < w; ++i)
        {
            for (size_t j = 0; j < h; ++j)
            {
                data[i][j] = rand() % 2;
            }
        }
    }
    
    void init_from_file(string file)//;
    {
        try
        {
            ifstream csv(file);
            string line;
            data = vector<vector<bool>>();
            for (int i = 0; getline(csv, line); ++i)
            {
                istringstream iss(line);
                string s;
                data.push_back(vector<bool>());
                while(getline(iss, s, ';'))
                {
                    if (s == "1" || s == "#")
                    {
                        data[i].push_back(1);
                    }
                    else
                    {
                        if (s == "0" || s == ".")
                        {
                            data[i].push_back(0);
                        }
                        else
                        {
                            throw IncorrectCommandException("Incorrect data. Use only 0 . 1 # ");
                        }
                    }
                }
            }
        }
        catch (exception& e)
        {
            static const string str("While reading csv: ");
            throw IncorrectCommandException(str + e.what());
        }
        _width = data.size();
        _height = data[0].size();
    }
    
    
    void print_world()//;
    {
        for (int i = 0; i < _width; ++i)
        {
            for (int j = 0; j < _height; ++j)
            {
                if (data[i][j])
                    cout << "*";
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
    
    
    
    void write_to_buffer(bool* buffer, int start_row, int row_count)//;
    {
        int index = 0;
        for (int i = 0; i < row_count; ++i)
        {
            for (int j = 0; j < _height; ++j, ++index)
            {
                buffer[index] = data[start_row + i][j];
            }
        }
    }
    
    void init_from_buffer(bool* buffer, int w, int h)//;
    {
        _width = w;
        _height = h;
        data.resize(_width, vector<bool>(_height));
        int index = 0;
        for (int i = 0; i < _width; ++i)
        {
            for (int j = 0; j < _height; ++j, ++index)
            {
                data[i][j] = buffer[index];
            }
        }
    }
    
    void write_row(bool* buffer, int row_number)//;
    {
        for (int i = 0; i < _height; ++i)
        {
            buffer[i] = data[row_number][i];
        }
    }
    
};
/*
 void Field::init_random(size_t w, size_t h)
 {
 _width = w;
 _height = h;
 
 data.resize(_width, vector<bool>(_height));
 
 for (int i = 0; i < _width; ++i) {
 for (int j = 0; j < _height; ++j) {
 data[i][j] = rand() % 2;
 }
 }
 }*/
/*
 void Field::init_from_file(string file) {
 try {
 ifstream csv(file);
 string line;
 data = vector<vector<bool>>();
 for (int i = 0; getline(csv, line); ++i) {
 istringstream iss(line);
 string s;
 data.push_back(vector<bool>());
 while(getline(iss, s, ';'))
 {
 if (s == "1" || s == "#")
 data[i].push_back(1);
 else {if (s == "0" || s == ".")
 data[i].push_back(0);
 else {
 throw IncorrectCommandException("Incorrect data. Use only 0 . 1 # ");
 }
 }
 }
 }
 } catch (exception& e) {
 static const string str("While reading csv: ");
 throw IncorrectCommandException(str + e.what());
 }
 _width = data.size();
 _height = data[0].size();
 }
 *//*
    void Field::print_world()
    {
    for (int i = 0; i < _width; ++i) {
    for (int j = 0; j < _height; ++j) {
    if (data[i][j])
    cout << "*";
    else
    cout << " ";
    }
    cout << endl;
    }
    }*/
/*
 void Field::write_to_buffer(bool* buffer, int start_row, int row_count)
 {
 int index = 0;
 for (int i = 0; i < row_count; ++i)
 {
 for (int j = 0; j < _height; ++j, ++index)
 {
 buffer[index] = data[start_row + i][j];
 }
 }
 }*/
/*
 void Field::init_from_buffer(bool* buffer, int w, int h) {
 _width = w;
 _height = h;
 data.resize(_width, vector<bool>(_height));
 int index = 0;
 for (int i = 0; i < _width; ++i) {
 for (int j = 0; j < _height; ++j, ++index) {
 data[i][j] = buffer[index];
 }
 }
 }*//*
     
     void Field::write_row(bool* buffer, int row_number)
     {
     for (int i = 0; i < _height; ++i)
     {
     buffer[i] = data[row_number][i];
     }
     }*/

#endif  