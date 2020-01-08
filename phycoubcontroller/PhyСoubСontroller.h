#ifndef PHYCOUBCONTROLLER_H
#define PHYCOUBCONTROLLER_H

#include <future>

class Phycoubcontroller
{
  public:
    virtual ~Phycoubcontroller() = default;

    virtual void startCalculation();
    virtual void calculateOnce();
    virtual void stopCalculation();

  private:
    bool isCalculating = false;
    std::future< void > calculationThread;
};

#endif // PHYCOUBCONTROLLER_H
