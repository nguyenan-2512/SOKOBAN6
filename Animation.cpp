#include "Animation.h"
#include <iostream>

Animation::Animation() : currentFrame(0), frameTime(0.1f), elapsedTime(0.0f),
isPlaying(false), isLooping(true), useMultipleTextures(false) {
}

Animation::~Animation() {
}

bool Animation::loadSpriteSheet(const std::string& filename) {
    if (!spriteSheet.loadFromFile(filename)) {
        std::cerr << "Failed to load spritesheet: " << filename << std::endl;
        return false;
    }
    return true;
}

void Animation::addFrame(int x, int y, int width, int height) {
    frames.push_back(sf::IntRect(x, y, width, height));
}

void Animation::addFrameRow(int startX, int startY, int frameWidth, int frameHeight, int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        addFrame(startX + (i * frameWidth), startY, frameWidth, frameHeight);
    }
}

void Animation::play() {
    isPlaying = true;
}

void Animation::pause() {
    isPlaying = false;
}

void Animation::stop() {
    isPlaying = false;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void Animation::setLoop(bool loop) {
    isLooping = loop;
}

void Animation::setFrameTime(float time) {
    frameTime = time;
}

void Animation::update(float deltaTime) {
    if (!isPlaying || frames.empty()) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime) {
        elapsedTime = 0.0f;
        currentFrame++;

        if (currentFrame >= frames.size()) {
            if (isLooping) {
                currentFrame = 0;
            }
            else {
                currentFrame = frames.size() - 1;
                isPlaying = false;
            }
        }
    }
}

sf::IntRect Animation::getCurrentFrame() const {
    if (frames.empty()) return sf::IntRect();
    return frames[currentFrame];
}

sf::Texture& Animation::getTexture() {
    if (useMultipleTextures && !individualTextures.empty()) {
        // Trả về texture của frame hiện tại
        if (currentFrame < frameTextureIndices.size()) {
            int textureIndex = frameTextureIndices[currentFrame];
            if (textureIndex < individualTextures.size()) {
                return individualTextures[textureIndex];
            }
        }
        return individualTextures[0]; // fallback nếu lỗi index
    }
    return spriteSheet; // mode cũ (spritesheet)
}


bool Animation::isAnimationPlaying() const {
    return isPlaying;
}

bool Animation::isAnimationFinished() const {
    return !isLooping && currentFrame >= frames.size() - 1 && !isPlaying;
}
bool Animation::loadMultipleImages(const std::vector<std::string>& filenames) {
    individualTextures.clear();
    frames.clear();
    frameTextureIndices.clear();
    useMultipleTextures = true;
    
    for (size_t i = 0; i < filenames.size(); i++) {
        sf::Texture texture;
        if (!texture.loadFromFile(filenames[i])) {
            std::cerr << "Failed to load: " << filenames[i] << std::endl;
            return false;
        }
        individualTextures.push_back(texture);
        
        // Tự động thêm frame cho mỗi texture (full size)
        sf::Vector2u size = texture.getSize();
        frames.push_back(sf::IntRect(0, 0, size.x, size.y));
        frameTextureIndices.push_back(i);
        
        std::cout << "Loaded: " << filenames[i] << " (" << size.x << "x" << size.y << ")" << std::endl;
    }
    
    return !individualTextures.empty();
}

void Animation::addIndividualFrame(int textureIndex) {
    if (textureIndex < individualTextures.size()) {
        sf::Vector2u size = individualTextures[textureIndex].getSize();
        frames.push_back(sf::IntRect(0, 0, size.x, size.y));
        frameTextureIndices.push_back(textureIndex);
    }
}
bool Animation::loadMultipleImages(const std::vector<std::string>& filenames) {
    individualTextures.clear();
    frames.clear();
    frameTextureIndices.clear();
    useMultipleTextures = true;

    for (size_t i = 0; i < filenames.size(); i++) {
        sf::Texture texture;
        if (!texture.loadFromFile(filenames[i])) {
            std::cerr << "Failed to load: " << filenames[i] << std::endl;
            return false;
        }
        individualTextures.push_back(texture);

        // Tự động thêm frame cho mỗi texture (full size)
        sf::Vector2u size = texture.getSize();
        frames.push_back(sf::IntRect(0, 0, size.x, size.y));
        frameTextureIndices.push_back(i);

        std::cout << "Loaded: " << filenames[i] << " (" << size.x << "x" << size.y << ")" << std::endl;
    }

    return !individualTextures.empty();
}

void Animation::addIndividualFrame(int textureIndex) {
    if (textureIndex < individualTextures.size()) {
        sf::Vector2u size = individualTextures[textureIndex].getSize();
        frames.push_back(sf::IntRect(0, 0, size.x, size.y));
        frameTextureIndices.push_back(textureIndex);
    }
}