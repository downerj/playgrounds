#ifndef PLAYER_HPP
#define PLAYER_HPP

/****************************************************************************
 * 
 ****************************************************************************/
#include <utils/utiltypes.h>

/****************************************************************************
 * 
 ****************************************************************************/
class Velocity {
public:
    // constructors
    Velocity();

    // destructor
    ~Velocity() { /* pass */ }

    // accessors
    float getDx();
    float getDy();

    // mutators
    void setDx(const float dx);
    void setDy(const float dy);
    void addDx(const float ddx);
    void addDy(const float ddy);

private:
    float mDx;
    float mDy;
};

/****************************************************************************
 * 
 ****************************************************************************/
class Player {
public:
    // constructors
    Player();
    Player(uint winWidth, uint winHeight);

    // destructor
    ~Player();

    // accessors
    struct UtilPath2f  & getImage();
    struct UtilPoint2f & getPosition();
    Velocity & getVelocity();
    float      getRotation();
    float      getDirection();
    uint       getColor();

    // mutators
    void setImage(const struct UtilPath2f & image);
    void setPosition(const struct UtilPoint2f & position);
    void setVelocity(const Velocity & velocity);
    void setRotation(const float degrees);
    void setDirection(const float degrees);
    void setColor(const uint color);

    // logic functions
    void update();
    void draw();

private:
    struct UtilPath2f  mImage;
    struct UtilPoint2f mPosition;
    Velocity mVelocity;
    float    mRotation;
    float    mDirection;
    float    mDegreesToRotateImage;
    uint     mColor;
};

#endif // PLAYER_HPP