#ifndef DoubleBuffer_h
#define DoubleBuffer_h

#include <CircularBuffer.h>

template<typename T, size_t S> class DoubleBuffer {
    private:
    CircularBuffer<T, S> backBuffer;
    CircularBuffer<T, S> currentBuffer;
    bool swapped = false;
    public:
    DoubleBuffer() { }
    CircularBuffer<T, S> &getBackBuffer() { return swapped ? currentBuffer : backBuffer; }
    CircularBuffer<T, S> &getCurrentBuffer() { return swapped ? backBuffer : currentBuffer; }
    void swapBuffers() { swapped = !swapped; }
};

#endif