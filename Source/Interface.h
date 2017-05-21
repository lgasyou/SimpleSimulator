#pragma once

#define abstract

class NoCopyable {
public:
    NoCopyable() = default;

    NoCopyable(const NoCopyable &) = delete;

    NoCopyable &operator=(const NoCopyable &) = delete;
};

// Base class of interfaces.
class Interface : public NoCopyable {
public:
    virtual ~Interface() = default;
};

class Object {
public:
    virtual ~Object() = default;
};
