//
//  Display.cpp
//  Bilinear_Interpolation
//
//  Created by  Maulik Patel on 22/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#include "Display.h"

#include <cstdio>
#include <cstring>

namespace {
    constexpr uint16_t Width = 200;
    constexpr uint16_t Height = 100;
}

Display::Display(const std::string& name)  : m_name(name), m_frameBuffer(Width * Height)
{}

Dimension Display::size() const
{
    return { Width, Height };
}

void Display::draw(const Point point, const uint16_t *pixels, const uint16_t width)
{
    std::memcpy(&m_frameBuffer[point.y * Width + point.x], pixels, width * sizeof(uint16_t));
}

void Display::present()
{
    auto pixels = m_frameBuffer.data();
    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {

          printf("%04X ", *pixels++);
        }
    printf("\n");
    }
}



bool Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    m_window = SDL_CreateWindow("Linear Ramp",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width,
            Height, SDL_WINDOW_SHOWN);

    if (m_window == NULL) {
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STATIC, Width, Height);

    if (m_renderer == NULL) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    if (m_texture == NULL) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_buffer = new uint32_t[Width * Height];

    memset(m_buffer, 0, Width * Height * sizeof(uint32_t));

    return true;
}

void Display::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {

    uint32_t color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer[(y * Width) + x] = color;
}

void Display::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer, Width * sizeof(uint32_t));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);

}

bool Display::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Display::close() {
    delete[] m_buffer;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Display::render(){
    if(Display::init() == false) {
        std::cout << "Error initialising SDL." << std::endl;
    }
    
    auto d = size();
    auto pixels = m_frameBuffer.data();
    for (int y = 0; y < d.height; ++y) {
        for (int x = 0; x < d.width; ++x) {
          volatile uint32_t color = *pixels++;
          color <<= 8;
          color += 0xFF;
          m_buffer[(y * d.width) + x] = color;
        }
    }
    while (true) {
        // Draw the screen
        Display::update();

        // Check for messages/events
        if(Display::processEvents() == false) {
            break;
        }
    }
    Display::close();
}
