#include "pimpl_example.hpp"
#include "csc/utils/logger.hpp"

/*
     PIMPL (Pointer to IMPLementation)

     - уменьшает compile-time depends
     - скрывает детали реализации
     - стабилизирует ABI
*/

namespace logger = csc::utils::logger;

struct Widget::Impl
{
     std::string name = "PIMPL Demo";
     int counter = 0;

     void work()
     {
          ++counter;
          logger::info( "{} : {}", name, counter );
     }
};

Widget::Widget() : m_( std::make_unique< Impl >() ) {}
Widget::~Widget() = default;
void Widget::do_work() const
{
     m_->work();
}
