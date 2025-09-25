#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
    sf::Texture spriteSheet;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float frameTime;        // Thời gian mỗi frame (giây)
    float elapsedTime;      // Thời gian đã trôi qua
    bool isPlaying;
    bool isLooping;
private:
    std::vector<sf::Texture> individualTextures;  // Lưu nhiều texture
    std::vector<int> frameTextureIndices;         // Index texture cho mỗi frame  
    bool useMultipleTextures;
public:
    Animation();
    ~Animation();

    // Load spritesheet và thiết lập frames
    bool loadSpriteSheet(const std::string& filename);
    void addFrame(int x, int y, int width, int height);
    void addFrameRow(int startX, int startY, int frameWidth, int frameHeight, int frameCount);

    // Điều khiển animation
    void play();
    void pause();
    void stop();
    void setLoop(bool loop);
    void setFrameTime(float time);

    // Update và get frame hiện tại
    void update(float deltaTime);
    sf::IntRect getCurrentFrame() const;
    sf::Texture& getTexture();

    // Kiểm tra trạng thái
    bool isAnimationPlaying() const;
    bool isAnimationFinished() const;
    bool loadMultipleImages(const std::vector<std::string>& filenames);
    void addIndividualFrame(int textureIndex);
};

