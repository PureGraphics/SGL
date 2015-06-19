#ifndef interface_buffer_h
#define interface_buffer_h

class interface_buffer {
public:
    interface_buffer() {
        _buffer_w = _buffer_h = 0;
    }
    ~interface_buffer() {}
public:
    virtual void set_viewport(int w, int h);
protected:
    int _buffer_w;
    int _buffer_h;
};

#endif