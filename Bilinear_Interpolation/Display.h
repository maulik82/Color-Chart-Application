//
//  Display.h
//  Bilinear_Interpolation
//
//  Created by  Maulik Patel on 22/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#pragma once

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include "lib.h"

struct Point
{
  int16_t x;
  int16_t y;
};

struct Dimension
{
  uint16_t width;
  uint16_t height;
};

class Display
{
private:
    const std::string m_name;
    std::vector<uint16_t> m_frameBuffer;
    SDL_Window *m_window{nullptr};
    SDL_Renderer *m_renderer{nullptr};
    SDL_Texture *m_texture{nullptr};
    uint32_t *m_buffer{nullptr};

public:
    Display(const std::string& name);
    ~Display() = default;
    Dimension size() const;
    void draw(Point point, const uint16_t* pixels, uint16_t width);
    void present();
    
    
    bool init();
    void update();
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    bool processEvents();
    void close();
    void render();
};

