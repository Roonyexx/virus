#include "Simulation.h"
#include <iostream>


void Simulation::onValueChange(float value)
{
    std::cout << value << std::endl;
}

Simulation::Simulation(uint32_t numPeople, float infProb, uint32_t infDur)
    : population{ infProb, infDur, sf::Vector2u(1280, 640)}, window { sf::VideoMode{ 1280, 720 }, "Virus", sf::Style::Titlebar | sf::Style::Close }
{
    gui.setWindow(window);
}


void Simulation::run()
{
    initializeUI();
    while (window.isOpen()) 
    {
        handleEvents();
        population.update();
        window.clear({ 30, 30, 30 });
        population.draw(window);
        gui.draw();
        window.display();
    }
}

void Simulation::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        gui.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Simulation::initializeUI()
{
    using namespace tgui;
    auto mainGroup = Group::create();
    mainGroup->setPosition(0, 640);
    mainGroup->setSize(1280, 80);
    

    auto createSliderWithLabel = 
        [](auto onValueChanged, const String& label, const sf::Vector2f position, const float min = 0, const float max = 10, const float startValue = 0.f, const float step = 0.1f) {
        auto subGroup = Group::create();
        subGroup->setPosition(position.x, position.y);

        auto labelWidget = Label::create(label);
        labelWidget->setPosition(0, 0);
        labelWidget->setHorizontalAlignment(HorizontalAlignment::Center);
        labelWidget->setVerticalAlignment(VerticalAlignment::Bottom);
        labelWidget->setTextSize(15);
        labelWidget->getRenderer()->setTextColor(sf::Color::White);
        labelWidget->getRenderer()->setTextStyle(TextStyle::Bold);


        auto slider = EditBoxSlider::create(min, max, startValue, 1, step);
        slider->setPosition(5, 20);
        slider->onValueChange(onValueChanged);

        labelWidget->setSize(slider->getSize().x, 20);

        subGroup->add(labelWidget);
        subGroup->add(slider);

        return subGroup;
    };

    auto test = createSliderWithLabel([this](float value){ this->onValueChange(value); }, "test", { 0, 5 });
    mainGroup->add(test);
    gui.add(mainGroup);
}
