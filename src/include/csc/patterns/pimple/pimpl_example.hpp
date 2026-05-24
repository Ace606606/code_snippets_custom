#include <memory>

/*
     PIMPL (Pointer to IMPLementation)

     - уменьшает compile-time depends
     - скрывает детали реализации
     - стабилизирует ABI
*/

class Widget
{
public:
     Widget();
     ~Widget();

     void do_work() const;

private:
     struct Impl;
     std::unique_ptr< Impl > m_;
};
