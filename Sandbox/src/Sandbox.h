//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_SANDBOX_H
#define FREESIA_SANDBOX_H

#include <Freesia.h>

class Sandbox : public Freesia::Layer
{
public:
    Sandbox();

    void OnAttach() override;
    void OnUpdate(Freesia::TimeStep ts) override;
};

#endif //FREESIA_SANDBOX_H
