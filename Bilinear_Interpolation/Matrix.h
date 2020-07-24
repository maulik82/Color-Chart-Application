//
//  Matrix.h
//  Bilinear_Interpolation
//
//  Created by  Maulik Patel on 22/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#pragma once
#include "lib.h"
#include "Display.h"

class Matrix {
    uint16_t m_tl{0}, m_tr{0}, m_bl{0}, m_br{0};
    std::unique_ptr<Display> disp;


public:
    uint16_t m_numRows, m_numColumns;
    array2d_u16 m_data;

    ~Matrix() =default;
    Matrix(const std::string& name) : disp (std::make_unique<Display>(name))
    {
        auto d = disp->size();
        m_numRows = d.height;
        m_numColumns = d.width;
        m_data.resize(m_numRows);
        for (size_t i{0} ; i < m_numRows; ++i)
            m_data[i].resize(m_numColumns);
    }
    
    Matrix(uint16_t numRows, uint16_t numColumns ) :
    m_numRows{numRows}, m_numColumns{numColumns}
    {
        m_data.resize(numRows);
        for (size_t i{0} ; i < numRows; ++i)
            m_data[i].resize(numColumns);
    }

    void setCornerValues( uint16_t tl, uint16_t tr, uint16_t bl, uint16_t br  ) {
        m_tl = tl; m_tr = tr; m_bl = bl; m_br = br;
    }

    void printRaw() const {
        std::cout << "the size of matrix is " << m_numRows << " x " << m_numColumns << std::endl;;
        for( size_t i{0}; i<m_data.size(); i++ )
        {
            auto row = m_data.at(i);
//            std::cout << std::fixed;
//            std::cout << std::setprecision(2);
//            std::cout << "row #" << i <<" : ";
            for( auto ele : row )
                std::cout << ele << ",";
            std::cout << std::endl;
        }
    }
    
    void print() const {
        for (int16_t x = 0; x < m_numColumns; ++ x)
        {
           for (int16_t y = 0; y < m_numRows; ++ y)
           {
               disp->draw({x,y}, &m_data[y][x], 1);
           }
        }
        disp->present();
    }
    
    
    
    int performBilinearInterpolation() {
       
        linearInterpolation(m_tl, m_tr, m_numColumns, m_data.at(0) );               // first interpolate top row
        linearInterpolation(m_bl, m_br, m_numColumns, m_data.at(m_numRows-1));      // now interpolate bottom row
        
        {
            Matrix m_T{ m_numColumns, m_numRows};   // create new transpose matrix

            for (size_t i{0}; i < m_data.size(); ++i)
                for (size_t j{0}; j < m_data.at(0).size(); ++j)
                    m_T.m_data[j][i] = m_data[i][j];
            
            // now linear interpolate all rows of transpose matrix
            for( size_t i{0}; i< m_T.m_numRows; i++ )
            {
                uint16_t start = m_T.m_data[i][0];
                uint16_t end = m_T.m_data[i][m_T.m_numColumns-1];
        //        std::cout << "\n row " << i << "," << start << "," << end << std::endl;
                linearInterpolation(start, end, m_T.m_numColumns, m_T.m_data[i]);
            }
            
            // now transpose again the Transpose Matrix
            for (size_t i{0}; i < m_T.m_data.size(); ++i)
                for (size_t j{0}; j < m_T.m_data.at(0).size(); ++j)
                    m_data[j][i] = m_T.m_data[i][j];
            
        }   //temporary transpose matrix should be out of scope and hence destroyed here
        
        return 0;
    }
    
    
    void renderToDisplay() {
        disp->render();
    }
};
