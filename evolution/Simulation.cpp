#include "Simulation.h"
#include <iostream>



Simulation::Simulation(float mortality, float infProb, uint32_t incTime, uint32_t infDur, uint32_t walkRange, uint32_t hospitalCapacity)
    : population{ sf::Vector2u(1120, 720), walkRange, &hospital }, virus{ mortality, infProb, incTime, infDur }, 
    window{ sf::VideoMode{ 1280, 720 }, "Virus", sf::Style::Titlebar | sf::Style::Close }, walkRange{ walkRange },
    hospital{ hospitalCapacity }
{
    gui.setWindow(window);
}

void Simulation::step()
{
    population.update(virus);
}

void Simulation::reset()
{
    Field newPopulation{ sf::Vector2u(1120, 720), walkRange, &hospital };
    population = newPopulation;
    paused = true;
}


void Simulation::run()
{
    initializeUI();
    while (window.isOpen()) 
    {
        handleEvents();
        if(!paused) population.update(virus);
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

        if (event.type == sf::Event::Closed) 
        {
            window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
                sf::Vector2i pos{ sf::Mouse::getPosition(window) };
                Person* p{ population.findPerson(pos) };
                if (p != nullptr && p->getStatus() == Status::Healthy)
                {
                    p->setStatus(Status::incubationPeriod);
                }
        }
    }
}

void Simulation::initializeUI()
{
    using namespace tgui;
    auto mainGroup = Group::create();
    mainGroup->setPosition(1120, 0);
    mainGroup->setSize(160, 720);
    

    auto createSliderWithLabel = 
        [](auto onValueChanged, const String& label, const sf::Vector2f position, const float min = 0, const float max = 10, const float startValue = 0.f, const float step = 0.1f, const uint32_t decimalPlaces = 0) {
        auto subGroup = Group::create();
        subGroup->setPosition(position.x, position.y);

        auto labelWidget = Label::create(label);
        labelWidget->setPosition(0, 0);
        labelWidget->setHorizontalAlignment(HorizontalAlignment::Center);
        labelWidget->setVerticalAlignment(VerticalAlignment::Bottom);
        labelWidget->setTextSize(10);
        labelWidget->getRenderer()->setTextColor(sf::Color::White);
        labelWidget->getRenderer()->setTextStyle(TextStyle::Bold);


        auto slider = EditBoxSlider::create(min, max, startValue, decimalPlaces, step);
        slider->setValue(startValue);
        slider->setPosition(5, 20);
        slider->onValueChange(onValueChanged);

        labelWidget->setSize(slider->getSize().x, 20);

        subGroup->add(labelWidget);
        subGroup->add(slider);

        return subGroup;
    };

    auto createButton = [](auto battonPressed, const String& label, const sf::Vector2f position) {
        auto button = Button::create(label);
        button->onClick(battonPressed);
        button->setPosition(position.x, position.y);

        button->setSize(45, 40);
        return button;
    };

    auto reset = createButton([this]() { this->reset(); }, "reset", { 7, 10 });
    auto start = createButton([this]() { this->paused = !(this->paused); }, "start", { 57, 10 });
    auto step = createButton([this]() { this->step(); }, "step", { 107, 10 });

    mainGroup->add(reset);
    mainGroup->add(start);
    mainGroup->add(step);

    auto mortality = createSliderWithLabel([virus = &virus](float value){ virus->setMortality(value); }, "mortality", { 0, 50 }, 0, 1, virus.getMortality(), 0.01f, 2);
    auto infProb = createSliderWithLabel([virus = &virus](float value){ virus->setInfectionProbability(value); }, "infection probability", { 0, 100 }, 0, 1, virus.getInfectionProbability(), 0.01f, 2);
    auto incTime = createSliderWithLabel([virus = &virus](float value){ virus->setIncubationTime(round(value)); }, "incubation time", { 0, 150 }, 0, 50, virus.getIncubationTime(), 0);
    auto infDur = createSliderWithLabel([virus = &virus](float value){ virus->setInfectionDuration(round(value)); }, "infection duration", { 0, 200 }, 1, 50, virus.getInfectionDuration(), 0);
    auto walkRange = createSliderWithLabel([this, population = &population](float value){ this->walkRange = round(value); population->setWalkRange(this->walkRange); }, "walk range", { 0, 250 }, 0, 50, this->walkRange, 0);
    auto hospitalCapacity = createSliderWithLabel([hospital = &hospital, population = &population](float value) { 
        hospital->setCapacity(population->percentToPeople(round(value)));
    }, "hospital capacity", { 0, 300 }, 0, 100, 0, 0);

    mainGroup->add(mortality);
    mainGroup->add(infProb);
    mainGroup->add(incTime);
    mainGroup->add(infDur);
    mainGroup->add(walkRange);
    mainGroup->add(hospitalCapacity);
    gui.add(mainGroup);
}
