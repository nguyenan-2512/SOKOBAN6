#include "Player.h"
#include <iostream>

Player::Player(int x, int y, int tileSize) : GameObject(x, y, tileSize),
currentDirection(PlayerDirection::IDLE), isMoving(false) {
    loadAnimations();
}

Player::~Player() {
}

bool Player::loadAnimations() {
    std::cout << "=== Loading Player Animations ===" << std::endl;

    // IDLE Animation (4 hướng đứng yên)
    std::vector<std::string> idleFiles = {
        "Sokoban pack/PNG/nhintrai.png",
        "Sokoban pack/PNG/nhinphai.png",
        "Sokoban pack/PNG/nhinxuong.png",
        "Sokoban pack/PNG/nhinlen.png"
    };
    if (!idleAnimation.loadMultipleImages(idleFiles)) {
        std::cerr << "Failed to load idle animation" << std::endl;
        return false;
    }
    idleAnimation.setFrameTime(0.5f);
    idleAnimation.setLoop(true);
    std::cout << "✅ Loaded idle animation with " << idleFiles.size() << " frames" << std::endl;

    // WALK DOWN Animation (2 frames)
    std::vector<std::string> walkDownFiles = {
        "Sokoban pack/PNG/dixuong.png",
        "Sokoban pack/PNG/dixuong2.png"
    };
    if (!walkDownAnimation.loadMultipleImages(walkDownFiles)) {
        std::cerr << "Failed to load walk down animation" << std::endl;
        return false;
    }
    walkDownAnimation.setFrameTime(0.2f);
    walkDownAnimation.setLoop(true);
    std::cout << "✅ Loaded walk down animation with " << walkDownFiles.size() << " frames" << std::endl;

    // WALK UP Animation (2 frames)
    std::vector<std::string> walkUpFiles = {
        "Sokoban pack/PNG/dilen.png",
        "Sokoban pack/PNG/dilen2.png"
    };
    if (!walkUpAnimation.loadMultipleImages(walkUpFiles)) {
        std::cerr << "Failed to load walk up animation" << std::endl;
        return false;
    }
    walkUpAnimation.setFrameTime(0.2f);
    walkUpAnimation.setLoop(true);
    std::cout << "✅ Loaded walk up animation with " << walkUpFiles.size() << " frames" << std::endl;

    // WALK LEFT Animation (2 frames)
    std::vector<std::string> walkLeftFiles = {
        "Sokoban pack/PNG/ditra.png",
        "Sokoban pack/PNG/ditra2.png"
    };
    if (!walkLeftAnimation.loadMultipleImages(walkLeftFiles)) {
        std::cerr << "Failed to load walk left animation" << std::endl;
        return false;
    }
    walkLeftAnimation.setFrameTime(0.2f);
    walkLeftAnimation.setLoop(true);
    std::cout << "✅ Loaded walk left animation with " << walkLeftFiles.size() << " frames" << std::endl;

    // WALK RIGHT Animation (2 frames)
    std::vector<std::string> walkRightFiles = {
        "Sokoban pack/PNG/diphai.png",
        "Sokoban pack/PNG/diphai2.png"
    };
    if (!walkRightAnimation.loadMultipleImages(walkRightFiles)) {
        std::cerr << "Failed to load walk right animation" << std::endl;
        return false;
    }
    walkRightAnimation.setFrameTime(0.2f);
    walkRightAnimation.setLoop(true);
    std::cout << "✅ Loaded walk right animation with " << walkRightFiles.size() << " frames" << std::endl;

    // Gán animation mặc định
    setAnimation(&idleAnimation);
    return true;
}


void Player::draw(sf::RenderWindow& window) {
    if (hasAnimation && currentAnimation) {
        sf::Vector2f pos = sprite.getPosition();
        std::cout << "Player position: (" << pos.x << ", " << pos.y << ")" << std::endl;
        window.draw(sprite);
    }
    else {
        std::cerr << "Warning: No valid animation for player" << std::endl;
    }
}

void Player::update() {
    GameObject::update(); // Cập nhật animation

    // Nếu không đang di chuyển, chuyển về idle sau một khoảng thời gian
    static sf::Clock idleTimer;
    if (isMoving && idleTimer.getElapsedTime().asSeconds() > 0.3f) {
        setMoving(false);
        idleTimer.restart();
    }
}

void Player::move(int dx, int dy) {
    // Di chuyển vị trí
    setPosition(getX() + dx, getY() + dy);

    // Xác định hướng và set animation
    if (dx > 0) {
        setDirection(PlayerDirection::RIGHT);
    }
    else if (dx < 0) {
        setDirection(PlayerDirection::LEFT);
    }
    else if (dy > 0) {
        setDirection(PlayerDirection::DOWN);
    }
    else if (dy < 0) {
        setDirection(PlayerDirection::UP);
    }

    setMoving(true);
}

void Player::setDirection(PlayerDirection direction) {
    if (currentDirection == direction && isMoving) return;
    currentDirection = direction;

    std::cout << "Switching to direction: " << static_cast<int>(direction) << std::endl;

    switch (direction) {
    case PlayerDirection::IDLE:
        setAnimation(&idleAnimation);
        break;
    case PlayerDirection::UP:
        setAnimation(&walkUpAnimation);
        break;
    case PlayerDirection::DOWN:
        setAnimation(&walkDownAnimation);
        break;
    case PlayerDirection::LEFT:
        setAnimation(&walkLeftAnimation);
        break;
    case PlayerDirection::RIGHT:
        setAnimation(&walkRightAnimation);
        break;
    default:
        std::cerr << "Unknown direction: " << static_cast<int>(direction) << std::endl;
    }
}

void Player::setMoving(bool moving) {
    isMoving = moving;
    if (!moving) {
        setDirection(PlayerDirection::IDLE);
    }
}

// Thêm method để kiểm tra trạng thái
bool Player::getIsMoving() const {
    return isMoving;
}

PlayerDirection Player::getCurrentDirection() const {
    return currentDirection;
}